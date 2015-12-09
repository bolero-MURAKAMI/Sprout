/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_FLOAT_TO_STRING_HPP
#define SPROUT_STRING_FLOAT_TO_STRING_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/string/string.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/tpp/algorithm/max_element.hpp>
#include <sprout/detail/char_literal.hpp>
#include <sprout/detail/char_conversion.hpp>
#include <sprout/detail/math/int.hpp>
#include <sprout/detail/math/float.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		SPROUT_STATIC_CONSTEXPR std::size_t decimal_places_length = 6;
	}	// namespace detail

	//
	// printed_float_digits
	//
	template<typename FloatType>
	struct printed_float_digits
		: public sprout::integral_constant<
			std::size_t,
			sprout::numeric_limits<FloatType>::max_exponent10 + sprout::detail::decimal_places_length + 2
		>
	{};

	namespace detail {
		template<typename Elem, typename FloatType, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string_impl(FloatType val, bool negative, int digits, int v, sprout::index_tuple<Indexes...>) {
			typedef sprout::detail::string_construct_access<Elem, sprout::printed_float_digits<FloatType>::value> access_type;
			return negative
				? access_type::raw_construct(
					static_cast<std::size_t>(digits + 2 + sprout::detail::decimal_places_length),
					SPROUT_CHAR_LITERAL('-', Elem),
					(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, digits - 1 - Indexes))
						: Indexes == digits ? SPROUT_CHAR_LITERAL('.', Elem)
						: Indexes < digits + 1 + sprout::detail::decimal_places_length
							? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at(v, digits + sprout::detail::decimal_places_length - Indexes))
						: Elem()
						)...
					)
				: access_type::raw_construct(
					static_cast<std::size_t>(digits + 1 + sprout::detail::decimal_places_length),
					(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, digits - 1 - Indexes))
						: Indexes == digits ? SPROUT_CHAR_LITERAL('.', Elem)
						: Indexes < digits + 1 + sprout::detail::decimal_places_length
							? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at(v, digits + sprout::detail::decimal_places_length - Indexes))
						: Elem()
						)...
					)
				;
		}
		template<typename Elem, typename FloatType>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string(FloatType val, bool negative, int digits) {
			return sprout::detail::float_to_string_impl<Elem>(
				val, negative, digits, static_cast<int>((val - sprout::math::floor(val)) * sprout::detail::int_pow<int>(sprout::detail::decimal_places_length)),
				sprout::make_index_tuple<sprout::printed_float_digits<FloatType>::value - 1>::make()
				);
		}
	}	// namespace detail

	//
	// float_to_string
	//
	template<
		typename Elem, typename FloatType,
		typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
	float_to_string(FloatType val) {
		typedef sprout::detail::string_construct_access<Elem, sprout::printed_float_digits<FloatType>::value> access_type;
		return sprout::math::isinf(val) ? sprout::math::signbit(val)
				? access_type::raw_construct(4, SPROUT_CHAR_LITERAL('-', Elem), SPROUT_CHAR_LITERAL('i', Elem), SPROUT_CHAR_LITERAL('n', Elem), SPROUT_CHAR_LITERAL('f', Elem))
				: access_type::raw_construct(3, SPROUT_CHAR_LITERAL('i', Elem), SPROUT_CHAR_LITERAL('n', Elem), SPROUT_CHAR_LITERAL('f', Elem))
			: sprout::math::isnan(val) ? sprout::math::signbit(val)
				? access_type::raw_construct(4, SPROUT_CHAR_LITERAL('-', Elem), SPROUT_CHAR_LITERAL('n', Elem), SPROUT_CHAR_LITERAL('a', Elem), SPROUT_CHAR_LITERAL('n', Elem))
				: access_type::raw_construct(3, SPROUT_CHAR_LITERAL('n', Elem), SPROUT_CHAR_LITERAL('a', Elem), SPROUT_CHAR_LITERAL('n', Elem))
			: sprout::detail::float_to_string<Elem>(
				sprout::detail::float_round_at(val < 0 ? -val : val, sprout::detail::decimal_places_length),
				sprout::math::signbit(val),
				sprout::detail::float_digits_checked(val)
				)
			;
	}

	namespace detail {
		template<typename FloatType>
		struct printed_float_exponent10_digits
			: public sprout::integral_constant<
				std::size_t,
				sprout::tpp::max_element_c<int, sprout::detail::int_digits_mf<int, sprout::numeric_limits<FloatType>::max_exponent10>::value, 2>::value
			>
		{};
	}	// namespace detail

	//
	// printed_float_exp_digits
	//
	template<typename FloatType>
	struct printed_float_exp_digits
		: public sprout::integral_constant<
			std::size_t,
			5 + sprout::detail::decimal_places_length + sprout::detail::printed_float_exponent10_digits<FloatType>::value
		>
	{};

	namespace detail {
		template<typename Elem, typename FloatType, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_exp_digits<FloatType>::value>
		float_to_string_exp(FloatType val, bool negative, int exponent10, int e10_digits, sprout::index_tuple<Indexes...>) {
			typedef sprout::detail::string_construct_access<Elem, sprout::printed_float_exp_digits<FloatType>::value> access_type;
			return negative
				? access_type::raw_construct(
					static_cast<std::size_t>(5 + sprout::detail::decimal_places_length + e10_digits),
					SPROUT_CHAR_LITERAL('-', Elem),
					(Indexes == 0 ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, 0))
						: Indexes == 1 ? SPROUT_CHAR_LITERAL('.', Elem)
						: Indexes < 2 + sprout::detail::decimal_places_length
							? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, 1 - Indexes))
						: Indexes == 2 + sprout::detail::decimal_places_length ? SPROUT_CHAR_LITERAL('e', Elem)
						: Indexes == 3 + sprout::detail::decimal_places_length ? (exponent10 < 0 ? SPROUT_CHAR_LITERAL('-', Elem) : SPROUT_CHAR_LITERAL('+', Elem))
						: Indexes < 4 + sprout::detail::decimal_places_length + e10_digits
							? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at(exponent10, 3 + sprout::detail::decimal_places_length + e10_digits - Indexes))
						: Elem()
						)...
					)
				: access_type::raw_construct(
					static_cast<std::size_t>(4 + sprout::detail::decimal_places_length + e10_digits),
					(Indexes == 0 ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, 0))
						: Indexes == 1 ? SPROUT_CHAR_LITERAL('.', Elem)
						: Indexes < 2 + sprout::detail::decimal_places_length
							? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, 1 - Indexes))
						: Indexes == 2 + sprout::detail::decimal_places_length ? SPROUT_CHAR_LITERAL('e', Elem)
						: Indexes == 3 + sprout::detail::decimal_places_length ? (exponent10 < 0 ? SPROUT_CHAR_LITERAL('-', Elem) : SPROUT_CHAR_LITERAL('+', Elem))
						: Indexes < 4 + sprout::detail::decimal_places_length + e10_digits
							? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at(exponent10, 3 + sprout::detail::decimal_places_length + e10_digits - Indexes))
						: Elem()
						)...
					)
				;
		}
	}	// namespace detail

	//
	// float_to_string_exp
	//
	template<
		typename Elem, typename FloatType,
		typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_exp_digits<FloatType>::value>
	float_to_string_exp(FloatType val) {
		typedef sprout::detail::string_construct_access<Elem, sprout::printed_float_exp_digits<FloatType>::value> access_type;
		return sprout::math::isinf(val) ? sprout::math::signbit(val)
				? access_type::raw_construct(4, SPROUT_CHAR_LITERAL('-', Elem), SPROUT_CHAR_LITERAL('i', Elem), SPROUT_CHAR_LITERAL('n', Elem), SPROUT_CHAR_LITERAL('f', Elem))
				: access_type::raw_construct(3, SPROUT_CHAR_LITERAL('i', Elem), SPROUT_CHAR_LITERAL('n', Elem), SPROUT_CHAR_LITERAL('f', Elem))
			: sprout::math::isnan(val) ? sprout::math::signbit(val)
				? access_type::raw_construct(4, SPROUT_CHAR_LITERAL('-', Elem), SPROUT_CHAR_LITERAL('n', Elem), SPROUT_CHAR_LITERAL('a', Elem), SPROUT_CHAR_LITERAL('n', Elem))
				: access_type::raw_construct(3, SPROUT_CHAR_LITERAL('n', Elem), SPROUT_CHAR_LITERAL('a', Elem), SPROUT_CHAR_LITERAL('n', Elem))
			: sprout::detail::float_to_string_exp<Elem>(
				sprout::detail::float_round_at(
					(val < 0 ? -val : val) / sprout::detail::float_pow10<FloatType>(sprout::detail::float_exponent10(val)),
					sprout::detail::decimal_places_length
					),
				sprout::math::signbit(val),
				sprout::detail::float_exponent10(val),
				NS_SSCRISK_CEL_OR_SPROUT::max(sprout::detail::int_digits(sprout::detail::float_exponent10(val)), 2),
				sprout::make_index_tuple<sprout::printed_float_exp_digits<FloatType>::value - 1>::make()
				)
			;
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
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_float_digits<FloatType>::value>
	to_string(FloatType val) {
		return sprout::to_string_of<char>(val);
	}

	//
	// to_wstring
	//
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_float_digits<FloatType>::value>
	to_wstring(FloatType val) {
		return sprout::to_string_of<wchar_t>(val);
	}

	//
	// to_u16string
	//
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_float_digits<FloatType>::value>
	to_u16string(FloatType val) {
		return sprout::to_string_of<char16_t>(val);
	}

	//
	// to_u32string
	//
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_float_digits<FloatType>::value>
	to_u32string(FloatType val) {
		return sprout::to_string_of<char32_t>(val);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_FLOAT_TO_STRING_HPP
