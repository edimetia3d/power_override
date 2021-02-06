//
// Created by edi on 2/5/21.
//
#include <dlfcn.h>

extern "C" { void *__libc_dlsym(void *map, const char *name); }
extern "C" { void *__libc_dlopen_mode(const char *name, int mode); }
namespace powerhook {
void *real_dlsym(void *handle, const char *symbol) {
  typedef void *(*fnDlsym)(void *, const char *);
  static fnDlsym internal_dlsym = (fnDlsym) __libc_dlsym(__libc_dlopen_mode("libdl.so.2", RTLD_LAZY), "dlsym");
  return (*internal_dlsym)(handle, symbol);
}
}
