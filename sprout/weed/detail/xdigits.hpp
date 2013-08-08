/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_DETAIL_XDIGITS_HPP
#define SPROUT_WEED_DETAIL_XDIGITS_HPP

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
			struct xdigits;

			template<>
			struct xdigits<char> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char, 22> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string("0123456789abcdefABCDEF"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char, 22> sprout::weed::detail::xdigits<char>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string("0123456789abcdefABCDEF"))
				;

			template<>
			struct xdigits<wchar_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<wchar_t, 22> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(L"0123456789abcdefABCDEF"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<wchar_t, 22> sprout::weed::detail::xdigits<wchar_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(L"0123456789abcdefABCDEF"))
				;

#if SPROUT_USE_UNICODE_LITERALS
			template<>
			struct xdigits<char16_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char16_t, 22> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(u"0123456789abcdefABCDEF"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char16_t, 22> sprout::weed::detail::xdigits<char16_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(u"0123456789abcdefABCDEF"))
				;

			template<>
			struct xdigits<char32_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char32_t, 22> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(U"0123456789abcdefABCDEF"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char32_t, 22> sprout::weed::detail::xdigits<char32_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(U"0123456789abcdefABCDEF"))
				;
#endif

			template<typename Dummy>
			struct xvalues;

#		define SPROUT_WEED_XDIGITS_TABLE_DEF \
			table_type{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 10, 11, 12, 13, 14, 15}}

			template<>
			struct xvalues<void> {
			public:
				typedef sprout::array<std::uint8_t, 22> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_WEED_XDIGITS_TABLE_DEF)
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::weed::detail::xvalues<void>::table_type
			sprout::weed::detail::xvalues<void>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_WEED_XDIGITS_TABLE_DEF)
				;

#		undef SPROUT_WEED_XDIGITS_TABLE_DEF

			template<typename IntType>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> xvalue_at(std::size_t i) {
				return i < 22
					? sprout::tuples::tuple<IntType, bool>(
						static_cast<IntType>(sprout::weed::detail::xvalues<void>::table[i]),
						true
						)
					: sprout::tuples::tuple<IntType, bool>(
						IntType(),
						false
						)
					;
			}
			template<typename IntType, typename Elem>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_xdigit(Elem c) {
				return sprout::weed::detail::xvalue_at<IntType>(
					sprout::distance(
						sprout::weed::detail::xdigits<Elem>::table.begin(),
						sprout::find(
							sprout::weed::detail::xdigits<Elem>::table.begin(),
							sprout::weed::detail::xdigits<Elem>::table.end(),
							c
							)
						)
					);
			}
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_XDIGITS_HPP
