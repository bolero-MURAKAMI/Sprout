#ifndef SPROUT_DARKROOM_MATERIALS_UNIFORM_HPP
#define SPROUT_DARKROOM_MATERIALS_UNIFORM_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>

namespace sprout {
	namespace darkroom {
		namespace materials {
			//
			// uniform_element
			//
			template<typename Element>
			class uniform_element {
			public:
				typedef Element result_type;
			private:
				result_type elem_;
			public:
				explicit SPROUT_CONSTEXPR uniform_element(result_type const& elem)
					: elem_(elem)
				{}
				template<typename Unit>
				SPROUT_CONSTEXPR result_type operator()(Unit const&, Unit const&) const {
					return elem_;
				}
			};
			//
			// make_uniform
			//
			template<typename Element>
			SPROUT_CONSTEXPR sprout::darkroom::materials::uniform_element<Element>
			make_uniform(Element const& elem) {
				return sprout::darkroom::materials::uniform_element<Element>(elem);
			}
			//
			// make_uniform_material_image
			//
			template<typename Color, typename Reflection>
			SPROUT_CONSTEXPR sprout::tuples::tuple<
				sprout::darkroom::materials::uniform_element<Color>,
				sprout::darkroom::materials::uniform_element<Reflection>
			> make_uniform_material_image(Color const& col, Reflection const& ref) {
				return sprout::tuples::make_tuple(
					sprout::darkroom::materials::make_uniform(col),
					sprout::darkroom::materials::make_uniform(ref)
					);
			}
		}	// namespace materials
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_MATERIALS_UNIFORM_HPP
