#ifndef SPROUT_FUNCTIONAL_HASH_HASH_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_HPP

#include <cstddef>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace hash_detail {
		template <typename T>
		struct is_basic_number
			: public std::integral_constant<
				bool,
				std::is_integral<T>::value
					&& (sizeof(T) <= sizeof(std::size_t))
			>
		{};
		template <typename T>
		struct is_long_number
			: public std::integral_constant<
				bool,
				std::is_integral<T>::value
					&& (sizeof(T) > sizeof(std::size_t))
					&& std::is_signed<T>::value
			>
		{};
		template <typename T>
		struct is_ulong_number
			: public std::integral_constant<
				bool,
				std::is_integral<T>::value
					&& (sizeof(T) > sizeof(std::size_t))
					&& std::is_unsigned<T>::value
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
					i - std::numeric_limits<std::size_t>::digits
					)
				: seed ^ static_cast<std::size_t>(val + (seed << 6) + (seed >> 2))
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_signed_1(T val, int length, std::size_t seed, T positive) {
			return hash_value_signed_2(val, length, seed, positive, length * std::numeric_limits<std::size_t>::digits);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_signed(T val) {
			return sprout::hash_detail::hash_value_signed_1(
				val,
				(std::numeric_limits<T>::digits - 1) / std::numeric_limits<std::size_t>::digits,
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
					i - std::numeric_limits<std::size_t>::digits
					)
				: seed ^ static_cast<std::size_t>(val + (seed << 6) + (seed >> 2))
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_unsigned_1(T val, int length, std::size_t seed) {
			return hash_value_unsigned_2(val, length, seed, length * std::numeric_limits<std::size_t>::digits);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value_unsigned(T val) {
			return sprout::hash_detail::hash_value_unsigned_1(
				val,
				(std::numeric_limits<T>::digits - 1) / std::numeric_limits<std::size_t>::digits,
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
	}	// namespace hash_detail

	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::hash_detail::is_basic_number<T>::value, std::size_t>::type
	hash_value(T v) {
		return static_cast<std::size_t>(v);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::hash_detail::is_long_number<T>::value, std::size_t>::type
	hash_value(T v) {
		return sprout::hash_detail::hash_value_signed(v);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::hash_detail::is_ulong_number<T>::value, std::size_t>::type
	hash_value(T v) {
		return sprout::hash_detail::hash_value_unsigned(v);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<std::is_enum<T>::value, std::size_t>::type
	hash_value(T v) {
		return sprout::hash_value(static_cast<typename std::underlying_type<T>::type>(v));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<std::is_pointer<typename std::remove_reference<T>::type>::value, std::size_t>::type
	hash_value(T&& v) {
		return sprout::hash_detail::hash_value_pointer(v);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(T const (&v)[N]) {
		return sprout::hash_range(&v[0], &v[0] + N);
	}

	//
	// to_hash
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	to_hash(T const& v) {
		using sprout::hash_value;
		return hash_value(v);
	}

	//
	// hash_combine
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_combine(std::size_t seed, T const& v) {
		return seed ^ (sprout::to_hash(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
	}

	//
	// hash_range
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR std::size_t
	hash_range(std::size_t seed, Iterator first, Iterator last) {
		return first != last
			? sprout::hash_range(sprout::hash_combine(seed, *first), sprout::next(first), last)
			: seed
			;
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR std::size_t
	hash_range(Iterator first, Iterator last) {
		return sprout::hash_range(0, first, last);
	}

	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_values_combine_impl(std::size_t seed, T const& v) {
			return sprout::hash_combine(seed, v);
		}
		template<typename Head, typename... Tail>
		inline SPROUT_CONSTEXPR std::size_t
		hash_values_combine_impl(std::size_t seed, Head const& head, Tail const&... tail) {
			return sprout::detail::hash_values_combine_impl(sprout::hash_combine(seed, head), tail...);
		}
	}	// namespace detail

	//
	// hash_values_combine
	//
	template<typename... Args>
	inline SPROUT_CONSTEXPR std::size_t
	hash_values_combine(std::size_t seed, Args const&... args) {
		return sprout::detail::hash_values_combine_impl(seed, args...);
	}

	//
	// hash_values
	//
	template<typename... Args>
	inline SPROUT_CONSTEXPR std::size_t
	hash_values(Args const&... args) {
		return sprout::hash_values_combine(0, args...);
	}

	//
	// hash
	//
	template<typename T>
	struct hash {
	public:
		typedef T argument_type;
		typedef std::size_t result_type;
	public:
		SPROUT_CONSTEXPR std::size_t operator()(T const& v) const {
			return sprout::to_hash(v);
		}
	};
	template<typename T>
	struct hash<T const>
		: public sprout::hash<T>
	{};
	template<typename T>
	struct hash<T volatile>
		: public sprout::hash<T>
	{};
	template<typename T>
	struct hash<T const volatile>
		: public sprout::hash<T>
	{};

#define SPROUT_HASH_SPECIALIZE(type) \
	template<> \
	struct hash<type> { \
	public: \
		typedef type argument_type; \
		typedef std::size_t result_type; \
	public: \
		SPROUT_CONSTEXPR std::size_t operator()(type v) const { \
			return sprout::to_hash(v); \
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
			return sprout::to_hash(v); \
		} \
	}

	SPROUT_HASH_SPECIALIZE(bool);
	SPROUT_HASH_SPECIALIZE(char);
	SPROUT_HASH_SPECIALIZE(signed char);
	SPROUT_HASH_SPECIALIZE(unsigned char);
	SPROUT_HASH_SPECIALIZE(char16_t);
	SPROUT_HASH_SPECIALIZE(char32_t);
	SPROUT_HASH_SPECIALIZE(wchar_t);
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

	template<typename T>
	struct hash<T*> {
	public:
		typedef T* argument_type;
		typedef std::size_t result_type;
	public:
		std::size_t operator()(T* v) const {
			return sprout::to_hash(v);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_HPP
