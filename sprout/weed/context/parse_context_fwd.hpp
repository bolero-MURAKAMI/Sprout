/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_FWD_HPP
#define SPROUT_WEED_CONTEXT_PARSE_CONTEXT_FWD_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace weed {
		//
		// parse_context
		//
		template<typename Iterator>
		class parse_context {
		public:
			template<typename Expr, typename = void>
			struct eval;
		private:
			Iterator first_;
			Iterator last_;
		public:
			SPROUT_CONSTEXPR parse_context(Iterator first, Iterator last)
				: first_(first)
				, last_(last)
			{}
			SPROUT_CONSTEXPR parse_context(parse_context const& other, Iterator current)
				: first_(current)
				, last_(other.last_)
			{}
			SPROUT_CONSTEXPR Iterator begin() const {
				return first_;
			}
			SPROUT_CONSTEXPR Iterator end() const {
				return last_;
			}
			SPROUT_CONSTEXPR bool empty() const {
				return first_ == last_;
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_CONTEXT_PARSE_CONTEXT_FWD_HPP
