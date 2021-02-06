//
// Created by edi on 2/5/21.
//
#include "powerhook/power_override.hpp"

#include <map>
#include <string>

#include <dlfcn.h>
#include <cassert>

#include "powerhook/real_dlsym.hpp"

namespace powerhook {

template<class T1, class T2>
inline bool has_key(const T1 &container, const T2 &key) {
  return container.find(key) != container.end();
}

static std::map<std::string, void *> &symbol_overrode_fn_map() {
  static std::map<std::string, void *> map;
  return map;
}

static std::map<std::string, void *> &symbol_handle_map() {
  static std::map<std::string, void *> map;
  return map;
}

OverrideFuncRegister::OverrideFuncRegister(const char *func_name, void *fn_ptr, const char *file, int line) {
  printf("New override [%s] reged from file: %s:%d\n", func_name, file, line);
  symbol_overrode_fn_map()[std::string(func_name)] = fn_ptr;
}
}

using powerhook::symbol_overrode_fn_map;
using powerhook::symbol_handle_map;
using powerhook::has_key;
void *dlsym(void *handle, const char *symbol) {
  if (handle == RTLD_DEFAULT) {
    // RTLD_DEFAULT will be overrode by real_dlsym automatically
    return powerhook::real_dlsym(RTLD_DEFAULT, symbol);
  }

  auto key = std::string(symbol);
  if (handle == RTLD_NEXT) {
    // Looking for "next" from global or some shared object
    // note: if there are multi shared object that providing symbol,this branch will return nullptr
    auto possible = powerhook::real_dlsym(RTLD_NEXT, symbol);
    if (!possible) {
      if (has_key(symbol_handle_map(), key)) {
        possible = powerhook::real_dlsym(symbol_handle_map()[key], symbol);
      }
    }
    return possible;
  }

  assert(handle != RTLD_NEXT && handle != RTLD_DEFAULT); // handle must be a real handle

  // if symbol is a power_overode one, we return the overrode version
  if (has_key(symbol_overrode_fn_map(), key)) {
    if (has_key(symbol_handle_map(), key)) {
      auto old_handle = symbol_handle_map()[key];
      if (old_handle != handle) {
        symbol_handle_map()[key] = nullptr;
      }
    } else {
      symbol_handle_map()[key] = handle;
    }
    return symbol_overrode_fn_map()[key];
  } else {
    return powerhook::real_dlsym(handle, symbol);
  }
  return nullptr;
}
