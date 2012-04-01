#ifndef SPROUT_WEED_DETAIL_DIGITS_HPP
#define SPROUT_WEED_DETAIL_DIGITS_HPP

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
			struct digits;

			template<>
			struct digits<char> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char, 10> table = sprout::to_string("0123456789");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char, 10> sprout::weed::detail::digits<char>::table;

			template<>
			struct digits<wchar_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<wchar_t, 10> table = sprout::to_string(L"0123456789");
			};
			SPROUT_CONSTEXPR sprout::basic_string<wchar_t, 10> sprout::weed::detail::digits<wchar_t>::table;

			template<>
			struct digits<char16_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char16_t, 10> table = sprout::to_string(u"0123456789");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char16_t, 10> sprout::weed::detail::digits<char16_t>::table;

			template<>
			struct digits<char32_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char32_t, 10> table = sprout::to_string(U"0123456789");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char32_t, 10> sprout::weed::detail::digits<char32_t>::table;

			template<typename Dummy>
			struct values;

			template<>
			struct values<void> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::array<std::uint8_t, 10> table = sprout::array<std::uint8_t, 10>{
					{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
					};
			};
			SPROUT_CONSTEXPR sprout::array<std::uint8_t, 10> sprout::weed::detail::values<void>::table;

			template<typename IntType>
			SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> value_at(std::size_t i) {
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
			SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_digit(Elem c) {
				return sprout::weed::detail::value_at<IntType>(
					NS_SSCRISK_CEL_OR_SPROUT::distance(
						sprout::weed::detail::digits<Elem>::table.begin(),
						NS_SSCRISK_CEL_OR_SPROUT::find(
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
