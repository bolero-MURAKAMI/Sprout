#ifndef SPROUT_TUPLE_MAKE_CLONE_HPP
#define SPROUT_TUPLE_MAKE_CLONE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// make_clone
		//
		template<typename Tuple, typename... Args>
		SPROUT_CONSTEXPR inline typename sprout::tuples::tuple_traits<
			typename std::remove_reference<Tuple>::type
		>::clone_type make_clone(Args&&... args) {
			typedef typename std::remove_reference<Tuple>::type tuple_type;
			return sprout::tuples::make_clone_functor<tuple_type>().template operator()(sprout::forward<Args>(args)...);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_MAKE_CLONE_HPP
