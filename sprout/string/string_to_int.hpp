#ifndef SPROUT_STRING_STRING_TO_INT_HPP
#define SPROUT_STRING_STRING_TO_INT_HPP

#include <cstddef>
#include <string>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>
#include <sprout/cstdlib/str_to_int.hpp>
#include <sprout/utility/enabler_if.hpp>

namespace sprout {
	namespace detail {
		template<
			typename IntType,
			typename Elem,
			std::size_t N,
			typename Traits
		>
		inline IntType string_to_int_dynamic(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx, int base = 10) {
			Elem* endptr = nullptr;
			IntType result = sprout::detail::str_to_int<IntType>(str.c_str(), &endptr, base);
			*idx = endptr - str.c_str();
			return result;
		}
	}

	//
	// string_to_int
	//
	template<
		typename IntType,
		typename Elem,
		std::size_t N,
		typename Traits,
		typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR IntType string_to_int(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx, int base = 10) {
		return !idx ? sprout::detail::str_to_int<IntType>(str.begin(), base)
			: sprout::detail::string_to_int_dynamic<IntType>(str, idx, base)
			;
	}
	template<
		typename IntType,
		typename Elem,
		std::size_t N,
		typename Traits,
		typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR IntType string_to_int(sprout::basic_string<Elem, N, Traits> const& str, int base = 10) {
		return sprout::detail::str_to_int<IntType>(str.begin(), base);
	}

	//
	// stoi
	//
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR int stoi(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx, int base = 10) {
		return sprout::string_to_int<int>(str, idx, base);
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR int stoi(sprout::basic_string<Elem, N, Traits> const& str, int base = 10) {
		return sprout::string_to_int<int>(str, base);
	}

	//
	// stol
	//
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR long stol(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx, int base = 10) {
		return sprout::string_to_int<long>(str, idx, base);
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR long stol(sprout::basic_string<Elem, N, Traits> const& str, int base = 10) {
		return sprout::string_to_int<long>(str, base);
	}

	//
	// stoul
	//
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR unsigned long stoul(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx, int base = 10) {
		return sprout::string_to_int<unsigned long>(str, idx, base);
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR unsigned long stoul(sprout::basic_string<Elem, N, Traits> const& str, int base = 10) {
		return sprout::string_to_int<unsigned long>(str, base);
	}

	//
	// stoll
	//
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR long long stoll(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx, int base = 10) {
		return sprout::string_to_int<long long>(str, idx, base);
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR long long stoll(sprout::basic_string<Elem, N, Traits> const& str, int base = 10) {
		return sprout::string_to_int<long long>(str, base);
	}

	//
	// stoull
	//
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR unsigned long long stoull(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx, int base = 10) {
		return sprout::string_to_int<unsigned long long>(str, idx, base);
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR unsigned long long stoull(sprout::basic_string<Elem, N, Traits> const& str, int base = 10) {
		return sprout::string_to_int<unsigned long long>(str, base);
	}

	//
	// from_string
	//
	template<
		typename IntType,
		typename Elem,
		std::size_t N,
		typename Traits,
		typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR IntType from_string(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx) {
		return sprout::string_to_int<IntType>(str, idx);
	}
	template<
		typename IntType,
		typename Elem,
		std::size_t N,
		typename Traits,
		typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR IntType from_string(sprout::basic_string<Elem, N, Traits> const& str) {
		return sprout::string_to_int<IntType>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_STRING_TO_INT_HPP
