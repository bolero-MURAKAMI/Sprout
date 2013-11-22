/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_FUNCTIONAL_LESS_HPP
#define SPROUT_TYPE_FUNCTIONAL_LESS_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		//
		// less
		//
		template<typename T, typename U>
		struct less
			: public sprout::integral_constant<bool, ((T::value) < (U::value))>
		{};

		//
		// less_
		//
		struct less_ {
		public:
			template<typename T, typename U>
			struct apply
				: public sprout::types::less<T, U>
			{};
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_FUNCTIONAL_LESS_HPP
