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
		template<typename T>
		struct is_real_std_random_parameter
			: public sprout::bool_constant<
				std::is_same<T, float>::value
					|| std::is_same<T, double>::value
					|| std::is_same<T, long double>::value
			>
		{};
		template<typename T>
		struct is_int_std_random_parameter
			: public sprout::bool_constant<
				std::is_same<T, short>::value
					|| std::is_same<T, int>::value
					|| std::is_same<T, long>::value
					|| std::is_same<T, long long>::value
					|| std::is_same<T, unsigned short>::value
					|| std::is_same<T, unsigned int>::value
					|| std::is_same<T, unsigned long>::value
					|| std::is_same<T, unsigned long long>::value
			>
		{};
		template<typename T>
		struct is_uint_std_random_parameter
			: public sprout::bool_constant<
				std::is_same<T, unsigned short>::value
					|| std::is_same<T, unsigned int>::value
					|| std::is_same<T, unsigned long>::value
					|| std::is_same<T, unsigned long long>::value
			>
		{};

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename T>
		SPROUT_STATIC_CONSTEXPR bool is_seed_seq_v = sprout::random::is_seed_seq<T>::value;
		template<typename T>
		SPROUT_STATIC_CONSTEXPR bool is_real_std_random_parameter_v = sprout::random::is_real_std_random_parameter<T>::value;
		template<typename T>
		SPROUT_STATIC_CONSTEXPR bool is_int_std_random_parameter_v = sprout::random::is_int_std_random_parameter<T>::value;
		template<typename T>
		SPROUT_STATIC_CONSTEXPR bool is_uint_std_random_parameter_v = sprout::random::is_uint_std_random_parameter<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_TYPE_TRAITS_HPP
