#ifndef SPROUT_ENDIAN_TRAITS_HPP
#define SPROUT_ENDIAN_TRAITS_HPP

#include <cstddef>
#include <climits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// big_endian_traits
	//
	template<typename T>
	class big_endian_traits {
	public:
		typedef T type;
	public:
		static SPROUT_CONSTEXPR std::size_t size() {
			return sizeof(type);
		}
		static SPROUT_CONSTEXPR unsigned char get_byte(type const& t, std::size_t i) {
			return static_cast<unsigned char>(
				(t & (UCHAR_MAX << CHAR_BIT * ((size() - 1) - i)))
					>> CHAR_BIT * ((size() - 1) - i)
				);
		}
	};
	//
	// little_endian_traits
	//
	template<typename T>
	class little_endian_traits {
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
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_ENDIAN_TRAITS_HPP
