#ifndef SPROUT_DARKROOM_LIGHTS_POINT_LIGHT_HPP
#define SPROUT_DARKROOM_LIGHTS_POINT_LIGHT_HPP

#include <limits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/colors/rgb.hpp>
#include <sprout/darkroom/coords/vector.hpp>
#include <sprout/darkroom/rays/ray.hpp>
#include <sprout/darkroom/materials/material.hpp>
#include <sprout/darkroom/intersects/intersection.hpp>
#include <sprout/darkroom/objects/intersect.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace darkroom {
		namespace lights {
			//
			// basic_point_light
			//
			template<
				typename Position = sprout::darkroom::coords::vector3d,
				typename Color = sprout::darkroom::colors::rgb_f
			>
			class basic_point_light {
			public:
				typedef Position position_type;
				typedef typename sprout::darkroom::access::unit<position_type>::type unit_type;
				typedef Color color_type;
			private:
				position_type pos_;
				color_type col_;
			private:
				template<typename Intersection>
				SPROUT_CONSTEXPR color_type shade_4(
					Intersection const& inter,
					unit_type const& intensity
					) const
				{
					return sprout::tuples::remake<color_type>(
						col_,
						sprout::darkroom::colors::r(col_)
							* sprout::darkroom::colors::r(
								sprout::darkroom::materials::color(
									sprout::darkroom::intersects::material(inter)
									)
								)
							* intensity
							,
						sprout::darkroom::colors::g(col_)
							* sprout::darkroom::colors::g(
								sprout::darkroom::materials::color(
									sprout::darkroom::intersects::material(inter)
									)
								)
							* intensity
							,
						sprout::darkroom::colors::b(col_)
							* sprout::darkroom::colors::b(
								sprout::darkroom::materials::color(
									sprout::darkroom::intersects::material(inter)
									)
								)
							* intensity
						);
				}
				template<typename Intersection, typename LightRayIntersection>
				SPROUT_CONSTEXPR color_type shade_3(
					Intersection const& inter,
					position_type const& diff,
					position_type const& direction,
					LightRayIntersection const& light_ray_inter
					) const
				{
					return shade_4(
						inter,
						!sprout::darkroom::intersects::does_intersect(light_ray_inter)
							|| sprout::darkroom::intersects::distance(light_ray_inter)
								> sprout::darkroom::coords::length(diff)
							|| sprout::darkroom::intersects::distance(light_ray_inter)
								< std::numeric_limits<unit_type>::epsilon()
							? NS_SSCRISK_CEL_OR_SPROUT_DETAIL::max(
								std::numeric_limits<unit_type>::epsilon(),
								sprout::darkroom::coords::dot(
									direction,
									sprout::darkroom::intersects::normal(inter)
									)
									/ (sprout::darkroom::coords::length(diff) + 1)
								)
							: 0
						);
				}
				template<typename Intersection, typename Objects>
				SPROUT_CONSTEXPR color_type shade_2(
					Intersection const& inter,
					Objects const& objs,
					position_type const& diff,
					position_type const& direction
					) const
				{
					return shade_3(
						inter,
						diff,
						direction,
						sprout::darkroom::objects::intersect_list(
							objs,
							sprout::darkroom::rays::make_ray(
								sprout::darkroom::coords::add(
									sprout::darkroom::coords::scale(
										direction,
										std::numeric_limits<unit_type>::epsilon() * 256
										),
									sprout::darkroom::intersects::point_of_intersection(inter)
									),
								direction
								)
							)
						);
				}
				template<typename Intersection, typename Objects>
				SPROUT_CONSTEXPR color_type shade_1(
					Intersection const& inter,
					Objects const& objs,
					position_type const& diff
					) const
				{
					return shade_2(
						inter,
						objs,
						diff,
						sprout::darkroom::coords::normalize(diff)
						);
				}
			public:
				SPROUT_CONSTEXPR basic_point_light(
					position_type const& pos,
					color_type const& col
					)
					: pos_(pos)
					, col_(col)
				{}
				template<typename Intersection, typename Objects>
				SPROUT_CONSTEXPR color_type operator()(Intersection const& inter, Objects const& objs) const {
					return shade_1(
						inter,
						objs,
						sprout::darkroom::coords::sub(
							pos_,
							sprout::darkroom::intersects::point_of_intersection(inter)
							)
						);
				}
			};
			//
			// make_point_light
			//
			template<typename Position, typename Color>
			SPROUT_CONSTEXPR inline sprout::darkroom::lights::basic_point_light<Position, Color>
			make_point_light(Position const& pos, Color const& col) {
				return sprout::darkroom::lights::basic_point_light<Position, Color>(pos, col);
			}
		}	// namespace lights
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_LIGHTS_POINT_LIGHT_HPP
