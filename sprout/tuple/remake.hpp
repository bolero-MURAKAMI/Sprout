#ifndef SPROUT_TUPLE_REMAKE_HPP
#define SPROUT_TUPLE_REMAKE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// remake
		//
		template<typename Tuple, typename Tup, typename... Args>
		SPROUT_CONSTEXPR inline typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type remake(
			Tup&& tup,
			Args&&... args
			)
		{
			return sprout::tuples::tuple_construct_traits<Tuple>::remake(
				sprout::forward<Tup>(tup),
				sprout::forward<Args>(args)...
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_REMAKE_HPP
