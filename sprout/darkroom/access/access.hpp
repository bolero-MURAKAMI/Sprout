/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_ACCESS_ACCESS_HPP
#define SPROUT_DARKROOM_ACCESS_ACCESS_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace darkroom {
		namespace access {
			//
			// element
			//
			template<std::size_t I, typename T>
			struct element
				: public sprout::tuples::tuple_element<I, T>
			{};
			//
			// size
			//
			template<typename T>
			struct size
				: public sprout::tuples::tuple_size<T>
			{};
			//
			// unit
			//
			template<typename T>
			struct unit
				: public sprout::darkroom::access::element<0, T>
			{};
			//
			// get
			//
			template<std::size_t I, typename T>
			inline SPROUT_CONSTEXPR auto
			get(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tuples::get<I>(sprout::forward<T>(t))))
			-> decltype(sprout::tuples::get<I>(sprout::forward<T>(t)))
			{
				return sprout::tuples::get<I>(sprout::forward<T>(t));
			}
		}	// namespace access
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_ACCESS_ACCESS_HPP
