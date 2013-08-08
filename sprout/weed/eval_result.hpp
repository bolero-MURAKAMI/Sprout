/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_EVAL_RESULT_HPP
#define SPROUT_WEED_EVAL_RESULT_HPP

#include <sprout/config.hpp>
#include <sprout/weed/parser_result.hpp>

namespace sprout {
	namespace weed {
		//
		// eval_result
		//
		template<typename Context, typename Iterator, typename Attribute>
		class eval_result {
		public:
			typedef sprout::weed::parser_result<Iterator, Attribute> presult_type;
		private:
			presult_type presult_;
			Context ctx_;
		public:
			eval_result() = default;
			SPROUT_CONSTEXPR eval_result(
				bool success,
				Iterator current,
				Attribute const& attr,
				Context const& ctx
				)
				: presult_(success, current, attr)
				, ctx_(ctx)
			{}
			SPROUT_CONSTEXPR eval_result(
				presult_type const& presult,
				Context const& ctx
				)
				: presult_(presult)
				, ctx_(ctx)
			{}
			SPROUT_CONSTEXPR presult_type const& presult() const {
				return presult_;
			}
			SPROUT_CONSTEXPR bool success() const {
				return presult_.success();
			}
			SPROUT_CONSTEXPR Iterator current() const {
				return presult_.current();
			}
			SPROUT_CONSTEXPR Attribute const& attr() const {
				return presult_.attr();
			}
			SPROUT_CONSTEXPR Context const& ctx() const {
				return ctx_;
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_EVAL_RESULT_HPP
