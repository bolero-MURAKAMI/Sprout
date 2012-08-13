#ifndef SPROUT_DARKROOM_RENDERERS_INFINITY_HPP
#define SPROUT_DARKROOM_RENDERERS_INFINITY_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/darkroom/colors/rgb.hpp>
#include <sprout/darkroom/coords/vector.hpp>

namespace sprout {
	namespace darkroom {
		namespace renderers {
			//
			// normal_to_color
			//
			template<typename Color, typename Normal>
			inline SPROUT_CONSTEXPR Color normal_to_color(Normal const& nor) {
				return sprout::tuples::make<Color>(
					0.5 + sprout::darkroom::coords::x(nor) * 0.5,
					0.5 + sprout::darkroom::coords::y(nor) * 0.5,
					0.5 + sprout::darkroom::coords::z(nor) * 0.5
					);
			}

			//
			// direction_gradation
			//
			class direction_gradation {
			public:
				template<typename TargetColor, typename Vector>
				SPROUT_CONSTEXPR TargetColor operator()(Vector const& dir) const {
					return sprout::darkroom::renderers::normal_to_color<TargetColor>(dir);
				}
			};
			//
			// make_direction_gradation
			//
			inline SPROUT_CONSTEXPR sprout::darkroom::renderers::direction_gradation
			make_direction_gradation() {
				return sprout::darkroom::renderers::direction_gradation();
			}

			//
			// uniform_color
			//
			template<typename Color = sprout::darkroom::colors::rgb_f>
			class uniform_color {
			public:
				typedef Color color_type;
			private:
				color_type color_;
			public:
				SPROUT_CONSTEXPR uniform_color()
					: color_()
				{}
				SPROUT_CONSTEXPR uniform_color(uniform_color const&) = default;
				explicit SPROUT_CONSTEXPR uniform_color(color_type const& color)
					: color_(color)
				{}
				template<typename TargetColor, typename Vector>
				SPROUT_CONSTEXPR TargetColor operator()(Vector const&) const {
					return color_;
				}
			};
			//
			// make_uniform_color
			//
			inline SPROUT_CONSTEXPR sprout::darkroom::renderers::uniform_color<>
			make_uniform_color() {
				return sprout::darkroom::renderers::uniform_color<>();
			}
			template<typename Color>
			inline SPROUT_CONSTEXPR sprout::darkroom::renderers::uniform_color<Color>
			make_uniform_color(Color const& color) {
				return sprout::darkroom::renderers::uniform_color<Color>(color);
			}
		}	// namespace renderers
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_RENDERERS_INFINITY_HPP
