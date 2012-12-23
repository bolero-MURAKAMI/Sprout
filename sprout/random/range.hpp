#ifndef SPROUT_RANDOM_RANGE_HPP
#define SPROUT_RANDOM_RANGE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/generator_iterator.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/random/iterator.hpp>

namespace sprout {
	namespace random {
		//
		// make_range
		//
		template<
			typename Engine, typename Distribution,
			typename sprout::enabler_if<!std::is_integral<Distribution>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		make_range(
			Engine const& engine, Distribution const& distribution,
			typename sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type>::difference_type count = -1
			)
		-> sprout::range::range_container<sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type> >
		{
			return sprout::range::range_container<sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type> >(
				sprout::random::begin(engine, distribution, count),
				sprout::random::end(engine, distribution)
				);
		}
		template<typename Engine>
		inline SPROUT_CONSTEXPR auto
		make_range(
			Engine const& engine,
			typename sprout::generator_iterator<typename std::remove_reference<decltype(engine())>::type>::difference_type count = -1
			)
		-> sprout::range::range_container<sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type> >
		{
			return sprout::range::range_container<sprout::generator_iterator<typename std::remove_reference<decltype(distribution(engine))>::type> >(
				sprout::random::begin(engine, count),
				sprout::random::end(engine)
				);
		}
	}	// namespace random
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_RANGE_HPP
