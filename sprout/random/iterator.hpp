#ifndef SPROUT_RANDOM_ITERATOR_HPP
#define SPROUT_RANDOM_ITERATOR_HPP

#include <utility>
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
			typename sprout::enabler_if<!std::is_integral<Distribution>::value>::tyep = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		begin(
			Engine const& engine, Distribution const& distribution,
			typename sprout::generator_iterator<typename std::decay<decltype(distribution(engine))>::type>::difference_type count = -1
			)
			-> sprout::generator_iterator<typename std::decay<decltype(distribution(engine))>::type>
		{
			return sprout::generator_iterator<typename std::decay<decltype(distribution(engine))>::type>(distribution(engine), count);
		}
		template<typename Engine>
		inline SPROUT_CONSTEXPR auto
		begin(
			Engine const& engine,
			typename sprout::generator_iterator<typename std::decay<decltype(engine())>::type>::difference_type count = -1
			)
			-> sprout::generator_iterator<typename std::decay<decltype(engine())>::type>
		{
			return sprout::generator_iterator<typename std::decay<decltype(engine())>::type>(engine(), count);
		}

		//
		// end
		//
		template<
			typename Engine, typename Distribution,
			typename sprout::enabler_if<!std::is_integral<Distribution>::value>::tyep = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		end(Engine const& engine, Distribution const& distribution)
			-> sprout::generator_iterator<typename std::decay<decltype(distribution(engine))>::type>
		{
			return sprout::generator_iterator<typename std::decay<decltype(distribution(engine))>::type>();
		}
		template<typename Engine>
		inline SPROUT_CONSTEXPR auto
		end(Engine const& engine)
			-> sprout::generator_iterator<typename std::decay<decltype(engine())>::type>
		{
			return sprout::generator_iterator<typename std::decay<decltype(engine())>::type>();
		}
	}	// namespace random
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_ITERATOR_HPP
