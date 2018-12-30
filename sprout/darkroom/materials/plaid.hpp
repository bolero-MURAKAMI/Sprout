/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_MATERIALS_PLAID_HPP
#define SPROUT_DARKROOM_MATERIALS_PLAID_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/index_tuple/make_index_tuple.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/type_traits/enabler_if.hpp>
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
				calculate_1(Unit const& u, Unit const& v) const {
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
					return calculate_1(
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
			namespace detail {
				template<typename... Elements, sprout::index_t... Indexes>
				inline SPROUT_CONSTEXPR auto
				make_plaid_material_image_impl(
					sprout::index_tuple<Indexes...>,
					Elements const&... elems
					)
				-> decltype(sprout::tuples::make_tuple(
					sprout::darkroom::materials::make_plaid(sprout::pack_get<Indexes * 2>(elems...), sprout::pack_get<Indexes * 2 + 1>(elems...))...
					))
				{
					return sprout::tuples::make_tuple(
						sprout::darkroom::materials::make_plaid(sprout::pack_get<Indexes * 2>(elems...), sprout::pack_get<Indexes * 2 + 1>(elems...))...
						);
				}
				template<typename Unit, typename... Elements, sprout::index_t... Indexes>
				inline SPROUT_CONSTEXPR auto
				make_plaid_material_image_impl(
					Unit const& scale,
					sprout::index_tuple<Indexes...>,
					Elements const&... elems
					)
				-> decltype(sprout::tuples::make_tuple(
					sprout::darkroom::materials::make_plaid(sprout::pack_get<Indexes * 2>(elems...), sprout::pack_get<Indexes * 2 + 1>(elems...), scale)...
					))
				{
					return sprout::tuples::make_tuple(
						sprout::darkroom::materials::make_plaid(sprout::pack_get<Indexes * 2>(elems...), sprout::pack_get<Indexes * 2 + 1>(elems...), scale)...
						);
				}
			}	// namespace detail
			template<
				typename... Elements,
				typename sprout::enabler_if<sizeof...(Elements) % 2 == 0>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR auto
			make_plaid_material_image(Elements const&... elems)
			-> decltype(sprout::darkroom::materials::detail::make_plaid_material_image_impl(sprout::make_index_tuple<sizeof...(Elements) / 2>::make(), elems...))
			{
				return sprout::darkroom::materials::detail::make_plaid_material_image_impl(sprout::make_index_tuple<sizeof...(Elements) / 2>::make(), elems...);
			}
			template<
				typename Unit, typename... Elements,
				typename sprout::enabler_if<sizeof...(Elements) % 2 == 0>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR auto
			make_plaid_material_image(Unit const& scale, Elements const&... elems)
			-> decltype(sprout::darkroom::materials::detail::make_plaid_material_image_impl(scale, sprout::make_index_tuple<sizeof...(Elements) / 2>::make(), elems...))
			{
				return sprout::darkroom::materials::detail::make_plaid_material_image_impl(scale, sprout::make_index_tuple<sizeof...(Elements) / 2>::make(), elems...);
			}
		}	// namespace materials
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_MATERIALS_PLAID_HPP
