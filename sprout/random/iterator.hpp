/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_ITERATOR_HPP
#define SPROUT_RANDOM_ITERATOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/generator_iterator.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace random {
		//
		// begin
		//
		template<
			typename Engine, typename Distribution,
			typename sprout::enabler_if<!std::is_integral<Distribution>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		begin(
			Engine const& engine, Distribution const& distribution,
			typename sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type>::difference_type count = -1
			)
		-> sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type>
		{
			return count >= 0
				? sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type>(distribution(engine), count)
				: sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type>(distribution(engine))
				;
		}
		template<typename Engine>
		inline SPROUT_CONSTEXPR auto
		begin(
			Engine const& engine,
			typename sprout::generator_iterator<typename std::remove_reference<decltype(engine())>::type>::difference_type count = -1
			)
		-> sprout::generator_iterator<typename std::remove_reference<decltype(engine())>::type>
		{
			return count >= 0
				? sprout::generator_iterator<typename std::remove_reference<decltype(engine())>::type>(engine(), count)
				: sprout::generator_iterator<typename std::remove_reference<decltype(engine())>::type>(engine())
				;
		}

		//
		// end
		//
		template<
			typename Engine, typename Distribution,
			typename sprout::enabler_if<!std::is_integral<Distribution>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		end(Engine const& engine, Distribution const& distribution)
		-> sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type>
		{
			return sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type>();
		}
		template<typename Engine>
		inline SPROUT_CONSTEXPR auto
		end(Engine const& engine)
		-> sprout::generator_iterator<typename std::remove_reference<decltype(engine())>::type>
		{
			return sprout::generator_iterator<typename std::remove_reference<decltype(engine())>::type>();
		}
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_ITERATOR_HPP
