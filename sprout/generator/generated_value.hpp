/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_GENERATED_VALUE_HPP
#define SPROUT_GENERATOR_GENERATED_VALUE_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/generator/generator_access_traits.hpp>

namespace sprout {
	namespace generators {
		//
		// generated_value
		//
		//	effect:
		//		sprout::generators::generator_access_traits<T>::get_generated_value(t)
		//		[default]
		//			ADL callable get_generated_value(t) -> get_generated_value(t)
		//			[default]
		//				T is not const
		//					&& callable sprout::as_const(t).generated_value()
		//					-> sprout::const_reference_cast<decltype(std::declval<T&>().generated_value())>(sprout::as_const(cont).generated_value())
		//				otherwise, callable t.generated_value() -> t.generated_value()
		//				otherwise, T is InputIterator -> *t
		//				otherwise -> sprout::tuples::get<0>(t)
		//
		template<typename T>
		inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_generated_value(std::declval<T>()))
		generated_value(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_generated_value(std::declval<T>()))
		{
			return sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_generated_value(SPROUT_FORWARD(T, t));
		}
	}	// namespace generators
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_GENERATED_VALUE_HPP
