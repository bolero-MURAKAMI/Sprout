#ifndef SPROUT_WEED_TRAITS_PARSER_LIMIT_OF_HPP
#define SPROUT_WEED_TRAITS_PARSER_LIMIT_OF_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/expr/expr.hpp>
#include <sprout/weed/expr/tag.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// limit_of
			//
			template<typename T, typename Iterator, typename Context, typename = void>
			struct limit_of
				: public std::integral_constant<std::size_t, static_cast<std::size_t>(-1)>
			{};
			template<typename T, typename Iterator, typename Context>
			struct limit_of<T const, Iterator, Context>
				: public sprout::weed::traits::limit_of<T, Iterator, Context>
			{};
			template<typename Arg, typename Iterator, typename Context>
			struct limit_of<sprout::weed::expr<sprout::weed::tag::terminal, Arg>, Iterator, Context>
				: public sprout::weed::traits::limit_of<Arg, Iterator, Context>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_PARSER_LIMIT_OF_HPP
