/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_TRAITS_EXPR_EXPR_OF_HPP
#define SPROUT_WEED_TRAITS_EXPR_EXPR_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/expr/expr_fwd.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// expr_of
			//
			template<typename Tag, typename... Args>
			struct expr_of
				: public sprout::identity<
					sprout::weed::expr<
						Tag,
						typename sprout::weed::traits::terminal_or_expr_of<
							typename std::remove_reference<Args>::type
						>::type...
					>
				>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_EXPR_EXPR_OF_HPP
