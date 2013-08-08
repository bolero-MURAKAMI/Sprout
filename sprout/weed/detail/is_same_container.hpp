/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_DETAIL_IS_SAME_CONTAINER_HPP
#define SPROUT_WEED_DETAIL_IS_SAME_CONTAINER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/traits/type/is_container.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename T, typename U, typename = void>
			struct is_same_container
				: public std::false_type
			{};
			template<typename T, typename U>
			struct is_same_container<
				T,
				U,
				typename std::enable_if<
					sprout::weed::traits::is_container<T>::value
					&& sprout::weed::traits::is_container<U>::value
					&& std::is_same<
						typename T::value_type,
						typename U::value_type
					>::value
				>::type
			>
				: public std::true_type
			{};
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_IS_SAME_CONTAINER_HPP
