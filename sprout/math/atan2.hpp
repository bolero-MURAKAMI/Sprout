#ifndef SPROUT_MATH_ATAN2_HPP
#define SPROUT_MATH_ATAN2_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/atan.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/utility/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <cmath>
#endif

namespace sprout {
	namespace math {
		namespace detail {
			template<typename Y, typename X, typename Enable = void>
			struct atan2_promoted {};
			template<typename Y, typename X>
			struct atan2_promoted<
				Y,
				X,
				typename std::enable_if<
					std::is_arithmetic<Y>::value && std::is_arithmetic<X>::value
						&& (std::is_same<Y, long double>::value || std::is_same<X, long double>::value)
				>::type
			> {
			public:
				typedef long double type;
			};
			template<typename Y, typename X>
			struct atan2_promoted<
				Y,
				X,
				typename std::enable_if<
					std::is_arithmetic<Y>::value && std::is_arithmetic<X>::value
						&& !(std::is_same<Y, long double>::value || std::is_same<X, long double>::value)
				>::type
			> {
			public:
				typedef double type;
			};
		}	// namespace detail
		//
		// atan2_promoted
		//
		template<typename Y, typename X>
		struct atan2_promoted
			: public sprout::math::detail::atan2_promoted<
				typename std::remove_cv<Y>::type,
				typename std::remove_cv<X>::type
			>
		{};

		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			atan2(FloatType y, FloatType x) {
				return x < 0
					? sprout::math::detail::atan(y / x) + (y < 0 ? -1 : 1) * sprout::math::pi<FloatType>()
					: sprout::math::detail::atan(y / x)
					;
			}

			template<
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::math::atan2_promoted<ArithmeticType1, ArithmeticType2>::type
			atan2(ArithmeticType1 y, ArithmeticType2 x) {
				typedef typename sprout::math::atan2_promoted<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::atan2(static_cast<type>(y), static_cast<type>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::atan2;
#	else
		using sprout::math::detail::atan2;
#	endif
	}	// namespace math

	using sprout::math::atan2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ATAN2_HPP
