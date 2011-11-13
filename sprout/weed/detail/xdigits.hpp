#ifndef SPROUT_WEED_DETAIL_XDIGITS_HPP
#define SPROUT_WEED_DETAIL_XDIGITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/array.hpp>
#include <sprout/tuple/tuple.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename Elem>
			struct xdigits;

			template<>
			struct xdigits<char> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char, 22> table = sprout::to_string("0123456789abcdefABCDEF");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char, 22> sprout::weed::detail::xdigits<char>::table;

			template<>
			struct xdigits<wchar_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<wchar_t, 22> table = sprout::to_string(L"0123456789abcdefABCDEF");
			};
			SPROUT_CONSTEXPR sprout::basic_string<wchar_t, 22> sprout::weed::detail::xdigits<wchar_t>::table;

			template<>
			struct xdigits<char16_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char16_t, 22> table = sprout::to_string(u"0123456789abcdefABCDEF");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char16_t, 22> sprout::weed::detail::xdigits<char16_t>::table;

			template<>
			struct xdigits<char32_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char32_t, 22> table = sprout::to_string(U"0123456789abcdefABCDEF");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char32_t, 22> sprout::weed::detail::xdigits<char32_t>::table;

			template<typename Dummy>
			struct xvalues;

			template<>
			struct xvalues<void> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::array<std::uint8_t, 22> table = sprout::array<std::uint8_t, 22>{
					{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 10, 11, 12, 13, 14, 15}
					};
			};
			SPROUT_CONSTEXPR sprout::array<std::uint8_t, 22> sprout::weed::detail::xvalues<void>::table;

			template<typename IntType>
			SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> xvalue_at(std::size_t i) {
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
			SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_xdigit(Elem c) {
				return sprout::weed::detail::xvalue_at<IntType>(
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(
						sprout::weed::detail::xdigits<Elem>::table.begin(),
						NS_SSCRISK_CEL_OR_SPROUT_DETAIL::find(
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
