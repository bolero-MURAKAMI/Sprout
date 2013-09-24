/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_OBJECTS_SPHERE_HPP
#define SPROUT_DARKROOM_OBJECTS_SPHERE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/atan2.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/coords/vector.hpp>
#include <sprout/darkroom/rays/ray.hpp>
#include <sprout/darkroom/materials/material.hpp>

namespace sprout {
	namespace darkroom {
		namespace objects {
			//
			// basic_sphere
			//
			template<typename Material, typename Position = sprout::darkroom::coords::vector3d_t>
			class basic_sphere {
			public:
				typedef Material material_type;
				typedef Position position_type;
				typedef typename sprout::darkroom::access::unit<position_type>::type unit_type;
				typedef unit_type radius_type;
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
							))
					> type;
				};
			private:
				typedef sprout::tuples::tuple<int, bool, unit_type> zwo_type;
				typedef sprout::tuples::tuple<position_type, position_type> drei_type;
				struct zw {
					SPROUT_STATIC_CONSTEXPR std::size_t hit_side = 0;
					SPROUT_STATIC_CONSTEXPR std::size_t does_intersect = 1;
					SPROUT_STATIC_CONSTEXPR std::size_t distance = 2;
				};
				struct dr {
					SPROUT_STATIC_CONSTEXPR std::size_t point_of_intersection = 0;
					SPROUT_STATIC_CONSTEXPR std::size_t normal = 1;
				};
			private:
				position_type pos_;
				radius_type rad_;
				material_type mat_;
			private:
				template<typename Ray>
				SPROUT_CONSTEXPR zwo_type
				zweitens_2(Ray const&, unit_type const& i1, unit_type const& i2, int hit_side, bool does_intersect) const {
					return zwo_type(
						hit_side,
						does_intersect,
						hit_side < 0 ? i2
							: hit_side > 0 ? i1
							: -1
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR zwo_type
				zweitens_1(Ray const& ray, unit_type const& i1, unit_type const& i2) const {
					return zweitens_2(
						ray,
						i1,
						i2,
						i2 > 0
							? i1 < 0 ? -1 : 1
							: 0
							,
						i2 > 0
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR zwo_type
				zweitens(Ray const& ray, bool neg, unit_type const& b, unit_type const& det) const {
					return neg
						? zweitens_1(ray, b - det, b + det)
						: zwo_type(0, false, -1)
						;
				}
				template<typename Ray>
				SPROUT_CONSTEXPR drei_type
				drittens_1(Ray const&, typename sprout::darkroom::access::unit<Ray>::type point_of_intersection) const {
					return drei_type(
						point_of_intersection,
						sprout::darkroom::coords::normalize(
							sprout::darkroom::coords::sub(point_of_intersection, pos_)
							)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR drei_type
				drittens(Ray const& ray, bool neg, unit_type const& distance) const {
					return neg
						? drittens_1(ray, sprout::darkroom::rays::point_of_intersection(ray, distance))
						: drei_type(
							sprout::tuples::make<position_type>(0, 0, 0),
							sprout::tuples::make<position_type>(1, 1, 1)
							)
						;
				}
				template<typename Ray, typename Vec>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_6(Ray const&, zwo_type const& zwo, drei_type const& drei, Vec const& normal) const {
					return typename intersection<Ray>::type(
						sprout::tuples::get<zw::does_intersect>(zwo),
						sprout::tuples::get<zw::distance>(zwo),
						sprout::tuples::get<dr::point_of_intersection>(drei),
						sprout::tuples::get<dr::normal>(drei),
						sprout::darkroom::materials::calculate_material(	// ! Spherical
							mat_,
							sprout::atan2(
								sprout::darkroom::coords::z(normal),
								sprout::darkroom::coords::x(normal)
								)
								/ sprout::math::pi<unit_type>()
								,
							sprout::atan2(
								sprout::darkroom::coords::y(normal),
								sprout::sqrt(
									sprout::darkroom::coords::x(normal) * sprout::darkroom::coords::x(normal)
										+ sprout::darkroom::coords::z(normal) * sprout::darkroom::coords::z(normal)
									)
								)
								/ sprout::math::half_pi<unit_type>()
							)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_5(Ray const& ray, zwo_type const& zwo, drei_type const& drei) const {
					return intersect_6(
						ray,
						zwo,
						drei,
						sprout::tuples::get<dr::normal>(drei)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_4(Ray const& ray, zwo_type const& zwo) const {
					return intersect_5(
						ray,
						zwo,
						drittens(
							ray,
							sprout::tuples::get<zw::does_intersect>(zwo),
							sprout::tuples::get<zw::distance>(zwo)
							)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_3(Ray const& ray, unit_type const& b, unit_type const& det_sq) const {
					return intersect_4(
						ray,
						zweitens(
							ray,
							det_sq > 0,
							b,
							det_sq > 0 ? sprout::sqrt(det_sq) : unit_type(0)
							)
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_2(Ray const& ray, position_type const& v, unit_type const& b) const {
					return intersect_3(
						ray,
						b,
						b * b - sprout::darkroom::coords::length_sq(v) + rad_ * rad_
						);
				}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect_1(Ray const& ray, position_type const& v) const {
					return intersect_2(
						ray,
						v,
						-sprout::darkroom::coords::dot(v, sprout::darkroom::rays::direction(ray))
						);
				}
			public:
				SPROUT_CONSTEXPR basic_sphere(position_type const& pos, radius_type rad, material_type const& mat)
					: pos_(pos)
					, rad_(rad)
					, mat_(mat)
				{}
				template<typename Ray>
				SPROUT_CONSTEXPR typename intersection<Ray>::type
				intersect(Ray const& ray) const {
					return intersect_1(
						ray,
						sprout::darkroom::coords::sub(sprout::darkroom::rays::position(ray), pos_)
						);
				}
			};
			//
			// make_sphere
			//
			template<typename Material, typename Position, typename Radius>
			inline SPROUT_CONSTEXPR sprout::darkroom::objects::basic_sphere<Material, Position>
			make_sphere(Position const& pos, Radius const& rad, Material const& mat) {
				return sprout::darkroom::objects::basic_sphere<Material, Position>(pos, rad, mat);
			}
		}	// namespace objects
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_OBJECTS_SPHERE_HPP
