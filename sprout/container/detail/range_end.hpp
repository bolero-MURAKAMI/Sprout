/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_DETAIL_RANGE_END_HPP
#define SPROUT_CONTAINER_DETAIL_RANGE_END_HPP

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
	sprout::not_found_via_adl end(...);
	sprout::not_found_via_adl range_end(...);
}	// namespace sprout_adl

namespace sprout_container_range_detail {
	using sprout_adl::end;

	template<typename T>
	struct has_adl_end_test {
	public:
		template<
			typename U = T,
			typename R = typename sprout::identity<decltype(end(std::declval<U>()))>::type
		>
		static sprout::is_found_via_adl<R> test(int);
		static sprout::false_type test(...);
	};

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_adl_end(Container& cont) {
		return end(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_adl_end(Container const& cont) {
		return end(cont);
	}
}	// namespace sprout_container_range_detail

namespace sprout {
	namespace detail {
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout_container_range_detail::has_adl_end_test<T>::test(0))>::type>
		struct has_adl_end
			: public Base_
		{};
#else
		template<typename T>
		struct has_adl_end
			: public sprout::identity<decltype(sprout_container_range_detail::has_adl_end_test<T>::test(0))>::type
		{};
#endif
		template<typename T, bool = sprout::is_within_namespace_sprout<T>::value>
		struct has_adl_end_without_sprout
			: public sprout::false_type
		{};
		template<typename T>
		struct has_adl_end_without_sprout<T, false>
			: public sprout::detail::has_adl_end<T>
		{};

		template<typename T>
		struct has_mem_end_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().end())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_end_test<T>::test(0))>::type>
		struct has_mem_end
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_end
			: public sprout::identity<decltype(sprout::detail::has_mem_end_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_end
			: public sprout::bool_constant<
				sprout::is_const_iterator_cast_convertible<
					typename sprout::container_traits<T const>::iterator,
					typename sprout::container_traits<T>::iterator
				>::value
				&& (
					sprout::detail::has_mem_end<T const>::value
						|| sprout::detail::has_adl_end_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_end<Container>::value,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_end_impl(Container& cont) {
			typedef typename sprout::container_traits<Container>::iterator type;
			return sprout::const_iterator_cast<type>(sprout::end(sprout::as_const(cont)));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_end<Container>::value
				&& sprout::detail::has_mem_end<Container>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_end_impl(Container& cont) {
			return cont.end();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_end<Container>::value
				&& !sprout::detail::has_mem_end<Container>::value
				&& sprout::detail::has_adl_end_without_sprout<Container&>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_end_impl(Container& cont) {
			return sprout_container_range_detail::range_adl_end(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_end<Container>::value
				&& !sprout::detail::has_mem_end<Container>::value
				&& !sprout::detail::has_adl_end_without_sprout<Container&>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_end_impl(Container& cont) {
			return std::end(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_end<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_end_impl(Container const& cont) {
			return cont.end();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_end<Container const>::value
				&& sprout::detail::has_adl_end_without_sprout<Container const&>::value
				,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_end_impl(Container const& cont) {
			return sprout_container_range_detail::range_adl_end(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_end<Container const>::value
				&& !sprout::detail::has_adl_end_without_sprout<Container const&>::value
				,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_end_impl(Container const& cont) {
			return std::end(cont);
		}
	}	// namespace detail
}	// namespace sprout

namespace sprout_container_range_detail {
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_end(Container& cont) {
		return sprout::detail::range_end_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_end(Container const& cont) {
		return sprout::detail::range_end_impl(cont);
	}
}	// namespace sprout_container_range_detail

#endif	// #ifndef SPROUT_CONTAINER_DETAIL_RANGE_END_HPP
