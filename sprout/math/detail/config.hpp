#ifndef SPROUT_MATH_DETAIL_CONFIG_HPP
#define SPROUT_MATH_DETAIL_CONFIG_HPP

#include <sprout/config.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <cmath>
#endif

#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	define NS_SPROUT_MATH_DETAIL std
#else	// #ifndef SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	define NS_SPROUT_MATH_DETAIL sprout::math::detail
#endif	// #ifndef SPROUT_USE_BUILTIN_CMATH_FUNCTION

#endif	// #ifndef SPROUT_MATH_DETAIL_CONFIG_HPP
