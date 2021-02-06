
#include <stdio.h>

#include <dlfcn.h>
#include "powerhook/power_override.hpp"

#define foo refoo

POWER_OVERRIDE(void, foo, (int a, int b)) {
  printf("overrode [%s] called\n", __func__);
  auto raw_fn = (RawFn_t) dlsym(RTLD_NEXT, POWERHOOK_STRINGIFY(foo));
  printf("=====call raw_fn start=====\n");
  if (raw_fn) {
    raw_fn(a, b);

  } else {
    printf("Cannot get raw function, you may dlopen/dlsym more than 1 shared lib, you may consider using soname_dl\n");
  }
  printf("=====call raw_fn end=====\n");
}
