/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_CURVE_CATMULL_ROM_SPLINE_HPP
#define SPROUT_MATH_CURVE_CATMULL_ROM_SPLINE_HPP

#include <sprout/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/tuple/tuple/make_tuple.hpp>
#include <sprout/math/curve/curve_point.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename Points, typename T>
			class catmull_rom_spline_impl {
			public:
				static SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
				call(Points const& p, T const& t) {
					using sprout::tuples::nested_get;
					using sprout::detail::pow2;
					using sprout::detail::pow3;
					return sprout::math::curve_point_traits<Points>::make(
						(-nested_get<0, 0>(p) + 3 * nested_get<1, 0>(p) - 3 * nested_get<2, 0>(p) + nested_get<3, 0>(p)) / 2 * pow3(t)
							+ (2 * nested_get<0, 0>(p) - 5 * nested_get<1, 0>(p) + 4 * nested_get<2, 0>(p) - nested_get<3, 0>(p)) / 2 * pow2(t)
							+ (-nested_get<0, 0>(p) + nested_get<2, 0>(p)) / 2 * t
							+ nested_get<1, 0>(p)
							,
						(-nested_get<0, 1>(p) + 3 * nested_get<1, 1>(p) - 3 * nested_get<2, 1>(p) + nested_get<3, 1>(p)) / 2 * pow3(t)
							+ (2 * nested_get<0, 1>(p) - 5 * nested_get<1, 1>(p) + 4 * nested_get<2, 1>(p) - nested_get<3, 1>(p)) / 2 * pow2(t)
							+ (-nested_get<0, 1>(p) + nested_get<2, 1>(p)) / 2 * t
							+ nested_get<1, 1>(p)
						);
				}
			};
			template<typename Points, typename T>
			class catmull_rom_spline_start_impl {
			public:
				static SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
				call(Points const& p, T const& t) {
					using sprout::tuples::nested_get;
					using sprout::detail::pow2;
					return sprout::math::curve_point_traits<Points>::make(
						(nested_get<0, 0>(p) - 2 * nested_get<1, 0>(p) + nested_get<2, 0>(p)) / 2 * pow2(t)
							+ (-3 * nested_get<0, 0>(p) + 4 * nested_get<1, 0>(p) - nested_get<2, 0>(p)) / 2 * t
							+ nested_get<0, 0>(p)
							,
						(nested_get<0, 1>(p) - 2 * nested_get<1, 1>(p) + nested_get<2, 1>(p)) / 2 * pow2(t)
							+ (-3 * nested_get<0, 1>(p) + 4 * nested_get<1, 1>(p) - nested_get<2, 1>(p)) / 2 * t
							+ nested_get<0, 1>(p)
						);
				}
			};
			template<typename Points, typename T>
			class catmull_rom_spline_end_impl {
			public:
				static SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
				call(Points const& p, T const& t) {
					using sprout::tuples::nested_get;
					using sprout::detail::pow2;
					return sprout::math::curve_point_traits<Points>::make(
						(nested_get<0, 0>(p) - 2 * nested_get<1, 0>(p) + nested_get<2, 0>(p)) / 2 * pow2(t)
							+ (-nested_get<0, 0>(p) + nested_get<2, 0>(p)) / 2 * t
							+ nested_get<1, 0>(p)
							,
						(nested_get<0, 1>(p) - 2 * nested_get<1, 1>(p) + nested_get<2, 1>(p)) / 2 * pow2(t)
							+ (-nested_get<0, 1>(p) + nested_get<2, 1>(p)) / 2 * t
							+ nested_get<1, 1>(p)
						);
				}
			};
		}	// namespace detail

		//
		// catmull_rom_spline
		// catmull_rom_spline_start
		// catmull_rom_spline_end
		//
		template<typename Points, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
		catmull_rom_spline(T const& t, Points const& p) {
			return sprout::math::detail::catmull_rom_spline_impl<Points, T>::call(p, t);
		}
		template<typename Points, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
		catmull_rom_spline_start(T const& t, Points const& p) {
			return sprout::math::detail::catmull_rom_spline_start_impl<Points, T>::call(p, t);
		}
		template<typename Points, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<Points>::type
		catmull_rom_spline_end(T const& t, Points const& p) {
			return sprout::math::detail::catmull_rom_spline_end_impl<Points, T>::call(p, t);
		}

		template<typename P0, typename P1, typename P2, typename P3, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<sprout::tuples::tuple<P0 const&, P1 const&, P2 const&, P3 const&> >::type
		catmull_rom_spline(T const& t, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3) {
			return sprout::math::catmull_rom_spline(t, sprout::tuples::forward_as_tuple(p0, p1, p2, p3));
		}
		template<typename P0, typename P1, typename P2, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<sprout::tuples::tuple<P0 const&, P1 const&, P2 const&> >::type
		catmull_rom_spline_start(T const& t, P0 const& p0, P1 const& p1, P2 const& p2) {
			return sprout::math::catmull_rom_spline_start(t, sprout::tuples::forward_as_tuple(p0, p1, p2));
		}
		template<typename P0, typename P1, typename P2, typename T>
		inline SPROUT_CONSTEXPR typename sprout::math::curve_point_result<sprout::tuples::tuple<P0 const&, P1 const&, P2 const&> >::type
		catmull_rom_spline_end(T const& t, P0 const& p0, P1 const& p1, P2 const& p2) {
			return sprout::math::catmull_rom_spline_end(t, sprout::tuples::forward_as_tuple(p0, p1, p2));
		}
	}	// namespace math

	using sprout::math::catmull_rom_spline;
	using sprout::math::catmull_rom_spline_start;
	using sprout::math::catmull_rom_spline_end;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CURVE_CATMULL_ROM_SPLINE_HPP
