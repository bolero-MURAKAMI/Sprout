/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_DETAIL_RANGE_INDEX_OF_HPP
#define SPROUT_CONTAINER_DETAIL_RANGE_INDEX_OF_HPP

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
	sprout::not_found_via_adl range_index_of(...);
}	// namespace sprout_adl

namespace sprout {
	namespace detail {
		template<typename T>
		struct has_mem_index_of_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().index_of(std::declval<typename sprout::container_traits<U>::iterator>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_index_of_test<T>::test(0))>::type>
		struct has_mem_index_of
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_index_of
			: public sprout::identity<decltype(sprout::detail::has_mem_index_of_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_index_of
			: public sprout::bool_constant<
				sprout::is_const_iterator_cast_convertible<
					typename sprout::container_traits<T const>::iterator,
					typename sprout::container_traits<T>::iterator
				>::value
				&& (
					sprout::detail::has_mem_index_of<T const>::value
					|| sprout::detail::has_mem_begin<T const>::value
					|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_index_of<Container>::value,
			typename sprout::container_traits<Container>::size_type
		>::type
		range_index_of_impl(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			typedef typename sprout::container_traits<Container>::iterator type;
			return sprout::index_of(sprout::as_const(cont), sprout::const_iterator_cast<type>(p));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_index_of<Container>::value
				&& sprout::detail::has_mem_index_of<Container>::value
				,
			typename sprout::container_traits<Container>::size_type
		>::type
		range_index_of_impl(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			return cont.index_of(p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_index_of<Container>::value
				&& !sprout::detail::has_mem_index_of<Container>::value
				,
			typename sprout::container_traits<Container>::size_type
		>::type
		range_index_of_impl(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			return sprout::distance(sprout::begin(cont), p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_index_of<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_index_of_impl(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
			return cont.index_of(p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_index_of<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_index_of_impl(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
			return sprout::distance(sprout::begin(cont), p);
		}
	}	// namespace detail
}	// namespace sprout

namespace sprout_container_range_detail {
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
	range_index_of(Container& cont, typename sprout::container_traits<Container>::iterator p) {
		return sprout::detail::range_index_of_impl(cont, p);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	range_index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
		return sprout::detail::range_index_of_impl(cont, p);
	}
}	// namespace sprout_container_range_detail

#endif	// #ifndef SPROUT_CONTAINER_DETAIL_RANGE_INDEX_OF_HPP
