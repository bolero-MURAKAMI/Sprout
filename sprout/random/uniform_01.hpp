#ifndef SPROUT_RANDOM_UNIFORM_01_HPP
#define SPROUT_RANDOM_UNIFORM_01_HPP

#include <iosfwd>
#include <istream>
#include <limits>
#include <sprout/config.hpp>
#include <sprout/random/random_result.hpp>

namespace sprout {
	namespace random {
		//
		// uniform_01
		//
		template<typename RealType = double>
		class uniform_01 {
		public:
			typedef RealType input_type;
			typedef RealType result_type;
		private:
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_01> generate_1(
				Engine const& eng,
				sprout::random::random_result<Engine> const& rnd,
				result_type result
				) const
			{
				return result < result_type(1)
					? sprout::random::random_result<Engine, uniform_01>(result, rnd.engine(), *this)
					: operator()(rnd.engine())
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_01> generate(
				Engine const& eng,
				sprout::random::random_result<Engine> const& rnd
				) const
			{
				typedef typename Engine::result_type base_result;
				return generate_1(
					eng,
					rnd,
					result_type(rnd.result() - eng.min()) * (
						result_type(1) / (
							result_type(eng.max() - eng.min()) + result_type(
								std::numeric_limits<base_result>::is_integer ? 1 : 0
								)
							)
						)
					);
			}
		public:
			SPROUT_CONSTEXPR result_type min() const {
				return result_type(0);
			}
			SPROUT_CONSTEXPR result_type max() const {
				return result_type(1);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_01> operator()(Engine const& eng) const {
				return generate(eng, eng());
			}
			template<typename Elem, typename Traits>
			friend std::basic_ostream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				uniform_01 const& rhs
				)
			{
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				uniform_01 const& rhs
				)
			{
				return lhs;
			}
			SPROUT_CONSTEXPR friend bool operator==(uniform_01 const& lhs, uniform_01 const& rhs) {
				return true;
			}
			SPROUT_CONSTEXPR friend bool operator!=(uniform_01 const& lhs, uniform_01 const& rhs) {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::uniform_01;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_UNIFORM_01_HPP

