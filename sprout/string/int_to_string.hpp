#ifndef SPROUT_STRING_INT_TO_STRING_HPP
#define SPROUT_STRING_INT_TO_STRING_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/string/string.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/detail/char_conversion.hpp>
#include <sprout/detail/int.hpp>

namespace sprout {
	//
	// printed_integer_digits
	//
	template<typename IntType, std::size_t Base = 10>
	struct printed_integer_digits
		: public std::integral_constant<
			std::size_t,
			sprout::integer_digits<IntType, Base>::value + (std::is_signed<IntType>::value ? 1 : 0)
		>
	{};

	namespace detail {
		template<
			typename Elem,
			int Base,
			typename IntType,
			sprout::index_t... Indexes,
			typename sprout::enabler_if<std::is_signed<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, Base>::value>
		int_to_string(IntType val, int digits, sprout::index_tuple<Indexes...>) {
			return val < 0 ? sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, Base>::value>{
					{
						static_cast<Elem>('-'),
						(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at<Base>(val, digits - 1 - Indexes))
							: Elem()
							)...
						},
						static_cast<std::size_t>(digits + 1)
					}
				: sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, Base>::value>{
					{
						(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at<Base>(val, digits - 1 - Indexes))
							: Elem()
							)...
						},
						static_cast<std::size_t>(digits)
					}
				;
		}
		template<
			typename Elem,
			int Base,
			typename IntType,
			sprout::index_t... Indexes,
			typename sprout::enabler_if<std::is_unsigned<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, Base>::value>
		int_to_string(IntType val, int digits, sprout::index_tuple<Indexes...>) {
			return sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, Base>::value>{
				{
					(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at<Base>(val, digits - 1 - Indexes))
						: Elem()
						)...
					},
					static_cast<std::size_t>(digits)
				};
		}
	}	// namespace detail

	//
	// int_to_string
	//
	template<
		typename Elem,
		int Base = 10,
		typename IntType,
		typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, Base>::value>
	int_to_string(IntType val) {
		return sprout::detail::int_to_string<Elem, Base>(
			val,
			sprout::detail::int_digits<Base>(val),
			sprout::index_range<0, sprout::integer_digits<IntType, Base>::value>::make()
			);
	}

	//
	// to_string_of
	//
	template<typename Elem, typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, 10>::value>
	to_string_of(IntType val) {
		return sprout::int_to_string<Elem, 10>(val);
	}

	//
	// to_string
	//
//	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_integer_digits<int>::value>
//	to_string(int val) {
//		return sprout::to_string_of<char>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_integer_digits<unsigned>::value>
//	to_string(unsigned val) {
//		return sprout::to_string_of<char>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_integer_digits<long>::value>
//	to_string(long val) {
//		return sprout::to_string_of<char>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_integer_digits<unsigned long>::value>
//	to_string(unsigned long val) {
//		return sprout::to_string_of<char>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_integer_digits<long long>::value>
//	to_string(long long val) {
//		return sprout::to_string_of<char>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_integer_digits<unsigned long long>::value>
//	to_string(unsigned long long val) {
//		return sprout::to_string_of<char>(val);
//	}
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_integer_digits<IntType>::value>
	to_string(IntType val) {
		return sprout::to_string_of<char>(val);
	}

	//
	// to_wstring
	//
//	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_integer_digits<int>::value>
//	to_wstring(int val) {
//		return sprout::to_string_of<wchar_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_integer_digits<unsigned>::value>
//	to_wstring(unsigned val) {
//		return sprout::to_string_of<wchar_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_integer_digits<long>::value>
//	to_wstring(long val) {
//		return sprout::to_string_of<wchar_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_integer_digits<unsigned long>::value>
//	to_wstring(unsigned long val) {
//		return sprout::to_string_of<wchar_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_integer_digits<long long>::value>
//	to_wstring(long long val) {
//		return sprout::to_string_of<wchar_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_integer_digits<unsigned long long>::value>
//	to_wstring(unsigned long long val) {
//		return sprout::to_string_of<wchar_t>(val);
//	}
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_integer_digits<IntType>::value>
	to_wstring(IntType val) {
		return sprout::to_string_of<wchar_t>(val);
	}

	//
	// to_u16string
	//
//	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_integer_digits<int>::value>
//	to_u16string(int val) {
//		return sprout::to_string_of<char16_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_integer_digits<unsigned>::value>
//	to_u16string(unsigned val) {
//		return sprout::to_string_of<char16_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_integer_digits<long>::value>
//	to_u16string(long val) {
//		return sprout::to_string_of<char16_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_integer_digits<unsigned long>::value>
//	to_u16string(unsigned long val) {
//		return sprout::to_string_of<char16_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_integer_digits<long long>::value>
//	to_u16string(long long val) {
//		return sprout::to_string_of<char16_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_integer_digits<unsigned long long>::value>
//	to_u16string(unsigned long long val) {
//		return sprout::to_string_of<char16_t>(val);
//	}
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_integer_digits<IntType>::value>
	to_u16string(IntType val) {
		return sprout::to_string_of<char16_t>(val);
	}

	//
	// to_u32string
	//
//	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_integer_digits<int>::value>
//	to_u32string(int val) {
//		return sprout::to_string_of<char32_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_integer_digits<unsigned>::value>
//	to_u32string(unsigned val) {
//		return sprout::to_string_of<char32_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_integer_digits<long>::value>
//	to_u32string(long val) {
//		return sprout::to_string_of<char32_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_integer_digits<unsigned long>::value>
//	to_u32string(unsigned long val) {
//		return sprout::to_string_of<char32_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_integer_digits<long long>::value>
//	to_u32string(long long val) {
//		return sprout::to_string_of<char32_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_integer_digits<unsigned long long>::value>
//	to_u32string(unsigned long long val) {
//		return sprout::to_string_of<char32_t>(val);
//	}
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_integer_digits<IntType>::value>
	to_u32string(IntType val) {
		return sprout::to_string_of<char32_t>(val);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_INT_TO_STRING_HPP
