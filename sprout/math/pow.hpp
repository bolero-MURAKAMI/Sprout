#ifndef SPROUT_MATH_POW_HPP
#define SPROUT_MATH_POW_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/utility/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <cmath>
#endif

namespace sprout {
	namespace math {
		namespace detail {
			template<typename X, typename Y, typename Enable = void>
			struct pow_promoted {};
			template<typename X, typename Y>
			struct pow_promoted<
				X,
				Y,
				typename std::enable_if<
					std::is_arithmetic<X>::value && std::is_arithmetic<Y>::value
						&& (std::is_same<X, long double>::value || std::is_same<Y, long double>::value)
				>::type
			> {
			public:
				typedef long double type;
			};
			template<typename X, typename Y>
			struct pow_promoted<
				X,
				Y,
				typename std::enable_if<
					std::is_arithmetic<X>::value && std::is_arithmetic<Y>::value
						&& !(std::is_same<X, long double>::value || std::is_same<Y, long double>::value)
				>::type
			> {
			public:
				typedef double type;
			};
		}	// namespace detail
		//
		// pow_promoted
		//
		template<typename X, typename Y>
		struct pow_promoted
			: public sprout::math::detail::pow_promoted<
				typename std::remove_cv<X>::type,
				typename std::remove_cv<Y>::type
			>
		{};

		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			pow(FloatType x, FloatType y) {
				return sprout::math::detail::exp(y * sprout::math::detail::log(x));
			}

			template<
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::math::pow_promoted<ArithmeticType1, ArithmeticType2>::type
			pow(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::math::pow_promoted<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::pow(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::pow;
#	else
		using sprout::math::detail::pow;
#	endif
	}	// namespace math

	using sprout::math::pow;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_POW_HPP
