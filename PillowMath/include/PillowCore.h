#pragma once

#include <concepts>
#include <type_traits>
#include <cmath>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept Floating = std::is_floating_point_v<T>;