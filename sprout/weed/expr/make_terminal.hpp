#ifndef SPROUT_WEED_EXPR_MAKE_TERMINAL_HPP
#define SPROUT_WEED_EXPR_MAKE_TERMINAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/weed/traits/type/is_c_str.hpp>
#include <sprout/weed/traits/expr/terminal_of.hpp>
#include <sprout/weed/detail/uncvref.hpp>

namespace sprout {
	namespace weed {
		//
		// make_terminal
		//
		template<typename Arg>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			!sprout::weed::traits::is_c_str<
				typename sprout::weed::detail::uncvref<Arg>::type
			>::value,
			typename sprout::weed::traits::terminal_of<Arg>::type
		>::type make_terminal(Arg&& arg) {
			return typename sprout::weed::traits::terminal_of<Arg>::type(
				sprout::forward<Arg>(arg)
				);
		}
		template<typename Arg>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sprout::weed::traits::is_c_str<
				typename sprout::weed::detail::uncvref<Arg>::type
			>::value,
			typename sprout::weed::traits::terminal_of<Arg>::type
		>::type make_terminal(Arg&& arg) {
			return typename sprout::weed::traits::terminal_of<Arg>::type(
				sprout::to_string(sprout::forward<Arg>(arg))
				);
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_EXPR_MAKE_TERMINAL_HPP
