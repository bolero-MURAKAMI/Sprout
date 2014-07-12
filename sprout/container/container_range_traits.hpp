/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP

#include <utility>
#include <type_traits>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/range_functions_fwd.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/size.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	//
	// container_range_traits
	//
	namespace detail {
		template<typename T>
		struct has_mem_size_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().size())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_size_test<T>::test(0))>::type>
		struct has_mem_size
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_size
			: public sprout::identity<decltype(sprout::detail::has_mem_size_test<T>::test(0))>::type
		{};
#endif

		template<typename Container, typename = void>
		struct container_range_traits_range_size_impl;
		template<typename Container>
		struct container_range_traits_range_size_impl<
			Container,
			typename std::enable_if<sprout::detail::has_mem_size<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
			range_size(Container const& cont) {
				return cont.size();
			}
		};
		template<typename Container>
		struct container_range_traits_range_size_impl<
			Container,
			typename std::enable_if<!sprout::detail::has_mem_size<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
			range_size(Container const& cont) {
				return sprout::distance(sprout::begin(cont), sprout::end(cont));
			}
		};

		template<typename T>
		struct has_mem_empty_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().empty())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_empty_test<T>::test(0))>::type>
		struct has_mem_empty
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_empty
			: public sprout::identity<decltype(sprout::detail::has_mem_empty_test<T>::test(0))>::type
		{};
#endif

		template<typename Container, typename = void>
		struct container_range_traits_range_empty_impl;
		template<typename Container>
		struct container_range_traits_range_empty_impl<
			Container,
			typename std::enable_if<sprout::detail::has_mem_empty<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR bool
			range_empty(Container const& cont) {
				return cont.empty();
			}
		};
		template<typename Container>
		struct container_range_traits_range_empty_impl<
			Container,
			typename std::enable_if<!sprout::detail::has_mem_empty<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR bool
			range_empty(Container const& cont) {
				return sprout::size(cont) == 0;
			}
		};
	}	// namespace detail

	template<typename Container>
	struct container_range_traits
		: public sprout::detail::container_range_traits_range_size_impl<Container>
		, public sprout::detail::container_range_traits_range_empty_impl<Container>
	{
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_begin(Container& cont) {
			return cont.begin();
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_begin(Container const& cont) {
			return cont.begin();
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_end(Container& cont) {
			return cont.end();
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_end(Container const& cont) {
			return cont.end();
		}
	};
	template<typename Container>
	struct container_range_traits<Container const> {
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_begin(Container const& cont) {
			return sprout::container_range_traits<Container>::range_begin(cont);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_end(Container const& cont) {
			return sprout::container_range_traits<Container>::range_end(cont);
		}
		// capacity:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
		range_size(Container const& cont) {
			return sprout::container_range_traits<Container>::range_size(cont);
		}
		static SPROUT_CONSTEXPR bool
		range_empty(Container const& cont) {
			return sprout::container_range_traits<Container>::range_empty(cont);
		}
	};

	template<typename T, std::size_t N>
	struct container_range_traits<T[N]> {
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_begin(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_begin(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_end(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr) + N;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_end(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr) + N;
		}
		// capacity:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::size_type
		range_size(T const (&)[N]) {
			return N;
		}
		static SPROUT_CONSTEXPR bool
		range_empty(T const (&)[N]) {
			return false;
		}
	};
	template<typename T, std::size_t N>
	struct container_range_traits<T const[N]> {
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_begin(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_begin(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::const_iterator
		range_end(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_end(arr);
		}
		// capacity:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
		range_size(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_size(arr);
		}
		static SPROUT_CONSTEXPR bool
		range_empty(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_empty(arr);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
