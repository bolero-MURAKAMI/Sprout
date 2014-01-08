/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_DETAIL_DIGITS_HPP
#define SPROUT_WEED_DETAIL_DIGITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/array/array.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/find.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename Elem>
			struct digits;

			template<>
			struct digits<char> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char, 10> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string("0123456789"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char, 10> sprout::weed::detail::digits<char>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string("0123456789"))
				;

			template<>
			struct digits<wchar_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<wchar_t, 10> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(L"0123456789"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<wchar_t, 10> sprout::weed::detail::digits<wchar_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(L"0123456789"))
				;

#if SPROUT_USE_UNICODE_LITERALS
			template<>
			struct digits<char16_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char16_t, 10> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(u"0123456789"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char16_t, 10> sprout::weed::detail::digits<char16_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(u"0123456789"))
				;

			template<>
			struct digits<char32_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char32_t, 10> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(U"0123456789"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char32_t, 10> sprout::weed::detail::digits<char32_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(U"0123456789"))
				;
#endif

			template<typename Dummy>
			struct values;

#		define SPROUT_WEED_DIGITS_TABLE_DEF \
			table_type{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}}

			template<>
			struct values<void> {
			public:
				typedef sprout::array<std::uint8_t, 10> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_WEED_DIGITS_TABLE_DEF)
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::weed::detail::values<void>::table_type
			sprout::weed::detail::values<void>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_WEED_DIGITS_TABLE_DEF)
				;

#		undef SPROUT_WEED_DIGITS_TABLE_DEF

			template<typename IntType>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> value_at(std::size_t i) {
				return i < 10
					? sprout::tuples::tuple<IntType, bool>(
						static_cast<IntType>(sprout::weed::detail::values<void>::table[i]),
						true
						)
					: sprout::tuples::tuple<IntType, bool>(
						IntType(),
						false
						)
					;
			}
			template<typename IntType, typename Elem>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_digit(Elem c) {
				return sprout::weed::detail::value_at<IntType>(
					sprout::distance(
						sprout::weed::detail::digits<Elem>::table.begin(),
						sprout::find(
							sprout::weed::detail::digits<Elem>::table.begin(),
							sprout::weed::detail::digits<Elem>::table.end(),
							c
							)
						)
					);
			}
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_DIGITS_HPP
