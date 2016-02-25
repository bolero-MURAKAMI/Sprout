/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
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
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl get_next_generator(...);
}	// namespace sprout_adl

namespace sprout_generator_detail {
	using sprout_adl::get_next_generator;

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::get_next_generator(std::declval<Gen&>()))
	get_next_generator(Gen& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<Gen>::get_next_generator(std::declval<Gen&>()))
	{
		return sprout::generators::generator_access_traits<Gen>::get_next_generator(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(sprout::generators::generator_access_traits<typename std::remove_reference<Gen>::type>::get_next_generator(std::declval<Gen&&>()))
	>::type
	get_next_generator(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<typename std::remove_reference<Gen>::type>::get_next_generator(std::declval<Gen&&>()))
	{
		return sprout::generators::generator_access_traits<Gen>::get_next_generator(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen const>::get_next_generator(std::declval<Gen const&>()))
	get_next_generator(Gen const& gen)
	SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<Gen const>::get_next_generator(std::declval<Gen const&>()))
	{
		return sprout::generators::generator_access_traits<Gen const>::get_next_generator(gen);
	}

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(get_next_generator(std::declval<Gen&>()))
	call_get_next_generator(Gen& gen)
	SPROUT_NOEXCEPT_IF_EXPR(get_next_generator(std::declval<Gen&>()))
	{
		return get_next_generator(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(get_next_generator(std::declval<Gen&&>()))
	>::type
	call_get_next_generator(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(get_next_generator(std::declval<Gen&&>()))
	{
		return get_next_generator(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(get_next_generator(std::declval<Gen const&>()))
	call_get_next_generator(Gen const& gen)
	SPROUT_NOEXCEPT_IF_EXPR(get_next_generator(std::declval<Gen const&>()))
	{
		return get_next_generator(gen);
	}
}	// namespace sprout_generator_detail

namespace sprout {
	namespace generators {
		//
		// next_generator
		//
		//	effect:
		//		ADL callable get_next_generator(t) -> get_next_generator(t)
		//		otherwise -> sprout::generators::generator_access_traits<T>::get_next_generator(t)
		//		[default]
		//			member callable t.next_generator() -> t.next_generator()
		//			otherwise -> sprout::tuples::get<0>(t)
		//
		template<typename T>
		inline SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_next_generator(std::declval<T>()))
		next_generator(T&& t)
		SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_next_generator(std::declval<T>()))
		{
			return sprout_generator_detail::call_get_next_generator(SPROUT_FORWARD(T, t));
		}
	}	// namespace generators

	using sprout::generators::next_generator;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_NEXT_GENERATOR_HPP
