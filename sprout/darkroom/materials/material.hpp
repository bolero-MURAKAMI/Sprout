/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_MATERIALS_MATERIAL_HPP
#define SPROUT_DARKROOM_MATERIALS_MATERIAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/colors/rgb.hpp>
#include <sprout/darkroom/materials/calculate.hpp>

namespace sprout {
	namespace darkroom {
		namespace materials {
			//
			// material
			//
			typedef sprout::tuples::tuple<sprout::darkroom::colors::rgb_f_t, double, double, double> material;

			//
			// has_color
			// has_reflection
			// has_alpha
			// has_refraction
			//
			template<typename T>
			struct has_color
				: public sprout::bool_constant<(sprout::darkroom::access::size<T>::value >= 1)>
			{};
			template<typename T>
			struct has_reflection
				: public sprout::bool_constant<(sprout::darkroom::access::size<T>::value >= 2)>
			{};
			template<typename T>
			struct has_alpha
				: public sprout::bool_constant<(sprout::darkroom::access::size<T>::value >= 3)>
			{};
			template<typename T>
			struct has_refraction
				: public sprout::bool_constant<(sprout::darkroom::access::size<T>::value >= 4)>
			{};

			//
			// color
			//
			template<
				typename T,
				typename sprout::enabler_if<sprout::darkroom::materials::has_color<typename std::decay<T>::type>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR auto
			color(T&& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::darkroom::access::get<0>(SPROUT_FORWARD(T, t)))
			-> decltype(sprout::darkroom::access::get<0>(SPROUT_FORWARD(T, t)))
			{
				return sprout::darkroom::access::get<0>(SPROUT_FORWARD(T, t));
			}
			template<
				typename T,
				typename sprout::enabler_if<!sprout::darkroom::materials::has_color<typename std::decay<T>::type>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::element<0, sprout::darkroom::materials::material>::type
			color(T&&)
			SPROUT_NOEXCEPT_IF_EXPR((typename sprout::darkroom::access::element<0, sprout::darkroom::materials::material>::type()))
			{
				return typename sprout::darkroom::access::element<0, sprout::darkroom::materials::material>::type();
			}
			//
			// reflection
			//
			template<
				typename T,
				typename sprout::enabler_if<sprout::darkroom::materials::has_reflection<typename std::decay<T>::type>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR auto
			reflection(T&& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::darkroom::access::get<1>(SPROUT_FORWARD(T, t)))
			-> decltype(sprout::darkroom::access::get<1>(SPROUT_FORWARD(T, t)))
			{
				return sprout::darkroom::access::get<1>(SPROUT_FORWARD(T, t));
			}
			template<
				typename T,
				typename sprout::enabler_if<!sprout::darkroom::materials::has_reflection<typename std::decay<T>::type>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::element<1, sprout::darkroom::materials::material>::type
			reflection(T&&)
			SPROUT_NOEXCEPT_IF_EXPR((typename sprout::darkroom::access::element<1, sprout::darkroom::materials::material>::type()))
			{
				return typename sprout::darkroom::access::element<1, sprout::darkroom::materials::material>::type();
			}
			//
			// alpha
			//
			template<
				typename T,
				typename sprout::enabler_if<sprout::darkroom::materials::has_alpha<typename std::decay<T>::type>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR auto
			alpha(T&& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::darkroom::access::get<2>(SPROUT_FORWARD(T, t)))
			-> decltype(sprout::darkroom::access::get<2>(SPROUT_FORWARD(T, t)))
			{
				return sprout::darkroom::access::get<2>(SPROUT_FORWARD(T, t));
			}
			template<
				typename T,
				typename sprout::enabler_if<!sprout::darkroom::materials::has_alpha<typename std::decay<T>::type>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::element<2, sprout::darkroom::materials::material>::type
			alpha(T&&)
			SPROUT_NOEXCEPT_IF_EXPR((typename sprout::darkroom::access::element<2, sprout::darkroom::materials::material>::type()))
			{
				return typename sprout::darkroom::access::element<2, sprout::darkroom::materials::material>::type();
			}
			//
			// refraction
			//
			template<
				typename T,
				typename sprout::enabler_if<sprout::darkroom::materials::has_refraction<typename std::decay<T>::type>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR auto
			refraction(T&& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout::darkroom::access::get<3>(SPROUT_FORWARD(T, t)))
			-> decltype(sprout::darkroom::access::get<3>(SPROUT_FORWARD(T, t)))
			{
				return sprout::darkroom::access::get<3>(SPROUT_FORWARD(T, t));
			}
			template<
				typename T,
				typename sprout::enabler_if<!sprout::darkroom::materials::has_refraction<typename std::decay<T>::type>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::element<3, sprout::darkroom::materials::material>::type
			refraction(T&&)
			SPROUT_NOEXCEPT_IF_EXPR((typename sprout::darkroom::access::element<3, sprout::darkroom::materials::material>::type()))
			{
				return typename sprout::darkroom::access::element<3, sprout::darkroom::materials::material>::type();
			}

			//
			// calculate_material
			//
			namespace detail {
				template<typename Material, typename Unit, sprout::index_t... Indexes>
				inline SPROUT_CONSTEXPR auto
				calculate_material_impl(Material const& mat, Unit const& u, Unit const& v, sprout::index_tuple<Indexes...>)
				-> decltype(sprout::tuples::make_tuple(
					sprout::darkroom::materials::calculate(sprout::darkroom::access::get<Indexes>(mat), u, v)...
					))
				{
					return sprout::tuples::make_tuple(
						sprout::darkroom::materials::calculate(sprout::darkroom::access::get<Indexes>(mat), u, v)...
						);
				}
			}	// namespace detail
			template<typename Material, typename Unit>
			inline SPROUT_CONSTEXPR auto
			calculate_material(Material const& mat, Unit const& u, Unit const& v)
			-> decltype(sprout::darkroom::materials::detail::calculate_material_impl(mat, u, v, sprout::tuples::tuple_indexes<Material>::make()))
			{
				return sprout::darkroom::materials::detail::calculate_material_impl(mat, u, v, sprout::tuples::tuple_indexes<Material>::make());
			}

			//
			// make_material_image
			//
			template<typename... Images>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<Images...>
			make_material_image(Images const&... images) {
				return sprout::tuples::make_tuple(images...);
			}
		}	// namespace materials
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_MATERIALS_MATERIAL_HPP
