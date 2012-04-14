#ifndef SPROUT_STRING_CONCAT_HPP
#define SPROUT_STRING_CONCAT_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>
#include <sprout/operation/fixed/push_back.hpp>
#include <sprout/operation/fixed/push_front.hpp>
#include <sprout/operation/fixed/append_back.hpp>
#include <sprout/operation/fixed/append_front.hpp>

namespace sprout {
	//
	// operator+
	//
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::push_back<sprout::basic_string<T, N, Traits>, T>::type operator+(
		sprout::basic_string<T, N, Traits> const& lhs,
		T const& rhs
		)
	{
		return sprout::fixed::push_back(lhs, rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::push_front<sprout::basic_string<T, N, Traits>, T>::type operator+(
		T const& lhs,
		sprout::basic_string<T, N, Traits> const& rhs
		)
	{
		return sprout::fixed::push_front(rhs, lhs);
	}
	template<typename T, std::size_t N, typename Traits, std::size_t N2>
	inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::append_back<
			sprout::basic_string<T, N, Traits>,
			sprout::basic_string<T, N2 - 1, Traits>
	>::type operator+(
		sprout::basic_string<T, N, Traits> const& lhs,
		T const (& rhs)[N2]
		)
	{
		return sprout::fixed::append_back(lhs, sprout::to_string(rhs));
	}
	template<typename T, std::size_t N, typename Traits, std::size_t N2>
	inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::append_front<
		sprout::basic_string<T, N, Traits>,
		sprout::basic_string<T, N2 - 1, Traits>
	>::type operator+(
		T const (& lhs)[N2],
		sprout::basic_string<T, N, Traits> const& rhs
		)
	{
		return sprout::fixed::append_front(rhs, sprout::to_string(lhs));
	}
	template<typename T, std::size_t N, typename Traits, std::size_t N2>
	inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::append_back<
		sprout::basic_string<T, N, Traits>,
		sprout::basic_string<T, N2, Traits>
	>::type operator+(
		sprout::basic_string<T, N, Traits> const& lhs,
		sprout::basic_string<T, N2, Traits> const& rhs
		)
	{
		return sprout::fixed::append_back(lhs, rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_CONCAT_HPP
