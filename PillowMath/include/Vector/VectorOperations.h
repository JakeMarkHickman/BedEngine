#pragma once

#include <type_traits>

#include "Vector3.h"
#include "Vector2.h"

namespace Pillow
{
    //TODO: this is for diffrent vectors eg vector2-3 or vector3-2 need to do symmetry for this

    //VECTOR 2 to VECTOR 3
    template<typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>>>
    inline bool operator==(const Vector3<T>& a, const Vector2<U>& b)
    {
        using CommonType = std::common_type_t<T, U>;

        return static_cast<CommonType>(a.x) == static_cast<CommonType>(b.x) &&
               static_cast<CommonType>(a.y) == static_cast<CommonType>(b.y);
    };
    template<typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>>>
    inline bool operator==(const Vector2<T>& a, const Vector3<U>& b)
    {
        using CommonType = std::common_type_t<T, U>;

        return static_cast<CommonType>(a.x) == static_cast<CommonType>(b.x) &&
               static_cast<CommonType>(a.y) == static_cast<CommonType>(b.y);
    };
}