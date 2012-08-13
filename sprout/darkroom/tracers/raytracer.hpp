#ifndef SPROUT_DARKROOM_TRACERS_RAYTRACER_HPP
#define SPROUT_DARKROOM_TRACERS_RAYTRACER_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/darkroom/colors/rgb.hpp>

namespace sprout {
	namespace darkroom {
		namespace tracers {
			//
			// raytracer
			//
			template<typename Color = sprout::darkroom::colors::rgb_f>
			class raytracer {
			public:
				typedef Color color_type;
			public:
				template<
					typename Renderer,
					typename Camera,
					typename Objects,
					typename Lights,
					typename Unit2D
				>
				SPROUT_CONSTEXPR color_type operator()(
					Renderer const& renderer,
					Camera const& camera,
					Objects const& objs,
					Lights const& lights,
					Unit2D const& x,
					Unit2D const& y,
					Unit2D const& width,
					Unit2D const& height,
					std::size_t depth_max = 8
					) const
				{
					return renderer.template operator()<color_type>(
						camera,
						objs,
						lights,
						camera.template operator()(x, y, width, height),
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
