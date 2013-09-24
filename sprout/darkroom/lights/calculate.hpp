/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_LIGHTS_CALCULATE_HPP
#define SPROUT_DARKROOM_LIGHTS_CALCULATE_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/darkroom/access/traits.hpp>
#include <sprout/darkroom/access/access.hpp>

namespace sprout {
	namespace darkroom {
		namespace lights {
			template<typename Light, typename Intersection, typename Objects>
			struct calculate_result;

			namespace detail {
				template<typename Light, typename Intersection, typename Objects, bool IsTuple>
				struct calculate_result;

				template<typename Light, typename Intersection, typename Objects>
				struct calculate_result<Light, Intersection, Objects, false>
					: public sprout::identity<typename Light::color_type>
				{};
				template<typename Light, typename Intersection, typename Objects>
				struct calculate_result<Light, Intersection, Objects, true>
					: public sprout::darkroom::lights::calculate_result<typename sprout::darkroom::access::unit<Light>::type, Intersection, Objects>
				{};
			}	// namespace detail

			//
			// calculate_result
			//
			template<typename Light, typename Intersection, typename Objects>
			struct calculate_result
				: public sprout::darkroom::lights::detail::calculate_result<
					Light, Intersection, Objects,
					sprout::darkroom::access::is_tuple<Light>::value
				>
			{};
			template<typename Light, typename Intersection, typename Objects>
			struct calculate_result<Light const, Intersection, Objects>
				: public sprout::darkroom::lights::calculate_result<Light, Intersection, Objects>
			{};
			template<typename Light, typename Intersection, typename Objects>
			struct calculate_result<Light volatile, Intersection, Objects>
				: public sprout::darkroom::lights::calculate_result<Light, Intersection, Objects>
			{};
			template<typename Light, typename Intersection, typename Objects>
			struct calculate_result<Light const volatile, Intersection, Objects>
				: public sprout::darkroom::lights::calculate_result<Light, Intersection, Objects>
			{};

			//
			// calculate
			//
			template<
				typename Light, typename Intersection, typename Objects,
				typename sprout::enabler_if<!sprout::darkroom::access::is_tuple<Light>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::lights::calculate_result<Light, Intersection, Objects>::type
			calculate(Light const& light, Intersection const& inter, Objects const& objs);
			template<
				typename Light, typename Intersection, typename Objects,
				typename sprout::enabler_if<sprout::darkroom::access::is_tuple<Light>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::lights::calculate_result<Light, Intersection, Objects>::type
			calculate(Light const& light, Intersection const& inter, Objects const& objs);

			namespace detail {
				template<typename Lights, typename Intersection, typename Objects, typename Color>
				inline SPROUT_CONSTEXPR typename sprout::darkroom::lights::calculate_result<Lights, Intersection, Objects>::type
				calculate_2(Color const& col) {
					return col;
				}
				template<typename Lights, typename Intersection, typename Objects, typename Color1, typename Color2, typename... Tail>
				inline SPROUT_CONSTEXPR typename sprout::darkroom::lights::calculate_result<Lights, Intersection, Objects>::type
				calculate_2(Color1 const& col1, Color2 const& col2, Tail const&... tail) {
					return sprout::darkroom::lights::detail::calculate_2<Lights, Intersection, Objects>(
						sprout::darkroom::colors::add(col1, col2),
						tail...
						);
				}
				template<typename Lights, typename Intersection, typename Objects, sprout::index_t... Indexes>
				inline SPROUT_CONSTEXPR typename sprout::darkroom::lights::calculate_result<Lights, Intersection, Objects>::type
				calculate_1(
					Lights const& lights, Intersection const& inter, Objects const& objs,
					sprout::index_tuple<Indexes...>
					)
				{
					return sprout::darkroom::lights::detail::calculate_2<Lights, Intersection, Objects>(
						sprout::darkroom::lights::calculate(sprout::darkroom::access::get<Indexes>(lights), inter, objs)...
						);
				}
			}	// namespace detail
			//
			// calculate_list
			//
			template<typename Lights, typename Intersection, typename Objects>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::lights::calculate_result<Lights, Intersection, Objects>::type
			calculate_list(Lights const& lights, Intersection const& inter, Objects const& objs) {
				return sprout::darkroom::lights::detail::calculate_1(
					lights, inter, objs,
					sprout::tuple_indexes<Lights>::make()
					);
			}

			//
			// calculate
			//
			template<
				typename Light, typename Intersection, typename Objects,
				typename sprout::enabler_if<!sprout::darkroom::access::is_tuple<Light>::value>::type
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::lights::calculate_result<Light, Intersection, Objects>::type
			calculate(Light const& light, Intersection const& inter, Objects const& objs) {
				return light(inter, objs);
			}
			template<
				typename Light, typename Intersection, typename Objects,
				typename sprout::enabler_if<sprout::darkroom::access::is_tuple<Light>::value>::type
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::lights::calculate_result<Light, Intersection, Objects>::type
			calculate(Light const& light, Intersection const& inter, Objects const& objs) {
				return sprout::darkroom::lights::calculate_list(light, inter, objs);
			}
		}	// namespace lights
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_LIGHTS_CALCULATE_HPP
