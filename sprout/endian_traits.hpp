#ifndef SPROUT_ENDIAN_TRAITS_HPP
#define SPROUT_ENDIAN_TRAITS_HPP

#include <cstddef>
#include <climits>
#include <type_traits>
#include <sprout/config.hpp>

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
			static SPROUT_CONSTEXPR std::size_t size() {
				return sizeof(type);
			}
			static SPROUT_CONSTEXPR unsigned char get_byte(type const& t, std::size_t i) {
				return static_cast<unsigned char>(t);
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
			static SPROUT_CONSTEXPR unsigned char get_byte(type const& t, std::size_t i) {
				return static_cast<unsigned char>(t);
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
