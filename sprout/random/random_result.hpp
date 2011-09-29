#ifndef SPROUT_RANDOM_RANDOM_RESULT_HPP
#define SPROUT_RANDOM_RANDOM_RESULT_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace random {
		//
		// random_result
		//
		template<typename Engine, typename Distribution = void, typename Enable = void>
		class random_result;

		template<typename Engine, typename Distribution>
		class random_result<
			Engine,
			Distribution,
			typename std::enable_if<!std::is_same<Distribution, void>::value>::type
		> {
		public:
			typedef Engine engine_type;
			typedef Distribution distribution_type;
			typedef typename distribution_type::result_type result_type;
		private:
			result_type result_;
			engine_type engine_;
			distribution_type distribution_;
		public:
			SPROUT_CONSTEXPR random_result(
				result_type result,
				engine_type const& engine,
				distribution_type const& distribution
				)
				: result_(result)
				, engine_(engine)
				, distribution_(distribution)
			{}
			SPROUT_CONSTEXPR operator result_type() const {
				return result_;
			}
			SPROUT_CONSTEXPR result_type operator*() const {
				return result_;
			}
			SPROUT_CONSTEXPR random_result operator()() const {
				return distribution_(engine_);
			}
			result_type& result() {
				return result_;
			}
			SPROUT_CONSTEXPR result_type const& result() const {
				return result_;
			}
			engine_type& engine() {
				return engine_;
			}
			SPROUT_CONSTEXPR engine_type const& engine() const {
				return engine_;
			}
			distribution_type& distribution() {
				return distribution_;
			}
			SPROUT_CONSTEXPR distribution_type const& distribution() const {
				return distribution_;
			}
			SPROUT_CONSTEXPR result_type min() const {
				return distribution_.min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return distribution_.max();
			}
		};
		template<typename Engine, typename Distribution>
		class random_result<
			Engine,
			Distribution,
			typename std::enable_if<std::is_same<Distribution, void>::value>::type
		> {
		public:
			typedef Engine engine_type;
			typedef typename engine_type::result_type result_type;
		private:
			result_type result_;
			engine_type engine_;
		public:
			SPROUT_CONSTEXPR random_result(
				result_type result,
				engine_type const& engine
				)
				: result_(result)
				, engine_(engine)
			{}
			SPROUT_CONSTEXPR operator result_type() const {
				return result_;
			}
			SPROUT_CONSTEXPR result_type operator*() const {
				return result_;
			}
			SPROUT_CONSTEXPR random_result operator()() const {
				return engine_();
			}
			result_type& result() {
				return result_;
			}
			SPROUT_CONSTEXPR result_type const& result() const {
				return result_;
			}
			engine_type& engine() {
				return engine_;
			}
			SPROUT_CONSTEXPR engine_type const& engine() const {
				return engine_;
			}
			SPROUT_CONSTEXPR result_type min() const {
				return engine_.min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return engine_.max();
			}
		};
	}	// namespace random

	using sprout::random::random_result;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_RANDOM_RESULT_HPP

