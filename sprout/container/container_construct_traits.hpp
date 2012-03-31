#ifndef SPROUT_CONTAINER_CONTAINER_TRAITS_CONSTRUCT_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_TRAITS_CONSTRUCT_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// container_construct_traits
	//
	template<typename Container>
	struct container_construct_traits;

	namespace detail {
		template<typename Container, typename... Args>
		SPROUT_CONSTEXPR typename sprout::container_construct_traits<Container>::copied_type
		default_make_container(Args&&... args) {
			typedef typename sprout::container_construct_traits<Container>::copied_type copied_type;
			return copied_type{{sprout::forward<Args>(args)...}};
		}
	}	// namespace detail

	template<typename Container>
	struct container_construct_traits {
	public:
		typedef Container copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return sprout::forward<Cont>(cont);
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::detail::default_make_container<Container>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<Container>::difference_type size,
			Args&&... args
			)
		{
			return make(sprout::forward<Args>(args)...);
		}
	};
	template<typename Container>
	struct container_construct_traits<Container const>
		: public sprout::container_construct_traits<Container>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_CONSTRUCT_TRAITS_HPP
