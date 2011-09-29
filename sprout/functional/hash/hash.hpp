#ifndef SPROUT_FUNCTIONAL_HASH_HPP
#define SPROUT_FUNCTIONAL_HASH_HPP

#include <cstddef>
#include <limits>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>

namespace sprout {
	//
	// hash_value
	//
	SPROUT_CONSTEXPR inline std::size_t hash_value(bool v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(char v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(wchar_t v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned char v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(signed char v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(short v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned short v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(int v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned int v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(long v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned long v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(long long v);
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned long long v);
	//SPROUT_CONSTEXPR std::size_t inline hash_value(float v);
	//SPROUT_CONSTEXPR std::size_t inline hash_value(double v);
	//SPROUT_CONSTEXPR std::size_t inline hash_value(long double v);
	template<typename T>
	SPROUT_CONSTEXPR std::size_t hash_value(T*);
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR std::size_t hash_value(T const (&v)[N]);

	namespace hash_detail {
		template<typename T>
		SPROUT_CONSTEXPR std::size_t hash_value_signed_2(T val, int length, std::size_t seed, T positive, std::size_t i) {
			return i > 0
				? hash_value_signed_2(
					val,
					length,
					seed ^ static_cast<std::size_t>((positive >> i) + (seed << 6) + (seed >> 2)),
					positive,
					i - std::numeric_limits<std::size_t>::digits
					)
				: seed ^ static_cast<std::size_t>(val + (seed << 6) + (seed >> 2))
				;
		}
		template<typename T>
		SPROUT_CONSTEXPR std::size_t hash_value_signed_1(T val, int length, std::size_t seed, T positive) {
			return hash_value_signed_2(val, length, seed, positive, length * std::numeric_limits<std::size_t>::digits);
		}
		template<typename T>
		SPROUT_CONSTEXPR std::size_t hash_value_signed(T val) {
			return sprout::hash_detail::hash_value_signed_1(
				val,
				(std::numeric_limits<T>::digits - 1) / std::numeric_limits<std::size_t>::digits,
				0,
				val < 0 ? -1 - val : val
				);
		}

		template<typename T>
		SPROUT_CONSTEXPR std::size_t hash_value_unsigned_2(T val, int length, std::size_t seed, std::size_t i) {
			return i > 0
				? hash_value_unsigned_2(
					val,
					length,
					seed ^ static_cast<std::size_t>((val >> i) + (seed << 6) + (seed >> 2)),
					i - std::numeric_limits<std::size_t>::digits
					)
				: seed ^ static_cast<std::size_t>(val + (seed << 6) + (seed >> 2))
				;
		}
		template<typename T>
		SPROUT_CONSTEXPR std::size_t hash_value_unsigned_1(T val, int length, std::size_t seed) {
			return hash_value_unsigned_2(val, length, seed, length * std::numeric_limits<std::size_t>::digits);
		}
		template<typename T>
		SPROUT_CONSTEXPR std::size_t hash_value_unsigned(T val) {
			return sprout::hash_detail::hash_value_unsigned_1(
				val,
				(std::numeric_limits<T>::digits - 1) / std::numeric_limits<std::size_t>::digits,
				0
				);
		}

		SPROUT_CONSTEXPR inline std::size_t hash_value_pointer_1(std::size_t x) {
			return x + (x >> 3);
		}
		template<typename T>
		SPROUT_CONSTEXPR std::size_t hash_value_pointer(T* v) {
			return sprout::hash_detail::hash_value_pointer_1(static_cast<std::size_t>(reinterpret_cast<std::ptrdiff_t>(v)));
		}
	}	// namespace hash_detail

	//
	// hash_value
	//
	SPROUT_CONSTEXPR inline std::size_t hash_value(bool v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(char v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(wchar_t v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned char v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(signed char v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(short v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned short v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(int v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned int v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(long v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned long v) {
		return static_cast<std::size_t>(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(long long v) {
		return sprout::hash_detail::hash_value_signed(v);
	}
	SPROUT_CONSTEXPR inline std::size_t hash_value(unsigned long long v) {
		return sprout::hash_detail::hash_value_unsigned(v);
	}
	template<typename T>
	SPROUT_CONSTEXPR std::size_t hash_value(T* v) {
		return sprout::hash_detail::hash_value_pointer(v);
	}
	template<typename T, std::size_t N >
	SPROUT_CONSTEXPR std::size_t hash_value(T const (&v)[N]) {
		return sprout::hash_range(&v[0], &v[0] + N);
	}

	//
	// hash_combine
	//
	template<typename T>
	SPROUT_CONSTEXPR std::size_t hash_combine(std::size_t seed, T const& v) {
		return seed ^ (sprout::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
	}

	//
	// hash_range
	//
	template<typename Iterator>
	SPROUT_CONSTEXPR std::size_t hash_range(Iterator first, Iterator last) {
		return sprout::hash_range(0, first, last);
	}
	template<typename Iterator>
	SPROUT_CONSTEXPR std::size_t hash_range(std::size_t seed, Iterator first, Iterator last) {
		return first != last
			? sprout::hash_range(sprout::hash_combine(seed, *first), first + 1, last)
			: seed
			;
	}

#define SPROUT_HASH_SPECIALIZE(type) \
	template<> \
	struct hash<type> { \
	public: \
		typedef type argument_type; \
		typedef std::size_t result_type; \
	public: \
		SPROUT_CONSTEXPR std::size_t operator()(type v) const { \
			return sprout::hash_value(v); \
		} \
	}
#define SPROUT_HASH_SPECIALIZE_REF(type) \
	template<> \
	struct hash<type> { \
	public: \
		typedef type argument_type; \
		typedef std::size_t result_type; \
	public: \
		SPROUT_CONSTEXPR std::size_t operator()(type const& v) const { \
			return sprout::hash_value(v); \
		} \
	}

	//
	// hash
	//
	SPROUT_HASH_SPECIALIZE(bool);
	SPROUT_HASH_SPECIALIZE(char);
	SPROUT_HASH_SPECIALIZE(wchar_t);
	SPROUT_HASH_SPECIALIZE(signed char);
	SPROUT_HASH_SPECIALIZE(unsigned char);
	SPROUT_HASH_SPECIALIZE(short);
	SPROUT_HASH_SPECIALIZE(unsigned short);
	SPROUT_HASH_SPECIALIZE(int);
	SPROUT_HASH_SPECIALIZE(unsigned int);
	SPROUT_HASH_SPECIALIZE(long);
	SPROUT_HASH_SPECIALIZE(unsigned long);
	SPROUT_HASH_SPECIALIZE(long long);
	SPROUT_HASH_SPECIALIZE(unsigned long long);

#undef SPROUT_HASH_SPECIALIZE
#undef SPROUT_HASH_SPECIALIZE_REF

	template <class T>
	struct hash<T*> {
	public:
		typedef T* argument_type;
		typedef std::size_t result_type;
	public: \
		SPROUT_CONSTEXPR std::size_t operator()(T* v) const {
			return sprout::hash_value(v);
		}
	};
}	//namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HPP

