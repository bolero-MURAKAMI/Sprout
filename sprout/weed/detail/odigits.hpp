#ifndef SPROUT_WEED_DETAIL_ODIGITS_HPP
#define SPROUT_WEED_DETAIL_ODIGITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/array.hpp>
#include <sprout/tuple/tuple.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename Elem>
			struct odigits;

			template<>
			struct odigits<char> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char, 8> table = sprout::to_string("01234567");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char, 8> sprout::weed::detail::odigits<char>::table;

			template<>
			struct odigits<wchar_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<wchar_t, 8> table = sprout::to_string(L"01234567");
			};
			SPROUT_CONSTEXPR sprout::basic_string<wchar_t, 8> sprout::weed::detail::odigits<wchar_t>::table;

			template<>
			struct odigits<char16_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char16_t, 8> table = sprout::to_string(u"01234567");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char16_t, 8> sprout::weed::detail::odigits<char16_t>::table;

			template<>
			struct odigits<char32_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char32_t, 8> table = sprout::to_string(U"01234567");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char32_t, 8> sprout::weed::detail::odigits<char32_t>::table;

			template<typename Dummy>
			struct ovalues;

			template<>
			struct ovalues<void> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::array<std::uint8_t, 8> table = sprout::array<std::uint8_t, 8>{
					{0, 1, 2, 3, 4, 5, 6, 7}
					};
			};
			SPROUT_CONSTEXPR sprout::array<std::uint8_t, 8> sprout::weed::detail::ovalues<void>::table;

			template<typename IntType>
			SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> ovalue_at(std::size_t i) {
				return i < 8
					? sprout::tuples::tuple<IntType, bool>(
						static_cast<IntType>(sprout::weed::detail::ovalues<void>::table[i]),
						true
						)
					: sprout::tuples::tuple<IntType, bool>(
						IntType(),
						false
						)
					;
			}
			template<typename IntType, typename Elem>
			SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_odigit(Elem c) {
				return sprout::weed::detail::ovalue_at<IntType>(
					NS_SSCRISK_CEL_OR_SPROUT::distance(
						sprout::weed::detail::odigits<Elem>::table.begin(),
						NS_SSCRISK_CEL_OR_SPROUT::find(
							sprout::weed::detail::odigits<Elem>::table.begin(),
							sprout::weed::detail::odigits<Elem>::table.end(),
							c
							)
						)
					);
			}
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_ODIGITS_HPP
