/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_INTERSECTS_INTERSECTION_HPP
#define SPROUT_DARKROOM_INTERSECTS_INTERSECTION_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/coords/vector.hpp>
#include <sprout/darkroom/materials/material.hpp>

namespace sprout {
	namespace darkroom {
		namespace intersects {
			//
			// intersection
			//
			typedef sprout::tuples::tuple<
				bool,
				double,
				sprout::darkroom::coords::vector3d_t,
				sprout::darkroom::coords::vector3d_t,
				sprout::darkroom::materials::material,
				bool
			> intersection;

			//
			// has_is_from_inside
			//
			template<typename T>
			struct has_is_from_inside
				: public sprout::integral_constant<bool, (sprout::darkroom::access::size<T>::value >= 6)>
			{};

			//
			// does_intersect
			// distance
			// point_of_intersection
			// normal
			// material
			// is_from_inside
			//
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			does_intersect(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<0>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<0>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<0>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			distance(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<1>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<1>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<1>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			point_of_intersection(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<2>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<2>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<2>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			normal(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<3>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<3>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<3>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			material(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<4>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<4>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<4>(sprout::forward<T>(t));
			}
			template<
				typename T,
				typename sprout::enabler_if<sprout::darkroom::intersects::has_is_from_inside<T>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR auto
			is_from_inside(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<5>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<5>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<5>(sprout::forward<T>(t));
			}
			template<
				typename T,
				typename sprout::enabler_if<!sprout::darkroom::intersects::has_is_from_inside<T>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::element<5, sprout::darkroom::intersects::intersection>::type
			is_from_inside(T&&)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR((typename sprout::darkroom::access::element<5, sprout::darkroom::intersects::intersection>::type())))
			{
				return typename sprout::darkroom::access::element<5, sprout::darkroom::intersects::intersection>::type();
			}

			//
			// make_intersection
			//
			template<typename... Elements>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<Elements...>
			make_intersection(Elements const&... elems) {
				return sprout::tuples::make_tuple(elems...);
			}
		}	// namespace intersects
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_INTERSECTS_INTERSECTION_HPP
