#ifndef SIMPLECASTING_H
#define SIMPLECASTING_H

#include <cassert>

template <typename To, typename From> inline bool isa(const From *Val) {
    return To::classof(Val);
}

template <typename To, typename From> inline To *cast(From *Val) {
    assert(isa<To>(Val) && "Invalid cast!");
    return static_cast<To *>(Val);
}

template <typename To, typename From> inline To *dyn_cast(From *Val) {
    return isa<To>(Val) ? cast<To>(Val) : nullptr;
}

#endif // SIMPLECASTING_H
