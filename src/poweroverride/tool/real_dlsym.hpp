//
// Created by edi on 2/5/21.
//

#ifndef POWEROVERRIDE_REAL_DLSYM_HPP
#define POWEROVERRIDE_REAL_DLSYM_HPP

namespace poweroverride {
/**
* real_dlsym is a `dlsym` which will never be overrode
*/
void *real_dlsym(void *handle, const char *symbol);
}

#endif //POWEROVERRIDE_REAL_DLSYM_HPP
