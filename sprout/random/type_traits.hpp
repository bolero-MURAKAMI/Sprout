/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_TYPE_TRAITS_HPP
#define SPROUT_RANDOM_TYPE_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/has_xxx.hpp>

namespace sprout {
	namespace random {
		//
		// is_seed_seq
		//
		SPROUT_HAS_XXX_TYPE_DEF(is_seed_seq, result_type);

		//
		// is_real_std_random_parameter
		// is_int_std_random_parameter
		// is_uint_std_random_parameter
		//
		template<typename RealType>
		struct is_real_std_random_parameter
			: public sprout::integral_constant<
				bool,
				std::is_same<RealType, float>::value
					|| std::is_same<RealType, double>::value
					|| std::is_same<RealType, long double>::value
			>
		{};
		template<typename IntType>
		struct is_int_std_random_parameter
			: public sprout::integral_constant<
				bool,
				std::is_same<IntType, short>::value
					|| std::is_same<IntType, int>::value
					|| std::is_same<IntType, long>::value
					|| std::is_same<IntType, long long>::value
					|| std::is_same<IntType, unsigned short>::value
					|| std::is_same<IntType, unsigned int>::value
					|| std::is_same<IntType, unsigned long>::value
					|| std::is_same<IntType, unsigned long long>::value
			>
		{};
		template<typename UIntType>
		struct is_uint_std_random_parameter
			: public sprout::integral_constant<
				bool,
				std::is_same<UIntType, unsigned short>::value
					|| std::is_same<UIntType, unsigned int>::value
					|| std::is_same<UIntType, unsigned long>::value
					|| std::is_same<UIntType, unsigned long long>::value
			>
		{};
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_TYPE_TRAITS_HPP
