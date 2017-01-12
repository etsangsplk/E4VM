#pragma once
//
// Include this header to be able to use Term as a key for e4std::Map
//

#include "e4rt/term.h"
#include "e4std/map.h"

namespace e4std {

template<>
inline bool compare_equal(const e4::Term& a, const e4::Term& b) {
    return a.get_raw() == b.get_raw();
}

template<>
inline bool compare_less(const e4::Term& a, const e4::Term& b) {
    return a.get_raw() < b.get_raw();
}

} // ns e4std
