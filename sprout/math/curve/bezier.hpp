/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_CURVE_BEZIER_HPP
#define SPROUT_MATH_CURVE_BEZIER_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/tuple/tuple/make_tuple.hpp>
#include <sprout/math/curve/curve_point.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename Points, typename T, std::size_t N = sprout::tuple_size<Points>::value - 1>
			class bezier_impl;
			template<typename Points, typename T>
			class bezier_impl<Points, T, 2> {
			public:
				static SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
				call(Points const& p, T const& t) {
					using sprout::tuples::nested_get;
					using sprout::detail::pow2;
					return sprout::math::curve_point_traits<Points>::make(
						pow2(1 - t) * nested_get<0, 0>(p)
							+ 2 * t * (1 - t) * nested_get<1, 0>(p)
							+ pow2(t) * nested_get<2, 0>(p)
							,
						pow2(1 - t) * nested_get<0, 1>(p)
							+ 2 * t * (1 - t) * nested_get<1, 1>(p)
							+ pow2(t) * nested_get<2, 1>(p)
						);
				}
			};
			template<typename Points, typename T>
			class bezier_impl<Points, T, 3> {
			public:
				static SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
				call(Points const& p, T const& t) {
					using sprout::tuples::nested_get;
					using sprout::detail::pow2;
					using sprout::detail::pow3;
					return sprout::math::curve_point_traits<Points>::make(
						pow3(1 - t) * nested_get<0, 0>(p)
							+ 3 * t * pow2(1 - t) * nested_get<1, 0>(p)
							+ 3 * pow2(t) * (1 - t) * nested_get<2, 0>(p)
							+ pow3(t) * nested_get<3, 0>(p)
							,
						pow3(1 - t) * nested_get<0, 1>(p)
							+ 3 * t * pow2(1 - t) * nested_get<1, 1>(p)
							+ 3 * pow2(t) * (1 - t) * nested_get<2, 1>(p)
							+ pow3(t) * nested_get<3, 1>(p)
						);
				}
			};
			template<typename Points, typename T>
			class bezier_impl<Points, T, 4> {
			public:
				static SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
				call(Points const& p, T const& t) {
					using sprout::tuples::nested_get;
					using sprout::detail::pow2;
					using sprout::detail::pow3;
					using sprout::detail::pow4;
					return sprout::math::curve_point_traits<Points>::make(
						pow4(1 - t) * nested_get<0, 0>(p)
							+ 4 * t * pow3(1 - t) * nested_get<1, 0>(p)
							+ 6 * pow2(t) * pow2(1 - t) * nested_get<2, 0>(p)
							+ 4 * pow3(t) * (1 - t) * nested_get<3, 0>(p)
							+ pow4(t) * nested_get<4, 0>(p)
							,
						pow4(1 - t) * nested_get<0, 1>(p)
							+ 4 * t * pow3(1 - t) * nested_get<1, 1>(p)
							+ 6 * pow2(t) * pow2(1 - t) * nested_get<2, 1>(p)
							+ 4 * pow3(t) * (1 - t) * nested_get<3, 1>(p)
							+ pow4(t) * nested_get<4, 1>(p)
						);
				}
			};
			template<typename Points, typename T>
			class bezier_impl<Points, T, 5> {
			public:
				static SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
				call(Points const& p, T const& t) {
					using sprout::tuples::nested_get;
					using sprout::detail::pow2;
					using sprout::detail::pow3;
					using sprout::detail::pow4;
					using sprout::detail::pow5;
					return sprout::math::curve_point_traits<Points>::make(
						pow5(1 - t) * nested_get<0, 0>(p)
							+ 5 * t * pow4(1 - t) * nested_get<1, 0>(p)
							+ 10 * pow2(t) * pow3(1 - t) * nested_get<2, 0>(p)
							+ 10 * pow3(t) * pow2(1 - t) * nested_get<3, 0>(p)
							+ 5 * pow4(t) * (1 - t) * nested_get<4, 0>(p)
							+ pow5(t) * nested_get<5, 0>(p)
							,
						pow5(1 - t) * nested_get<0, 1>(p)
							+ 5 * t * pow4(1 - t) * nested_get<1, 1>(p)
							+ 10 * pow2(t) * pow3(1 - t) * nested_get<2, 1>(p)
							+ 10 * pow3(t) * pow2(1 - t) * nested_get<3, 1>(p)
							+ 5 * pow4(t) * (1 - t) * nested_get<4, 1>(p)
							+ pow5(t) * nested_get<5, 1>(p)
						);
				}
			};
		}	// namespace detail

		//
		// bezier
		//
		template<typename Points, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
		bezier(T const& t, Points const& p) {
			return sprout::math::detail::bezier_impl<Points, T>::call(p, t);
		}
		template<std::size_t N, typename Points, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
		bezier(T const& t, Points const& p) {
			return sprout::math::detail::bezier_impl<Points, T, N>::call(p, t);
		}

		template<typename P0, typename P1, typename P2, typename... PTail, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<sprout::tuples::tuple<P0 const&, P1 const&, P2 const&, PTail const&...> >::type
		bezier(T const& t, P0 const& p0, P1 const& p1, P2 const& p2, PTail const&... p) {
			return sprout::math::bezier(t, sprout::tuples::forward_as_tuple(p0, p1, p2, p...));
		}
		template<std::size_t N, typename P0, typename P1, typename P2, typename... PTail, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<sprout::tuples::tuple<P0 const&, P1 const&, P2 const&, PTail const&...> >::type
		bezier(T const& t, P0 const& p0, P1 const& p1, P2 const& p2, PTail const&... p) {
			return sprout::math::bezier<N>(t, sprout::tuples::forward_as_tuple(p0, p1, p2, p...));
		}
	}	// namespace math

	using sprout::math::bezier;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CURVE_BEZIER_HPP
