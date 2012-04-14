#ifndef SPROUT_STRING_TO_STRING_HPP
#define SPROUT_STRING_TO_STRING_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>
#include <sprout/string/make_string.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/utility/enabler_if.hpp>
#include <sprout/detail/char_conversion.hpp>

namespace sprout {
	namespace detail {
		template<
			typename Elem,
			std::size_t Base,
			typename IntType,
			typename... Args,
			typename sprout::enabler_if<(sizeof...(Args) == sprout::integer_digits<IntType, Base>::value - 1)>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<IntType, Base>::value>
		int_to_string_impl_1(IntType val, bool negative, Args... args) {
			return negative ? sprout::make_string_as<Elem>(static_cast<Elem>('-'), args...)
				: sprout::make_string_as<Elem>(args...)
				;
		}
		template<
			typename Elem,
			std::size_t Base,
			typename IntType,
			typename... Args,
			typename sprout::enabler_if<(sizeof...(Args) < sprout::integer_digits<IntType, Base>::value - 1)>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<IntType, Base>::value>
		int_to_string_impl_1(IntType val, bool negative, Args... args) {
			return val == 0
				? (negative ? sprout::make_string_as<Elem>(static_cast<Elem>('-'), args...)
					: sprout::make_string_as<Elem>(args...)
					)
				: sprout::detail::int_to_string_impl_1<Elem, Base>(
					val / Base,
					negative,
					sprout::detail::int_to_char<Elem>(val % Base, Base),
					args...
					)
				;
		}
		template<typename Elem, std::size_t Base, typename IntType>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<IntType, Base>::value>
		int_to_string_impl(IntType val) {
			return val == 0 ? sprout::make_string_as<Elem>(static_cast<Elem>('0'))
				: val < 0 ? sprout::detail::int_to_string_impl_1<Elem, Base>(-val, true)
				: sprout::detail::int_to_string_impl_1<Elem, Base>(val, false)
				;
		}

		template<
			typename Elem,
			std::size_t Base,
			typename UIntType,
			typename... Args,
			typename sprout::enabler_if<(sizeof...(Args) == sprout::integer_digits<UIntType, Base>::value)>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<UIntType, Base>::value>
		uint_to_string_impl_1(UIntType val, Args... args) {
			return sprout::make_string_as<Elem>(args...);
		}
		template<
			typename Elem,
			std::size_t Base,
			typename UIntType,
			typename... Args,
			typename sprout::enabler_if<(sizeof...(Args) < sprout::integer_digits<UIntType, Base>::value)>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<UIntType, Base>::value>
		uint_to_string_impl_1(UIntType val, Args... args) {
			return val == 0
				? sprout::make_string_as<Elem>(args...)
				: sprout::detail::uint_to_string_impl_1<Elem, Base>(
					val / Base,
					sprout::detail::int_to_char<Elem>(val % Base, Base),
					args...
					)
				;
		}
		template<typename Elem, std::size_t Base, typename UIntType>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<UIntType, Base>::value>
		uint_to_string_impl(UIntType val) {
			return val == 0 ? sprout::make_string_as<Elem>(static_cast<Elem>('0'))
				: sprout::detail::uint_to_string_impl_1<Elem, Base>(val)
				;
		}

		template<
			typename Elem,
			std::size_t Base,
			typename IntType,
			typename sprout::enabler_if<std::is_signed<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<IntType, Base>::value>
		int_to_string(IntType val) {
			return sprout::detail::int_to_string_impl<Elem, Base>(val);
		}
		template<
			typename Elem,
			std::size_t Base,
			typename IntType,
			typename sprout::enabler_if<std::is_unsigned<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<IntType, Base>::value>
		int_to_string(IntType val) {
			return sprout::detail::uint_to_string_impl<Elem, Base>(val);
		}
	}	// namespace detail

