/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_BERNOULLI_DISTRIBUTION_HPP
#define SPROUT_RANDOM_BERNOULLI_DISTRIBUTION_HPP

#include <iosfwd>
#include <sprout/config.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/results.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	namespace random {
		//
		// bernoulli_distribution
		//
		template<typename RealType = double>
		class bernoulli_distribution {
		public:
			typedef int input_type;
			typedef bool result_type;
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef bernoulli_distribution distribution_type;
			private:
				RealType p_;
			public:
				SPROUT_CONSTEXPR param_type()
					: p_(RealType(0.5))
				{}
				param_type(param_type const&) = default;
				explicit SPROUT_CONSTEXPR param_type(RealType p_arg)
					: p_((SPROUT_ASSERT(p_arg >= RealType(0)), SPROUT_ASSERT(p_arg <= RealType(1)), p_arg))
				{}
				SPROUT_CONSTEXPR RealType p() const SPROUT_NOEXCEPT {
					return p_;
				}
				template<typename Elem, typename Traits>
				friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
					std::basic_istream<Elem, Traits>& lhs,
					param_type& rhs
					)
				{
					RealType p;
					if (lhs >> p) {
						if (p >= RealType(0) && p <= RealType(1)) {
							rhs.p_ = p;
						} else {
							lhs.setstate(std::ios_base::failbit);
						}
					}
					return lhs;
				}
				template<typename Elem, typename Traits>
				friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
					std::basic_ostream<Elem, Traits>& lhs,
					param_type const& rhs
					)
				{
					return lhs << rhs.p_;
				}
				friend SPROUT_CONSTEXPR bool operator==(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return lhs.p_ == rhs.p_;
				}
				friend SPROUT_CONSTEXPR bool operator!=(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return !(lhs == rhs);
				}
			};
		private:
			RealType p_;
		private:
			template<typename Engine, typename EngineResult>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, bernoulli_distribution> generate(
				EngineResult const& rnd
				) const
			{
				return sprout::random::random_result<Engine, bernoulli_distribution>(
					RealType(sprout::random::result(rnd) - sprout::random::next(rnd).min())
						<= p_ * RealType(sprout::random::next(rnd).max() - sprout::random::next(rnd).min())
						,
					sprout::random::next(rnd),
					*this
					);
			}
		public:
			SPROUT_CONSTEXPR bernoulli_distribution() SPROUT_NOEXCEPT
				: p_(RealType(0.5))
			{}
			bernoulli_distribution(bernoulli_distribution const&) = default;
			explicit SPROUT_CONSTEXPR bernoulli_distribution(RealType p_arg)
				: p_((SPROUT_ASSERT(p_arg >= RealType(0)), SPROUT_ASSERT(p_arg <= RealType(1)), p_arg))
			{}
			explicit SPROUT_CONSTEXPR bernoulli_distribution(param_type const& parm) SPROUT_NOEXCEPT
				: p_(parm.p())
			{}
			SPROUT_CONSTEXPR RealType p() const SPROUT_NOEXCEPT {
				return p_;
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return false;
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return true;
			}
			SPROUT_CXX14_CONSTEXPR void reset() SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR param_type param() const SPROUT_NOEXCEPT {
				return param_type(p_);
			}
			SPROUT_CXX14_CONSTEXPR void param(param_type const& parm) {
				p_ = parm.p();
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type operator()(Engine& eng) const {
				typedef typename Engine::result_type base_result;
				return p_ == RealType(0)
					? false
					: RealType(static_cast<base_result>(eng()) - eng.min()) <= p_ * RealType(eng.max() - eng.min())
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, bernoulli_distribution> const operator()(Engine const& eng) const {
				return p_ == RealType(0)
					? sprout::random::random_result<Engine, bernoulli_distribution>(false, eng, *this)
					: generate<Engine>(eng())
					;
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type operator()(Engine& eng, param_type const& parm) const {
				return bernoulli_distribution(parm)(eng);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, bernoulli_distribution> const operator()(Engine const& eng, param_type const& parm) const {
				return bernoulli_distribution(parm)(eng);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				bernoulli_distribution& rhs
				)
			{
				param_type parm;
				if (lhs >> parm) {
					rhs.param(parm);
				}
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				bernoulli_distribution const& rhs
				)
			{
				return lhs << rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator==(bernoulli_distribution const& lhs, bernoulli_distribution const& rhs) SPROUT_NOEXCEPT {
				return lhs.param() == rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator!=(bernoulli_distribution const& lhs, bernoulli_distribution const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::bernoulli_distribution;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_BERNOULLI_DISTRIBUTION_HPP
