//
// Created by edi on 2/5/21.
//

#ifndef POWERHOOK_POWER_OVERRIDE_HPP
#define POWERHOOK_POWER_OVERRIDE_HPP

#include "powerhook/common.h"

namespace powerhook {
struct OverrideFuncRegister {
  OverrideFuncRegister(const char *filename, const char *func_name, void *fn_ptr, const char *src_file, int src_line);
};

void *DlOpenSym(const char *filename, const char *symbol);
}

/**
 * POWER_OVERRIDE is used to define a function to override function in specific lib by LD_PRELOAD
 * filename : same as `filename` in dlopen
 * eg. void foo(int a,int b) -> POWER_OVERRIDE(void,foo,(int a,int b))
 * Note1: POWER_OVERRIDE can only override C style functions
 * NOte2: In func definition, user could use RawFn() to retrive raw function pointer
 */

#define POWER_OVERRIDE(ret_t, funcname, params, filename) \
namespace POWERHOOK_NAMESPACE(funcname) {        \
    ret_t POWERHOOK_CONCAT(impl_,funcname) params;        \
    void * RawFn(){                                      \
      static auto ret = powerhook::DlOpenSym(filename,POWERHOOK_STRINGIFY(funcname)); \
      return ret;\
    }                                                      \
    static powerhook::OverrideFuncRegister POWERHOOK_CONCAT(reg_c_,funcname) (filename,POWERHOOK_STRINGIFY(funcname), reinterpret_cast<void *>(&POWERHOOK_CONCAT(impl_,funcname)),__FILE__,__LINE__); \
}                                               \
ret_t POWERHOOK_NAMESPACE(funcname)::POWERHOOK_CONCAT(impl_,funcname) params

#endif //POWERHOOK_POWER_OVERRIDE_HPP
