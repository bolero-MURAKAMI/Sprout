#ifndef SPROUT_TUPLE_DEEP_COPY_HPP
#define SPROUT_TUPLE_DEEP_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// deep_copy
		//
		template<typename Tuple>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_construct_traits<
			typename std::remove_reference<Tuple>::type
		>::copied_type deep_copy(Tuple&& tup) {
			typedef typename std::remove_reference<Tuple>::type tuple_type;
			return sprout::tuples::tuple_construct_traits<tuple_type>::deep_copy(sprout::forward<Tuple>(tup));
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_DEEP_COPY_HPP
