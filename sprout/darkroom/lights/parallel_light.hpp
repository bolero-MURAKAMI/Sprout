/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_LIGHTS_PARALLEL_LIGHT_HPP
#define SPROUT_DARKROOM_LIGHTS_PARALLEL_LIGHT_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/colors/rgb.hpp>
#include <sprout/darkroom/coords/vector.hpp>
#include <sprout/darkroom/rays/ray.hpp>
#include <sprout/darkroom/materials/material.hpp>
#include <sprout/darkroom/intersects/intersection.hpp>
#include <sprout/darkroom/objects/intersect.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace darkroom {
		namespace lights {
			//
			// basic_parallel_light
			//
			template<
				typename Position = sprout::darkroom::coords::vector3d_t,
				typename Color = sprout::darkroom::colors::rgb_f_t
			>
			class basic_parallel_light {
			public:
				typedef Position position_type;
				typedef typename sprout::darkroom::access::unit<position_type>::type unit_type;
				typedef Color color_type;
			private:
				position_type dir_;
				color_type col_;
			private:
				template<typename Intersection>
				SPROUT_CONSTEXPR color_type
				shade_2(Intersection const& inter, unit_type const& intensity) const {
					return sprout::darkroom::colors::mul(
						sprout::darkroom::colors::filter(
							col_,
							sprout::darkroom::materials::color(sprout::darkroom::intersects::material(inter))
							),
						intensity
						);
				}
				template<typename Intersection, typename LightRayIntersection>
				SPROUT_CONSTEXPR color_type
				shade_1(Intersection const& inter, LightRayIntersection const& light_ray_inter) const {
					return shade_2(
						inter,
						!sprout::darkroom::intersects::does_intersect(light_ray_inter)
							|| sprout::darkroom::intersects::distance(light_ray_inter)
								< sprout::numeric_limits<unit_type>::epsilon()
							? NS_SSCRISK_CEL_OR_SPROUT::max(
								sprout::numeric_limits<unit_type>::epsilon(),
								sprout::darkroom::coords::dot(
									dir_,
									sprout::darkroom::intersects::normal(inter)
									)
								)
							: 0
						);
				}
			public:
				SPROUT_CONSTEXPR basic_parallel_light(position_type const& dir, color_type const& col)
					: dir_(sprout::darkroom::coords::normalize(dir))
					, col_(col)
				{}
				template<typename Intersection, typename Objects>
				SPROUT_CONSTEXPR color_type
				operator()(Intersection const& inter, Objects const& objs) const {
					return shade_1(
						inter,
						sprout::darkroom::objects::intersect_list(
							objs,
							sprout::darkroom::rays::make_ray(
								sprout::darkroom::coords::add(
									sprout::darkroom::coords::scale(
										dir_,
										sprout::numeric_limits<unit_type>::epsilon() * 256
										),
									sprout::darkroom::intersects::point_of_intersection(inter)
									),
								dir_
								)
							)
						);
				}
			};
			//
			// make_parallel_light
			//
			template<typename Position, typename Color>
			inline SPROUT_CONSTEXPR sprout::darkroom::lights::basic_parallel_light<Position, Color>
			make_parallel_light(Position const& pos, Color const& col) {
				return sprout::darkroom::lights::basic_parallel_light<Position, Color>(pos, col);
			}
		}	// namespace lights
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_LIGHTS_PARALLEL_LIGHT_HPP
