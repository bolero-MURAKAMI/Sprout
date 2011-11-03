#ifndef SPROUT_TUPLE_REMAKE_CLONE_HPP
#define SPROUT_TUPLE_REMAKE_CLONE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// remake_clone
		//
		template<typename Tuple, typename Other, typename... Args>
		SPROUT_CONSTEXPR inline typename sprout::tuples::tuple_traits<
			typename std::remove_reference<Tuple>::type
		>::clone_type remake_clone(
			Other&& other,
			Args&&... args
			)
		{
			typedef typename std::remove_reference<Tuple>::type tuple_type;
			return sprout::tuples::remake_clone_functor<tuple_type>().template operator()(
				sprout::forward<Other>(other),
				sprout::forward<Args>(args)...
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_REMAKE_CLONE_HPP
