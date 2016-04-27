/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_NEXT_VALUE_HPP
#define SPROUT_GENERATOR_NEXT_VALUE_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/generator/generator_generate_traits.hpp>

namespace sprout {
	namespace generators {
		//
		// next_value
		//
		//	effect:
		//		sprout::generators::generator_generate_traits<T>::generate_next_value(t)
		//		[default]
		//			ADL callable generate_next_value(t) -> generate_next_value(t)
		//			[default]
		//				otherwise, callable t.next_value() -> t.next_value()
		//				otherwise, T is InputIterator -> sprout::next(t)
		//				otherwise, callable t() -> t()
		//				otherwise -> sprout::generators::next_value(sprout::generators::next_generator(t))
		//
		template<typename T>
		inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_generate_traits<typename std::remove_reference<T>::type>::generate_next_value(std::declval<T>()))
		next_value(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_generate_traits<typename std::remove_reference<T>::type>::generate_next_value(std::declval<T>()))
		{
			return sprout::generators::generator_generate_traits<typename std::remove_reference<T>::type>::generate_next_value(SPROUT_FORWARD(T, t));
		}
	}	// namespace generators
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_NEXT_VALUE_HPP
