/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_EXPR_EXPR_HPP
#define SPROUT_WEED_EXPR_EXPR_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/weed/expr/expr_fwd.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/traits/expr/expr_of.hpp>

namespace sprout {
	namespace weed {
		//
		// expr
		//
		template<typename Tag, typename... Args>
		class expr {
		public:
			typedef Tag expr_tag;
			typedef sprout::tuples::tuple<Args...> args_type;
		private:
			args_type args_;
		public:
			template<typename... As>
			explicit SPROUT_CONSTEXPR expr(As&&... args)
				: args_(SPROUT_FORWARD(As, args)...)
			{}
			SPROUT_CONSTEXPR args_type const& args() const {
				return args_;
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_EXPR_EXPR_HPP
