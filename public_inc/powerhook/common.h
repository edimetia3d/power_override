//
// Created by edi on 2/5/21.
//

#ifndef POWERHOOK_PUBLIC_INC_POWERHOOK_COMMON_H_
#define POWERHOOK_PUBLIC_INC_POWERHOOK_COMMON_H_

#define _POWERHOOK_STRINGIFY(x) #x
#define POWERHOOK_STRINGIFY(x) _POWERHOOK_STRINGIFY(x)
#define _POWERHOOK_CONCAT(x, y) x##y
#define POWERHOOK_CONCAT(x, y) _POWERHOOK_CONCAT(x,y)

#endif //POWERHOOK_PUBLIC_INC_POWERHOOK_COMMON_H_