/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_INTEGER_HPP
#define SPROUT_DETAIL_INTEGER_HPP

#include <climits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>

namespace sprout {
	namespace detail {
		template<typename LeastInt>
		struct int_fast_t {
			typedef LeastInt fast;
			typedef fast type;
		};

		template<int Category>
		struct int_least_helper {};
		template<>
		struct int_least_helper<1> {
			typedef long long least;
		};
		template<>
		struct int_least_helper<2> {
			typedef long least;
		};
		template<>
		struct int_least_helper<3> {
			typedef int least;
		};
		template<>
		struct int_least_helper<4> {
			typedef short least;
		};
		template<>
		struct int_least_helper<5> {
			typedef signed char least;
		};
		template<>
		struct int_least_helper<6> {
			typedef unsigned long long least;
		};
		template<>
		struct int_least_helper<7> {
			typedef unsigned long least;
		};
		template<>
		struct int_least_helper<8> {
			typedef unsigned int least;
		};
		template<>
		struct int_least_helper<9> {
			typedef unsigned short least;
		};
		template<>
		struct int_least_helper<10> {
			typedef unsigned char least;
		};

		template<int Bits>
		struct exact_signed_base_helper {};
		template<int Bits>
		struct exact_unsigned_base_helper {};

		template<>
		struct exact_signed_base_helper<sizeof(signed char) * CHAR_BIT> {
			typedef signed char exact;
		};
		template<>
		struct exact_unsigned_base_helper<sizeof(unsigned char) * CHAR_BIT> {
			typedef unsigned char exact;
		};
#if USHRT_MAX != UCHAR_MAX
		template<>
		struct exact_signed_base_helper<sizeof(short) * CHAR_BIT> {
			typedef short exact;
		};
		template<> struct exact_unsigned_base_helper<sizeof(unsigned short) * CHAR_BIT> {
			typedef unsigned short exact;
		};
#endif
#if UINT_MAX != USHRT_MAX
		template<>
		struct exact_signed_base_helper<sizeof(int) * CHAR_BIT> {
			typedef int exact;
		};
		template<>
		struct exact_unsigned_base_helper<sizeof(unsigned int) * CHAR_BIT> {
			typedef unsigned int exact;
		};
#endif
#if ULONG_MAX != UINT_MAX
		template<>
		struct exact_signed_base_helper<sizeof(long) * CHAR_BIT> {
			typedef long exact;
		};
		template<>
		struct exact_unsigned_base_helper<sizeof(unsigned long) * CHAR_BIT> {
			typedef unsigned long exact;
		};
#endif
#if ULLONG_MAX != ULONG_MAX
		template<>
		struct exact_signed_base_helper<sizeof(long long) * CHAR_BIT> {
			typedef long long exact;
		};
		template<>
		struct exact_unsigned_base_helper<sizeof(unsigned long long) * CHAR_BIT> {
			typedef unsigned long long exact;
		};
#endif

		template<int Bits>
		struct int_t
			: public sprout::detail::exact_signed_base_helper<Bits>
		{
			typedef typename sprout::detail::int_least_helper<
				0
				+ (Bits - 1 <= sprout::numeric_limits<long long>::digits)
				+ (Bits - 1 <= sprout::numeric_limits<long>::digits)
				+ (Bits - 1 <= sprout::numeric_limits<int>::digits)
				+ (Bits - 1 <= sprout::numeric_limits<short>::digits)
				+ (Bits - 1 <= sprout::numeric_limits<signed char>::digits)
			>::least least;
			typedef typename sprout::detail::int_fast_t<least>::type fast;
		};
		template<int Bits>
		struct uint_t
			: public sprout::detail::exact_unsigned_base_helper<Bits>
		{
			typedef typename sprout::detail::int_least_helper<
				5
				+ (Bits <= sprout::numeric_limits<unsigned long long>::digits)
				+ (Bits <= sprout::numeric_limits<unsigned long>::digits)
				+ (Bits <= sprout::numeric_limits<unsigned int>::digits)
				+ (Bits <= sprout::numeric_limits<unsigned short>::digits)
				+ (Bits <= sprout::numeric_limits<unsigned char>::digits)
			>::least least;
			typedef typename sprout::detail::int_fast_t<least>::type fast;
		};

		template<long long MaxValue>
		struct int_max_value_t {
			typedef typename sprout::detail::int_least_helper<
				0
				+ (MaxValue <= sprout::numeric_limits<long long>::max())
				+ (MaxValue <= sprout::numeric_limits<long>::max())
				+ (MaxValue <= sprout::numeric_limits<int>::max())
				+ (MaxValue <= sprout::numeric_limits<short>::max())
				+ (MaxValue <= sprout::numeric_limits<signed char>::max())
			>::least least;
			typedef typename sprout::detail::int_fast_t<least>::type fast;
		};
		template<long long MinValue>
		struct int_min_value_t {
			typedef typename sprout::detail::int_least_helper<
				0
				+ (MinValue >= sprout::numeric_limits<long long>::min())
				+ (MinValue >= sprout::numeric_limits<long>::min())
				+ (MinValue >= sprout::numeric_limits<int>::min())
				+ (MinValue >= sprout::numeric_limits<short>::min())
				+ (MinValue >= sprout::numeric_limits<signed char>::min())
			>::least least;
			typedef typename sprout::detail::int_fast_t<least>::type fast;
		};

		template<unsigned long long MaxValue>
		struct uint_value_t {
			typedef typename sprout::detail::int_least_helper<
				5
				+ (MaxValue <= sprout::numeric_limits<long long>::max())
				+ (MaxValue <= sprout::numeric_limits<long>::max())
				+ (MaxValue <= sprout::numeric_limits<int>::max())
				+ (MaxValue <= sprout::numeric_limits<short>::max())
				+ (MaxValue <= sprout::numeric_limits<signed char>::max())
			>::least least;
			typedef typename sprout::detail::int_fast_t<least>::type fast;
		};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_INTEGER_HPP
