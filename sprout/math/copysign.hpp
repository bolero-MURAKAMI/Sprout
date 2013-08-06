#ifndef SPROUT_MATH_COPYSIGN_HPP
#define SPROUT_MATH_COPYSIGN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			copysign(FloatType x, FloatType y) {
				return x == 0
						? y == 0 ? y
							: sprout::math::signbit(y) ? -FloatType(0)
							: FloatType(0)
					: sprout::math::isnan(x)
						? sprout::math::isnan(y) ? y
							: sprout::math::signbit(y) ? -sprout::numeric_limits<FloatType>::quiet_NaN()
							: sprout::numeric_limits<FloatType>::quiet_NaN()
					: sprout::math::signbit(y) != sprout::math::signbit(x) ? -x
					: x
					;
			}
			template<
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
			copysign(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::copysign(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail
		//
		// issue:
		//	[ !SPROUT_USE_BUILTIN_CMATH_FUNCTION ]
		//	copysign(Å}x, -0) returns -x for |x| is not 0 .
		//		# returns +x . ( same as copysign(Å}x, +0) )
		//	copysign(Å}x, -NaN) returns -x for |x| is not NaN .
		//		# returns +x . ( same as copysign(Å}x, +NaN) )
		//
		using NS_SPROUT_MATH_DETAIL::copysign;
	}	// namespace math

	using sprout::math::copysign;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COPYSIGN_HPP
