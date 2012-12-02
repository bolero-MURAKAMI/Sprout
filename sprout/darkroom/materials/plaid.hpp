#ifndef SPROUT_DARKROOM_MATERIALS_PLAID_HPP
#define SPROUT_DARKROOM_MATERIALS_PLAID_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/math/fmod.hpp>

namespace sprout {
	namespace darkroom {
		namespace materials {
			//
			// plaid_element
			//
			template<typename Element, typename Scale = double>
			class plaid_element {
			public:
				typedef Element result_type;
				typedef Scale unit_type;
			private:
				result_type elem1_;
				result_type elem2_;
				unit_type scale_;
			private:
				template<typename Unit>
				SPROUT_CONSTEXPR result_type
				calc_1(Unit const& u, Unit const& v) const {
					return (u >= 0 && v >= 0) || (u < 0 && v < 0) ? elem1_ : elem2_;
				}
			public:
				SPROUT_CONSTEXPR plaid_element(result_type const& elem1, result_type const& elem2, unit_type const& scale = 1)
					: elem1_(elem1)
					, elem2_(elem2)
					, scale_(scale)
				{}
				template<typename Unit>
				SPROUT_CONSTEXPR result_type
				operator()(Unit const& u, Unit const& v) const {
					return calc_1(
						(u < 0
							? scale_ + sprout::fmod(u, scale_)
							: sprout::fmod(u, scale_)
							)
							- scale_ / 2
							,
						(v < 0
							? scale_ + sprout::fmod(v, scale_)
							: sprout::fmod(v, scale_)
							)
							- scale_ / 2
						);
				}
			};
			//
			// make_plaid
			//
			template<typename Element>
			inline SPROUT_CONSTEXPR sprout::darkroom::materials::plaid_element<Element>
			make_plaid(Element const& elem1, Element const& elem2) {
				return sprout::darkroom::materials::plaid_element<Element>(elem1, elem2);
			}
			template<typename Element, typename Unit>
			inline SPROUT_CONSTEXPR sprout::darkroom::materials::plaid_element<Element>
			make_plaid(Element const& elem1, Element const& elem2, Unit const& scale) {
				return sprout::darkroom::materials::plaid_element<Element, Unit>(elem1, elem2, scale);
			}
			//
			// make_plaid_material_image
			//
			template<typename Color, typename Reflection>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				sprout::darkroom::materials::plaid_element<Color>,
				sprout::darkroom::materials::plaid_element<Reflection>
			>
			make_plaid_material_image(
				Color const& col1, Color const& col2,
				Reflection const& ref1, Reflection const& ref2
				)
			{
				return sprout::tuples::make_tuple(
					sprout::darkroom::materials::make_plaid(col1, col2),
					sprout::darkroom::materials::make_plaid(ref1, ref2)
					);
			}
			template<typename Color, typename Reflection, typename Unit>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				sprout::darkroom::materials::plaid_element<Color, Unit>,
				sprout::darkroom::materials::plaid_element<Reflection, Unit>
			>
			make_plaid_material_image(
				Color const& col1, Color const& col2,
				Reflection const& ref1, Reflection const& ref2,
				Unit const& scale
				)
			{
				return sprout::tuples::make_tuple(
					sprout::darkroom::materials::make_plaid(col1, col2, scale),
					sprout::darkroom::materials::make_plaid(ref1, ref2, scale)
					);
			}
		}	// namespace materials
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_MATERIALS_PLAID_HPP
