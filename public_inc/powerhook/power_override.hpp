//
// Created by edi on 2/5/21.
//

#ifndef POWERHOOK_POWER_OVERRIDE_HPP
#define POWERHOOK_POWER_OVERRIDE_HPP

#include "powerhook/common.h"

namespace powerhook {
struct OverrideFuncRegister {
  OverrideFuncRegister(const char *func_name, void *fn_ptr, const char *file, int line);
};
}

/**
 * POWER_OVERRIDE is used to define a function to override other by LD_PRELOAD
 * the arg is just a split of normal function declaration.
 * eg. void foo(int a,int b) -> POWER_OVERRIDE(void,foo,(int a,int b))
 * Note1: POWER_OVERRIDE only works for C style functions ( func name will not be mangled)
 * NOte2: In func defination, user could use `RawFn_t` to refer the function pointer type
 */
#define POWER_OVERRIDE(ret_t, funcname, params) \
namespace POWERHOOK_CONCAT(_private_c_,funcname) { \
    extern "C" {ret_t funcname params;}    \
    using RawFn_t = ret_t (*)params;    \
    static powerhook::OverrideFuncRegister POWERHOOK_CONCAT(reg_c_,funcname) (POWERHOOK_STRINGIFY(funcname), reinterpret_cast<void *>(funcname),__FILE__,__LINE__); \
}                                               \
ret_t POWERHOOK_CONCAT(_private_c_,funcname)::funcname params

#endif //POWERHOOK_POWER_OVERRIDE_HPP
