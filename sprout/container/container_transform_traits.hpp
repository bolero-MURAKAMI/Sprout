/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_CONTAINER_TRANSFORM_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_TRANSFORM_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/detail/array_like.hpp>

namespace sprout {
	//
	// container_transform_traits
	//
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

		template<typename Container, typename Type>
		struct default_array_rebind_type;
		template<
			template<typename, std::size_t> class Array,
			typename T,
			std::size_t N,
			typename Type
		>
		struct default_array_rebind_type<Array<T, N>, Type> {
		public:
			typedef Array<Type, N> type;
		};

		template<typename Container, typename = void>
		struct inherit_default_rebind_size {};
		template<typename Container>
		struct inherit_default_rebind_size<
			Container,
			typename std::enable_if<sprout::detail::is_array_like<Container>::value>::type
		> {
		public:
			template<typename sprout::container_traits<Container>::size_type Size>
			struct rebind_size
				: public sprout::detail::default_array_rebind_size<Container, Size>
			{};
		};

		template<typename Container, typename = void>
		struct inherit_default_rebind_type {};
		template<typename Container>
		struct inherit_default_rebind_type<
			Container,
			typename std::enable_if<sprout::detail::is_array_like<Container>::value>::type
		> {
		public:
			template<typename Type>
			struct rebind_type
				: public sprout::detail::default_array_rebind_type<Container, Type>
			{};
		};
	}	// namespace detail

	template<typename Container>
	struct container_transform_traits
		: public sprout::detail::inherit_default_rebind_size<Container>
		, public sprout::detail::inherit_default_rebind_type<Container>
	{};
	template<typename Container>
	struct container_transform_traits<Container const> {
	public:
		template<typename sprout::container_traits<Container>::size_type Size>
		struct rebind_size {
			typedef typename sprout::container_transform_traits<Container>::template rebind_size<Size>::type const type;
		};
		template<typename Type>
		struct rebind_type {
			typedef typename sprout::container_transform_traits<Container>::template rebind_type<Type>::type const type;
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
		template<typename Type>
		struct rebind_type {
		public:
			typedef Type type[N];
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
		template<typename Type>
		struct rebind_type {
		public:
			typedef Type type[N];
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_TRANSFORM_TRAITS_HPP
