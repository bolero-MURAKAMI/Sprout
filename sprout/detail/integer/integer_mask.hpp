/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_INTEGER_INTEGER_MASK_HPP
#define SPROUT_DETAIL_INTEGER_INTEGER_MASK_HPP

#include <cstddef>
#include <climits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/integer.hpp>

namespace sprout {
	namespace detail {
		template<std::size_t Bits>
		struct high_bit_mask_t {
		public:
			typedef typename sprout::detail::uint_t<(Bits + 1)>::least least;
			typedef typename sprout::detail::uint_t<(Bits + 1)>::fast fast;
		public:
			SPROUT_STATIC_CONSTEXPR least high_bit = least(1u) << Bits;
			SPROUT_STATIC_CONSTEXPR fast high_bit_fast = fast(1u) << Bits;
			SPROUT_STATIC_CONSTEXPR std::size_t bit_position = Bits;
		};

		template<std::size_t Bits>
		struct low_bits_mask_t {
		public:
			typedef typename sprout::detail::uint_t<Bits>::least least;
			typedef typename sprout::detail::uint_t<Bits>::fast fast;
		public:
			SPROUT_STATIC_CONSTEXPR least sig_bits = ~(~(least(0u)) << Bits);
			SPROUT_STATIC_CONSTEXPR fast sig_bits_fast = fast(sig_bits);
			SPROUT_STATIC_CONSTEXPR std::size_t bit_count = Bits;
		};

#define SPROUT_LOW_BITS_MASK_SPECIALIZE(Type) \
		template<> \
		struct low_bits_mask_t<sprout::numeric_limits<Type>::digits> { \
		public: \
			typedef sprout::numeric_limits<Type> limits_type; \
			typedef typename sprout::detail::uint_t<limits_type::digits>::least least; \
			typedef typename sprout::detail::uint_t<limits_type::digits>::fast fast; \
		public: \
			SPROUT_STATIC_CONSTEXPR least sig_bits = ~(least(0u)); \
			SPROUT_STATIC_CONSTEXPR fast sig_bits_fast = fast(sig_bits); \
			SPROUT_STATIC_CONSTEXPR std::size_t bit_count = limits_type::digits; \
		}

		SPROUT_LOW_BITS_MASK_SPECIALIZE(unsigned char);
#if USHRT_MAX > UCHAR_MAX
		SPROUT_LOW_BITS_MASK_SPECIALIZE(unsigned short);
#endif
#if UINT_MAX > USHRT_MAX
		SPROUT_LOW_BITS_MASK_SPECIALIZE(unsigned int);
#endif
#if ULONG_MAX > UINT_MAX
		SPROUT_LOW_BITS_MASK_SPECIALIZE(unsigned long);
#endif
#if ULLONG_MAX > ULONG_MAX
		SPROUT_LOW_BITS_MASK_SPECIALIZE(unsigned long long);
#endif

#undef SPROUT_LOW_BITS_MASK_SPECIALIZE
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_INTEGER_INTEGER_MASK_HPP
