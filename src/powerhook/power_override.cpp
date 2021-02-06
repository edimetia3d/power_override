//
// Created by edi on 2/5/21.
//
#include "powerhook/power_override.hpp"

#include <map>
#include <string>

#include <dlfcn.h>

#include "powerhook/tool/real_dlsym.hpp"

namespace powerhook {

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
  printf("New override [%s] on disk [%s] reged in file: %s:%d\n", func_name, filename, src_file, src_line);
  auto handle = dlopen(filename, RTLD_LAZY);
  symbol_overrode_fn_map()[std::string(func_name)][handle] = fn_ptr;
}
void *DlOpenSym(const char *filename, const char *symbol) {
  auto handle = dlopen(filename, RTLD_LAZY);
  auto ret = real_dlsym(handle, symbol);
  return ret;
}
}

using powerhook::symbol_overrode_fn_map;
using powerhook::has_key;
void *dlsym(void *handle, const char *symbol) {

  if (handle != RTLD_NEXT && handle != RTLD_DEFAULT) {
    auto funcname = std::string(symbol);

    if (has_key(symbol_overrode_fn_map(), funcname)) {
      if (has_key(symbol_overrode_fn_map()[funcname], handle)) {
        return symbol_overrode_fn_map()[funcname][handle];
      }
    }

  }

  return powerhook::real_dlsym(handle, symbol);
}
