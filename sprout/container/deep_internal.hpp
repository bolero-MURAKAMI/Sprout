#ifndef SPROUT_CONTAINER_DEEP_INTERNAL_HPP
#define SPROUT_CONTAINER_DEEP_INTERNAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/internal.hpp>

namespace sprout {
	namespace containers {
		namespace detail {
			template<typename Container, typename Prev, typename = void>
			struct deep_internal_impl
				: public sprout::containers::detail::deep_internal_impl<
					typename sprout::containers::internal<Container>::type, Container
				>
			{};
			template<typename Container, typename Prev>
			struct deep_internal_impl<
				Container, Prev,
				typename std::enable_if<std::is_same<Container, Prev&&>::value>::type
			> {
			public:
				typedef Container type;
			};
		}	// namespace detail
		//
		// deep_internal
		//
		template<typename Container>
		struct deep_internal
			: public sprout::containers::detail::deep_internal_impl<
				typename sprout::containers::internal<Container>::type, Container
			>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_DEEP_INTERNAL_HPP
