/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_NEXT_GENERATOR_HPP
#define SPROUT_GENERATOR_NEXT_GENERATOR_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/generator/generator_access_traits.hpp>

namespace sprout {
	namespace generators {
		//
		// next_generator
		//
		//	effect:
		//		sprout::generators::generator_access_traits<T>::get_next_generator(t)
		//		[default]
		//			ADL callable get_next_generator(t) -> get_next_generator(t)
		//			[default]
		//				T is not const
		//					&& callable sprout::as_const(t).next_generator()
		//					-> sprout::const_reference_cast<decltype(std::declval<T&>().next_generator())>(sprout::as_const(cont).next_generator())
		//				otherwise, callable t.next_generator() -> t.next_generator()
		//				otherwise, T is InputIterator -> t
		//				otherwise -> sprout::tuples::get<0>(t)
		//
		template<typename T>
		inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_next_generator(std::declval<T>()))
		next_generator(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_next_generator(std::declval<T>()))
		{
			return sprout::generators::generator_access_traits<typename std::remove_reference<T>::type>::get_next_generator(SPROUT_FORWARD(T, t));
		}
	}	// namespace generators
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_NEXT_GENERATOR_HPP
