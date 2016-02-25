/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_TRAITS_TYPE_IS_UNUSED_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_UNUSED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/weed/unused.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_unused
			//
			template<typename T>
			struct is_unused
				: public sprout::false_type
			{};
			template<typename T>
			struct is_unused<T const>
				: public sprout::weed::traits::is_unused<T>
			{};
			template<typename T>
			struct is_unused<T volatile>
				: public sprout::weed::traits::is_unused<T>
			{};
			template<typename T>
			struct is_unused<T const volatile>
				: public sprout::weed::traits::is_unused<T>
			{};
			template<>
			struct is_unused<sprout::weed::unused>
				: public sprout::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_UNUSED_HPP
