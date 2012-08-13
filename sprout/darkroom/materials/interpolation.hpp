#ifndef SPROUT_DARKROOM_MATERIALS_INTERPOLATION_HPP
#define SPROUT_DARKROOM_MATERIALS_INTERPOLATION_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/darkroom/colors/rgb.hpp>

namespace sprout {
	namespace darkroom {
		namespace materials {
			//
			// interpolation_type
			//
			struct interpolation_type {
			public:
				enum values {
					nearest_neighbor,
					bilinear,
					bicubic
				};
			};

			//
			// bilinear_interpolate
			//
			template<typename Color, typename Unit>
			inline SPROUT_CONSTEXPR Color bilinear_interpolate(
				Color const& c00, Color const& c01, Color const& c10, Color const& c11,
				Unit const& u, Unit const& v
				)
			{
				return sprout::darkroom::colors::add(
					sprout::darkroom::colors::mul(
						sprout::darkroom::colors::add(
							sprout::darkroom::colors::mul(c00, u),
							sprout::darkroom::colors::mul(c01, 1 - u)
							),
						v
						),
					sprout::darkroom::colors::mul(
						sprout::darkroom::colors::add(
							sprout::darkroom::colors::mul(c10, u),
							sprout::darkroom::colors::mul(c11, 1 - u)
							),
						1 - v
						)
					);
			}
		}	// namespace materials
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_MATERIALS_INTERPOLATION_HPP
