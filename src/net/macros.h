#pragma once
#include <cstddef>

#define DISALLOW_COPY_AND_ASSIGN(type)  \
    type(const type&) = delete;         \
    type& operator=(const type&) = delete

#define STEP_AND_CHECK_OUT_OF_RANGE(pos, step, end) \
do {                                                \
    pos += step;                                    \
    if (pos > end) {                                \
        return false;                               \
    }                                               \
} while (0)

#define ArraySize(arr) (sizeof(orz::macros_internal::ArraySizeHelper(arr)))

namespace orz
{
namespace macros_internal
{
    template<typename T, size_t N>
    char (&ArraySizeHelper(T (&array)[N]))[N];
}

template<typename To, typename From>
inline To implicit_cast(From const &f) {
    return f;
}

}