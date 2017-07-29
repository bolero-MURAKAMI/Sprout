/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_GENERATOR_ACCESS_TRAITS_HPP
#define SPROUT_GENERATOR_GENERATOR_ACCESS_TRAITS_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/generator/traits_fwd.hpp>
#include <sprout/generator/access_functions_fwd.hpp>
#include <sprout/generator/detail/generated_value.hpp>
#include <sprout/generator/detail/next_generator.hpp>

namespace sprout_generator_detail {
	using sprout_adl::get_generated_value;
	using sprout_adl::get_next_generator;

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(get_generated_value(std::declval<Gen>()))
	call_get_generated_value(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(get_generated_value(std::declval<Gen>()))
	{
		return get_generated_value(SPROUT_FORWARD(Gen, gen));
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(get_next_generator(std::declval<Gen>()))
	call_get_next_generator(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(get_next_generator(std::declval<Gen>()))
	{
		return get_next_generator(SPROUT_FORWARD(Gen, gen));
	}
}	// namespace sprout_generator_detail

namespace sprout {
	namespace generators {
		namespace detail {
			template<typename Gen>
			struct generator_access_traits_const_default {
			public:
				// get_generated_value
				static SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::get_generated_value(std::declval<Gen const&>()))
				get_generated_value(Gen const& t)
				SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<Gen>::get_generated_value(std::declval<Gen const&>()))
				{
					return sprout::generators::generator_access_traits<Gen>::get_generated_value(t);
				}
				// get_next_generator
				static SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::get_next_generator(std::declval<Gen const&>()))
				get_next_generator(Gen const& t)
				SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_access_traits<Gen>::get_next_generator(std::declval<Gen const&>()))
				{
					return sprout::generators::generator_access_traits<Gen>::get_next_generator(t);
				}
			};
		}	// namespace detail

		//
		// generator_access_get_generated_value_default
		//
		template<typename Gen>
		struct generator_access_get_generated_value_default {
		public:
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_generated_value(std::declval<Gen&>()))
			get_generated_value(Gen& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_generated_value(std::declval<Gen&>()))
			{
				return sprout_generator_detail::call_get_generated_value(t);
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_generated_value(std::declval<Gen&&>()))
			get_generated_value(Gen&& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_generated_value(std::declval<Gen&&>()))
			{
				return sprout_generator_detail::call_get_generated_value(sprout::move(t));
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_generated_value(std::declval<Gen const&>()))
			get_generated_value(Gen const& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_generated_value(std::declval<Gen const&>()))
			{
				return sprout_generator_detail::call_get_generated_value(t);
			}
		};
		//
		// generator_access_get_next_generator_default
		//
		template<typename Gen>
		struct generator_access_get_next_generator_default {
		public:
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_next_generator(std::declval<Gen&>()))
			get_next_generator(Gen& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_next_generator(std::declval<Gen&>()))
			{
				return sprout_generator_detail::call_get_next_generator(t);
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_next_generator(std::declval<Gen&&>()))
			get_next_generator(Gen&& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_next_generator(std::declval<Gen&&>()))
			{
				return sprout_generator_detail::call_get_next_generator(sprout::move(t));
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_get_next_generator(std::declval<Gen const&>()))
			get_next_generator(Gen const& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_get_next_generator(std::declval<Gen const&>()))
			{
				return sprout_generator_detail::call_get_next_generator(t);
			}
		};

		//
		// generator_access_traits_default
		//
		template<typename Gen>
		struct generator_access_traits_default
			: public sprout::generators::generator_access_get_generated_value_default<Gen>
			, public sprout::generators::generator_access_get_next_generator_default<Gen>
		{};

		//
		// generator_access_traits
		//
		template<typename Gen>
		struct generator_access_traits
			: public sprout::generators::generator_access_traits_default<Gen>
		{};
		template<typename Gen>
		struct generator_access_traits<Gen const>
			: public sprout::generators::detail::generator_access_traits_const_default<Gen>
		{};
	}	// namespace generators
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_GENERATOR_ACCESS_TRAITS_HPP
