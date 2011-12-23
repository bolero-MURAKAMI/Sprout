#ifndef TESTSPR_SPROUT_ARRAY_HPP
#define TESTSPR_SPROUT_ARRAY_HPP

#include <sprout/array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void array_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR int carr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			SPROUT_STATIC_CONSTEXPR auto arr1 = sprout::to_array(carr);
			SPROUT_STATIC_CONSTEXPR auto arr2 = sprout::make_array<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
			SPROUT_STATIC_CONSTEXPR auto arr3 = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

			TESTSPR_DOUBLE_ASSERT(testspr::equal(carr, arr1));
			TESTSPR_DOUBLE_ASSERT(testspr::equal(carr, arr2));
			TESTSPR_DOUBLE_ASSERT(testspr::equal(carr, arr3));

			// begin
			TESTSPR_DOUBLE_ASSERT(carr[0] == *arr1.begin());
			TESTSPR_DOUBLE_ASSERT(carr[0] == *arr2.begin());

			// cbegin
			TESTSPR_DOUBLE_ASSERT(carr[0] == *arr1.cbegin());
			TESTSPR_DOUBLE_ASSERT(carr[0] == *arr2.cbegin());

			// end
			TESTSPR_DOUBLE_ASSERT(carr[9] == *(arr1.end() - 1));
			TESTSPR_DOUBLE_ASSERT(carr[9] == *(arr2.end() - 1));

			// cend
			TESTSPR_DOUBLE_ASSERT(carr[9] == *(arr1.cend() - 1));
			TESTSPR_DOUBLE_ASSERT(carr[9] == *(arr2.cend() - 1));

			// rbegin
			TESTSPR_DOUBLE_ASSERT(carr[9] == *arr1.rbegin());
			TESTSPR_DOUBLE_ASSERT(carr[9] == *arr2.rbegin());

			// crbegin
			TESTSPR_DOUBLE_ASSERT(carr[9] == *arr1.crbegin());
			TESTSPR_DOUBLE_ASSERT(carr[9] == *arr2.crbegin());

			// rend
			TESTSPR_DOUBLE_ASSERT(carr[0] == *(arr1.rend() - 1));
			TESTSPR_DOUBLE_ASSERT(carr[0] == *(arr2.rend() - 1));

			// crend
			TESTSPR_DOUBLE_ASSERT(carr[0] == *(arr1.crend() - 1));
			TESTSPR_DOUBLE_ASSERT(carr[0] == *(arr2.crend() - 1));

			// size
			TESTSPR_DOUBLE_ASSERT(arr1.size() == 10);
			TESTSPR_DOUBLE_ASSERT(arr2.size() == 10);

			// empty
			TESTSPR_DOUBLE_ASSERT(!arr1.empty());
			TESTSPR_DOUBLE_ASSERT(!arr2.empty());
			TESTSPR_DOUBLE_ASSERT((array<int, 0>{{}}.empty()));

			// max_size
			TESTSPR_DOUBLE_ASSERT(arr1.max_size() == 10);
			TESTSPR_DOUBLE_ASSERT(arr2.max_size() == 10);

			// operator[]
			TESTSPR_DOUBLE_ASSERT(carr[0] == arr1[0]);
			TESTSPR_DOUBLE_ASSERT(carr[0] == arr2[0]);

			// at
			TESTSPR_DOUBLE_ASSERT(carr[0] == arr1.at(0));
			TESTSPR_DOUBLE_ASSERT(carr[0] == arr2.at(0));

			// front
			TESTSPR_DOUBLE_ASSERT(carr[0] == arr1.front());
			TESTSPR_DOUBLE_ASSERT(carr[0] == arr2.front());

			// back
			TESTSPR_DOUBLE_ASSERT(carr[9] == arr1.back());
			TESTSPR_DOUBLE_ASSERT(carr[9] == arr2.back());

			// data
			TESTSPR_DOUBLE_ASSERT(carr[0] == *arr1.data());
			TESTSPR_DOUBLE_ASSERT(carr[0] == *arr2.data());

			// c_array
			{
				auto arr = arr1;
				TESTSPR_ASSERT(carr[0] == *arr.c_array());
			}

			// assign
			{
				auto arr = arr1;
				arr.assign(-1);
				TESTSPR_ASSERT(arr[0] == -1);
			}

			// fill
			{
				auto arr = arr1;
				arr.fill(-1);
				TESTSPR_ASSERT(arr[0] == -1);
			}

			// swap
			{
				auto arr1 = array<int, 2>{{1, 2}};
				auto arr2 = array<int, 2>{{-1, -2}};
				arr1.swap(arr2);
				TESTSPR_ASSERT(arr1[0] == -1);
			}

			// operator=
			{
				auto arr1 = array<int, 2>{{1, 2}};
				arr1 = array<int, 2>{{-1, -2}};
				TESTSPR_ASSERT(arr1[0] == -1);
			}

			// operator==
			TESTSPR_DOUBLE_ASSERT(arr1 == arr2);

			// operator!=
			TESTSPR_DOUBLE_ASSERT(!(arr1 != arr2));

			// operator<
			TESTSPR_DOUBLE_ASSERT(!(arr1 < arr2));

			// operator>
			TESTSPR_DOUBLE_ASSERT(!(arr1 > arr2));

			// operator<=
			TESTSPR_DOUBLE_ASSERT(arr1 <= arr2);

			// operator>=
			TESTSPR_DOUBLE_ASSERT(arr1 >= arr2);
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ARRAY_HPP

