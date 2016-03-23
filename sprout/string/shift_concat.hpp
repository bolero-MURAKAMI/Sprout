/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_SHIFT_CONCAT_HPP
#define SPROUT_STRING_SHIFT_CONCAT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/string/string.hpp>

namespace sprout {
	namespace detail {
		template<std::size_t N>
		inline SPROUT_CONSTEXPR std::size_t checked_length(std::size_t n) {
			return n <= N ? n
				: throw std::length_error("length exceeded")
				;
		}
	}	// namespace detail

	namespace detail {
		template<typename T, std::size_t N, typename Traits, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
		string_rshift(
			sprout::basic_string<T, N, Traits> const& lhs, std::size_t lsize,
			T const& rhs,
			sprout::index_tuple<Indexes...>
			)
		{
			typedef sprout::detail::string_construct_access<T, N, Traits> access_type;
			return access_type::raw_construct(
				sprout::detail::checked_length<N>(lsize + 1),
				(Indexes < lsize ? lhs[Indexes]
					: Indexes < lsize + 1 ? rhs
					: T()
					)...
				);
		}
		template<typename T, std::size_t N, typename Traits, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
		string_rshift(
			sprout::basic_string<T, N, Traits> const& lhs, std::size_t lsize,
			T const* rhs, std::size_t rsize,
			sprout::index_tuple<Indexes...>
			)
		{
			typedef sprout::detail::string_construct_access<T, N , Traits> access_type;
			return access_type::raw_construct(
				sprout::detail::checked_length<N>(lsize + rsize),
				(Indexes < lsize ? lhs[Indexes]
					: Indexes < lsize + rsize ? rhs[Indexes - lsize]
					: T()
					)...
				);
		}
		template<typename T, std::size_t N1, std::size_t N2, typename Traits, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N1, Traits>
		string_rshift(
			sprout::basic_string<T, N1, Traits> const& lhs, std::size_t lsize,
			sprout::basic_string<T, N2, Traits> const& rhs, std::size_t rsize,
			sprout::index_tuple<Indexes...>
			)
		{
			typedef sprout::detail::string_construct_access<T, N1, Traits> access_type;
			return access_type::raw_construct(
				sprout::detail::checked_length<N1>(lsize + rsize),
				(Indexes < lsize ? lhs[Indexes]
					: Indexes < lsize + rsize ? rhs[Indexes - lsize]
					: T()
					)...
				);
		}
	}	// namespace detail
	//
	// operator<<
	//
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
	operator<<(sprout::basic_string<T, N, Traits> const& lhs, T const& rhs) {
		return sprout::detail::string_rshift(
			lhs, lhs.size(),
			rhs,
			sprout::make_index_tuple<N>::make()
			);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
	operator<<(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return sprout::detail::string_rshift(
			lhs, lhs.size(),
			rhs, Traits::length(rhs),
			sprout::make_index_tuple<N>::make()
			);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N1, Traits>
	operator<<(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return sprout::detail::string_rshift(
			lhs, lhs.size(),
			rhs, rhs.size(),
			sprout::make_index_tuple<N1>::make()
			);
	}

	namespace detail {
		template<typename T, std::size_t N, typename Traits, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
		string_lshift(
			sprout::basic_string<T, N, Traits> const& lhs, std::size_t lsize,
			T const& rhs,
			sprout::index_tuple<Indexes...>
			)
		{
			typedef sprout::detail::string_construct_access<T, N, Traits> access_type;
			return access_type::raw_construct(
				sprout::detail::checked_length<N>(1 + lsize),
				(Indexes < 1 ? rhs
					: Indexes < 1 + lsize ? lhs[Indexes - 1]
					: T()
					)...
				);
		}
		template<typename T, std::size_t N, typename Traits, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
		string_lshift(
			sprout::basic_string<T, N, Traits> const& lhs, std::size_t lsize,
			T const* rhs, std::size_t rsize,
			sprout::index_tuple<Indexes...>
			)
		{
			typedef sprout::detail::string_construct_access<T, N , Traits> access_type;
			return access_type::raw_construct(
				sprout::detail::checked_length<N>(rsize + lsize),
				(Indexes < rsize ? rhs[Indexes]
					: Indexes < rsize + lsize ? lhs[Indexes - rsize]
					: T()
					)...
				);
		}
		template<typename T, std::size_t N1, std::size_t N2, typename Traits, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N1, Traits>
		string_lshift(
			sprout::basic_string<T, N1, Traits> const& lhs, std::size_t lsize,
			sprout::basic_string<T, N2, Traits> const& rhs, std::size_t rsize,
			sprout::index_tuple<Indexes...>
			)
		{
			typedef sprout::detail::string_construct_access<T, N1, Traits> access_type;
			return access_type::raw_construct(
				sprout::detail::checked_length<N1>(rsize + lsize),
				(Indexes < rsize ? rhs[Indexes]
					: Indexes < rsize + lsize ? lhs[Indexes - rsize]
					: T()
					)...
				);
		}
	}	// namespace detail
	//
	// operator>>
	//
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
	operator>>(sprout::basic_string<T, N, Traits> const& lhs, T const& rhs) {
		return sprout::detail::string_lshift(
			lhs, lhs.size(),
			rhs,
			sprout::make_index_tuple<N>::make()
			);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
	operator>>(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return sprout::detail::string_lshift(
			lhs, lhs.size(),
			rhs, Traits::length(rhs),
			sprout::make_index_tuple<N>::make()
			);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N1, Traits>
	operator>>(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return sprout::detail::string_lshift(
			lhs, lhs.size(),
			rhs, rhs.size(),
			sprout::make_index_tuple<N1>::make()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_SHIFT_CONCAT_HPP
