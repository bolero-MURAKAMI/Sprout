/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUE_TRAITS_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_VALUE_TRAITS_HPP

#include <functional>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/detail/hash_float.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_signed.hpp>
#include <sprout/type_traits/is_unsigned.hpp>

namespace sprout {
	namespace hash_detail {
		template<typename T>
		struct is_basic_number
			: public sprout::bool_constant<
				std::is_integral<T>::value
					&& (sizeof(T) <= sizeof(std::size_t))
			>
		{};
		template<typename T>
		struct is_long_number
			: public sprout::bool_constant<
				std::is_integral<T>::value
					&& (sizeof(T) > sizeof(std::size_t))
					&& sprout::is_signed<T>::value
			>
		{};
		template<typename T>
		struct is_ulong_number
			: public sprout::bool_constant<
				std::is_integral<T>::value
					&& (sizeof(T) > sizeof(std::size_t))
					&& sprout::is_unsigned<T>::value
			>
		{};

		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_signed_2(T val, int length, std::size_t seed, T positive, std::size_t i) {
			return i > 0
				? hash_value_signed_2(
					val,
					length,
					seed ^ static_cast<std::size_t>((positive >> i) + (seed << 6) + (seed >> 2)),
					positive,
					i - sprout::numeric_limits<std::size_t>::digits
					)
				: seed ^ static_cast<std::size_t>(val + (seed << 6) + (seed >> 2))
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_signed_1(T val, int length, std::size_t seed, T positive) {
			return hash_value_signed_2(val, length, seed, positive, length * sprout::numeric_limits<std::size_t>::digits);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_signed(T val) {
			return sprout::hash_detail::hash_value_signed_1(
				val,
				(sprout::numeric_limits<T>::digits - 1) / sprout::numeric_limits<std::size_t>::digits,
				0,
				val < 0 ? -1 - val : val
				);
		}

		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_unsigned_2(T val, int length, std::size_t seed, std::size_t i) {
			return i > 0
				? hash_value_unsigned_2(
					val,
					length,
					seed ^ static_cast<std::size_t>((val >> i) + (seed << 6) + (seed >> 2)),
					i - sprout::numeric_limits<std::size_t>::digits
					)
				: seed ^ static_cast<std::size_t>(val + (seed << 6) + (seed >> 2))
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_unsigned_1(T val, int length, std::size_t seed) {
			return hash_value_unsigned_2(val, length, seed, length * sprout::numeric_limits<std::size_t>::digits);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_unsigned(T val) {
			return sprout::hash_detail::hash_value_unsigned_1(
				val,
				(sprout::numeric_limits<T>::digits - 1) / sprout::numeric_limits<std::size_t>::digits,
				0
				);
		}

		inline std::size_t
		hash_value_pointer_1(std::size_t x) {
			return x + (x >> 3);
		}
		template<typename T>
		std::size_t
		hash_value_pointer(T const* v) {
			return sprout::hash_detail::hash_value_pointer_1(static_cast<std::size_t>(reinterpret_cast<std::ptrdiff_t>(v)));
		}

		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<sprout::hash_detail::is_basic_number<T>::value, std::size_t>::type
		hash_value_impl(T v) {
			return static_cast<std::size_t>(v);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<sprout::hash_detail::is_long_number<T>::value, std::size_t>::type
		hash_value_impl(T v) {
			return sprout::hash_detail::hash_value_signed(v);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<sprout::hash_detail::is_ulong_number<T>::value, std::size_t>::type
		hash_value_impl(T v) {
			return sprout::hash_detail::hash_value_unsigned(v);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<std::is_enum<T>::value, std::size_t>::type
		hash_value_impl(T v) {
			return sprout::hash_detail::hash_value_impl(static_cast<typename std::underlying_type<T>::type>(v));
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<std::is_floating_point<T>::value, std::size_t>::type
		hash_value_impl(T v) {
			return sprout::detail::float_hash_value(v);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<std::is_pointer<typename std::remove_reference<T>::type>::value, std::size_t>::type
		hash_value_impl(T&& v) {
			return sprout::hash_detail::hash_value_pointer(v);
		}
		template<typename T, std::size_t N>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_impl(T const (& v)[N]) {
			return sprout::hash_range(v);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!std::is_arithmetic<T>::value && !std::is_enum<T>::value && !std::is_pointer<T>::value,
			std::size_t
		>::type
		hash_value_impl(T const& v) {
			return std::hash<typename std::decay<T>::type>()(v);
		}
	}	// namespace hash_detail

	//
	// hash_value_traits
	//
	template<typename T>
	struct hash_value_traits {
	public:
		static SPROUT_CONSTEXPR std::size_t
		hash_value(T const& v) {
			return sprout::hash_detail::hash_value_impl(v);
		}
	};
	template<typename T>
	struct hash_value_traits<T const>
		: public sprout::hash_value_traits<T>
	{};
	template<typename T>
	struct hash_value_traits<T volatile>
		: public sprout::hash_value_traits<T>
	{};
	template<typename T>
	struct hash_value_traits<T const volatile>
		: public sprout::hash_value_traits<T>
	{};
}	// namespace sprout

#include <sprout/functional/hash/hash_range.hpp>

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUE_TRAITS_HPP
