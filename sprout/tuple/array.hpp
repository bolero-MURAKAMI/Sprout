#ifndef SPROUT_TUPLE_ARRAY_HPP
#define SPROUT_TUPLE_ARRAY_HPP

#include <cstddef>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/array.hpp>

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename T, std::size_t N>
		T& get(sprout::array<T, N>& t) SPROUT_NOEXCEPT {
			static_assert(I < N, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename T, std::size_t N>
		SPROUT_CONSTEXPR T const& get(sprout::array<T, N> const& t) SPROUT_NOEXCEPT {
			static_assert(I < N, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename T, std::size_t N>
		T&& get(sprout::array<T, N>&& t) SPROUT_NOEXCEPT {
			return std::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_COMPARISON_HPP
