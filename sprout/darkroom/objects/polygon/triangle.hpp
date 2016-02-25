/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_OBJECTS_POLYGON_TRIANGLE_HPP
#define SPROUT_DARKROOM_OBJECTS_POLYGON_TRIANGLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/coords/vector.hpp>
#include <sprout/darkroom/rays/ray.hpp>
#include <sprout/darkroom/materials/material.hpp>

namespace sprout {
	namespace darkroom {
		namespace objects {
			//
			// basic_triangle
			//
			template<typename Material, typename Vertex = sprout::darkroom::coords::vector3d_t>
			class basic_triangle {
			public:
				typedef Material material_type;
				typedef Vertex position_type;
				typedef typename sprout::darkroom::access::unit<position_type>::type unit_type;
				typedef sprout::array<position_type, 3> vertices_type;
			public:
				template<typename Ray>
				struct intersection {
					typedef sprout::tuples::tuple<
						bool,
						unit_type,
						position_type,
						position_type,
						decltype(sprout::darkroom::materials::calculate_material(
							std::declval<material_type const&>(),
							std::declval<unit_type const&>(),
							std::declval<unit_type const&>()
							)),
						bool
					> type;
				};
			private:
				material_type mat_;
				vertices_type vertices_;
				position_type normal_;
			private:
				template<typename Vector>
				SPROUT_CONSTEXPR bool
				within_test(Vector const& d0, Vector const& d1) const {
					return sprout::darkroom::coords::dot(
						sprout::darkroom::coords::cross(d0, d1),
						normal_
						)
						>= 0
						;
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_5(Ray const& ray, int /*hit_side*/, bool does_intersect, unit_type distance) const {
					return typename intersection<Ray>::type(
						does_intersect,
						distance,
						does_intersect
							? sprout::darkroom::rays::point_of_intersection(ray, distance)
							: position_type(0, 0, 0)
							,
						normal_,// !!! TEMP: hit_side > 0 ? normal_ : sprout::darkroom::coords::negate(normal_),
						sprout::darkroom::materials::calculate_material(mat_, unit_type(0), unit_type(0)),	// ???
						false	// !!! TEMP: is_from_inside
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_4(Ray const& ray, position_type const& v, int hit_side, bool does_intersect) const {
					return intersect_5(
						ray,
						hit_side,
						does_intersect,
						does_intersect
							? sprout::darkroom::coords::length(v)
							: unit_type(-1)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_3(Ray const& ray, position_type const& v, position_type const& p, int hit_side, bool exist_forward) const {
					return intersect_4(
						ray,
						v,
						hit_side,
						exist_forward
							&& within_test(
								sprout::darkroom::coords::sub(p, vertices_[0]),
								sprout::darkroom::coords::sub(vertices_[1], vertices_[0])
								)
							&& within_test(
								sprout::darkroom::coords::sub(p, vertices_[1]),
								sprout::darkroom::coords::sub(vertices_[2], vertices_[1])
								)
							&& within_test(
								sprout::darkroom::coords::sub(p, vertices_[2]),
								sprout::darkroom::coords::sub(vertices_[0], vertices_[2])
								)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_2(Ray const& ray, unit_type const& t, int hit_side) const {
					return intersect_3(
						ray,
						sprout::darkroom::coords::scale(sprout::darkroom::rays::direction(ray), t),
						sprout::darkroom::coords::add(
							sprout::darkroom::rays::position(ray),
							sprout::darkroom::coords::scale(sprout::darkroom::rays::direction(ray), t)
							),
						hit_side,
						// ???
//						hit_side > 0 && t >= 0
						t >= 0
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_1(Ray const& ray, unit_type const& xpn, unit_type const& vn) const {
					return intersect_2(
						ray,
						xpn / vn,
						vn >= 0 ? 1 : -1
						);
				}
			public:
				SPROUT_CONSTEXPR basic_triangle(material_type const& mat, position_type const& v0, position_type const& v1, position_type const& v2)
					: mat_(mat)
					, vertices_{{v0, v1, v2}}
					, normal_(
						sprout::darkroom::coords::normalize(
							sprout::darkroom::coords::cross(
								sprout::darkroom::coords::sub(v2, v0),
								sprout::darkroom::coords::sub(v1, v0)
								)
							)
						)
				{}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect(Ray const& ray) const {
					return intersect_1(
						ray,
						sprout::darkroom::coords::dot(
							sprout::darkroom::coords::sub(vertices_[0], sprout::darkroom::rays::position(ray)),
							normal_
							),
						sprout::darkroom::coords::dot(
							sprout::darkroom::rays::direction(ray),
							normal_
							)
						);
				}
			};
			//
			// make_triangle
			//
			template<typename Material, typename Vertex>
			inline SPROUT_CONSTEXPR sprout::darkroom::objects::basic_triangle<Material, Vertex>
			make_triangle(Material const& mat, Vertex const& v0, Vertex const& v1, Vertex const& v2) {
				return sprout::darkroom::objects::basic_triangle<Material, Vertex>(mat, v0, v1, v2);
			}
		}	// namespace objects
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_OBJECTS_POLYGON_TRIANGLE_HPP
