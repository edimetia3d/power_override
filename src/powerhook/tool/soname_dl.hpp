//
// Created by edi on 2/5/21.
//

#ifndef POWERHOOK_SONAME_DL_HPP
#define POWERHOOK_SONAME_DL_HPP

namespace powerhook {
namespace tool {

/**
 * SonameDl will `always` load symbols from a shared object.
 * 1. global symbol will always be ignored
 * 2. this behavior will not be overrode by "dlsym overriding"
 */
struct SonameDl {

  SonameDl(const char *soname, int mode);

  void *dlsym(const char *symbol) const;

  ~SonameDl();
 private:
  void *handle_;
  const char *soname_;
};
}
}
#endif //POWERHOOK_SONAME_DL_HPP
