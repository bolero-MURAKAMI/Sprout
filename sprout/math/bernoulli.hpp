/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_BERNOULLI_HPP
#define SPROUT_MATH_BERNOULLI_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#		define SPROUT_BERNOULLI_TABLE_DEF_FLOAT \
			{{ \
				1.F, \
				1.F / 6, \
				-1.F / 30, \
				1.F / 42, \
				-1.F / 30, \
				5.F / 66, \
				-691.F / 2730, \
				7.F / 6, \
				-3617.F / 510, \
				43867.F / 798, \
				-174611.F / 330, \
				854513.F / 138, \
				-236364091.F / 2730, \
				8553103.F / 6, \
				-236364091.F / 870, \
				8615841276005.F / 14322, \
				-7709321041217.F / 510, \
				2577687858367.F / 6, \
				-26315271553053477373.F / 1919190, \
				2929993913841559.F / 6, \
				-261082718496449122051.F / 13530, \
				1520097643918070802691.F / 1806, \
				-2.783326957930102423502e22F / 690, \
				5.96451111593912163278e23F / 282, \
				-1.20866265222965259346e23F, \
				7.500866746076964366856e24F, \
				-5.038778101481068914138e26F, \
				3.65287764848181233351e28F, \
				-2.849876930245088222627e30F, \
				2.386542749968362764465e32F, \
				-2.139994925722533366581e34F, \
				2.050097572347809756992e36F, \
				-2.09380059113463784091e38F \
			}}
#		define SPROUT_BERNOULLI_TABLE_DEF_DOUBLE \
			{{ \
				1., \
				1. / 6, \
				-1. / 30, \
				1. / 42, \
				-1. / 30, \
				5. / 66, \
				-691. / 2730, \
				7. / 6, \
				-3617. / 510, \
				43867. / 798, \
				-174611. / 330, \
				854513. / 138, \
				-236364091. / 2730, \
				8553103. / 6, \
				-236364091. / 870, \
				8615841276005. / 14322, \
				-7709321041217. / 510, \
				2577687858367. / 6, \
				-26315271553053477373. / 1919190, \
				2929993913841559. / 6, \
				-261082718496449122051. / 13530, \
				1520097643918070802691. / 1806, \
				-2.783326957930102423502e22 / 690, \
				5.96451111593912163278e23 / 282, \
				-1.20866265222965259346e23, \
				7.500866746076964366856e24, \
				-5.038778101481068914138e26, \
				3.65287764848181233351e28, \
				-2.849876930245088222627e30, \
				2.386542749968362764465e32, \
				-2.139994925722533366581e34, \
				2.050097572347809756992e36, \
				-2.09380059113463784091e38, \
				2.275269648846351555965e40, \
				-2.62577102862395760473e42, \
				3.21250821027180325182e44, \
				-4.159827816679471091392e46, \
				5.692069548203528002388e48, \
				-8.21836294197845756923e50, \
				1.250290432716699301673e53, \
				-2.001558323324837027493e55, \
				3.36749829153643742334e57, \
				-5.947097050313544771866e59, \
				1.101191032362797755956e62, \
				-2.135525954525350118866e64, \
				4.332889698664119241962e66, \
				-9.18855282416693282262e68, \
				2.034689677632907449346e71, \
				-4.70038339580357310786e73, \
				1.131804344548424927068e76, \
				-2.838224957069370695926e78 \
			}}
