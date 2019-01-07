/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_STATIC_VARIANT_VISITOR_HPP
#define SPROUT_VARIANT_STATIC_VARIANT_VISITOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/variant/variant.hpp>

namespace sprout {
	//
	// static_variant_visitor
	//
	class static_variant_visitor {
	public:
		template<typename... Types>
		struct visitor_result {
		public:
			typedef sprout::variant<typename std::decay<Types>::type...> type;
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_STATIC_VARIANT_VISITOR_HPP
