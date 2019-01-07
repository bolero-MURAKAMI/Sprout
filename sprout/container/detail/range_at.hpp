/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_DETAIL_RANGE_AT_HPP
#define SPROUT_CONTAINER_DETAIL_RANGE_AT_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/range_functions_fwd.hpp>
#include <sprout/container/detail/range_begin.hpp>
#include <sprout/container/detail/range_subscript_at.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_at(...);
}	// namespace sprout_adl

namespace sprout {
	namespace detail {
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
#if defined(_MSC_VER) && (_MSC_VER > 1900)
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

		template<typename T>
		struct is_substitutable_const_at
			: public sprout::bool_constant<
				sprout::is_const_reference_cast_convertible<
					typename sprout::container_traits<T const>::reference,
					typename sprout::container_traits<T>::reference
				>::value
				&& (
					sprout::detail::has_mem_at<T const>::value
					|| sprout::detail::has_mem_subscript<T const>::value
					|| sprout::detail::has_mem_begin<T const>::value
					|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_at<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			typedef typename sprout::container_traits<Container>::reference type;
			return sprout::const_reference_cast<type>(sprout::at(sprout::as_const(cont), i));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_at<Container>::value
				&& sprout::detail::has_mem_at<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return cont.at(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_at<Container>::value
				&& !sprout::detail::has_mem_at<Container>::value
				&& sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return cont[sprout::range_index_check(cont, i)];
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_at<Container>::value
				&& !sprout::detail::has_mem_at<Container>::value
				&& !sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return *sprout::next(sprout::begin(cont), sprout::range_index_check(cont, i));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_at<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return cont.at(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_at<Container const>::value
				&& sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return cont[sprout::range_index_check(cont, i)];
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_at<Container const>::value
				&& !sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return *sprout::next(sprout::begin(cont), sprout::range_index_check(cont, i));
		}
	}	// namespace detail
}	// namespace sprout

namespace sprout_container_range_detail {
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	range_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		return sprout::detail::range_at_impl(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::detail::range_at_impl(cont, i);
	}
}	// namespace sprout_container_range_detail

#endif	// #ifndef SPROUT_CONTAINER_DETAIL_RANGE_AT_HPP
