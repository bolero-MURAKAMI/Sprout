#ifndef SPROUT_FIXED_CONTAINER_ITERATOR_HPP
#define SPROUT_FIXED_CONTAINER_ITERATOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/detail/if.hpp>

namespace sprout {
	//
	// fixed_iterator
	//
	template<typename Container>
	struct fixed_iterator {
	public:
		typedef typename sprout::detail::if_c<
			std::is_const<Container>::value,
			typename sprout::fixed_container_traits<Container>::const_iterator,
			typename sprout::fixed_container_traits<Container>::iterator
		>::type type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_ITERATOR_HPP
