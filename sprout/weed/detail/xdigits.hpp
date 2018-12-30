/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
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
#include <sprout/detail/literal_def.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			SPROUT_LITERAL_STRING_DEF(xdigits, "0123456789abcdefABCDEF", 22);

			template<typename Dummy, typename X = void>
			struct xvalues;

#		define SPROUT_WEED_XDIGITS_TABLE_DEF \
			{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 10, 11, 12, 13, 14, 15}}

			template<typename X>
			struct xvalues<void, X> {
			public:
				typedef sprout::array<std::uint8_t, 22> value_type;
			public:
				SPROUT_STATIC_CONSTEXPR value_type value
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_WEED_XDIGITS_TABLE_DEF)
					;
			};
			template<typename X>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::weed::detail::xvalues<void, X>::value_type
			sprout::weed::detail::xvalues<void, X>::value
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_WEED_XDIGITS_TABLE_DEF)
				;

#		undef SPROUT_WEED_XDIGITS_TABLE_DEF

			template<typename IntType>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> xvalue_at(std::size_t i) {
				return i < 22
					? sprout::tuples::tuple<IntType, bool>(
						static_cast<IntType>(sprout::weed::detail::xvalues<void>::value[i]),
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
						sprout::weed::detail::xdigits<Elem>::value.begin(),
						sprout::find(
							sprout::weed::detail::xdigits<Elem>::value.begin(),
							sprout::weed::detail::xdigits<Elem>::value.end(),
							c
							)
						)
					);
			}
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_XDIGITS_HPP
