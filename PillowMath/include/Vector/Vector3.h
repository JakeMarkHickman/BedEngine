#pragma once

#include "../PillowCore.h"

namespace Pillow
{
    template<Arithmetic T>
    struct Vector3
    {
        Vector3() : x(T{0}), y(T{0}), z(T{0}) {};
        Vector3(T value) : x(value), y(value), z(value) {};
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {};
        Vector3(const Vector3& value) : x(value.x), y(value.y), z(value.z) {};

        T x;
        T y;
        T z;

        // ==
        template<Arithmetic U>
        bool operator==(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) == static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) == static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) == static_cast<CommonType>(other.z); 
        };
        template<Arithmetic U>
        bool operator==(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) == static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) == static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) == static_cast<CommonType>(scalar); 
        };

        // !=
        template<Arithmetic U>
        bool operator!=(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) != static_cast<CommonType>(other.x) || 
                   static_cast<CommonType>(y) != static_cast<CommonType>(other.y) || 
                   static_cast<CommonType>(z) != static_cast<CommonType>(other.z); 
        };
        template<Arithmetic U>
        bool operator!=(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) != static_cast<CommonType>(scalar) || 
                   static_cast<CommonType>(y) != static_cast<CommonType>(scalar) || 
                   static_cast<CommonType>(z) != static_cast<CommonType>(scalar); 
        };

        // >
        template<Arithmetic U>
        bool operator>(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) > static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) > static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) > static_cast<CommonType>(other.z); 
        };
        template<Arithmetic U>
        bool operator>(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) > static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) > static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) > static_cast<CommonType>(scalar); 
        };

        // <
        template<Arithmetic U>
        bool operator<(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) < static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) < static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) < static_cast<CommonType>(other.z); 
        };
        template<Arithmetic U>
        bool operator<(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) < static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) < static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) < static_cast<CommonType>(scalar); 
        };

        // >=
        template<Arithmetic U>
        bool operator>=(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) >= static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) >= static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) >= static_cast<CommonType>(other.z); 
        };
        template<Arithmetic U>
        bool operator>=(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) >= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) >= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) >= static_cast<CommonType>(scalar); 
        };

        // <=
        template<Arithmetic U>
        bool operator<=(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) <= static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) <= static_cast<CommonType>(other.y) && 
                   static_cast<CommonType>(z) <= static_cast<CommonType>(other.z); 
        };
        template<Arithmetic U>
        bool operator<=(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) <= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) <= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(z) <= static_cast<CommonType>(scalar); 
        };

        // *=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector3<T>& operator*=(const Vector3<U>& other)
        { 
            x *= static_cast<T>(other.x);
            y *= static_cast<T>(other.y);
            z *= static_cast<T>(other.z);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector3<T>& operator*=(const U& scalar)
        { 
            x *= static_cast<T>(scalar);
            y *= static_cast<T>(scalar);
            z *= static_cast<T>(scalar);

            return *this;
        };

        // /=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector3<T>& operator/=(const Vector3<U>& other)
        { 
            x /= static_cast<T>(other.x);
            y /= static_cast<T>(other.y);
            z /= static_cast<T>(other.z);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector3<T>& operator/=(const U& scalar)
        { 
            x /= static_cast<T>(scalar);
            y /= static_cast<T>(scalar);
            z /= static_cast<T>(scalar);

            return *this;
        };

        // +=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector3<T>& operator+=(const Vector3<U>& other)
        { 
            x += static_cast<T>(other.x);
            y += static_cast<T>(other.y);
            z += static_cast<T>(other.z);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector3<T>& operator+=(const U& scalar)
        { 
            x += static_cast<T>(scalar);
            y += static_cast<T>(scalar);
            z += static_cast<T>(scalar);

            return *this;
        };

        // -=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector3<T>& operator-=(const Vector3<U>& other)
        { 
            x -= static_cast<T>(other.x);
            y -= static_cast<T>(other.y);
            z -= static_cast<T>(other.z);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector3<T>& operator-=(const U& scalar)
        { 
            x -= static_cast<T>(scalar);
            y -= static_cast<T>(scalar);
            z -= static_cast<T>(scalar);

            return *this;
        };

        // *
        template<Arithmetic U>
        Vector3<std::common_type_t<T, U>> operator*(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector3<CommonType>(static_cast<CommonType>(x) * static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) * static_cast<CommonType>(other.y),
                                       static_cast<CommonType>(z) * static_cast<CommonType>(other.z));
        };
        template<Arithmetic U>
        Vector3<std::common_type_t<T, U>> operator*(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector3<CommonType>(static_cast<CommonType>(x) * static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) * static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(z) * static_cast<CommonType>(scalar));
        };

        // /
        template<Arithmetic U>
        Vector3<std::common_type_t<T, U>> operator/(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector3<CommonType>(static_cast<CommonType>(x) / static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) / static_cast<CommonType>(other.y),
                                       static_cast<CommonType>(z) / static_cast<CommonType>(other.z));
        };
        template<Arithmetic U>
        Vector3<std::common_type_t<T, U>> operator/(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector3<CommonType>(static_cast<CommonType>(x) / static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) / static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(z) / static_cast<CommonType>(scalar));
        };

        // +
        template<Arithmetic U>
        Vector3<std::common_type_t<T, U>> operator+(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector3<CommonType>(static_cast<CommonType>(x) + static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) + static_cast<CommonType>(other.y),
                                       static_cast<CommonType>(z) + static_cast<CommonType>(other.z));
        };
        template<Arithmetic U>
        Vector3<std::common_type_t<T, U>> operator+(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector3<CommonType>(static_cast<CommonType>(x) + static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) + static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(z) + static_cast<CommonType>(scalar));
        };

        // -
        template<Arithmetic U>
        Vector3<std::common_type_t<T, U>> operator-(const Vector3<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector3<CommonType>(static_cast<CommonType>(x) - static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) - static_cast<CommonType>(other.y),
                                       static_cast<CommonType>(z) - static_cast<CommonType>(other.z));
        };
        template<Arithmetic U>
        Vector3<std::common_type_t<T, U>> operator-(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector3<CommonType>(static_cast<CommonType>(x) - static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) - static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(z) - static_cast<CommonType>(scalar));
        };
    };

    //Creates a 3 float Vector
    using Vector3f = Vector3<float>;
    //Creates a 3 integer Vector
    using Vector3i = Vector3<int>;
    //Creates a 3 double Vector
    using Vector3d = Vector3<double>;
}