#ifndef SPROUT_TUPLE_STRING_HPP
#define SPROUT_TUPLE_STRING_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/string.hpp>

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename T, std::size_t N, typename Traits>
		inline SPROUT_CONSTEXPR T&
		get(sprout::basic_string<T, N, Traits>& t) SPROUT_NOEXCEPT {
			static_assert(I < N, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename T, std::size_t N, typename Traits>
		inline SPROUT_CONSTEXPR T const&
		get(sprout::basic_string<T, N, Traits> const& t) SPROUT_NOEXCEPT {
			static_assert(I < N, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename T, std::size_t N, typename Traits>
		inline SPROUT_CONSTEXPR T&&
		get(sprout::basic_string<T, N, Traits>&& t) SPROUT_NOEXCEPT {
			return sprout::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_STRING_HPP
