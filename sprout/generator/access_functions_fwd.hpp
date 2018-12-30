/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_ACCESS_FUNCTIONS_FWD_HPP
#define SPROUT_GENERATOR_ACCESS_FUNCTIONS_FWD_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/generator/traits_fwd.hpp>

namespace sprout {
	namespace generators {
		//
		// generated_value
		//
		template<typename T>
		SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_generated_value(std::declval<T>()))
		generated_value(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_generated_value(std::declval<T>()));

		//
		// next_generator
		//
		template<typename T>
		SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_next_generator(std::declval<T>()))
		next_generator(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_next_generator(std::declval<T>()));
	}	// namespace generators

	using sprout::generators::generated_value;
	using sprout::generators::next_generator;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_ACCESS_FUNCTIONS_FWD_HPP
