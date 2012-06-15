#ifndef SPROUT_LIBS_RANDOM_TEST_ENGINE_GENERIC_HPP
#define SPROUT_LIBS_RANDOM_TEST_ENGINE_GENERIC_HPP

#include <string>
#include <sstream>
#include <sprout/random/unique_seed.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	template<typename Engine>
	void random_engine_test_generic() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto eng1 = Engine(SPROUT_UNIQUE_SEED);
			SPROUT_STATIC_CONSTEXPR auto eng2 = Engine(SPROUT_UNIQUE_SEED);

			// min
			// max
			TESTSPR_BOTH_ASSERT(eng1.min() <= eng1.max());

			// operator==
			// operator!=
//			TESTSPR_BOTH_ASSERT(eng1 == eng1);
//			TESTSPR_BOTH_ASSERT(!(eng1 == eng2));
//			TESTSPR_BOTH_ASSERT(eng1 != eng2);
//			TESTSPR_BOTH_ASSERT(!(eng1 != eng1));
			TESTSPR_ASSERT(eng1 == eng1);
			TESTSPR_ASSERT(!(eng1 == eng2));
			TESTSPR_ASSERT(eng1 != eng2);
			TESTSPR_ASSERT(!(eng1 != eng1));

			{
				std::string s;

				// operator<<
				{
					std::ostringstream os;
					os << eng1;
					TESTSPR_ASSERT(os);

					s = os.str();
				}

				auto eng_temp = Engine();

				// operator>>
				{
					std::istringstream is(s);
					is >> eng_temp;
					TESTSPR_ASSERT(is);
				}

				//TESTSPR_ASSERT(eng_temp == eng1);
			}

			// operator()
			{
				SPROUT_STATIC_CONSTEXPR auto rnd = eng1();

				// result
				TESTSPR_BOTH_ASSERT(eng1.min() <= rnd.result());
				TESTSPR_BOTH_ASSERT(rnd.result() <= eng1.max());

				// engine
				TESTSPR_BOTH_ASSERT(rnd.engine().min() <= rnd.engine().max());
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef SPROUT_LIBS_RANDOM_TEST_ENGINE_GENERIC_HPP
