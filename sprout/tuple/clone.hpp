#ifndef SPROUT_TUPLE_CLONE_HPP
#define SPROUT_TUPLE_CLONE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// clone
		//
		template<typename Tuple>
		SPROUT_CONSTEXPR inline typename sprout::tuples::tuple_traits<
			typename std::remove_reference<Tuple>::type
		>::clone_type clone(Tuple&& cont) {
			typedef typename std::decay<Tuple>::type tuple_type;
			return sprout::tuples::clone_functor<tuple_type>().template operator()(sprout::forward<Tuple>(cont));
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_CLONE_HPP
