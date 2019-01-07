/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_OBJECTS_AA_PLANE_HPP
#define SPROUT_DARKROOM_OBJECTS_AA_PLANE_HPP

#include <type_traits>
#include <sprout/config.hpp>
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
			// aa_plane_direction
			//
			struct aa_plane_direction {
			public:
				enum values {
					x,
					y,
					z
				};
			};
			//
			// aa_plane_face
			//
			struct aa_plane_face {
			public:
				enum values {
					both,
					negative,
					positive,
					same_as_direction
				};
			};
			//
			// basic_aa_plane
			//
			template<typename Material, typename Position = sprout::darkroom::coords::vector3d_t>
			class basic_aa_plane {
			public:
				typedef Material material_type;
				typedef Position position_type;
				typedef typename sprout::darkroom::access::unit<position_type>::type unit_type;
				typedef sprout::darkroom::objects::aa_plane_direction aa_plane_direction;
				typedef sprout::darkroom::objects::aa_plane_face aa_plane_face;
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
				aa_plane_direction::values direction_value_;
				unit_type val_;
				material_type mat_;
				aa_plane_face::values face_;
			private:
				SPROUT_CONSTEXPR bool
				is_x() const {
					return direction_value_ == aa_plane_direction::x;
				}
				SPROUT_CONSTEXPR bool
				is_y() const {
					return direction_value_ == aa_plane_direction::y;
				}
				SPROUT_CONSTEXPR bool
				is_z() const {
					return direction_value_ == aa_plane_direction::z;
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_5(int hit_side, bool is_from_inside, bool does_intersect, unit_type distance, position_type const& point_of_intersection) const {
					return typename intersection<Ray>::type(
						does_intersect,
						distance,
						point_of_intersection,
						is_x() ? position_type(hit_side > 0 ? 1 : -1, 0, 0)
							: is_y() ? position_type(0, hit_side > 0 ? 1 : -1, 0)
							: position_type(0, 0, hit_side > 0 ? 1 : -1)
							,
						is_x() ? sprout::darkroom::materials::calculate_material(
							mat_,
							sprout::darkroom::coords::z(point_of_intersection),
							sprout::darkroom::coords::y(point_of_intersection)
							)
							: is_y() ? sprout::darkroom::materials::calculate_material(
								mat_,
								sprout::darkroom::coords::x(point_of_intersection),
								sprout::darkroom::coords::z(point_of_intersection)
								)
							: sprout::darkroom::materials::calculate_material(
								mat_,
								sprout::darkroom::coords::x(point_of_intersection),
								sprout::darkroom::coords::y(point_of_intersection)
								)
							,
						is_from_inside
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_4(Ray const& ray, int hit_side, bool is_from_inside, bool does_intersect, unit_type distance) const {
					return intersect_5<Ray>(
						hit_side,
						is_from_inside,
						does_intersect,
						distance,
						does_intersect
							? sprout::darkroom::rays::point_of_intersection(ray, distance)
							: position_type(0, 0, 0)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_3(Ray const& ray, unit_type pos_v, unit_type dir_v, int hit_side, bool is_from_inside, bool does_intersect) const {
					return intersect_4(
						ray,
						hit_side,
						is_from_inside,
						does_intersect,
						does_intersect
							? (pos_v - val_) / -dir_v
							: unit_type(-1)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_2(Ray const& ray, unit_type pos_v, unit_type dir_v, int hit_side, bool is_from_inside) const {
					return intersect_3(
						ray,
						pos_v,
						dir_v,
						hit_side,
						is_from_inside,
						(hit_side > 0 && dir_v < 0) || (hit_side < 0 && dir_v > 0)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_1(Ray const& ray, unit_type pos_v, unit_type dir_v) const {
					return intersect_2(
						ray,
						pos_v,
						dir_v,
						pos_v > val_ ? 1 : -1,
						face_ == aa_plane_face::both ? false
							: face_ == aa_plane_face::negative ? dir_v > 0
							: face_ == aa_plane_face::positive ? dir_v < 0
							: (val_ > 0 && dir_v < 0) || (val_ < 0 && dir_v > 0)
						);
				}
			public:
				SPROUT_CONSTEXPR basic_aa_plane(aa_plane_direction::values direction_value, unit_type val, material_type const& mat, aa_plane_face::values face = aa_plane_face::both)
					: direction_value_(direction_value)
					, val_(val)
					, mat_(mat)
					, face_(face)
				{}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect(Ray const& ray) const {
					return intersect_1(
						ray,
						(is_x() ? sprout::darkroom::coords::x(sprout::darkroom::rays::position(ray))
							: is_y() ? sprout::darkroom::coords::y(sprout::darkroom::rays::position(ray))
							: sprout::darkroom::coords::z(sprout::darkroom::rays::position(ray))
							),
						(is_x() ? sprout::darkroom::coords::x(sprout::darkroom::rays::direction(ray))
							: is_y() ? sprout::darkroom::coords::y(sprout::darkroom::rays::direction(ray))
							: sprout::darkroom::coords::z(sprout::darkroom::rays::direction(ray))
							)
						);
				}
			};
			//
			// make_aa_plane
			//
			template<typename Material, typename Unit>
			inline SPROUT_CONSTEXPR sprout::darkroom::objects::basic_aa_plane<Material>
			make_aa_plane(
				sprout::darkroom::objects::aa_plane_direction::values dir_val,
				Unit const& val,
				Material const& mat,
				sprout::darkroom::objects::aa_plane_face::values face_val = sprout::darkroom::objects::aa_plane_face::both
				)
			{
				return sprout::darkroom::objects::basic_aa_plane<Material>(dir_val, val, mat, face_val);
			}
		}	// namespace objects
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_OBJECTS_AA_PLANE_HPP
