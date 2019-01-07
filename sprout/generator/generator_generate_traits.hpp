/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_GENERATOR_GENERATE_TRAITS_HPP
#define SPROUT_GENERATOR_GENERATOR_GENERATE_TRAITS_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/generator/traits_fwd.hpp>
#include <sprout/generator/generate_functions_fwd.hpp>
#include <sprout/generator/detail/next_value.hpp>

namespace sprout_generator_detail {
	using sprout_adl::generate_next_value;

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(generate_next_value(std::declval<Gen>()))
	call_generate_next_value(Gen&& gen)
	SPROUT_NOEXCEPT_IF_EXPR(generate_next_value(std::declval<Gen>()))
	{
		return generate_next_value(SPROUT_FORWARD(Gen, gen));
	}
}	// namespace sprout_generator_detail

namespace sprout {
	namespace generators {
		namespace detail {
			template<typename Gen>
			struct generator_generate_traits_const_default {
			public:
				// generate_next_value
				static SPROUT_CONSTEXPR decltype(sprout::generators::generator_generate_traits<Gen>::generate_next_value(std::declval<Gen const&>()))
				generate_next_value(Gen const& t)
				SPROUT_NOEXCEPT_IF_EXPR(sprout::generators::generator_generate_traits<Gen>::generate_next_value(std::declval<Gen const&>()))
				{
					return sprout::generators::generator_generate_traits<Gen>::generate_next_value(t);
				}
			};
		}	// namespace detail

		//
		// generator_generate_generate_next_value_default
		//
		template<typename Gen>
		struct generator_generate_generate_next_value_default {
		public:
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_generate_next_value(std::declval<Gen&>()))
			generate_next_value(Gen& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_generate_next_value(std::declval<Gen&>()))
			{
				return sprout_generator_detail::call_generate_next_value(t);
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_generate_next_value(std::declval<Gen&&>()))
			generate_next_value(Gen&& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_generate_next_value(std::declval<Gen&&>()))
			{
				return sprout_generator_detail::call_generate_next_value(sprout::move(t));
			}
			static SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_generate_next_value(std::declval<Gen const&>()))
			generate_next_value(Gen const& t)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_generator_detail::call_generate_next_value(std::declval<Gen const&>()))
			{
				return sprout_generator_detail::call_generate_next_value(t);
			}
		};

		//
		// generator_generate_traits_default
		//
		template<typename Gen>
		struct generator_generate_traits_default
			: public sprout::generators::generator_generate_generate_next_value_default<Gen>
		{};

		//
		// generator_generate_traits
		//
		template<typename Gen>
		struct generator_generate_traits
			: public sprout::generators::generator_generate_traits_default<Gen>
		{};
		template<typename Gen>
		struct generator_generate_traits<Gen const>
			: public sprout::generators::detail::generator_generate_traits_const_default<Gen>
		{};
	}	// namespace generators
}	// namespace sprout

#include <sprout/generator/next_generator.hpp>
#include <sprout/generator/next_value.hpp>

#endif	// #ifndef SPROUT_GENERATOR_GENERATOR_GENERATE_TRAITS_HPP
