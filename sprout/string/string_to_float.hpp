#ifndef SPROUT_STRING_STRING_TO_FLOAT_HPP
#define SPROUT_STRING_STRING_TO_FLOAT_HPP

#include <cstddef>
#include <string>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>
#include <sprout/cstdlib/str_to_float.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace detail {
		template<
			typename FloatType,
			typename Elem,
			std::size_t N,
			typename Traits
		>
		inline FloatType string_to_float_dynamic(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx) {
			Elem* endptr = nullptr;
			FloatType result = sprout::detail::str_to_float<FloatType>(str.c_str(), &endptr);
			*idx = endptr - str.c_str();
			return result;
		}
	}

	//
	// string_to_float
	//
	template<
		typename FloatType,
		typename Elem,
		std::size_t N,
		typename Traits,
		typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR FloatType string_to_float(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx) {
		return !idx ? sprout::detail::str_to_float<FloatType>(str.begin())
			: sprout::detail::string_to_float_dynamic<FloatType>(str, idx)
			;
	}
	template<
		typename FloatType,
		typename Elem,
		std::size_t N,
		typename Traits,
		typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR FloatType string_to_float(sprout::basic_string<Elem, N, Traits> const& str) {
		return sprout::detail::str_to_float<FloatType>(str.begin());
	}

	//
	// stof
	//
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR float stof(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx) {
		return sprout::string_to_float<float>(str, idx);
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR float stof(sprout::basic_string<Elem, N, Traits> const& str) {
		return sprout::string_to_float<float>(str);
	}

	//
	// stod
	//
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR double stod(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx) {
		return sprout::string_to_float<double>(str, idx);
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR double stod(sprout::basic_string<Elem, N, Traits> const& str) {
		return sprout::string_to_float<double>(str);
	}

	//
	// stold
	//
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR long double stold(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx) {
		return sprout::string_to_float<long double>(str, idx);
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR long double stold(sprout::basic_string<Elem, N, Traits> const& str) {
		return sprout::string_to_float<long double>(str);
	}

	//
	// from_string
	//
	template<
		typename FloatType,
		typename Elem,
		std::size_t N,
		typename Traits,
		typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR FloatType from_string(sprout::basic_string<Elem, N, Traits> const& str, std::size_t* idx) {
		return sprout::string_to_float<FloatType>(str, idx);
	}
	template<
		typename FloatType,
		typename Elem,
		std::size_t N,
		typename Traits,
		typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR FloatType from_string(sprout::basic_string<Elem, N, Traits> const& str) {
		return sprout::string_to_float<FloatType>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_STRING_TO_FLOAT_HPP
