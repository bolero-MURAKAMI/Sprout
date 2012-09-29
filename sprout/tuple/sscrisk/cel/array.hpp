#ifndef SPROUT_TUPLE_SSCRISK_CEL_ARRAY_HPP
#define SPROUT_TUPLE_SSCRISK_CEL_ARRAY_HPP

#include <cstddef>
#include <type_traits>
#include <sscrisk/cel/array.hpp>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout_adl {
	//
	// tuple_get
	//
	template<std::size_t I, typename T, std::size_t N>
	inline SPROUT_CONSTEXPR T&
	tuple_get(sscrisk::cel::array<T, N>& t) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_get: index out of range");
		return t[I];
	}
	template<std::size_t I, typename T, std::size_t N>
	inline SPROUT_CONSTEXPR T const&
	tuple_get(sscrisk::cel::array<T, N> const& t) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_get: index out of range");
		return t[I];
	}
	template<std::size_t I, typename T, std::size_t N>
	inline SPROUT_CONSTEXPR T&&
	tuple_get(sscrisk::cel::array<T, N>&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout_adl

#endif	// #ifndef SPROUT_TUPLE_SSCRISK_CEL_ARRAY_HPP
