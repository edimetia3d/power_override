//
// Created by edi on 2/5/21.
//
#include <dlfcn.h>
#include <stdio.h>

#define foo refoo
extern "C"
void foo(int a, int b) {
  printf("overrode [%s] called\n", __func__);
  auto raw_fn = (void (*)(int, int)) dlsym(RTLD_NEXT, "refoo");
  printf("=====call raw_fn start=====\n");
  if (raw_fn) {
    raw_fn(a, b);
  } else {
    printf("Cannot get raw function\n");
  }
  printf("=====call raw_fn end=====\n");
}