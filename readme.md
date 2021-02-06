# PowerOverride

PowerOverride is a lib to help you override symbols that loaded by dlsym

Just compile to a shared lib, and use LD_PRELOAD.

# Quick Start

1. Only override functions loaded by `dlsym` in `libfoo.so`. Just define a function by using POWER_OVERRIDE

```cpp
#include
"poweroverride/power_override.hpp"

POWER_OVERRIDE(void, foo, (int a, int b), "libfoo.so") { // the filename rule is same as `dlopen`
auto raw = RawFn();
do_sth();
}
```

2. If `libfoo.so` is also linked by some part of your code, you may want to add a normal function to override these
   linked symbol. Because PowerOverride will not override symbols that are resloved by dynamic linker.

```cpp
extern "C"{
void foo(int a, int b){
auto raw = dlsym(RTLD_NEXT, "foo");
do_sth();
}
}
```

3. If you dlopend many lib that contains same symbol, e.g. `color()` in `libapple.so` and `liborange.so`
   You may want to add more POWER_OVERRIDE, to override other libs. because POWER_OVERRIDE only override one shared obj.

 ```cpp
#include
"poweroverride/power_override.hpp"

POWER_OVERRIDE(void, foo, (int a, int b), "libbar.so") {
auto raw = RawFn(); // Note, this RawFn() will return raw function pointer from "libbar.so" , not "libfoo.so"
do_sth();
}
```  

4. All override are under your control. If you want to share some code, you could abstract a `do_sth()` just like
   previous example. If Not, just implement function as you want.

