#ifndef SPROUT_WEED_DETAIL_NDIGITS_HPP
#define SPROUT_WEED_DETAIL_NDIGITS_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/weed/detail/digits.hpp>
#include <sprout/weed/detail/bdigits.hpp>
#include <sprout/weed/detail/odigits.hpp>
#include <sprout/weed/detail/xdigits.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<std::size_t Radix, typename IntType, typename Elem>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_ndigit(
				Elem c,
				typename std::enable_if<Radix == 10>::type* = 0
				)
			{
				return sprout::weed::detail::from_digit<IntType>(c);
			}
			template<std::size_t Radix, typename IntType, typename Elem>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_ndigit(
				Elem c,
				typename std::enable_if<Radix == 2>::type* = 0
				)
			{
				return sprout::weed::detail::from_bdigit<IntType>(c);
			}
			template<std::size_t Radix, typename IntType, typename Elem>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_ndigit(
				Elem c,
				typename std::enable_if<Radix == 8>::type* = 0
				)
			{
				return sprout::weed::detail::from_odigit<IntType>(c);
			}
			template<std::size_t Radix, typename IntType, typename Elem>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<IntType, bool> from_ndigit(
				Elem c,
				typename std::enable_if<Radix == 16>::type* = 0
				)
			{
				return sprout::weed::detail::from_xdigit<IntType>(c);
			}
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_NDIGITS_HPP
