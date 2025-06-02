#pragma once

#include "../PillowCore.h"

namespace Pillow
{
    template<Arithmetic T>
    struct Vector4
    {
        Vector4() : x(T{0}), y(T{0}), z(T{0}), w(T{0}) {};
        Vector4(T value) : x(value), y(value), z(value), w(value) {};
        Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
        Vector4(const Vector4& value) : x(value.x), y(value.y), z(value.z), w(value.w) {};

        T x;
        T y;
        T z;
        T w;

        // ==
        template<Arithmetic U>
        bool operator==(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) == static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) == static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) == static_cast<CommonType>(other.z) &&
                   static_cast<CommonType>(w) == static_cast<CommonType>(other.w); 
        };
        template<Arithmetic U>
        bool operator==(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) == static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) == static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) == static_cast<CommonType>(scalar) &&
                   static_cast<CommonType>(w) == static_cast<CommonType>(scalar); 
        };

        // !=
        template<Arithmetic U>
        bool operator!=(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) != static_cast<CommonType>(other.x) || 
                   static_cast<CommonType>(y) != static_cast<CommonType>(other.y) || 
                   static_cast<CommonType>(z) != static_cast<CommonType>(other.z) ||
                   static_cast<CommonType>(w) != static_cast<CommonType>(other.w); 
        };
        template<Arithmetic U>
        bool operator!=(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) != static_cast<CommonType>(scalar) || 
                   static_cast<CommonType>(y) != static_cast<CommonType>(scalar) || 
                   static_cast<CommonType>(z) != static_cast<CommonType>(scalar) ||
                   static_cast<CommonType>(w) != static_cast<CommonType>(scalar); 
        };

        // >
        template<Arithmetic U>
        bool operator>(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) > static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) > static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) > static_cast<CommonType>(other.z) &&
                   static_cast<CommonType>(w) > static_cast<CommonType>(other.w); 
        };
        template<Arithmetic U>
        bool operator>(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) > static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) > static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) > static_cast<CommonType>(scalar) &&
                   static_cast<CommonType>(w) > static_cast<CommonType>(scalar); 
        };

        // <
        template<Arithmetic U>
        bool operator<(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) < static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) < static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) < static_cast<CommonType>(other.z) &&
                   static_cast<CommonType>(w) < static_cast<CommonType>(other.w); 
        };
        template<Arithmetic U>
        bool operator<(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) < static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) < static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) < static_cast<CommonType>(scalar) &&
                   static_cast<CommonType>(w) < static_cast<CommonType>(scalar); 
        };

        // >=
        template<Arithmetic U>
        bool operator>=(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) >= static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) >= static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) >= static_cast<CommonType>(other.z) &&
                   static_cast<CommonType>(w) >= static_cast<CommonType>(other.w); 
        };
        template<Arithmetic U>
        bool operator>=(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) >= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) >= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) >= static_cast<CommonType>(scalar) &&
                   static_cast<CommonType>(w) >= static_cast<CommonType>(scalar); 
        };

        // <=
        template<Arithmetic U>
        bool operator<=(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) <= static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) <= static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) <= static_cast<CommonType>(other.z) &&
                   static_cast<CommonType>(w) <= static_cast<CommonType>(other.w); 
        };
        template<Arithmetic U>
        bool operator<=(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) <= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) <= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) <= static_cast<CommonType>(scalar) &&
                   static_cast<CommonType>(w) <= static_cast<CommonType>(scalar); 
        };

        // *=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector4<T>& operator*=(const Vector4<U>& other)
        { 
            x *= static_cast<T>(other.x);
            y *= static_cast<T>(other.y);
            z *= static_cast<T>(other.z);
            w *= static_cast<T>(other.w);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector4<T>& operator*=(const U& scalar)
        { 
            x *= static_cast<T>(scalar);
            y *= static_cast<T>(scalar);
            z *= static_cast<T>(scalar);
            w *= static_cast<T>(scalar);

            return *this;
        };

        // /=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector4<T>& operator/=(const Vector4<U>& other)
        { 
            x /= static_cast<T>(other.x);
            y /= static_cast<T>(other.y);
            z /= static_cast<T>(other.z);
            w /= static_cast<T>(other.w);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector4<T>& operator/=(const U& scalar)
        { 
            x /= static_cast<T>(scalar);
            y /= static_cast<T>(scalar);
            z /= static_cast<T>(scalar);
            w /= static_cast<T>(scalar);

            return *this;
        };

        // +=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector4<T>& operator+=(const Vector4<U>& other)
        { 
            x += static_cast<T>(other.x);
            y += static_cast<T>(other.y);
            z += static_cast<T>(other.z);
            w += static_cast<T>(other.w);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector4<T>& operator+=(const U& scalar)
        { 
            x += static_cast<T>(scalar);
            y += static_cast<T>(scalar);
            z += static_cast<T>(scalar);
            w += static_cast<T>(scalar);

            return *this;
        };

        // -=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector4<T>& operator-=(const Vector4<U>& other)
        { 
            x -= static_cast<T>(other.x);
            y -= static_cast<T>(other.y);
            z -= static_cast<T>(other.z);
            w -= static_cast<T>(other.w);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector4<T>& operator-=(const U& scalar)
        { 
            x -= static_cast<T>(scalar);
            y -= static_cast<T>(scalar);
            z -= static_cast<T>(scalar);
            w -= static_cast<T>(scalar);

            return *this;
        };

        // *
        template<Arithmetic U>
        Vector4<std::common_type_t<T, U>> operator*(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector4<CommonType>(static_cast<CommonType>(x) * static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) * static_cast<CommonType>(other.y),
                                       static_cast<CommonType>(z) * static_cast<CommonType>(other.z),
                                       static_cast<CommonType>(w) * static_cast<CommonType>(other.w));
        };
        template<Arithmetic U>
        Vector4<std::common_type_t<T, U>> operator*(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector4<CommonType>(static_cast<CommonType>(x) * static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) * static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(z) * static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(w) * static_cast<CommonType>(scalar));
        };

        // /
        template<Arithmetic U>
        Vector4<std::common_type_t<T, U>> operator/(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector4<CommonType>(static_cast<CommonType>(x) / static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) / static_cast<CommonType>(other.y),
                                       static_cast<CommonType>(z) / static_cast<CommonType>(other.z),
                                       static_cast<CommonType>(w) / static_cast<CommonType>(other.w));
        };
        template<Arithmetic U>
        Vector4<std::common_type_t<T, U>> operator/(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector4<CommonType>(static_cast<CommonType>(x) / static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) / static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(z) / static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(w) / static_cast<CommonType>(scalar));
        };

        // +
        template<Arithmetic U>
        Vector4<std::common_type_t<T, U>> operator+(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector4<CommonType>(static_cast<CommonType>(x) + static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) + static_cast<CommonType>(other.y),
                                       static_cast<CommonType>(z) + static_cast<CommonType>(other.z),
                                       static_cast<CommonType>(w) + static_cast<CommonType>(other.w));
        };
        template<Arithmetic U>
        Vector4<std::common_type_t<T, U>> operator+(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector4<CommonType>(static_cast<CommonType>(x) + static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) + static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(z) + static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(w) + static_cast<CommonType>(scalar));
        };

        // -
        template<Arithmetic U>
        Vector4<std::common_type_t<T, U>> operator-(const Vector4<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector4<CommonType>(static_cast<CommonType>(x) - static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) - static_cast<CommonType>(other.y),
                                       static_cast<CommonType>(z) - static_cast<CommonType>(other.z),
                                       static_cast<CommonType>(w) - static_cast<CommonType>(other.w));
        };
        template<Arithmetic U>
        Vector4<std::common_type_t<T, U>> operator-(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector4<CommonType>(static_cast<CommonType>(x) - static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) - static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(z) - static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(w) - static_cast<CommonType>(scalar));
        };
    };

    using Vector4f = Vector4<float>;
    using Vector4i = Vector4<int>;
    using Vector4d = Vector4<double>;
}