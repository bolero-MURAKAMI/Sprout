/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ARRAY_TEST_ARRAY_CPP
#define SPROUT_LIBS_ARRAY_TEST_ARRAY_CPP

#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void array_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR int carr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			SPROUT_STATIC_CONSTEXPR auto arr1 = sprout::to_array(carr);
			SPROUT_STATIC_CONSTEXPR auto arr2 = sprout::make_array<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
			SPROUT_STATIC_CONSTEXPR auto arr3 = sprout::make_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

			TESTSPR_BOTH_ASSERT(testspr::equal(carr, arr1));
			TESTSPR_BOTH_ASSERT(testspr::equal(carr, arr2));
			TESTSPR_BOTH_ASSERT(testspr::equal(carr, arr3));

			// begin
			TESTSPR_BOTH_ASSERT(carr[0] == *arr1.begin());
			TESTSPR_BOTH_ASSERT(carr[0] == *arr2.begin());

			// cbegin
			TESTSPR_BOTH_ASSERT(carr[0] == *arr1.cbegin());
			TESTSPR_BOTH_ASSERT(carr[0] == *arr2.cbegin());

			// end
			TESTSPR_BOTH_ASSERT(carr[9] == *(arr1.end() - 1));
			TESTSPR_BOTH_ASSERT(carr[9] == *(arr2.end() - 1));

			// cend
			TESTSPR_BOTH_ASSERT(carr[9] == *(arr1.cend() - 1));
			TESTSPR_BOTH_ASSERT(carr[9] == *(arr2.cend() - 1));

			// rbegin
			TESTSPR_BOTH_ASSERT(carr[9] == *arr1.rbegin());
			TESTSPR_BOTH_ASSERT(carr[9] == *arr2.rbegin());

			// crbegin
			TESTSPR_BOTH_ASSERT(carr[9] == *arr1.crbegin());
			TESTSPR_BOTH_ASSERT(carr[9] == *arr2.crbegin());

			// rend
			TESTSPR_BOTH_ASSERT(carr[0] == *(arr1.rend() - 1));
			TESTSPR_BOTH_ASSERT(carr[0] == *(arr2.rend() - 1));

			// crend
			TESTSPR_BOTH_ASSERT(carr[0] == *(arr1.crend() - 1));
			TESTSPR_BOTH_ASSERT(carr[0] == *(arr2.crend() - 1));

			// size
			TESTSPR_BOTH_ASSERT(arr1.size() == 10);
			TESTSPR_BOTH_ASSERT(arr2.size() == 10);

			// empty
			TESTSPR_BOTH_ASSERT(!arr1.empty());
			TESTSPR_BOTH_ASSERT(!arr2.empty());
			TESTSPR_BOTH_ASSERT((array<int, 0>{{}}.empty()));

			// max_size
			TESTSPR_BOTH_ASSERT(arr1.max_size() == 10);
			TESTSPR_BOTH_ASSERT(arr2.max_size() == 10);

			// operator[]
			TESTSPR_BOTH_ASSERT(carr[0] == arr1[0]);
			TESTSPR_BOTH_ASSERT(carr[0] == arr2[0]);

			// at
			TESTSPR_BOTH_ASSERT(carr[0] == arr1.at(0));
			TESTSPR_BOTH_ASSERT(carr[0] == arr2.at(0));

			// front
			TESTSPR_BOTH_ASSERT(carr[0] == arr1.front());
			TESTSPR_BOTH_ASSERT(carr[0] == arr2.front());

			// back
			TESTSPR_BOTH_ASSERT(carr[9] == arr1.back());
			TESTSPR_BOTH_ASSERT(carr[9] == arr2.back());

			// data
			TESTSPR_BOTH_ASSERT(carr[0] == *arr1.data());
			TESTSPR_BOTH_ASSERT(carr[0] == *arr2.data());
			{
				auto arr = arr1;
				TESTSPR_ASSERT(carr[0] == *arr.data());
			}

			// c_array
			TESTSPR_BOTH_ASSERT(carr[0] == *arr1.c_array());
			TESTSPR_BOTH_ASSERT(carr[0] == *arr2.c_array());
			{
				auto arr = arr1;
				TESTSPR_ASSERT(carr[0] == *arr.c_array());
			}

			// assign
			TESTSPR_BOTH_ASSERT(testspr::equal(arr1.assign(-1), sprout::array<int, 10>{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}));
			{
				auto arr = arr1;
				arr.assign(-1);
				TESTSPR_ASSERT(testspr::equal(arr, sprout::array<int, 10>{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}));
			}

			// fill
			TESTSPR_BOTH_ASSERT(testspr::equal(arr1.fill(-1), sprout::array<int, 10>{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}));
			{
				auto arr = arr1;
				arr.fill(-1);
				TESTSPR_ASSERT(testspr::equal(arr, sprout::array<int, 10>{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}));
			}

			// swap
			{
				auto arr1 = sprout::array<int, 2>{{1, 2}};
				auto arr2 = sprout::array<int, 2>{{-1, -2}};
				arr1.swap(arr2);
				TESTSPR_ASSERT(arr1[0] == -1);
			}

			// operator=
			{
				auto arr1 = sprout::array<int, 2>{{1, 2}};
				arr1 = sprout::array<int, 2>{{-1, -2}};
				TESTSPR_ASSERT(arr1[0] == -1);
			}

			// operator==
			TESTSPR_BOTH_ASSERT(arr1 == arr2);

			// operator!=
			TESTSPR_BOTH_ASSERT(!(arr1 != arr2));

			// operator<
			TESTSPR_BOTH_ASSERT(!(arr1 < arr2));

			// operator>
			TESTSPR_BOTH_ASSERT(!(arr1 > arr2));

			// operator<=
			TESTSPR_BOTH_ASSERT(arr1 <= arr2);

			// operator>=
			TESTSPR_BOTH_ASSERT(arr1 >= arr2);

			// get
			TESTSPR_BOTH_ASSERT(sprout::tuples::get<0>(arr1) == 1);
			TESTSPR_BOTH_ASSERT(sprout::tuples::get<1>(arr1) == 2);
			{
				auto arr4 = arr1;
				TESTSPR_ASSERT(sprout::tuples::get<0>(arr4) == 1);
				TESTSPR_ASSERT(sprout::tuples::get<1>(arr4) == 2);
			}

			// tuple_size
			TESTSPR_BOTH_ASSERT(sprout::tuples::tuple_size<decltype(arr1)>::value == 10);

			// tuple_element
			TESTSPR_BOTH_ASSERT((std::is_same<sprout::tuples::tuple_element<0, decltype(arr1)>::type, int const>::value));
			TESTSPR_BOTH_ASSERT((std::is_same<sprout::tuples::tuple_element<1, decltype(arr1)>::type, int const>::value));

			// is_array
			TESTSPR_BOTH_ASSERT(sprout::is_array_class<decltype(arr1)>::value);
			TESTSPR_BOTH_ASSERT(!sprout::is_array_class<int>::value);

			// sprout::to_hash, sprout::hash
			TESTSPR_BOTH_ASSERT(sprout::to_hash(arr1) == sprout::hash<decltype(arr1)>()(arr1));
			TESTSPR_BOTH_ASSERT(sprout::to_hash(arr1) != sprout::to_hash(sprout::array<int, 10>{{}}));
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::array_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ARRAY_TEST_ARRAY_CPP
