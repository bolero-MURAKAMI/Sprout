#ifndef SPROUT_PIT_CONTAINER_HPP
#define SPROUT_PIT_CONTAINER_HPP

#include <type_traits>
#include <sprout/utility/forward.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>

namespace sprout {
	//
	// container_construct_traits
	//
	template<typename Container>
	struct container_construct_traits<sprout::pit<Container> > {
	public:
		typedef typename sprout::container_construct_traits<Container>::copied_type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return copied_type();
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::make<copied_type>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::pit<Container> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};

	//
	// container_transform_traits
	//
	template<typename Container>
	struct container_transform_traits<sprout::pit<Container> > {
	public:
		template<typename sprout::container_traits<sprout::pit<Container> >::size_type Size>
		struct rebind_size {
		public:
			typedef sprout::pit<
				typename sprout::container_transform_traits<Container>::template rebind_size<Size>::type
			> type;
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_PIT_CONTAINER_HPP
