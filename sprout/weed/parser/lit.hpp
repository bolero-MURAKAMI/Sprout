/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_LIT_HPP
#define SPROUT_WEED_PARSER_LIT_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/remove_shallow_cvref.hpp>

namespace sprout {
	namespace weed {
		//
		// lit_g
		//
		struct lit_g {
		public:
			template<typename T, typename = void>
			struct eval;
		public:
			template<typename T>
			SPROUT_CONSTEXPR typename eval<
				typename sprout::remove_shallow_cvref<T>::type
			>::result_type
			operator()(T&& t) const {
				typedef eval<typename sprout::remove_shallow_cvref<T>::type> eval_type;
				return eval_type()(sprout::forward<T>(t));
			}
		};
		//
		// lit
		//
		SPROUT_STATIC_CONSTEXPR sprout::weed::lit_g lit = sprout::weed::lit_g();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_LIT_HPP
