/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_DETAIL_C_STR_AS_STRING_HPP
#define SPROUT_WEED_DETAIL_C_STR_AS_STRING_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type/void.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename T>
			struct c_str_as_string
				: public sprout::identity<sprout::types::void_>
			{};
			template<typename T>
			struct c_str_as_string<T const>
				: public sprout::weed::detail::c_str_as_string<T>
			{};
			template<typename T>
			struct c_str_as_string<T volatile>
				: public sprout::weed::detail::c_str_as_string<T>
			{};
			template<typename T>
			struct c_str_as_string<T const volatile>
				: public sprout::weed::detail::c_str_as_string<T>
			{};
			template<typename T, std::size_t N>
			struct c_str_as_string<T[N]>
				: public sprout::identity<sprout::basic_string<T, N - 1> >
			{};
			template<typename T, std::size_t N>
			struct c_str_as_string<T const[N]>
				: public sprout::identity<sprout::basic_string<T, N - 1> >
			{};
			template<typename T, std::size_t N>
			struct c_str_as_string<T volatile[N]>
				: public sprout::identity<sprout::basic_string<T, N - 1> >
			{};
			template<typename T, std::size_t N>
			struct c_str_as_string<T const volatile[N]>
				: public sprout::identity<sprout::basic_string<T, N - 1> >
			{};
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_C_STR_AS_STRING_HPP
