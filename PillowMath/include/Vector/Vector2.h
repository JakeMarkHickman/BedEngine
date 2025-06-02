#pragma once

#include "../PillowCore.h"

namespace Pillow
{
    template<Arithmetic T>
    struct Vector2
    {
        Vector2() : x(T{0}), y(T{0}) {};
        Vector2(T value) : x(value), y(value) {};
        Vector2(T x, T y) : x(x), y(y) {};
        Vector2(const Vector2& value) : x(value.x), y(value.y) {};

        T x;
        T y;
        
        // ==
        template<Arithmetic U>
        bool operator==(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) == static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) == static_cast<CommonType>(other.y);
        };
        template<Arithmetic U>
        bool operator==(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) == static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) == static_cast<CommonType>(scalar); 
        };

        // !=
        template<Arithmetic U>
        bool operator!=(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) != static_cast<CommonType>(other.x) || 
                   static_cast<CommonType>(y) != static_cast<CommonType>(other.y); 
        };
        template<Arithmetic U>
        bool operator!=(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) != static_cast<CommonType>(scalar) || 
                   static_cast<CommonType>(y) != static_cast<CommonType>(scalar); 
        };

        // >
        template<Arithmetic U>
        bool operator>(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) > static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) > static_cast<CommonType>(other.y); 
        };
        template<Arithmetic U>
        bool operator>(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) > static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) > static_cast<CommonType>(scalar); 
        };

        // <
        template<Arithmetic U>
        bool operator<(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) < static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) < static_cast<CommonType>(other.y); 
        };
        template<Arithmetic U>
        bool operator<(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) < static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) < static_cast<CommonType>(scalar); 
        };

        // >=
        template<Arithmetic U>
        bool operator>=(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) >= static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) >= static_cast<CommonType>(other.y); 
        };
        template<Arithmetic U>
        bool operator>=(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) >= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) >= static_cast<CommonType>(scalar); 
        };

        // <=
        template<Arithmetic U>
        bool operator<=(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) <= static_cast<CommonType>(other.x) && 
                   static_cast<CommonType>(y) <= static_cast<CommonType>(other.y); 
        };
        template<Arithmetic U>
        bool operator<=(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return static_cast<CommonType>(x) <= static_cast<CommonType>(scalar) && 
                   static_cast<CommonType>(y) <= static_cast<CommonType>(scalar); 
        };

        // *=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector2<T>& operator*=(const Vector2<U>& other)
        { 
            x *= static_cast<T>(other.x);
            y *= static_cast<T>(other.y);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector2<T>& operator*=(const U& scalar)
        { 
            x *= static_cast<T>(scalar);
            y *= static_cast<T>(scalar);

            return *this;
        };

        // /=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector2<T>& operator/=(const Vector2<U>& other)
        { 
            x /= static_cast<T>(other.x);
            y /= static_cast<T>(other.y);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector2<T>& operator/=(const U& scalar)
        { 
            x /= static_cast<T>(scalar);
            y /= static_cast<T>(scalar);

            return *this;
        };

        // +=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector2<T>& operator+=(const Vector2<U>& other)
        { 
            x += static_cast<T>(other.x);
            y += static_cast<T>(other.y);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector2<T>& operator+=(const U& scalar)
        { 
            x += static_cast<T>(scalar);
            y += static_cast<T>(scalar);

            return *this;
        };

        // -=
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector2<T>& operator-=(const Vector2<U>& other)
        { 
            x -= static_cast<T>(other.x);
            y -= static_cast<T>(other.y);

            return *this;
        };
        template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U> && std::is_convertible_v<U, T>>>
        Vector2<T>& operator-=(const U& scalar)
        { 
            x -= static_cast<T>(scalar);
            y -= static_cast<T>(scalar);

            return *this;
        };

        // *
        template<Arithmetic U>
        Vector2<std::common_type_t<T, U>> operator*(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector2<CommonType>(static_cast<CommonType>(x) * static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) * static_cast<CommonType>(other.y));
        };
        template<Arithmetic U>
        Vector2<std::common_type_t<T, U>> operator*(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector2<CommonType>(static_cast<CommonType>(x) * static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) * static_cast<CommonType>(scalar));
        };

        // /
        template<Arithmetic U>
        Vector2<std::common_type_t<T, U>> operator/(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector2<CommonType>(static_cast<CommonType>(x) / static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) / static_cast<CommonType>(other.y));
        };
        template<Arithmetic U>
        Vector2<std::common_type_t<T, U>> operator/(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector2<CommonType>(static_cast<CommonType>(x) / static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) / static_cast<CommonType>(scalar));
        };

        // +
        template<Arithmetic U>
        Vector2<std::common_type_t<T, U>> operator+(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector2<CommonType>(static_cast<CommonType>(x) + static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) + static_cast<CommonType>(other.y));
        };
        template<Arithmetic U>
        Vector2<std::common_type_t<T, U>> operator+(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector2<CommonType>(static_cast<CommonType>(x) + static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) + static_cast<CommonType>(scalar));
        };

        // -
        template<Arithmetic U>
        Vector2<std::common_type_t<T, U>> operator-(const Vector2<U>& other) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector2<CommonType>(static_cast<CommonType>(x) - static_cast<CommonType>(other.x),
                                       static_cast<CommonType>(y) - static_cast<CommonType>(other.y));
        };
        template<Arithmetic U>
        Vector2<std::common_type_t<T, U>> operator-(const U& scalar) const 
        { 
            using CommonType = std::common_type_t<T, U>;
            return Vector2<CommonType>(static_cast<CommonType>(x) - static_cast<CommonType>(scalar),
                                       static_cast<CommonType>(y) - static_cast<CommonType>(scalar));
        };
    };

    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;
    using Vector2d = Vector2<double>;
}