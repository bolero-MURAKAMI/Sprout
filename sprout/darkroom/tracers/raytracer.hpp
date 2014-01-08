/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_TRACERS_RAYTRACER_HPP
#define SPROUT_DARKROOM_TRACERS_RAYTRACER_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/darkroom/colors/rgb.hpp>
#include <sprout/darkroom/cameras/calculate.hpp>
#include <sprout/darkroom/renderers/calculate.hpp>

namespace sprout {
	namespace darkroom {
		namespace tracers {
			//
			// raytracer
			//
			template<typename Color = sprout::darkroom::colors::rgb_f_t>
			class raytracer {
			public:
				typedef Color color_type;
			public:
				template<typename Renderer, typename Camera, typename Objects, typename Lights, typename Unit2D, typename Refractions>
				SPROUT_CONSTEXPR color_type operator()(
					Renderer const& renderer, Camera const& camera, Objects const& objs, Lights const& lights,
					Unit2D const& x, Unit2D const& y, Unit2D const& width, Unit2D const& height,
					std::size_t depth_max, Refractions const& refracs
					) const
				{
					return sprout::darkroom::renderers::calculate<color_type>(
						renderer,
						camera, objs, lights,
						sprout::darkroom::cameras::calculate(camera, x, y, width, height),
						depth_max, refracs
						);
				}
				template<typename Renderer, typename Camera, typename Objects, typename Lights, typename Unit2D>
				SPROUT_CONSTEXPR color_type operator()(
					Renderer const& renderer, Camera const& camera, Objects const& objs, Lights const& lights,
					Unit2D const& x, Unit2D const& y, Unit2D const& width, Unit2D const& height,
					std::size_t depth_max = sprout::darkroom::renderers::default_depth
					) const
				{
					return sprout::darkroom::renderers::calculate<color_type>(
						renderer,
						camera, objs, lights,
						sprout::darkroom::cameras::calculate(camera, x, y, width, height),
						depth_max
						);
				}
			};
			//
			// make_raytracer
			//
			inline SPROUT_CONSTEXPR sprout::darkroom::tracers::raytracer<>
			make_raytracer() {
				return sprout::darkroom::tracers::raytracer<>();
			}
			template<typename Color>
			inline SPROUT_CONSTEXPR sprout::darkroom::tracers::raytracer<Color>
			make_raytracer() {
				return sprout::darkroom::tracers::raytracer<Color>();
			}
		}	// namespace tracers
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_TRACERS_RAYTRACER_HPP
