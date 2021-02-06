//
// Created by edi on 2/5/21.
//
#include "poweroverride/power_override.hpp"

#include <map>
#include <string>

#include <dlfcn.h>
#include <link.h>

#include "spdlog/spdlog.h"

#include "poweroverride/tool/real_dlsym.hpp"

namespace poweroverride {

template<class T1, class T2>
inline bool has_key(const T1 &container, const T2 &key) {
  return container.find(key) != container.end();
}

using SonameFnMap_t = std::map<void *, void *>;
static std::map<std::string, SonameFnMap_t> &symbol_overrode_fn_map() {
  static std::map<std::string, SonameFnMap_t> map;
  return map;
}

OverrideFuncRegister::OverrideFuncRegister(const char *filename,
                                           const char *func_name,
                                           void *fn_ptr,
                                           const char *src_file,
                                           int src_line) {
  auto handle = dlopen(filename, RTLD_LAZY);
  symbol_overrode_fn_map()[std::string(func_name)][handle] = fn_ptr;
  spdlog::debug("func {}@{} in {}@{} reged at file: {}:{}", func_name, fn_ptr, filename, handle, src_file, src_line);
}
void *DlOpenSym(const char *filename, const char *symbol) {
  auto handle = dlopen(filename, RTLD_LAZY);
  auto ret = real_dlsym(handle, symbol);
  spdlog::debug("{} get real symbol {}@{} in {}@{}", __func__, symbol, ret, filename, handle);
  return ret;
}
}

using poweroverride::symbol_overrode_fn_map;
using poweroverride::has_key;
void *dlsym(void *handle, const char *symbol) {

  if (handle != RTLD_NEXT && handle != RTLD_DEFAULT) {
    auto funcname = std::string(symbol);

    if (has_key(symbol_overrode_fn_map(), funcname)) {
      if (has_key(symbol_overrode_fn_map()[funcname], handle)) {
        auto ret = symbol_overrode_fn_map()[funcname][handle];
        spdlog::debug("{} get symbol {}@{} in {}@{}", __func__, symbol, ret, "unkonwn", handle);
        return ret;
      } else {
        link_map *lmap;
        dlinfo(handle, RTLD_DI_LINKMAP, &lmap);
        spdlog::info("No override for {}@{} found, with {}x\"{}\" registered",
                     lmap->l_name,
                     handle,
                     symbol_overrode_fn_map()[funcname].size(),
                     symbol);
      }
    }
  }

  return poweroverride::real_dlsym(handle, symbol);
}
