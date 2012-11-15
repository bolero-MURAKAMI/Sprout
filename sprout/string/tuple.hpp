#ifndef SPROUT_STRING_TUPLE_HPP
#define SPROUT_STRING_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I, typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR T&
	tuple_get(sprout::basic_string<T, N, Traits>& t) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_get: index out of range");
		return t[I];
	}
	template<std::size_t I, typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR T const&
	tuple_get(sprout::basic_string<T, N, Traits> const& t) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_get: index out of range");
		return t[I];
	}
	template<std::size_t I, typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR T&&
	tuple_get(sprout::basic_string<T, N, Traits>&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename T, std::size_t N, typename Traits>
	struct tuple_size<sprout::basic_string<T, N, Traits> >
		: public std::integral_constant<std::size_t, N>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, std::size_t N, typename Traits>
	struct tuple_element<I, sprout::basic_string<T, N, Traits> > {
	public:
		static_assert(I < N, "tuple_element<>: index out of range");
		typedef T type;
	};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_STRING_TUPLE_HPP
