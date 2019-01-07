/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_RESULTS_HPP
#define SPROUT_ALGORITHM_FIXED_RESULTS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace fixed {
		namespace results {
			//
			// algorithm
			//
			template<typename Result>
			struct algorithm
				: public sprout::identity<typename sprout::container_construct_traits<Result>::copied_type>
			{};

			//
			// shuffle
			//
			template<typename Container, typename UniformRandomNumberGenerator>
			struct shuffle
				: public sprout::identity<
					sprout::pair<
						typename sprout::fixed::results::algorithm<Container>::type,
						typename std::decay<UniformRandomNumberGenerator>::type
					>
				>
			{};

			//
			// resized_relative
			//
			template<typename Result, typename sprout::container_traits<Result>::difference_type RelativeSize>
			struct resized_relative
				: public std::decay<
					typename sprout::container_transform_traits<Result>
						::template rebind_size<sprout::container_traits<Result>::static_size + RelativeSize>::type
				>
			{};

#if SPROUT_USE_TEMPLATE_ALIASES
			template<typename Result>
			using algorithm_t = typename sprout::fixed::results::algorithm<Result>::type;

			template<typename Container, typename UniformRandomNumberGenerator>
			using shuffle_t = typename sprout::fixed::results::shuffle<Container, UniformRandomNumberGenerator>::type;

			template<typename Result, typename sprout::container_traits<Result>::difference_type RelativeSize>
			using resized_relative_t = typename sprout::fixed::results::resized_relative<Result, RelativeSize>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
		}	// namespace results
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::algorithm;
		using sprout::fixed::results::shuffle;
		using sprout::fixed::results::resized_relative;

#if SPROUT_USE_TEMPLATE_ALIASES
		using sprout::fixed::results::algorithm_t;
		using sprout::fixed::results::shuffle_t;
		using sprout::fixed::results::resized_relative_t;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace results
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_RESULTS_HPP
