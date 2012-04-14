#ifndef SPROUT_STRING_MAKE_STRING_HPP
#define SPROUT_STRING_MAKE_STRING_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/array.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/string/string.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// make_string
	//
	namespace detail {
		template<typename T, std::size_t N, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N - 1> make_string_impl_1(
			sprout::array<T, N> const& arr,
			std::size_t n,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, N - 1>{{(Indexes < n ? arr[Indexes] : T())...}, n};
		}
		template<typename T, std::size_t N, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N - 1> make_string_impl(
			sprout::array<T, N> const& arr,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::detail::make_string_impl_1(
				arr,
				sprout::char_traits<T>::length(arr.begin()),
				sprout::index_tuple<Indexes...>()
				);
		}
	}	// namespace detail
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, 1 + sizeof...(Types)>
	make_string(T&& t, Types&&... args) {
		return sprout::detail::make_string_impl(
			sprout::make_array<typename std::decay<T>::type>(
				sprout::forward<T>(t),
				sprout::forward<Types>(args)...,
				typename std::decay<T>::type()
				),
			typename sprout::index_range<0, 1 + sizeof...(Types)>::type()
			);
	}

	//
	// make_string_as
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, 0>
	make_string_as() {
		return sprout::basic_string<typename std::decay<T>::type, 0>{};
	}
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR sprout::basic_string<typename std::decay<T>::type, sizeof...(Types)>
	make_string_as(Types&&... args) {
		return sprout::detail::make_string_impl(
			sprout::make_array<typename std::decay<T>::type>(
				sprout::forward<Types>(args)...,
				typename std::decay<T>::type()
				),
			typename sprout::index_range<0, 1 + sizeof...(Types)>::type()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_MAKE_STRING_HPP
