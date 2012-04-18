#ifndef SPROUT_STRING_FLOAT_TO_STRING_HPP
#define SPROUT_STRING_FLOAT_TO_STRING_HPP

#include <cstddef>
#include <cmath>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>
#include <sprout/utility/enabler_if.hpp>
#include <sprout/detail/char_conversion.hpp>
#include <sprout/detail/float.hpp>

namespace sprout {
	namespace detail {
		SPROUT_STATIC_CONSTEXPR std::size_t decimal_places_length = 6;
	}	// namespace detail

	//
	// printed_float_digits
	//
	template<typename FloatType>
	struct printed_float_digits
		: public std::integral_constant<
			std::size_t,
			std::numeric_limits<FloatType>::max_exponent10 + sprout::detail::decimal_places_length + 2
		>
	{};

	namespace detail {
		template<typename Elem, typename FloatType, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string(FloatType val, bool negative, int digits, sprout::index_tuple<Indexes...>) {
			return negative ? sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>{
					{
						static_cast<Elem>('-'),
						(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, digits - 1 - Indexes))
							: Indexes == digits ? static_cast<Elem>('.')
							: Indexes < digits + 1 + sprout::detail::decimal_places_length ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, digits - Indexes))
							: Elem()
							)...
						},
						static_cast<std::size_t>(digits + 2 + sprout::detail::decimal_places_length)
					}
				: sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>{
					{
						(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, digits - 1 - Indexes))
							: Indexes == digits ? static_cast<Elem>('.')
							: Indexes < digits + 1 + sprout::detail::decimal_places_length ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, digits - Indexes))
							: Elem()
							)...
						},
						static_cast<std::size_t>(digits + 1 + sprout::detail::decimal_places_length)
					}
				;
		}
	}	// namespace detail

	//
	// float_to_string
	//
	template<
		typename Elem,
		typename FloatType,
		typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
	float_to_string(FloatType val) {
		return sprout::detail::float_to_string<Elem>(
			sprout::detail::float_round_at(val < 0 ? -val : val, sprout::detail::decimal_places_length),
			val < 0,
			sprout::detail::float_digits(val),
			sprout::index_range<0, sprout::printed_float_digits<FloatType>::value - 1>::make()
			);
	}

	//
	// to_string_of
	//
	template<typename Elem, typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
	to_string_of(FloatType val) {
		return sprout::float_to_string<Elem>(val);
	}

	//
	// to_string
	//
//	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_float_digits<float>::value>
//	to_string(float val) {
//		return sprout::to_string_of<char>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_float_digits<double>::value>
//	to_string(double val) {
//		return sprout::to_string_of<char>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_float_digits<long double>::value>
//	to_string(long double val) {
//		return sprout::to_string_of<char>(val);
//	}
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_float_digits<FloatType>::value>
	to_string(FloatType val) {
		return sprout::to_string_of<char>(val);
	}

	//
	// to_wstring
	//
//	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_float_digits<float>::value>
//	to_wstring(float val) {
//		return sprout::to_string_of<wchar_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_float_digits<double>::value>
//	to_wstring(double val) {
//		return sprout::to_string_of<wchar_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_float_digits<long double>::value>
//	to_wstring(long double val) {
//		return sprout::to_string_of<wchar_t>(val);
//	}
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_float_digits<FloatType>::value>
	to_wstring(FloatType val) {
		return sprout::to_string_of<wchar_t>(val);
	}

	//
	// to_u16string
	//
//	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_float_digits<float>::value>
//	to_u16string(float val) {
//		return sprout::to_string_of<char16_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_float_digits<double>::value>
//	to_u16string(double val) {
//		return sprout::to_string_of<char16_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_float_digits<long double>::value>
//	to_u16string(long double val) {
//		return sprout::to_string_of<char16_t>(val);
//	}
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_float_digits<FloatType>::value>
	to_u16string(FloatType val) {
		return sprout::to_string_of<char16_t>(val);
	}

	//
	// to_u32string
	//
//	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_float_digits<float>::value>
//	to_u32string(float val) {
//		return sprout::to_string_of<char32_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_float_digits<double>::value>
//	to_u32string(double val) {
//		return sprout::to_string_of<char32_t>(val);
//	}
//	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_float_digits<long double>::value>
//	to_u32string(long double val) {
//		return sprout::to_string_of<char32_t>(val);
//	}
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_float_digits<FloatType>::value>
	to_u32string(FloatType val) {
		return sprout::to_string_of<char32_t>(val);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_FLOAT_TO_STRING_HPP
