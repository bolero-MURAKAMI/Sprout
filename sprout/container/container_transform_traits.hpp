#ifndef SPROUT_CONTAINER_CONTAINER_TRANSFORM_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_TRANSFORM_TRAITS_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// container_transform_traits
	//
	template<typename Container>
	struct container_transform_traits;

	namespace detail {
		template<typename Container, typename sprout::container_traits<Container>::size_type Size>
		struct default_array_rebind_size;

		template<
			template<typename, std::size_t> class Array,
			typename T,
			std::size_t N,
			typename sprout::container_traits<Array<T, N> >::size_type Size
		>
		struct default_array_rebind_size<Array<T, N>, Size> {
		public:
			typedef Array<T, Size> type;
		};
	}	// namespace detail

	template<typename Container>
	struct container_transform_traits {
	public:
		template<typename sprout::container_traits<Container>::size_type Size>
		struct rebind_size
			: public sprout::detail::default_array_rebind_size<Container, Size>
		{};
	};
	template<typename Container>
	struct container_transform_traits<Container const> {
	public:
		template<typename sprout::container_traits<Container>::size_type Size>
		struct rebind_size {
			typedef typename sprout::container_transform_traits<Container>::template rebind_size<Size>::type const type;
		};
	};

	template<typename T, std::size_t N>
	struct container_transform_traits<T[N]> {
	public:
		template<typename sprout::container_traits<T[N]>::size_type Size>
		struct rebind_size {
		public:
			typedef T type[Size];
		};
	};
	template<typename T, std::size_t N>
	struct container_transform_traits<T const[N]> {
	public:
		template<typename sprout::container_traits<T const[N]>::size_type Size>
		struct rebind_size {
		public:
			typedef T const type[Size];
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_TRANSFORM_TRAITS_HPP
