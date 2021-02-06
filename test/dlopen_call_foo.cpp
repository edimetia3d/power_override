//
// Created by edi on 2/5/21.
//
#include <dlfcn.h>

#include "foo.h"

#define _STRINGFY(x) #x
#define STRINGFY(x) _STRINGFY(x)
int main() {
  auto handle = dlopen("./libfoo.so", RTLD_LAZY | RTLD_LOCAL);
  using foo_t = void (*)(int, int);
  auto fn = (foo_t) dlsym(handle, STRINGFY(foo));
  fn(0, 1);
}