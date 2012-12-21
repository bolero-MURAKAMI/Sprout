#ifndef SPROUT_STRING_CONCAT_HPP
#define SPROUT_STRING_CONCAT_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/string/string.hpp>

namespace sprout {
	namespace detail {
		template<typename T, std::size_t N, typename Traits, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N + 1, Traits>
		string_concat(
			sprout::basic_string<T, N, Traits> const& lhs, std::size_t lsize,
			T const& rhs,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, N + 1, Traits>{
				{
					(Indexes < lsize ? lhs[Indexes]
						: Indexes < lsize + 1 ? rhs
						: T()
						)...
					},
				lsize + 1
				};
		}
		template<typename T, std::size_t N, typename Traits, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, 1 + N, Traits>
		string_concat(
			T const& lhs,
			sprout::basic_string<T, N, Traits> const& rhs, std::size_t rsize,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, 1 + N, Traits>{
				{
					(Indexes < 1 ? lhs
						: Indexes < 1 + rsize ? rhs[Indexes - 1]
						: T()
						)...
					},
				1 + rsize
				};
		}
		template<typename T, std::size_t N, typename Traits, std::size_t M, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N + (M - 1), Traits>
		string_concat(
			sprout::basic_string<T, N, Traits> const& lhs, std::size_t lsize,
			T const (& rhs)[M], std::size_t rsize,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, N + (M - 1), Traits>{
				{
					(Indexes < lsize ? lhs[Indexes]
						: Indexes < lsize + rsize ? rhs[Indexes - lsize]
						: T()
						)...
					},
				lsize + rsize
				};
		}
		template<typename T, std::size_t N, typename Traits, std::size_t M, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, (M - 1) + N, Traits>
		string_concat(
			T const (& lhs)[M], std::size_t lsize,
			sprout::basic_string<T, N, Traits> const& rhs, std::size_t rsize,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, (M - 1) + N, Traits>{
				{
					(Indexes < lsize ? lhs[Indexes]
						: Indexes < lsize + rsize ? rhs[Indexes - lsize]
						: T()
						)...
					},
				lsize + rsize
				};
		}
		template<typename T, std::size_t N1, std::size_t N2, typename Traits, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N1 + N2, Traits>
		string_concat(
			sprout::basic_string<T, N1, Traits> const& lhs, std::size_t lsize,
			sprout::basic_string<T, N2, Traits> const& rhs, std::size_t rsize,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, N1 + N2, Traits>{
				{
					(Indexes < lsize ? lhs[Indexes]
						: Indexes < lsize + rsize ? rhs[Indexes - lsize]
						: T()
						)...
					},
				lsize + rsize
				};
		}
	}	// namespace detail

	//
	// operator+
	//
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N + 1, Traits>
	operator+(sprout::basic_string<T, N, Traits> const& lhs, T const& rhs) {
		return sprout::detail::string_concat(
			lhs, lhs.size(),
			rhs,
			sprout::index_range<0, N + 1>::make()
			);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, 1 + N, Traits>
	operator+(T const& lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return sprout::detail::string_concat(
			lhs,
			rhs, rhs.size(),
			sprout::index_range<0, 1 + N>::make()
			);
	}
	template<typename T, std::size_t N, typename Traits, std::size_t M>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N + (M - 1), Traits>
	operator+(sprout::basic_string<T, N, Traits> const& lhs, T const (& rhs)[M]) {
		typedef sprout::char_traits_helper<Traits> traits_type;
		return sprout::detail::string_concat(
			lhs, lhs.size(),
			rhs, traits_type::length(rhs, M - 1),
			sprout::index_range<0, N + (M - 1)>::make()
			);
	}
	template<typename T, std::size_t N, typename Traits, std::size_t M>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, (M - 1) + N, Traits>
	operator+(T const (& lhs)[M], sprout::basic_string<T, N, Traits> const& rhs) {
		typedef sprout::char_traits_helper<Traits> traits_type;
		return sprout::detail::string_concat(
			lhs, traits_type::length(lhs, M - 1),
			rhs, rhs.size(),
			sprout::index_range<0, (M - 1) + N>::make()
			);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N1 + N2, Traits>
	operator+(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return sprout::detail::string_concat(
			lhs, lhs.size(),
			rhs, rhs.size(),
			sprout::index_range<0, N1 + N2>::make()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_CONCAT_HPP
