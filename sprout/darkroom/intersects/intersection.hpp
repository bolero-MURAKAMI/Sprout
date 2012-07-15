#ifndef SPROUT_DARKROOM_INTERSECTS_INTERSECTION_HPP
#define SPROUT_DARKROOM_INTERSECTS_INTERSECTION_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/coords/vector.hpp>
#include <sprout/darkroom/materials/material.hpp>

namespace sprout {
	namespace darkroom {
		namespace intersects {
			//
			// does_intersect
			// distance
			// point_of_intersection
			// normal
			// material
			//
			template<typename T>
			inline SPROUT_CONSTEXPR auto does_intersect(T&& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<0>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<0>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<0>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto distance(T&& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<1>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<1>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<1>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto point_of_intersection(T&& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<2>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<2>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<2>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto normal(T&& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<3>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<3>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<3>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto material(T&& t)
				SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<4>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<4>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<4>(sprout::forward<T>(t));
			}

			//
			// make_intersection
			//
			template<typename Distance, typename Point, typename Normal, typename Material>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<bool, Distance, Point, Normal, Material>
			make_intersection(bool b, Distance const& dist, Point const& p, Normal const& nor, Material const& mat) {
				return sprout::tuples::make_tuple(b, dist, p, nor, mat);
			}

			//
			// intersection
			//
			typedef sprout::tuples::tuple<
				bool,
				double,
				sprout::darkroom::coords::vector3d,
				sprout::darkroom::coords::vector3d,
				sprout::darkroom::materials::material
			> intersection;
		}	// namespace intersects
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_INTERSECTS_INTERSECTION_HPP
