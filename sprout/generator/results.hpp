/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_GENERATOR_RESULTS_HPP
#define SPROUT_GENERATOR_RESULTS_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/generator/generated_value.hpp>
#include <sprout/generator/next_generator.hpp>
#include <sprout/generator/next_value.hpp>

namespace sprout {
	namespace generators {
		namespace results {
			//
			// generated_value
			//
			template<typename Generator>
			struct generated_value
				: public std::decay<decltype(sprout::generators::generated_value(std::declval<Generator>()()))>
			{};

			//
			// next_generator
			//
			template<typename Generator>
			struct next_generator
				: public std::decay<decltype(sprout::generators::next_generator(std::declval<Generator>()()))>
			{};

			//
			// next_value
			//
			template<typename Generator>
			struct next_value
				: public std::decay<decltype(sprout::generators::next_value(std::declval<Generator>()()))>
			{};
		}	// namespace results
	}	// namespace generators

	namespace results {
		using sprout::generators::results::generated_value;
		using sprout::generators::results::next_generator;
		using sprout::generators::results::next_value;
	}	// namespace results
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_RESULTS_HPP
