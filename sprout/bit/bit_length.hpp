/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_BIT_LENGTH_HPP
#define SPROUT_BIT_BIT_LENGTH_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
	namespace detail {
		SPROUT_STATIC_CONSTEXPR std::size_t bit_len_8_table[std::size_t(UCHAR_MAX) + 1] = {
			0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
			5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
			6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
		};
		template<std::size_t Size>
		struct bit_len {
		private:
			SPROUT_STATIC_CONSTEXPR std::size_t next_size = Size - 1;
			SPROUT_STATIC_CONSTEXPR std::size_t shift_bits = next_size * CHAR_BIT;
		private:
			template<typename Integral>
			SPROUT_CONSTEXPR Integral
			impl(Integral x, unsigned char i) const {
				return bit_len_8_table[i]
					? bit_len_8_table[i] + next_size * CHAR_BIT
					: sprout::detail::bit_len<next_size>().template operator()(x)
					;
			}
		public:
			template<typename Integral>
			SPROUT_CONSTEXPR Integral
			operator()(Integral x) const {
				return impl(x, static_cast<unsigned char>((x >> shift_bits) & UCHAR_MAX));
			}
		};
		template<>
		struct bit_len<1> {
		public:
			template<typename Integral>
			SPROUT_CONSTEXPR Integral
			operator()(Integral x) const {
				return bit_len_8_table[static_cast<unsigned char>(x & UCHAR_MAX)];
			}
		};
	}	// namespace detail
	//
	// bit_length
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		Integral
	>::type
	bit_length(Integral x) {
		return sprout::detail::bit_len<sizeof(Integral)>().template operator()(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_BIT_LENGTH_HPP
