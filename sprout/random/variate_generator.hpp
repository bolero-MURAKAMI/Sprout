#ifndef SPROUT_RANDOM_VARIATE_GENERATOR_HPP
#define SPROUT_RANDOM_VARIATE_GENERATOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/if.hpp>
#include <sprout/random/detail/ptr_helper.hpp>
#include <sprout/random/random_result.hpp>

namespace sprout {
	namespace random {
		//
		// variate_generator
		//
		template<typename Engine, typename Distribution>
		class variate_generator {
		private:
			typedef sprout::random::detail::ptr_helper<Engine> engine_helper_type;
			typedef sprout::random::detail::ptr_helper<Distribution> distribution_helper_type;
		public:
			typedef typename engine_helper_type::value_type engine_value_type;
			typedef typename distribution_helper_type::value_type distribution_value_type;
			typedef typename engine_helper_type::reference_type engine_reference_type;
			typedef typename distribution_helper_type::reference_type distribution_reference_type;
			typedef typename engine_helper_type::const_reference_type engine_const_reference_type;
			typedef typename distribution_helper_type::const_reference_type distribution_const_reference_type;
			typedef typename engine_helper_type::rvalue_type engine_param_type;
			typedef typename distribution_helper_type::rvalue_type distribution_param_type;
		public:
			typedef Engine engine_type;
			typedef Distribution distribution_type;
			typedef typename distribution_value_type::result_type result_type;
		private:
			engine_type engine_;
			distribution_type distribution_;
		public:
			SPROUT_CONSTEXPR variate_generator(
				engine_param_type engine,
				distribution_param_type distribution
				)
				: engine_(engine)
				, distribution_(distribution)
			{}
			SPROUT_CONSTEXPR sprout::random::random_result<engine_value_type, distribution_value_type> operator()() const {
				return distribution_(engine_);
			}
			engine_reference_type engine() {
				return engine_helper_type::ref(engine_);
			}
			SPROUT_CONSTEXPR engine_const_reference_type engine() const {
				return engine_helper_type::ref(engine_);
			}
			distribution_reference_type distribution() {
				return distribution_helper_type::ref(distribution_);
			}
			SPROUT_CONSTEXPR distribution_const_reference_type distribution() const {
				return distribution_helper_type::ref(distribution_);
			}
			SPROUT_CONSTEXPR result_type min() const {
				return distribution_.min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return distribution_.max();
			}
		};

		//
		// combine
		//
		template<typename Engine, typename Distribution>
		SPROUT_CONSTEXPR sprout::random::variate_generator<Engine const&, Distribution const&> combine(
			Engine const& engine,
			Distribution const& distribution
			)
		{
			return sprout::random::variate_generator<Engine const&, Distribution const&>(engine, distribution);
		}
	}	// namespace random

	using sprout::random::variate_generator;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_VARIATE_GENERATOR_HPP

