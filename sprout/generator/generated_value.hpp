/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
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
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl get_generated_value(...);
}	// namespace sprout_adl

namespace sprout_generator_detail {
	using sprout_adl::get_generated_value;

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::get_generated_value(std::declval<Gen&>()))
	get_generated_value(Gen& gen)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<Gen>::get_generated_value(std::declval<Gen&>())))
	{
		return sprout::generators::generator_access_traits<Gen>::get_generated_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(sprout::generators::generator_access_traits<typename std::remove_reference<Gen>::type>::get_generated_value(std::declval<Gen&&>()))
	>::type
	get_generated_value(Gen&& gen)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<typename std::remove_reference<Gen>::type>::get_generated_value(std::declval<Gen&&>())))
	{
		return sprout::generators::generator_access_traits<Gen>::get_generated_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen const>::get_generated_value(std::declval<Gen const&>()))
	get_generated_value(Gen const& gen)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<Gen const>::get_generated_value(std::declval<Gen const&>())))
	{
		return sprout::generators::generator_access_traits<Gen const>::get_generated_value(gen);
	}

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(get_generated_value(std::declval<Gen&>()))
	call_get_generated_value(Gen& gen)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(get_generated_value(std::declval<Gen&>())))
	{
		return get_generated_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(get_generated_value(std::declval<Gen&&>()))
	>::type
	call_get_generated_value(Gen&& gen)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(get_generated_value(std::declval<Gen&&>())))
	{
		return get_generated_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(get_generated_value(std::declval<Gen const&>()))
	call_get_generated_value(Gen const& gen)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(get_generated_value(std::declval<Gen const&>())))
	{
		return get_generated_value(gen);
	}
}	// namespace sprout_generator_detail

namespace sprout {
	namespace generators {
		//
		// generated_value
		//
		//	effect:
		//		ADL callable get_generated_value(t) -> get_generated_value(t)
		//		otherwise -> sprout::generators::generator_access_traits<T>::get_generated_value(t)
		//		[default]
		//			member callable t.generated_value() -> t.generated_value()
		//			otherwise -> sprout::tuples::get<0>(t)
		//
		template<typename T>
		inline SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_generated_value(std::declval<T>()))
		generated_value(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout_generator_detail::call_get_generated_value(std::declval<T>())))
		{
			return sprout_generator_detail::call_get_generated_value(sprout::forward<T>(t));
		}
	}	// namespace generators

	using sprout::generators::generated_value;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_GENERATED_VALUE_HPP
