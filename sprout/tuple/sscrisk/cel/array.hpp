#ifndef SPROUT_TUPLE_SSCRISK_CEL_ARRAY_HPP
#define SPROUT_TUPLE_SSCRISK_CEL_ARRAY_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sscrisk/cel/array.hpp>

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename T, std::size_t N>
		inline SPROUT_CONSTEXPR T&
		get(sscrisk::cel::array<T, N>& t) SPROUT_NOEXCEPT {
			static_assert(I < N, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename T, std::size_t N>
		inline SPROUT_CONSTEXPR T const&
		get(sscrisk::cel::array<T, N> const& t) SPROUT_NOEXCEPT {
			static_assert(I < N, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename T, std::size_t N>
		inline SPROUT_CONSTEXPR T&&
		get(sscrisk::cel::array<T, N>&& t) SPROUT_NOEXCEPT {
			return sprout::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_SSCRISK_CEL_ARRAY_HPP
