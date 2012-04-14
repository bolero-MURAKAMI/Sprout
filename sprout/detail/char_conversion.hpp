#ifndef SPROUT_DETAIL_CHAR_CONVERSION_HPP
#define SPROUT_DETAIL_CHAR_CONVERSION_HPP

#include <cstddef>
#include <stdexcept>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename Elem, typename IntType>
		inline SPROUT_CONSTEXPR Elem int_to_char(IntType val, std::size_t base){
			return val >= 0 && val < 10 ? static_cast<Elem>('0') + val
				: val >= 10 && val < base ? static_cast<Elem>('a') + (val - 10)
				: throw std::invalid_argument("value out of bounds")
				;
		}
		template<typename Elem, typename IntType>
		inline SPROUT_CONSTEXPR Elem int_to_char(IntType val){
			return val >= 0 && val < 10 ? static_cast<Elem>('0') + val
				: throw std::invalid_argument("value out of bounds")
				;
		}

		template<typename IntType, typename Elem>
		inline SPROUT_CONSTEXPR IntType char_to_int(Elem c, std::size_t base){
			return c >= static_cast<Elem>('0') && c <= static_cast<Elem>('9') ? c - static_cast<Elem>('0')
				: c >= static_cast<Elem>('a') && c <= static_cast<Elem>('a' + (base - 11)) ? c - static_cast<Elem>('a') + 10
				: c >= static_cast<Elem>('A') && c <= static_cast<Elem>('A' + (base - 11)) ? c - static_cast<Elem>('A') + 10
				: static_cast<IntType>(-1)
				;
		}
		template<typename IntType, typename Elem>
		inline SPROUT_CONSTEXPR IntType char_to_int(Elem c){
			return c >= static_cast<Elem>('0') && c <= static_cast<Elem>('9') ? c - static_cast<Elem>('0')
				: static_cast<IntType>(-1)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_CHAR_CONVERSION_HPP
