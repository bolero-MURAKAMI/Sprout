/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_OBJECTS_INTERSECT_HPP
#define SPROUT_DARKROOM_OBJECTS_INTERSECT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/tuple/flex.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/darkroom/access/traits.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/intersects/intersection.hpp>

namespace sprout {
	namespace darkroom {
		namespace objects {
			template<typename Object, typename Ray>
			struct intersection_result;

			namespace detail {
				template<typename Object, typename Ray, typename IndexTuple>
				struct intersection_result_impl;
				template<typename Object, typename Ray, sprout::index_t... Indexes>
				struct intersection_result_impl<Object, Ray, sprout::index_tuple<Indexes...> >
					: public sprout::tuples::common_recursive_flex_type<
						typename sprout::darkroom::objects::intersection_result<typename sprout::darkroom::access::element<Indexes, Object>::type, Ray>::type...
					>
				{};

				template<typename Object, typename Ray, bool IsTuple>
				struct intersection_result;
				template<typename Object, typename Ray>
				struct intersection_result<Object, Ray, false>
					: public Object::template intersection<Ray>
				{};
				template<typename Object, typename Ray>
				struct intersection_result<Object, Ray, true>
					: public sprout::darkroom::objects::detail::intersection_result_impl<
						Object, Ray,
						typename sprout::make_index_tuple<sprout::darkroom::access::size<Object>::value>::type
					>
				{};
			}	// namespace detail

			//
			// intersection_result
			//
			template<typename Object, typename Ray>
			struct intersection_result
				: public sprout::darkroom::objects::detail::intersection_result<
					Object, Ray,
					sprout::darkroom::access::is_tuple<Object>::value
				>
			{};
			template<typename Object, typename Ray>
			struct intersection_result<Object const, Ray>
				: public sprout::darkroom::objects::intersection_result<Object, Ray>
			{};
			template<typename Object, typename Ray>
			struct intersection_result<Object volatile, Ray>
				: public sprout::darkroom::objects::intersection_result<Object, Ray>
			{};
			template<typename Object, typename Ray>
			struct intersection_result<Object const volatile, Ray>
				: public sprout::darkroom::objects::intersection_result<Object, Ray>
			{};

			//
			// intersect
			//
			template<
				typename Object, typename Ray,
				typename sprout::enabler_if<!sprout::darkroom::access::is_tuple<Object>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::objects::intersection_result<Object, Ray>::type
			intersect(Object const& obj, Ray const& ray);
			template<
				typename Object, typename Ray,
				typename sprout::enabler_if<sprout::darkroom::access::is_tuple<Object>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::objects::intersection_result<Object, Ray>::type
			intersect(Object const& obj, Ray const& ray);

			namespace detail {
				template<std::size_t N>
				struct intersect_list_impl {
				private:
					template<typename Objects, typename Ray, typename A, typename B>
					SPROUT_CONSTEXPR typename sprout::darkroom::objects::intersection_result<Objects, Ray>::type
					comp(A const& a, B const& b) const {
						typedef typename sprout::darkroom::objects::intersection_result<Objects, Ray>::type type;
						return sprout::darkroom::intersects::does_intersect(a)
								&& sprout::darkroom::intersects::does_intersect(b)
							? sprout::darkroom::intersects::distance(a) < sprout::darkroom::intersects::distance(b)
								? sprout::tuples::recursive_flex<type>(a)
								: sprout::tuples::recursive_flex<type>(b)
							: sprout::darkroom::intersects::does_intersect(a)
								? sprout::tuples::recursive_flex<type>(a)
								: sprout::tuples::recursive_flex<type>(b)
							;
					}
				public:
					template<typename Objects, typename Ray>
					SPROUT_CONSTEXPR typename sprout::darkroom::objects::intersection_result<Objects, Ray>::type
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
					SPROUT_CONSTEXPR typename sprout::darkroom::objects::intersection_result<Objects, Ray>::type
					operator()(Objects const& objs, Ray const& ray) const {
						return sprout::tuples::recursive_flex(
							sprout::darkroom::objects::intersect(sprout::darkroom::access::get<0>(objs), ray)
							);
					}
				};
			}	// namespace detail
			//
			// intersect_list
			//
			template<typename Objects, typename Ray>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::objects::intersection_result<Objects, Ray>::type
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
				typename sprout::enabler_if<!sprout::darkroom::access::is_tuple<Object>::value>::type
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::objects::intersection_result<Object, Ray>::type
			intersect(Object const& obj, Ray const& ray) {
				return obj.intersect(ray);
			}
			template<
				typename Object, typename Ray,
				typename sprout::enabler_if<sprout::darkroom::access::is_tuple<Object>::value>::type
			>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::objects::intersection_result<Object, Ray>::type
			intersect(Object const& obj, Ray const& ray) {
				return sprout::darkroom::objects::intersect_list(obj, ray);
			}
		}	// namespace objects
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_OBJECTS_INTERSECT_HPP
