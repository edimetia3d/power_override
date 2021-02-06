
#include <stdio.h>

#include <dlfcn.h>
#include "powerhook/power_override.hpp"

#define foo refoo

static void base_foo(int a, int b, void *raw_fn_in) {
  using Fn_t = void (*)(int, int);
  auto raw_fn = (Fn_t) (raw_fn_in);
  printf("overrode [%s] called\n", __func__);
  printf("=====call raw_fn start=====\n");
  if (raw_fn) {
    raw_fn(a, b);
  } else {
    printf("Cannot get raw function, you may dlopen/dlsym more than 1 shared lib, you may consider using soname_dl\n");
  }
  printf("=====call raw_fn end=====\n");
}

extern "C" {
void foo(int a, int b) {
  auto raw = dlsym(RTLD_NEXT, "refoo");
  return base_foo(a, b, raw);
}
}

POWER_OVERRIDE(void, foo, (int a, int b), "./libfoo.so") {
  base_foo(a, b, RawFn());
}
