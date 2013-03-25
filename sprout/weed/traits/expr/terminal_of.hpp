#ifndef SPROUT_WEED_TRAITS_EXPR_TERMINAL_OF_HPP
#define SPROUT_WEED_TRAITS_EXPR_TERMINAL_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/remove_shallow_cvref.hpp>
#include <sprout/weed/expr/expr_fwd.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/traits/type/is_c_str.hpp>
#include <sprout/weed/detail/c_str_as_string.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// terminal_of
			//
			template<typename Arg, typename = void>
			struct terminal_of;
			template<typename Arg>
			struct terminal_of<
				Arg,
				typename std::enable_if<
					!sprout::weed::traits::is_c_str<
						typename sprout::remove_shallow_cvref<Arg>::type
					>::value
				>::type
			>
				: public sprout::identity<
					sprout::weed::expr<
						sprout::weed::tag::terminal,
						typename sprout::remove_shallow_cvref<Arg>::type
					>
				>
			{};
			template<typename Arg>
			struct terminal_of<
				Arg,
				typename std::enable_if<
					sprout::weed::traits::is_c_str<
						typename sprout::remove_shallow_cvref<Arg>::type
					>::value
				>::type
			>
				: public sprout::identity<
					sprout::weed::expr<
						sprout::weed::tag::terminal,
						typename sprout::weed::detail::c_str_as_string<
							typename sprout::remove_shallow_cvref<Arg>::type
						>::type
					>
				>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_EXPR_TERMINAL_OF_HPP
