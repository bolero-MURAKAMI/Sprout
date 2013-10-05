#ifndef SPROUT_LIBS_RANDOM_TEST_DISTRIBUTION_GENERIC_HPP
#define SPROUT_LIBS_RANDOM_TEST_DISTRIBUTION_GENERIC_HPP

#include <string>
#include <sstream>
#include <sprout/random/linear_congruential.hpp>
#include <sprout/random/unique_seed.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	template<typename Distribution, typename Engine = sprout::random::minstd_rand0>
	void random_distribution_test_generic() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto parm = typename Distribution::param_type();

			SPROUT_STATIC_CONSTEXPR auto dist1 = Distribution(parm);
			SPROUT_STATIC_CONSTEXPR auto dist2 = Distribution(parm);

			// min
			// max
			TESTSPR_BOTH_ASSERT(dist1.min() <= dist1.max());

			// param
			TESTSPR_BOTH_ASSERT(parm == dist1.param());
			{
				auto dist_temp = Distribution();
				dist_temp.param(parm);
				TESTSPR_ASSERT(dist_temp == dist1);
			}

			// operator==
			// operator!=
			TESTSPR_BOTH_ASSERT(dist1 == dist2);
			TESTSPR_BOTH_ASSERT(!(dist1 != dist2));

			{
				std::string s;

				// operator<<
				{
					std::ostringstream os;
					os << dist1;
					// ???
#if !defined(__clang__)
					TESTSPR_ASSERT(!!os);
#endif
					s = os.str();
				}

				auto dist_temp = Distribution();

				// operator>>
				{
					std::istringstream is(s);
					is >> dist_temp;
					// ???
#if !defined(__clang__)
					TESTSPR_ASSERT(!!is);
#endif
				}

				TESTSPR_ASSERT(dist_temp == dist1);
			}

			// operator()
			{
				SPROUT_STATIC_CONSTEXPR auto eng = Engine(SPROUT_UNIQUE_SEED);
				{
					SPROUT_STATIC_CONSTEXPR auto rnd = dist1(eng);

					// result
					TESTSPR_BOTH_ASSERT(dist1.min() <= rnd.result());
					TESTSPR_BOTH_ASSERT(rnd.result() <= dist1.max());

					// engine
					TESTSPR_BOTH_ASSERT(rnd.engine().min() <= rnd.engine().max());

					// distribution
					TESTSPR_BOTH_ASSERT(rnd.distribution().min() <= rnd.distribution().max());
				}
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef SPROUT_LIBS_RANDOM_TEST_DISTRIBUTION_GENERIC_HPP
