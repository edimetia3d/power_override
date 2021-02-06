//
// Created by edi on 2/5/21.
//

#ifndef POWERHOOK_REAL_DLSYM_HPP
#define POWERHOOK_REAL_DLSYM_HPP

namespace powerhook {
/**
* real_dlsym is a `dlsym` which will never be overrode
*/
void *real_dlsym(void *handle, const char *symbol);
}

#endif //POWERHOOK_REAL_DLSYM_HPP
