/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_DETAIL_TABLE_HPP
#define SPROUT_UUID_DETAIL_TABLE_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/string.hpp>
#include <sprout/detail/literal_def.hpp>

namespace sprout {
	namespace uuids {
		namespace detail {
			SPROUT_LITERAL_STRING_DEF(digits, "0123456789abcdefABCDEF", 22);
			SPROUT_LITERAL_CHAR_DEF(dash, '-');
			SPROUT_LITERAL_CHAR_DEF(lbrace, '{');
			SPROUT_LITERAL_CHAR_DEF(rbrace, '}');

			template<typename Dummy, typename X = void>
			struct values;

#		define SPROUT_UUID_TABLE_DEF \
			{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 10, 11, 12, 13, 14, 15}}

			template<typename X>
			struct values<void, X> {
			public:
				typedef sprout::array<std::uint8_t, 22> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_UUID_TABLE_DEF)
					;
			};
			template<typename X>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::uuids::detail::values<void, X>::table_type
			sprout::uuids::detail::values<void, X>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_UUID_TABLE_DEF)
				;

#		undef SPROUT_UUID_TABLE_DEF
		}	// namespace detail
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_DETAIL_TABLE_HPP
