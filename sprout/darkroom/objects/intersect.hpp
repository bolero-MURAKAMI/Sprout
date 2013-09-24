/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_OBJECTS_INTERSECT_HPP
#define SPROUT_DARKROOM_OBJECTS_INTERSECT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/intersects/intersection.hpp>

namespace sprout {
	namespace darkroom {
		namespace objects {
			//
			// intersect
			//
			template<
				typename Object, typename Ray,
				typename sprout::enabler_if<!sprout::darkroom::access::is_tuple<Object>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename Object::template intersection<Ray>::type
			intersect(Object const& obj, Ray const& ray);
			template<
				typename Object, typename Ray,
				typename sprout::enabler_if<sprout::darkroom::access::is_tuple<Object>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename Object::template intersection<Ray>::type
			intersect(Object const& obj, Ray const& ray);

			namespace detail {
				template<std::size_t N>
				struct intersect_list_impl {
				private:
					template<typename Objects, typename Ray, typename A, typename B>
					SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Objects>::type::template intersection<Ray>::type
					comp(A const& a, B const& b) const {
						return sprout::darkroom::intersects::does_intersect(a)
								&& sprout::darkroom::intersects::does_intersect(b)
							? sprout::darkroom::intersects::distance(a) < sprout::darkroom::intersects::distance(b)
								? a
								: b
							: sprout::darkroom::intersects::does_intersect(a)
								? a
								: b
							;
					}
				public:
					template<typename Objects, typename Ray>
					SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Objects>::type ::template intersection<Ray>::type
					operator()(Objects const& objs, Ray const& ray) const {
						return comp<Objects, Ray>(
							sprout::darkroom::objects::intersect(sprout::darkroom::access::get<N>(objs), ray),
							intersect_list_impl<N - 1>()(objs, ray)
							);
					}
				};
				template<>
				struct intersect_list_impl<0> {
				public:
					template<typename Objects, typename Ray>
					SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Objects>::type::template intersection<Ray>::type
					operator()(Objects const& objs, Ray const& ray) const {
						return sprout::darkroom::objects::intersect(sprout::darkroom::access::get<0>(objs), ray);
					}
				};
			}	// namespace detail
			//
			// intersect_list
			//
			template<typename Objects, typename Ray>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Objects>::type::template intersection<Ray>::type
			intersect_list(Objects const& objs, Ray const& ray) {
				return sprout::darkroom::objects::detail::intersect_list_impl<
					sprout::darkroom::access::size<Objects>::value - 1
					>()(objs, ray);
			}

			//
			// intersect
			//
			template<
				typename Object, typename Ray,
				typename sprout::enabler_if<!sprout::darkroom::access::is_tuple<Object>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename Object::template intersection<Ray>::type
			intersect(Object const& obj, Ray const& ray) {
				return obj.intersect(ray);
			}
			template<
				typename Object, typename Ray,
				typename sprout::enabler_if<sprout::darkroom::access::is_tuple<Object>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Object>::type::template intersection<Ray>::type
			intersect(Object const& obj, Ray const& ray) {
				return sprout::darkroom::objects::intersect_list(obj, ray);
			}
		}	// namespace objects
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_OBJECTS_INTERSECT_HPP
