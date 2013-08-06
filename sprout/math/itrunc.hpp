#ifndef SPROUT_MATH_ITRUNC_HPP
#define SPROUT_MATH_ITRUNC_HPP

#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <sprout/math/trunc.hpp>
#endif

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			itrunc_impl(FloatType x) {
				return sprout::numeric_limits<To>::max() < x || sprout::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("itrunc: large float rounding."), static_cast<To>(x))
					: static_cast<To>(x)
					;
			}
			template<
				typename To = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			itrunc(FloatType x) {
				return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<To>::min()
					: sprout::math::detail::itrunc_impl<To>(sprout::math::trunc(x))
					;
			}
#else
			template<
				typename To = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			itrunc(FloatType x) {
				return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<To>::min()
					: x == 0 ? To(0)
					: sprout::numeric_limits<To>::max() < x || sprout::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("itrunc: large float rounding."), static_cast<To>(x))
					: static_cast<To>(x)
					;
			}
#endif
			template<
				typename To = int,
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			itrunc(IntType x) {
				return sprout::math::detail::itrunc<To>(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::itrunc;
	}	// namespace math

	using sprout::math::itrunc;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ITRUNC_HPP
