#ifndef SPROUT_WEED_DETAIL_BDIGITS_HPP
#define SPROUT_WEED_DETAIL_BDIGITS_HPP

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
			struct bdigits;

			template<>
			struct bdigits<char> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char, 2> table = sprout::to_string("01");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char, 2> sprout::weed::detail::bdigits<char>::table;

			template<>
			struct bdigits<wchar_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<wchar_t, 2> table = sprout::to_string(L"01");
			};
			SPROUT_CONSTEXPR sprout::basic_string<wchar_t, 2> sprout::weed::detail::bdigits<wchar_t>::table;

			template<>
			struct bdigits<char16_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char16_t, 2> table = sprout::to_string(u"01");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char16_t, 2> sprout::weed::detail::bdigits<char16_t>::table;

			template<>
			struct bdigits<char32_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char32_t, 2> table = sprout::to_string(U"01");
			};
			SPROUT_CONSTEXPR sprout::basic_string<char32_t, 2> sprout::weed::detail::bdigits<char32_t>::table;

			template<typename Dummy>
			struct bvalues;

			template<>
			struct bvalues<void> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::array<std::uint8_t, 2> table = sprout::array<std::uint8_t, 2>{
					{0, 1}
					};
			};
			SPROUT_CONSTEXPR sprout::array<std::uint8_t, 2> sprout::weed::detail::bvalues<void>::table;

			template<typename IntType>
			SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> bvalue_at(std::size_t i) {
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
			SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_bdigit(Elem c) {
				return sprout::weed::detail::bvalue_at<IntType>(
					NS_SSCRISK_CEL_OR_SPROUT::distance(
						sprout::weed::detail::bdigits<Elem>::table.begin(),
						NS_SSCRISK_CEL_OR_SPROUT::find(
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
