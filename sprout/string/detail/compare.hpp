/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_DETAIL_COMPARE_HPP
#define SPROUT_STRING_DETAIL_COMPARE_HPP

#include <sprout/config.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace string_detail {
		template<typename String>
		static SPROUT_CONSTEXPR int
		compare_impl_1(
			int compared, typename String::size_type n1, typename String::size_type n2
			)
		{
			return compared != 0 ? compared
				: n1 < n2 ? -1
				: n2 < n1 ? 1
				: 0
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR int
		compare_impl(
			typename String::const_iterator data, typename String::size_type pos1, typename String::size_type n1,
			ConstIterator s, typename String::size_type n2
			)
		{
			return sprout::string_detail::compare_impl_1<String>(
				String::traits_type::compare(data + pos1, s, NS_SSCRISK_CEL_OR_SPROUT::min(n1, n2)),
				n1, n2
				);
		}
	}	// namespace string_detail
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_DETAIL_COMPARE_HPP
