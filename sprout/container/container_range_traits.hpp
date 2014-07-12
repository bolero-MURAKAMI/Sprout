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
			typename std::enable_if<sprout::detail::has_mem_size<Container const>::value>::type
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
			typename std::enable_if<!sprout::detail::has_mem_size<Container const>::value>::type
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
			typename std::enable_if<sprout::detail::has_mem_empty<Container const>::value>::type
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
			typename std::enable_if<!sprout::detail::has_mem_empty<Container const>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR bool
			range_empty(Container const& cont) {
				return sprout::size(cont) == 0;
			}
		};

		template<typename T>
		struct has_mem_front_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().front())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_front_test<T>::test(0))>::type>
		struct has_mem_front
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_front
			: public sprout::identity<decltype(sprout::detail::has_mem_front_test<T>::test(0))>::type
		{};
#endif

		template<typename Container, typename = void>
		struct container_range_traits_range_front_impl;
		template<typename Container>
		struct container_range_traits_range_front_impl<
			Container,
			typename std::enable_if<sprout::detail::has_mem_front<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_front(Container& cont) {
				return cont.front();
			}
		};
		template<typename Container>
		struct container_range_traits_range_front_impl<
			Container,
			typename std::enable_if<!sprout::detail::has_mem_front<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_front(Container& cont) {
				return *sprout::begin(cont);
			}
		};

		template<typename Container, typename = void>
		struct container_range_traits_range_front_const_impl;
		template<typename Container>
		struct container_range_traits_range_front_const_impl<
			Container,
			typename std::enable_if<sprout::detail::has_mem_front<Container const>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_front(Container const& cont) {
				return cont.front();
			}
		};
		template<typename Container>
		struct container_range_traits_range_front_const_impl<
			Container,
			typename std::enable_if<!sprout::detail::has_mem_front<Container const>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_front(Container const& cont) {
				return *sprout::begin(cont);
			}
		};

		template<typename T>
		struct has_mem_back_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().back())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_back_test<T>::test(0))>::type>
		struct has_mem_back
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_back
			: public sprout::identity<decltype(sprout::detail::has_mem_back_test<T>::test(0))>::type
		{};
#endif

		template<typename Container, typename = void>
		struct container_range_traits_range_back_impl;
		template<typename Container>
		struct container_range_traits_range_back_impl<
			Container,
			typename std::enable_if<sprout::detail::has_mem_back<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_back(Container& cont) {
				return cont.back();
			}
		};
		template<typename Container>
		struct container_range_traits_range_back_impl<
			Container,
			typename std::enable_if<!sprout::detail::has_mem_back<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_back(Container& cont) {
				return *sprout::prev(sprout::end(cont));
			}
		};

		template<typename Container, typename = void>
		struct container_range_traits_range_back_const_impl;
		template<typename Container>
		struct container_range_traits_range_back_const_impl<
			Container,
			typename std::enable_if<sprout::detail::has_mem_back<Container const>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_back(Container const& cont) {
				return cont.back();
			}
		};
		template<typename Container>
		struct container_range_traits_range_back_const_impl<
			Container,
			typename std::enable_if<!sprout::detail::has_mem_back<Container const>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_back(Container const& cont) {
				return *sprout::prev(sprout::end(cont));
			}
		};

		template<typename T>
		struct has_mem_at_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().at(std::declval<typename sprout::container_traits<U>::size_type>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_at_test<T>::test(0))>::type>
		struct has_mem_at
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_at
			: public sprout::identity<decltype(sprout::detail::has_mem_at_test<T>::test(0))>::type
		{};
#endif

		template<typename Container, typename = void>
		struct container_range_traits_range_at_impl;
		template<typename Container>
		struct container_range_traits_range_at_impl<
			Container,
			typename std::enable_if<sprout::detail::has_mem_at<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
				return cont.at(i);
			}
		};
		template<typename Container>
		struct container_range_traits_range_at_impl<
			Container,
			typename std::enable_if<!sprout::detail::has_mem_at<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
				return *sprout::next(sprout::begin(cont), i);
			}
		};

		template<typename Container, typename = void>
		struct container_range_traits_range_at_const_impl;
		template<typename Container>
		struct container_range_traits_range_at_const_impl<
			Container,
			typename std::enable_if<sprout::detail::has_mem_at<Container const>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				return cont.at(i);
			}
		};
		template<typename Container>
		struct container_range_traits_range_at_const_impl<
			Container,
			typename std::enable_if<!sprout::detail::has_mem_at<Container const>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				return *sprout::next(sprout::begin(cont), i);
			}
		};
	}	// namespace detail

	template<typename Container>
	struct container_range_traits
		: public sprout::detail::container_range_traits_range_size_impl<Container>
		, public sprout::detail::container_range_traits_range_empty_impl<Container>
		, public sprout::detail::container_range_traits_range_front_impl<Container>
		, public sprout::detail::container_range_traits_range_front_const_impl<Container>
		, public sprout::detail::container_range_traits_range_back_impl<Container>
		, public sprout::detail::container_range_traits_range_back_const_impl<Container>
		, public sprout::detail::container_range_traits_range_at_impl<Container>
		, public sprout::detail::container_range_traits_range_at_const_impl<Container>
	{
		using sprout::detail::container_range_traits_range_front_impl<Container>::range_front;
		using sprout::detail::container_range_traits_range_front_const_impl<Container>::range_front;
		using sprout::detail::container_range_traits_range_back_impl<Container>::range_back;
		using sprout::detail::container_range_traits_range_back_const_impl<Container>::range_back;
		using sprout::detail::container_range_traits_range_at_impl<Container>::range_at;
		using sprout::detail::container_range_traits_range_at_const_impl<Container>::range_at;
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
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
		range_data(Container& cont) {
			return cont.data();
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
		range_data(Container const& cont) {
			return cont.data();
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
		// element access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_front(Container const& cont) {
			return sprout::container_range_traits<Container>::range_front(cont);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_back(Container const& cont) {
			return sprout::container_range_traits<Container>::range_back(cont);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return sprout::container_range_traits<Container>::range_at(cont, i);
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
		range_data(Container const& cont) {
			return sprout::container_range_traits<Container>::range_data(cont);
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
		// element access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_front(T (& arr)[N]) {
			return arr[0];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_front(T const (& arr)[N]) {
			return arr[0];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_back(T (& arr)[N]) {
			return arr[N - 1];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_back(T const (& arr)[N]) {
			return arr[N - 1];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_at(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
			return arr[i];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return arr[i];
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::pointer
		range_data(T (& arr)[N]) {
			return &arr[0];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::pointer
		range_data(T const (& arr)[N]) {
			return &arr[0];
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
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
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
		// element access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_front(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_front(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_back(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_back(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return sprout::container_range_traits<T[N]>::range_at(arr, i);
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::pointer
		range_data(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_data(arr);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
