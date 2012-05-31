#ifndef SPROUT_TUPLE_ARRAY_HPP
#define SPROUT_TUPLE_ARRAY_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array.hpp>

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename T, std::size_t N>
		inline SPROUT_CONSTEXPR T&
		get(sprout::array<T, N>& t) SPROUT_NOEXCEPT {
			static_assert(I < N, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename T, std::size_t N>
		inline SPROUT_CONSTEXPR T const&
		get(sprout::array<T, N> const& t) SPROUT_NOEXCEPT {
			static_assert(I < N, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename T, std::size_t N>
		inline SPROUT_CONSTEXPR T&&
		get(sprout::array<T, N>&& t) SPROUT_NOEXCEPT {
			return sprout::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_ARRAY_HPP