#		define SPROUT_BERNOULLI_TABLE_DEF_LONG_DOUBLE \
			{{ \
				1.L, \
				1.L / 6, \
				-1.L / 30, \
				1.L / 42, \
				-1.L / 30, \
				5.L / 66, \
				-691.L / 2730, \
				7.L / 6, \
				-3617.L / 510, \
				43867.L / 798, \
				-174611.L / 330, \
				854513.L / 138, \
				-236364091.L / 2730, \
				8553103.L / 6, \
				-236364091.L / 870, \
				8615841276005.L / 14322, \
				-7709321041217.L / 510, \
				2577687858367.L / 6, \
				-26315271553053477373.L / 1919190, \
				2929993913841559.L / 6, \
				-261082718496449122051.L / 13530, \
				1520097643918070802691.L / 1806, \
				-2.783326957930102423502e22L / 690, \
				5.96451111593912163278e23L / 282, \
				-1.20866265222965259346e23L, \
				7.500866746076964366856e24L, \
				-5.038778101481068914138e26L, \
				3.65287764848181233351e28L, \
				-2.849876930245088222627e30L, \
				2.386542749968362764465e32L, \
				-2.139994925722533366581e34L, \
				2.050097572347809756992e36L, \
				-2.09380059113463784091e38L, \
				2.275269648846351555965e40L, \
				-2.62577102862395760473e42L, \
				3.21250821027180325182e44L, \
				-4.159827816679471091392e46L, \
				5.692069548203528002388e48L, \
				-8.21836294197845756923e50L, \
				1.250290432716699301673e53L, \
				-2.001558323324837027493e55L, \
				3.36749829153643742334e57L, \
				-5.947097050313544771866e59L, \
				1.101191032362797755956e62L, \
				-2.135525954525350118866e64L, \
				4.332889698664119241962e66L, \
				-9.18855282416693282262e68L, \
				2.034689677632907449346e71L, \
				-4.70038339580357310786e73L, \
				1.131804344548424927068e76L, \
				-2.838224957069370695926e78L \
			}}

			template<typename T, typename X = void>
			struct bernoulli_numbers;

			template<typename X>
			struct bernoulli_numbers<float, X> {
			public:
				typedef float type;
			public:
				SPROUT_STATIC_CONSTEXPR std::size_t limit = 64;
			public:
				typedef sprout::array<type, limit / 2 + 1> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_BERNOULLI_TABLE_DEF_FLOAT)
					;
			};
			template<typename X>
			SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::math::detail::bernoulli_numbers<
				float, X
			>::limit;
			template<typename X>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::math::detail::bernoulli_numbers<
				float, X
			>::table_type sprout::math::detail::bernoulli_numbers<
				float, X
			>::table SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_BERNOULLI_TABLE_DEF_FLOAT);

			template<typename X>
			struct bernoulli_numbers<double, X> {
			public:
				typedef double type;
			public:
				SPROUT_STATIC_CONSTEXPR std::size_t limit = 100;
			public:
				typedef sprout::array<type, limit / 2 + 1> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_BERNOULLI_TABLE_DEF_DOUBLE)
					;
			};
			template<typename X>
			SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::math::detail::bernoulli_numbers<
				double, X
			>::limit;
			template<typename X>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::math::detail::bernoulli_numbers<
				double, X
			>::table_type sprout::math::detail::bernoulli_numbers<
				double, X
			>::table SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_BERNOULLI_TABLE_DEF_DOUBLE);

			template<typename X>
			struct bernoulli_numbers<long double, X> {
			public:
				typedef long double type;
			public:
				SPROUT_STATIC_CONSTEXPR std::size_t limit = 100;
			public:
				typedef sprout::array<type, limit / 2 + 1> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_BERNOULLI_TABLE_DEF_LONG_DOUBLE)
					;
			};
			template<typename X>
			SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::math::detail::bernoulli_numbers<
				long double, X
			>::limit;
			template<typename X>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::math::detail::bernoulli_numbers<
				long double, X
			>::table_type sprout::math::detail::bernoulli_numbers<
				long double, X
			>::table SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_BERNOULLI_TABLE_DEF_LONG_DOUBLE);

#		undef SPROUT_BERNOULLI_TABLE_DEF_FLOAT
#		undef SPROUT_BERNOULLI_TABLE_DEF_DOUBLE
#		undef SPROUT_BERNOULLI_TABLE_DEF_LONG_DOUBLE
		}	// namespace detail
		//
		// bernoulli_number_limit
		//
		template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
		inline SPROUT_CONSTEXPR std::size_t bernoulli_number_limit() {
			typedef typename std::remove_cv<T>::type type;
			return sprout::math::detail::bernoulli_numbers<type>::limit;
		}
		//
		// bernoulli_number
		//
		template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
		inline SPROUT_CONSTEXPR T bernoulli_number(std::size_t x) {
			typedef typename std::remove_cv<T>::type type;
			return SPROUT_ASSERT(x <= sprout::math::bernoulli_number_limit<type>()),
				x == 1 ? type(-1) / 2
					: x % 2 ? type(0)
					: sprout::math::detail::bernoulli_numbers<type>::table[x / 2]
				;
		}
	}	// namespace math

	using sprout::math::bernoulli_number;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_BERNOULLI_HPP
