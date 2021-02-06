//
// Created by edi on 2/5/21.
//

#ifndef POWEROVERRIDE_POWER_OVERRIDE_HPP
#define POWEROVERRIDE_POWER_OVERRIDE_HPP

#include "poweroverride/common.h"

namespace poweroverride {
struct OverrideFuncRegister {
  OverrideFuncRegister(const char *filename, const char *func_name, void *fn_ptr, const char *src_file, int src_line);
};

void *DlOpenSym(const char *filename, const char *symbol);
}

/**
 * POWER_OVERRIDE is used to help you override functions that loaded by dlsym
 * filename : same as `filename` in dlopen
 * eg. void foo(int a,int b) -> POWER_OVERRIDE(void,foo,(int a,int b))
 * Note1: POWER_OVERRIDE can only override C style functions
 * NOte2: In func definition, user could use RawFn() to retrive raw function pointer
 */

#define POWER_OVERRIDE(ret_t, funcname, params, filename) \
namespace POWEROVERRIDE_NAMESPACE(funcname) {        \
    ret_t POWEROVERRIDE_CONCAT(impl_,funcname) params;    \
    using RawFn_t = ret_t (*) params;                         \
    RawFn_t RawFn(){                                      \
      static auto ret = poweroverride::DlOpenSym(filename,POWEROVERRIDE_STRINGIFY(funcname)); \
      return (RawFn_t)ret;\
    }                                                      \
    static poweroverride::OverrideFuncRegister POWEROVERRIDE_CONCAT(reg_c_,funcname) (filename,POWEROVERRIDE_STRINGIFY(funcname), reinterpret_cast<void *>(&POWEROVERRIDE_CONCAT(impl_,funcname)),__FILE__,__LINE__); \
}                                               \
ret_t POWEROVERRIDE_NAMESPACE(funcname)::POWEROVERRIDE_CONCAT(impl_,funcname) params

#endif //POWEROVERRIDE_POWER_OVERRIDE_HPP
