/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_FUNCTIONAL_PLUS_HPP
#define SPROUT_TYPE_FUNCTIONAL_PLUS_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/common_decay.hpp>

namespace sprout {
	namespace types {
		//
		// plus
		//
		template<typename T, typename U, typename Result = void>
		struct plus
			: public sprout::integral_constant<Result, (T::value + U::value)>
		{};
		template<typename T, typename U>
		struct plus<T, U, void>
			: public sprout::integral_constant<
				typename sprout::common_decay<typename T::value_type, typename U::value_type>::type,
				(T::value + U::value)
			>
		{};

		//
		// plus_mf
		//
		template<typename Result = void>
		struct plus_mf {
		public:
			template<typename T, typename U>
			struct apply
				: public sprout::types::plus<T, U, Result>
			{};
		};

		//
		// plus_
		//
		typedef sprout::types::plus_mf<> plus_;

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename T, typename U, typename Result = void>
		SPROUT_STATIC_CONSTEXPR typename sprout::types::plus<T, U, Result>::value_type plus_v = sprout::types::plus<T, U, Result>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_FUNCTIONAL_PLUS_HPP
