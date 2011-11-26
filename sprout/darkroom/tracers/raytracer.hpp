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
					typename Unit
				>
				SPROUT_CONSTEXPR color_type operator()(
					Renderer const& renderer,
					Camera const& camera,
					Objects const& objs,
					Lights const& lights,
					Unit const& x,
					Unit const& y,
					Unit const& width,
					Unit const& height,
					std::size_t depth_max = 8
					) const
				{
					return renderer.template operator()<color_type>(
						camera,
						objs,
						lights,
						camera.template operator()(
							static_cast<typename Camera::unit_type>(x) / width - 0.5,
							static_cast<typename Camera::unit_type>(y) / height - 0.5
							),
						depth_max
						);
				}
			};
		}	// namespace tracers
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_TRACERS_RAYTRACER_HPP
