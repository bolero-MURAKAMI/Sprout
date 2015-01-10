/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_TRAITS_TYPE_IS_CONTAINER_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_CONTAINER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/array/array.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_container
			//
			template<typename T>
			struct is_container
				: public sprout::false_type
			{};
			template<typename T>
			struct is_container<T const>
				: public sprout::weed::traits::is_container<T>
			{};
			template<typename T>
			struct is_container<T volatile>
				: public sprout::weed::traits::is_container<T>
			{};
			template<typename T>
			struct is_container<T const volatile>
				: public sprout::weed::traits::is_container<T>
			{};
			template<typename T, std::size_t N>
			struct is_container<sprout::array<T, N> >
				: public sprout::true_type
			{};
			template<typename T, std::size_t N, typename Traits>
			struct is_container<sprout::basic_string<T, N, Traits> >
				: public sprout::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_CONTAINER_HPP
