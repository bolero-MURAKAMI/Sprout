#ifndef SPROUT_DARKROOM_LIGHTS_LIGHT_LIST_HPP
#define SPROUT_DARKROOM_LIGHTS_LIGHT_LIST_HPP

#include <limits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/colors/rgb.hpp>

namespace sprout {
	namespace darkroom {
		namespace lights {
			//
			// light_list
			//
			template<typename... Lights>
			class light_list {
			public:
				typedef sprout::tuples::tuple<Lights...> lights_type;
				typedef typename sprout::darkroom::access::unit<lights_type>::type::color_type color_type;
			private:
				lights_type lights_;
			private:
				template<typename Color>
				SPROUT_CONSTEXPR color_type shade_2(Color const& col) const {
					return col;
				}
				template<typename Color1, typename Color2, typename... Tail>
				SPROUT_CONSTEXPR color_type shade_2(Color1 const& col1, Color2 const& col2, Tail const&... tail) const {
					return shade_2(
						sprout::darkroom::colors::add(col1, col2),
						tail...
						);
				}
				template<typename Intersection, typename Objects, sprout::index_t... Indexes>
				SPROUT_CONSTEXPR color_type shade_1(
					Intersection const& inter, Objects const& objs,
					sprout::index_tuple<Indexes...>
					) const
				{
					return shade_2(sprout::darkroom::access::get<Indexes>(lights_).template operator()(inter, objs)...);
				}
			public:
				explicit SPROUT_CONSTEXPR light_list(Lights const&... lights)
					: lights_(lights...)
				{}
				template<typename Intersection, typename Objects>
				SPROUT_CONSTEXPR color_type operator()(Intersection const& inter, Objects const& objs) const {
					return shade_1(inter, objs, sprout::index_range<0, sizeof...(Lights)>::make());
				}
			};
			//
			// make_light_list
			//
			template<typename... Lights>
			inline SPROUT_CONSTEXPR sprout::darkroom::lights::light_list<Lights...>
			make_light_list(Lights const&... lights) {
				return sprout::darkroom::lights::light_list<Lights...>(lights...);
			}
		}	// namespace lights
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_LIGHTS_LIGHT_LIST_HPP
