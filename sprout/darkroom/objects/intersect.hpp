#ifndef SPROUT_DARKROOM_OBJECTS_INTERSECT_HPP
#define SPROUT_DARKROOM_OBJECTS_INTERSECT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/intersects/intersection.hpp>

namespace sprout {
	namespace darkroom {
		namespace objects {
			//
			// intersect
			//
			template<typename Object, typename Ray>
			inline SPROUT_CONSTEXPR typename Object::template intersection<Ray>::type
			intersect(Object const& obj, Ray const& ray) {
				return obj.intersect(ray);
			}

			//
			// intersect_list
			//
			namespace detail {
				template<std::size_t N>
				struct intersect_list_impl {
				private:
					template<typename Objects, typename Ray, typename A, typename B>
					SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Objects>::type
						::template intersection<Ray>::type
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
					SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Objects>::type
						::template intersection<Ray>::type
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
					SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Objects>::type
						::template intersection<Ray>::type
					operator()(Objects const& objs, Ray const& ray) const {
						return sprout::darkroom::objects::intersect(sprout::darkroom::access::get<0>(objs), ray);
					}
				};
			}	// namespace detail
			template<typename Objects, typename Ray>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Objects>::type
				::template intersection<Ray>::type
			intersect_list(Objects const& objs, Ray const& ray) {
				return sprout::darkroom::objects::detail::intersect_list_impl<
					sprout::darkroom::access::size<Objects>::value - 1
					>()(objs, ray);
			}
		}	// namespace objects
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_OBJECTS_INTERSECT_HPP
