/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ENDIAN_TRAITS_HPP
#define SPROUT_ENDIAN_TRAITS_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
	namespace detail {
		template<typename T, typename Enable = void>
		class default_big_endian_traits;
		template<typename T>
		class default_big_endian_traits<
			T,
			typename std::enable_if<std::is_integral<T>::value && sizeof(T) == 1>::type
		> {
		public:
			typedef T type;
		public:
			static SPROUT_CONSTEXPR std::size_t
			size() {
				return sizeof(type);
			}
			static SPROUT_CONSTEXPR unsigned char
			get_byte(type const& t, std::size_t) {
				return static_cast<unsigned char>(t);
			}
			static SPROUT_CXX14_CONSTEXPR void
			set_byte(type& t, std::size_t, unsigned char value) {
				t = static_cast<type>(value);
			}
		};
		template<typename T>
		class default_big_endian_traits<
			T,
			typename std::enable_if<std::is_integral<T>::value && !(sizeof(T) == 1)>::type
		> {
		public:
			typedef T type;
		public:
			static SPROUT_CONSTEXPR std::size_t
			size() {
				return sizeof(type);
			}
			static SPROUT_CONSTEXPR unsigned char
			get_byte(type const& t, std::size_t i) {
				return static_cast<unsigned char>(
					(t & (UCHAR_MAX << CHAR_BIT * ((size() - 1) - i)))
						>> CHAR_BIT * ((size() - 1) - i)
					);
			}
			static SPROUT_CXX14_CONSTEXPR void
			set_byte(type& t, std::size_t i, unsigned char value) {
				t &= ~(UCHAR_MAX << CHAR_BIT * ((size() - 1) - i));
				t |= (value << CHAR_BIT * ((size() - 1) - i));
			}
		};

		template<typename T, typename Enable = void>
		class default_little_endian_traits;
		template<typename T>
		class default_little_endian_traits<
			T,
			typename std::enable_if<std::is_integral<T>::value && sizeof(T) == 1>::type
		> {
		public:
			typedef T type;
		public:
			static SPROUT_CONSTEXPR std::size_t size() {
				return sizeof(type);
			}
			static SPROUT_CONSTEXPR unsigned char get_byte(type const& t, std::size_t) {
				return static_cast<unsigned char>(t);
			}
			static SPROUT_CXX14_CONSTEXPR void
			set_byte(type& t, std::size_t, unsigned char value) {
				t = static_cast<type>(value);
			}
		};
		template<typename T>
		class default_little_endian_traits<
			T,
			typename std::enable_if<std::is_integral<T>::value && !(sizeof(T) == 1)>::type
		> {
		public:
			typedef T type;
		public:
			static SPROUT_CONSTEXPR std::size_t size() {
				return sizeof(type);
			}
			static SPROUT_CONSTEXPR unsigned char get_byte(type const& t, std::size_t i) {
				return static_cast<unsigned char>(
					(t & (UCHAR_MAX << CHAR_BIT * i))
						>> CHAR_BIT * i
					);
			}
			static SPROUT_CXX14_CONSTEXPR void
			set_byte(type& t, std::size_t i, unsigned char value) {
				t &= ~(UCHAR_MAX << CHAR_BIT * i);
				t |= (value << CHAR_BIT * i);
			}
		};
	}	// namespace detail

	//
	// big_endian_traits
	//
	template<typename T>
	class big_endian_traits
		: public sprout::detail::default_big_endian_traits<T>
	{};

	//
	// little_endian_traits
	//
	template<typename T>
	class little_endian_traits
		: public sprout::detail::default_little_endian_traits<T>
	{};

	//
	// endian_traits
	//
	template<typename T>
	class endian_traits
		: public sprout::big_endian_traits<T>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ENDIAN_TRAITS_HPP
