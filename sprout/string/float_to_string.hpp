#ifndef SPROUT_STRING_FLOAT_TO_STRING_HPP
#define SPROUT_STRING_FLOAT_TO_STRING_HPP

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>
#include <sprout/string/make_string.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/utility/enabler_if.hpp>
#include <sprout/detail/char_conversion.hpp>

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
			/*std::numeric_limits<floatFloatType>::max_exponent10 + sprout::detail::decimal_places_length + 3*/
			sprout::integer_digits<std::intmax_t>::value + sprout::detail::decimal_places_length + 3
		>
	{};

	namespace detail {
		template<typename FloatType>
		inline SPROUT_CONSTEXPR unsigned float_extract_rounded_impl(FloatType val) {
			return static_cast<unsigned>(val * 1000000)
				+ (static_cast<unsigned>(val * 10000000) % 10 >= 5 ? 1 : 0)
				;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR unsigned float_extract_rounded(FloatType val) {
			using std::floor;
			return sprout::detail::float_extract_rounded_impl(val - floor(val));
		}

		template<
			typename Elem,
			typename FloatType,
			typename... Args,
			typename sprout::enabler_if<(sizeof...(Args) == sprout::printed_float_digits<FloatType>::value - 1)>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string_impl_1(FloatType val, bool negative, Args... args) {
			return negative ? sprout::make_string_as<Elem>(static_cast<Elem>('-'), args...)
				: sprout::make_string_as<Elem>(args...)
				;
		}
		template<
			typename Elem,
			typename FloatType,
			typename... Args,
			typename sprout::enabler_if<(sizeof...(Args) < sprout::printed_float_digits<FloatType>::value - 1)>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string_impl_1(FloatType val, bool negative, Args... args) {
			return !(val < 1) ? sprout::detail::float_to_string_impl_1<Elem>(
					val / 10,
					negative,
					sprout::detail::int_to_char<Elem>(static_cast<std::uintmax_t>(val) % 10),
					args...
					)
				: negative ? sprout::make_string_as<Elem>(static_cast<Elem>('-'), args...)
				: sprout::make_string_as<Elem>(args...)
				;
		}

		template<
			typename Elem,
			typename FloatType,
			typename... Args,
			typename sprout::enabler_if<(sizeof...(Args) == sprout::printed_float_digits<FloatType>::value - 3)>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string_impl(FloatType val, bool negative, unsigned temp, std::size_t decimal_digits, Args... args) {
			return negative ? sprout::make_string_as<Elem>(static_cast<Elem>('-'), static_cast<Elem>('0'), static_cast<Elem>('.'), args...)
				: sprout::make_string_as<Elem>(static_cast<Elem>('0'), static_cast<Elem>('.'), args...)
				;
		}
		template<
			typename Elem,
			typename FloatType,
			typename... Args,
			typename sprout::enabler_if<(sizeof...(Args) < sprout::printed_float_digits<FloatType>::value - 3)>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string_impl(FloatType val, bool negative, unsigned temp, std::size_t decimal_digits, Args... args) {
			return decimal_digits ? sprout::detail::float_to_string_impl<Elem>(
					val,
					negative,
					temp / 10,
					decimal_digits - 1,
					sprout::detail::int_to_char<Elem>(temp % 10),
					args...
					)
				: !(val < 1) ? sprout::detail::float_to_string_impl_1<Elem>(
					val,
					negative,
					static_cast<Elem>('.'),
					args...
					)
				: negative ? sprout::make_string_as<Elem>(static_cast<Elem>('-'), static_cast<Elem>('0'), static_cast<Elem>('.'), args...)
				: sprout::make_string_as<Elem>(static_cast<Elem>('0'), static_cast<Elem>('.'), args...)
				;
		}

		template<
			typename Elem,
			typename FloatType
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string(FloatType val) {
			using std::floor;
			return val < 0 ? sprout::detail::float_to_string_impl<Elem>(
					-val,
					true,
					sprout::detail::float_extract_rounded(-val),
					sprout::detail::decimal_places_length
					)
				: sprout::detail::float_to_string_impl<Elem>(
					val,
					false,
					sprout::detail::float_extract_rounded(val),
					sprout::detail::decimal_places_length
					)
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
		return sprout::detail::float_to_string<Elem>(val);
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