	//
	// int_to_string
	//
	template<
		typename Elem,
		std::size_t Base,
		typename IntType,
		typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<IntType, Base>::value>
	int_to_string(IntType val) {
		return sprout::detail::int_to_string<Elem, Base>(val);
	}

	//
	// to_string_of
	//
	template<typename Elem, typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::integer_digits<IntType, 10>::value>
	to_string_of(IntType val) {
		return sprout::int_to_string<Elem, 10>(val);
	}

	//
	// to_string
	//
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::integer_digits<int>::value>
	to_string(int val) {
		return sprout::to_string_of<char>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::integer_digits<unsigned>::value>
	to_string(unsigned val) {
		return sprout::to_string_of<char>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::integer_digits<long>::value>
	to_string(long val) {
		return sprout::to_string_of<char>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::integer_digits<unsigned long>::value>
	to_string(unsigned long val) {
		return sprout::to_string_of<char>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::integer_digits<long long>::value>
	to_string(long long val) {
		return sprout::to_string_of<char>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::integer_digits<unsigned long long>::value>
	to_string(unsigned long long val) {
		return sprout::to_string_of<char>(val);
	}
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::integer_digits<IntType>::value>
	to_string(IntType val) {
		return sprout::to_string_of<char>(val);
	}

	//
	// to_wstring
	//
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::integer_digits<int>::value>
	to_wstring(int val) {
		return sprout::to_string_of<wchar_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::integer_digits<unsigned>::value>
	to_wstring(unsigned val) {
		return sprout::to_string_of<wchar_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::integer_digits<long>::value>
	to_wstring(long val) {
		return sprout::to_string_of<wchar_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::integer_digits<unsigned long>::value>
	to_wstring(unsigned long val) {
		return sprout::to_string_of<wchar_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::integer_digits<long long>::value>
	to_wstring(long long val) {
		return sprout::to_string_of<wchar_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::integer_digits<unsigned long long>::value>
	to_wstring(unsigned long long val) {
		return sprout::to_string_of<wchar_t>(val);
	}
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::integer_digits<IntType>::value>
	to_wstring(IntType val) {
		return sprout::to_string_of<wchar_t>(val);
	}

	//
	// to_u16string
	//
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::integer_digits<int>::value>
	to_u16string(int val) {
		return sprout::to_string_of<char16_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::integer_digits<unsigned>::value>
	to_u16string(unsigned val) {
		return sprout::to_string_of<char16_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::integer_digits<long>::value>
	to_u16string(long val) {
		return sprout::to_string_of<char16_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::integer_digits<unsigned long>::value>
	to_u16string(unsigned long val) {
		return sprout::to_string_of<char16_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::integer_digits<long long>::value>
	to_u16string(long long val) {
		return sprout::to_string_of<char16_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::integer_digits<unsigned long long>::value>
	to_u16string(unsigned long long val) {
		return sprout::to_string_of<char16_t>(val);
	}
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::integer_digits<IntType>::value>
	to_u16string(IntType val) {
		return sprout::to_string_of<char16_t>(val);
	}

	//
	// to_u32string
	//
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::integer_digits<int>::value>
	to_u32string(int val) {
		return sprout::to_string_of<char32_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::integer_digits<unsigned>::value>
	to_u32string(unsigned val) {
		return sprout::to_string_of<char32_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::integer_digits<long>::value>
	to_u32string(long val) {
		return sprout::to_string_of<char32_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::integer_digits<unsigned long>::value>
	to_u32string(unsigned long val) {
		return sprout::to_string_of<char32_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::integer_digits<long long>::value>
	to_u32string(long long val) {
		return sprout::to_string_of<char32_t>(val);
	}
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::integer_digits<unsigned long long>::value>
	to_u32string(unsigned long long val) {
		return sprout::to_string_of<char32_t>(val);
	}
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::integer_digits<IntType>::value>
	to_u32string(IntType val) {
		return sprout::to_string_of<char32_t>(val);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_TO_STRING_HPP
