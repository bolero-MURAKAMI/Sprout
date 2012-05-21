#ifndef SPROUT_INTEGER_BIT_LENGTH_HPP
#define SPROUT_INTEGER_BIT_LENGTH_HPP

#include <climits>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>

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
			template <typename IntType>
			SPROUT_CONSTEXPR IntType impl(IntType x, unsigned char i) const {
				return bit_len_8_table[i]
					? bit_len_8_table[i] + next_size * CHAR_BIT
					: sprout::detail::bit_len<next_size>().template operator()(x)
					;
			}
		public:
			template <typename IntType>
			SPROUT_CONSTEXPR IntType operator()(IntType x) const {
				return impl(x, static_cast<unsigned char>((x >> shift_bits) & UCHAR_MAX));
			}
		};
		template<>
		struct bit_len<1> {
		public:
			template<typename IntType>
			SPROUT_CONSTEXPR IntType operator()(IntType x) const {
				return bit_len_8_table[static_cast<unsigned char>(x & UCHAR_MAX)];
			}
		};
	}	// namespace detail
	//
	// bit_length
	//
	template<typename IntType>
	SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<IntType>::value,
		IntType
	>::type bit_length(IntType x) {
		return sprout::detail::bit_len<sizeof(IntType)>().template operator()(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_INTEGER_BIT_LENGTH_HPP
