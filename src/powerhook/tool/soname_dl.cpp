//
// Created by edi on 2/5/21.
//
#include "powerhook/tool/soname_dl.hpp"

#include <dlfcn.h>

#include "powerhook/real_dlsym.hpp"

namespace powerhook {
namespace tool {

SonameDl::~SonameDl() {
  if (handle_) {
    dlclose(handle_);
  }
}
SonameDl::SonameDl(const char *soname, int mode) {
  soname_ = soname;
  handle_ = dlopen(soname, mode);
}
void *SonameDl::dlsym(const char *symbol) const {
  return real_dlsym(handle_, symbol);
}

}
}