/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_VARIATE_GENERATOR_HPP
#define SPROUT_RANDOM_VARIATE_GENERATOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/random/detail/ptr_helper.hpp>
#include <sprout/random/random_result_fwd.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/utility/swap.hpp>

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
			typedef typename std::conditional<
				std::is_reference<engine_type>::value && !std::is_const<typename std::remove_reference<engine_type>::type>::value,
				sprout::random::random_result<engine_type, distribution_type>,
				sprout::random::random_result<engine_value_type, distribution_value_type>
			>::type random_result_type;
		private:
			static SPROUT_CONSTEXPR random_result_type call(variate_generator const& g, sprout::true_type) {
				return random_result_type(g.distribution_(g.engine_), g.distribution_, g.engine_);
			}
			static SPROUT_CONSTEXPR random_result_type call(variate_generator const& g, sprout::false_type) {
				return g.distribution_(sprout::as_const(g.engine_));
			}
		private:
			engine_type engine_;
			distribution_type distribution_;
		public:
			SPROUT_CONSTEXPR variate_generator()
				: engine_()
				, distribution_()
			{}
			variate_generator(variate_generator const&) = default;
			SPROUT_CONSTEXPR variate_generator(
				engine_param_type engine,
				distribution_param_type distribution
				)
				: engine_(engine)
				, distribution_(distribution)
			{}
			SPROUT_CONSTEXPR random_result_type operator()() const {
				typedef sprout::bool_constant<std::is_reference<engine_type>::value && !std::is_const<typename std::remove_reference<engine_type>::type>::value> tag;
				return call(*this, tag());
			}
			SPROUT_CONSTEXPR random_result_type next_value() const {
				return (*this)();
			}
			SPROUT_CXX14_CONSTEXPR engine_reference_type engine() SPROUT_NOEXCEPT {
				return engine_helper_type::ref(engine_);
			}
			SPROUT_CONSTEXPR engine_const_reference_type engine() const SPROUT_NOEXCEPT {
				return engine_helper_type::ref(engine_);
			}
			SPROUT_CXX14_CONSTEXPR distribution_reference_type distribution() SPROUT_NOEXCEPT {
				return distribution_helper_type::ref(distribution_);
			}
			SPROUT_CONSTEXPR distribution_const_reference_type distribution() const SPROUT_NOEXCEPT {
				return distribution_helper_type::ref(distribution_);
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return distribution_.min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return distribution_.max();
			}
			SPROUT_CXX14_CONSTEXPR void swap(variate_generator& other)
			SPROUT_NOEXCEPT_IF(
				SPROUT_NOEXCEPT_EXPR(sprout::swap(engine_, other.engine_))
				&& SPROUT_NOEXCEPT_EXPR(sprout::swap(distribution_, other.distribution_))
				)
			{
				sprout::swap(engine_, other.engine_);
				sprout::swap(distribution_, other.distribution_);
			}
			friend SPROUT_CONSTEXPR bool operator==(variate_generator const& lhs, variate_generator const& rhs) SPROUT_NOEXCEPT {
				return lhs.engine_ == rhs.engine_
					&& lhs.distribution_ == rhs.distribution_
					;
			}
			friend SPROUT_CONSTEXPR bool operator!=(variate_generator const& lhs, variate_generator const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
		};

		//
		// swap
		//
		template<typename Engine, typename Distribution>
		inline SPROUT_CXX14_CONSTEXPR void
		swap(sprout::random::variate_generator<Engine, Distribution>& lhs, sprout::random::variate_generator<Engine, Distribution>& rhs)
		SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
		{
			lhs.swap(rhs);
		}

		//
		// combine
		//
		template<typename Engine, typename Distribution>
		inline SPROUT_CONSTEXPR sprout::random::variate_generator<
			typename sprout::lvalue_reference<Engine>::type,
			typename sprout::lvalue_reference<Distribution>::type
		>
		combine(Engine&& engine, Distribution&& distribution) {
			typedef sprout::random::variate_generator<
				typename sprout::lvalue_reference<Engine>::type,
				typename sprout::lvalue_reference<Distribution>::type
			> type;
			return type(
				sprout::lvalue_forward<Engine>(engine),
				sprout::lvalue_forward<Distribution>(distribution)
				);
		}

		//
		// ccombine
		//
		template<typename Engine, typename Distribution>
		inline SPROUT_CONSTEXPR sprout::random::variate_generator<Engine const&, Distribution const&>
		ccombine(Engine const& engine, Distribution const& distribution) {
			return sprout::random::variate_generator<Engine const&, Distribution const&>(engine, distribution);
		}

		//
		// combine_copy
		//
		template<typename Engine, typename Distribution>
		inline SPROUT_CONSTEXPR sprout::random::variate_generator<Engine, Distribution>
		combine_copy(Engine const& engine, Distribution const& distribution) {
			return sprout::random::variate_generator<Engine, Distribution>(engine, distribution);
		}
	}	// namespace random

	using sprout::random::variate_generator;
}	// namespace sprout

#include <sprout/random/random_result.hpp>

#endif	// #ifndef SPROUT_RANDOM_VARIATE_GENERATOR_HPP
