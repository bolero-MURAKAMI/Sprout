/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_DETAIL_RANGE_BEGIN_HPP
#define SPROUT_CONTAINER_DETAIL_RANGE_BEGIN_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/is_within_namespace_sprout.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/range_functions_fwd.hpp>
#include <sprout/iterator/const_iterator_cast.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl begin(...);
	sprout::not_found_via_adl range_begin(...);
}	// namespace sprout_adl

namespace sprout_container_range_detail {
	using sprout_adl::begin;

	template<typename T>
	struct has_adl_begin_test {
	public:
		template<
			typename U = T,
			typename R = typename sprout::identity<decltype(begin(std::declval<U>()))>::type
		>
		static sprout::is_found_via_adl<R> test(int);
		static sprout::false_type test(...);
	};

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_adl_begin(Container& cont) {
		return begin(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_adl_begin(Container const& cont) {
		return begin(cont);
	}
}	// namespace sprout_container_range_detail

namespace sprout {
	namespace detail {
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout_container_range_detail::has_adl_begin_test<T>::test(0))>::type>
		struct has_adl_begin
			: public Base_
		{};
#else
		template<typename T>
		struct has_adl_begin
			: public sprout::identity<decltype(sprout_container_range_detail::has_adl_begin_test<T>::test(0))>::type
		{};
#endif
		template<typename T, bool = sprout::is_within_namespace_sprout<T>::value>
		struct has_adl_begin_without_sprout
			: public sprout::false_type
		{};
		template<typename T>
		struct has_adl_begin_without_sprout<T, false>
			: public sprout::detail::has_adl_begin<T>
		{};

		template<typename T>
		struct has_mem_begin_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().begin())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_begin_test<T>::test(0))>::type>
		struct has_mem_begin
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_begin
			: public sprout::identity<decltype(sprout::detail::has_mem_begin_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_begin
			: public sprout::bool_constant<
				sprout::is_const_iterator_cast_convertible<
					typename sprout::container_traits<T const>::iterator,
					typename sprout::container_traits<T>::iterator
				>::value
				&& (
					sprout::detail::has_mem_begin<T const>::value
						|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_begin<Container>::value,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_begin_impl(Container& cont) {
			typedef typename sprout::container_traits<Container>::iterator type;
			return sprout::const_iterator_cast<type>(sprout::begin(sprout::as_const(cont)));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_begin<Container>::value
				&& sprout::detail::has_mem_begin<Container>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_begin_impl(Container& cont) {
			return cont.begin();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_begin<Container>::value
				&& !sprout::detail::has_mem_begin<Container>::value
				&& sprout::detail::has_adl_begin_without_sprout<Container&>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_begin_impl(Container& cont) {
			return sprout_container_range_detail::range_adl_begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_begin<Container>::value
				&& !sprout::detail::has_mem_begin<Container>::value
				&& !sprout::detail::has_adl_begin_without_sprout<Container&>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_begin_impl(Container& cont) {
			return std::begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_begin<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_begin_impl(Container const& cont) {
			return cont.begin();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_begin<Container const>::value
				&& sprout::detail::has_adl_begin_without_sprout<Container const&>::value
				,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_begin_impl(Container const& cont) {
			return sprout_container_range_detail::range_adl_begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_begin<Container const>::value
				&& !sprout::detail::has_adl_begin_without_sprout<Container const&>::value
				,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_begin_impl(Container const& cont) {
			return std::begin(cont);
		}
	}	// namespace detail
}	// namespace sprout

namespace sprout_container_range_detail {
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_begin(Container& cont) {
		return sprout::detail::range_begin_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_begin(Container const& cont) {
		return sprout::detail::range_begin_impl(cont);
	}
}	// namespace sprout_container_range_detail

#endif	// #ifndef SPROUT_CONTAINER_DETAIL_RANGE_BEGIN_HPP
