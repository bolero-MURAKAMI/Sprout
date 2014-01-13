/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_RESULT_HPP
#define SPROUT_WEED_PARSER_RESULT_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace weed {
		//
		// parser_result
		//
		template<typename Iterator, typename Attribute>
		class parser_result {
		private:
			bool success_;
			Iterator current_;
			Attribute attr_;
		public:
			SPROUT_CONSTEXPR parser_result() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			SPROUT_CONSTEXPR parser_result(
				bool success,
				Iterator current,
				Attribute const& attr
				)
				: success_(success)
				, current_(current)
				, attr_(attr)
			{}
			SPROUT_CONSTEXPR bool success() const {
				return success_;
			}
			SPROUT_CONSTEXPR Iterator current() const {
				return current_;
			}
			SPROUT_CONSTEXPR Attribute const& attr() const {
				return attr_;
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_RESULT_HPP
