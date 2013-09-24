/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_RENDERERS_WHITTED_STYLE_HPP
#define SPROUT_DARKROOM_RENDERERS_WHITTED_STYLE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/colors/rgb.hpp>
#include <sprout/darkroom/coords/vector.hpp>
#include <sprout/darkroom/rays/ray.hpp>
#include <sprout/darkroom/materials/material.hpp>
#include <sprout/darkroom/intersects/intersection.hpp>
#include <sprout/darkroom/objects/intersect.hpp>
#include <sprout/darkroom/renderers/infinity.hpp>

namespace sprout {
	namespace darkroom {
		namespace renderers {
			//
			// whitted_mirror
			//
			class whitted_mirror {
			private:
				template<
					typename Color,
					typename Camera, typename Objects, typename Lights,
					typename Ray, typename Intersection, typename Tracer,
					typename Direction
				>
				SPROUT_CONSTEXPR Color
				color_1(
					Camera const& camera, Objects const& objs, Lights const& lights,
					Ray const& ray, Intersection const& inter, Tracer const& tracer,
					std::size_t depth_max,
					Direction const& reflect_dir
					) const
				{
					return tracer.template operator()<Color>(
						camera, objs, lights,
						sprout::tuples::remake<Ray>(
							ray,
							sprout::darkroom::coords::add(
								sprout::darkroom::intersects::point_of_intersection(inter),
								sprout::darkroom::coords::scale(
									reflect_dir,
									sprout::numeric_limits<typename sprout::darkroom::access::unit<Direction>::type>::epsilon() * 256
									)
								// ???
//								sprout::darkroom::coords::scale(
//									sprout::darkroom::intersects::normal(inter),
//									sprout::numeric_limits<typename sprout::darkroom::access::unit<Direction>::type>::epsilon() * 256
//									)
								),
							reflect_dir
							),
						depth_max - 1
						);
				}
			public:
				template<
					typename Color,
					typename Camera, typename Objects, typename Lights,
					typename Ray, typename Intersection, typename Tracer
				>
				SPROUT_CONSTEXPR Color
				operator()(
					Camera const& camera, Objects const& objs, Lights const& lights,
					Ray const& ray, Intersection const& inter, Tracer const& tracer,
					std::size_t depth_max
					) const
				{
					typedef typename std::decay<
						decltype(sprout::darkroom::materials::reflection(sprout::darkroom::intersects::material(inter)))
					>::type reflection_type;
					return depth_max > 0
						&& sprout::darkroom::intersects::does_intersect(inter)
						&& sprout::darkroom::materials::reflection(sprout::darkroom::intersects::material(inter))
							> sprout::numeric_limits<reflection_type>::epsilon()
						? color_1<Color>(
							camera, objs, lights,
							ray, inter, tracer,
							depth_max,
							sprout::darkroom::coords::reflect(
								sprout::darkroom::rays::direction(ray),
								sprout::darkroom::intersects::normal(inter)
								)
							)
						: sprout::tuples::make<Color>(0, 0, 0)
						;
				}
			};
			//
			// whitted_style
			//
			template<typename InfinityColor = sprout::darkroom::renderers::direction_gradation>
			class whitted_style {
			public:
				typedef InfinityColor infinity_color_type;
			private:
				infinity_color_type infinity_color_;
			private:
				template<typename Color, typename Ray, typename Intersection>
				SPROUT_CONSTEXPR Color
				color_3(
					Ray const& ray, Intersection const& inter,
					Color const& diffuse_color, Color const& mirror_color
					) const
				{
					return sprout::darkroom::intersects::does_intersect(inter)
						? sprout::darkroom::colors::add(
							sprout::darkroom::colors::mul(
								diffuse_color,
								1 - sprout::darkroom::materials::reflection(sprout::darkroom::intersects::material(inter))
								),
							sprout::darkroom::colors::mul(
								mirror_color,
								sprout::darkroom::materials::reflection(sprout::darkroom::intersects::material(inter))
								)
							)
						: infinity_color_.template operator()<Color>(sprout::darkroom::rays::direction(ray))
						;
				}
				template<
					typename Color,
					typename Camera, typename Objects, typename Lights,
					typename Ray, typename Intersection
				>
				SPROUT_CONSTEXPR Color
				color_2(
					Camera const& camera, Objects const& objs, Lights const& lights,
					Ray const& ray, std::size_t depth_max, Intersection const& inter,
					Color const& diffuse_color
					) const
				{
					return color_3<Color>(
						ray, inter,
						diffuse_color,
						sprout::darkroom::renderers::whitted_mirror().template operator()<Color>(
							camera, objs, lights,
							ray, inter, *this,
							depth_max
							)
						);
				}
				template<
					typename Color,
					typename Camera, typename Objects, typename Lights,
					typename Ray, typename Intersection
				>
				SPROUT_CONSTEXPR Color
				color_1(
					Camera const& camera, Objects const& objs, Lights const& lights,
					Ray const& ray, std::size_t depth_max, Intersection const& inter
					) const
				{
					return color_2<Color>(
						camera, objs, lights,
						ray, depth_max, inter,
						lights.template operator()(inter, objs)
						);
				}
			public:
				SPROUT_CONSTEXPR whitted_style()
					: infinity_color_()
				{}
				SPROUT_CONSTEXPR whitted_style(whitted_style const&) = default;
				explicit SPROUT_CONSTEXPR whitted_style(infinity_color_type const& infinity_color)
					: infinity_color_(infinity_color)
				{}
				template<typename Color, typename Camera, typename Objects, typename Lights, typename Ray>
				SPROUT_CONSTEXPR Color
				operator()(
					Camera const& camera, Objects const& objs, Lights const& lights,
					Ray const& ray, std::size_t depth_max
					) const
				{
					return color_1<Color>(
						camera, objs, lights,
						ray, depth_max,
						sprout::darkroom::objects::intersect(objs, ray)
						);
				}
			};
			//
			// make_whitted_style
			//
			inline SPROUT_CONSTEXPR sprout::darkroom::renderers::whitted_style<>
			make_whitted_style() {
				return sprout::darkroom::renderers::whitted_style<>();
			}
			template<typename InfinityColor>
			inline SPROUT_CONSTEXPR sprout::darkroom::renderers::whitted_style<InfinityColor>
			make_whitted_style(InfinityColor const& infinity_color) {
				return sprout::darkroom::renderers::whitted_style<InfinityColor>(infinity_color);
			}
		}	// namespace renderers
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_RENDERERS_WHITTED_STYLE_HPP
