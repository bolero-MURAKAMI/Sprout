/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_DETAIL_RANGE_DATA_HPP
#define SPROUT_CONTAINER_DETAIL_RANGE_DATA_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/is_const_cast_convertible.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_data(...);
}	// namespace sprout_adl

namespace sprout {
	namespace detail {
		template<typename T>
		struct has_mem_data_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().data())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_data_test<T>::test(0))>::type>
		struct has_mem_data
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_data
			: public sprout::identity<decltype(sprout::detail::has_mem_data_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_data
			: public sprout::bool_constant<
				sprout::is_const_cast_convertible<
					typename sprout::container_traits<T const>::pointer,
					typename sprout::container_traits<T>::pointer
				>::value
				&& sprout::detail::has_mem_data<T const>::value
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_data<Container>::value,
			typename sprout::container_traits<Container>::pointer
		>::type
		range_data_impl(Container& cont) {
			typedef typename sprout::container_traits<Container>::pointer type;
			return const_cast<type>(sprout::data(sprout::as_const(cont)));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_data<Container>::value,
			typename sprout::container_traits<Container>::pointer
		>::type
		range_data_impl(Container& cont) {
			return cont.data();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
		range_data_impl(Container const& cont) {
			return cont.data();
		}
	}	// namespace detail
}	// namespace sprout

namespace sprout_container_range_detail {
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
	range_data(Container& cont) {
		return sprout::detail::range_data_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
	range_data(Container const& cont) {
		return sprout::detail::range_data_impl(cont);
	}
}	// namespace sprout_container_range_detail

#endif	// #ifndef SPROUT_CONTAINER_DETAIL_RANGE_DATA_HPP
