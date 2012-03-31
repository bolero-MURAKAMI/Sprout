#ifndef SPROUT_TUPLE_MAKE_HPP
#define SPROUT_TUPLE_MAKE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// make
		//
		template<typename Tuple, typename... Args>
		SPROUT_CONSTEXPR inline typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type make(Args&&... args) {
			return sprout::tuples::tuple_construct_traits<Tuple>::make(
				sprout::forward<Args>(args)...
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_MAKE_HPP
