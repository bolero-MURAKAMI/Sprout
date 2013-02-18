#ifndef SPROUT_WEED_DETAIL_BDIGITS_HPP
#define SPROUT_WEED_DETAIL_BDIGITS_HPP

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
			struct bdigits;

			template<>
			struct bdigits<char> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char, 2> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string("01"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char, 2> sprout::weed::detail::bdigits<char>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string("01"))
				;

			template<>
			struct bdigits<wchar_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<wchar_t, 2> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(L"01"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<wchar_t, 2> sprout::weed::detail::bdigits<wchar_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(L"01"))
				;

#if SPROUT_USE_UNICODE_LITERALS
			template<>
			struct bdigits<char16_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char16_t, 2> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(u"01"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char16_t, 2> sprout::weed::detail::bdigits<char16_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(u"01"))
				;

			template<>
			struct bdigits<char32_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char32_t, 2> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(U"01"))
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char32_t, 2> sprout::weed::detail::bdigits<char32_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(U"01"))
				;
#endif

			template<typename Dummy>
			struct bvalues;

#		define SPROUT_WEED_BDIGITS_TABLE_DEF \
			table_type{{0, 1}}

			template<>
			struct bvalues<void> {
			public:
				typedef sprout::array<std::uint8_t, 2> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_WEED_BDIGITS_TABLE_DEF)
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::weed::detail::bvalues<void>::table_type
			sprout::weed::detail::bvalues<void>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_WEED_BDIGITS_TABLE_DEF)
				;

#		undef SPROUT_WEED_BDIGITS_TABLE_DEF

			template<typename IntType>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> bvalue_at(std::size_t i) {
				return i < 2
					? sprout::tuples::tuple<IntType, bool>(
						static_cast<IntType>(sprout::weed::detail::bvalues<void>::table[i]),
						true
						)
					: sprout::tuples::tuple<IntType, bool>(
						IntType(),
						false
						)
					;
			}
			template<typename IntType, typename Elem>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_bdigit(Elem c) {
				return sprout::weed::detail::bvalue_at<IntType>(
					sprout::distance(
						sprout::weed::detail::bdigits<Elem>::table.begin(),
						sprout::find(
							sprout::weed::detail::bdigits<Elem>::table.begin(),
							sprout::weed::detail::bdigits<Elem>::table.end(),
							c
							)
						)
					);
			}
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_BDIGITS_HPP
