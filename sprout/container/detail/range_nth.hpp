/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_DETAIL_RANGE_NTH_HPP
#define SPROUT_CONTAINER_DETAIL_RANGE_NTH_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/range_functions_fwd.hpp>
#include <sprout/container/detail/range_begin.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/const_iterator_cast.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_nth(...);
}	// namespace sprout_adl

namespace sprout {
	namespace detail {
		template<typename T>
		struct has_mem_nth_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().nth(std::declval<typename sprout::container_traits<U>::size_type>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_nth_test<T>::test(0))>::type>
		struct has_mem_nth
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_nth
			: public sprout::identity<decltype(sprout::detail::has_mem_nth_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_nth
			: public sprout::bool_constant<
				sprout::is_const_iterator_cast_convertible<
					typename sprout::container_traits<T const>::iterator,
					typename sprout::container_traits<T>::iterator
				>::value
				&& (
					sprout::detail::has_mem_nth<T const>::value
					|| sprout::detail::has_mem_begin<T const>::value
					|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_nth<Container>::value,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_nth_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			typedef typename sprout::container_traits<Container>::iterator type;
			return sprout::const_iterator_cast<type>(sprout::nth(sprout::as_const(cont), i));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_nth<Container>::value
				&& sprout::detail::has_mem_nth<Container>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_nth_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return cont.nth(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_nth<Container>::value
				&& !sprout::detail::has_mem_nth<Container>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_nth_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return sprout::next(sprout::begin(cont), i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_nth<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_nth_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return cont.nth(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_nth<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_nth_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return sprout::next(sprout::begin(cont), i);
		}
	}	// namespace detail
}	// namespace sprout

namespace sprout_container_range_detail {
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_nth(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		return sprout::detail::range_nth_impl(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::detail::range_nth_impl(cont, i);
	}
}	// namespace sprout_container_range_detail

#endif	// #ifndef SPROUT_CONTAINER_DETAIL_RANGE_NTH_HPP
