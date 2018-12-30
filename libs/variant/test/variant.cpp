/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_VARIANT_TEST_VARIANT_CPP
#define SPROUT_LIBS_VARIANT_TEST_VARIANT_CPP

#include <sstream>
#include <sprout/variant.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void variant_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto var1 = sprout::variant<int, double>(1.0);
			SPROUT_STATIC_CONSTEXPR auto var2 = sprout::variant<int, double>();

			// constructor
			{
				SPROUT_STATIC_CONSTEXPR auto var3 = sprout::variant<int, double>();
				TESTSPR_BOTH_ASSERT(var3.which() == 0);
				TESTSPR_BOTH_ASSERT(sprout::get<int>(var3) == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto var3 = sprout::variant<int, double>(var1);
				TESTSPR_BOTH_ASSERT(var3.which() == 1);
				TESTSPR_BOTH_ASSERT(sprout::get<double>(var3) == 1.0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto var3 = sprout::variant<int, double>(1.0);
				TESTSPR_BOTH_ASSERT(var3.which() == 1);
				TESTSPR_BOTH_ASSERT(sprout::get<double>(var3) == 1.0);
			}

			// swap
			{
				auto var3 = var1;
				auto var4 = var2;
				var3.swap(var4);
				TESTSPR_ASSERT(var3.which() == 0);
				TESTSPR_ASSERT(sprout::get<int>(var3) == 0);
				TESTSPR_ASSERT(var4.which() == 1);
				TESTSPR_ASSERT(sprout::get<double>(var4) == 1.0);
			}
			{
				auto var3 = var1;
				auto var4 = var2;
				swap(var3, var4);
				TESTSPR_ASSERT(var3.which() == 0);
				TESTSPR_ASSERT(sprout::get<int>(var3) == 0);
				TESTSPR_ASSERT(var4.which() == 1);
				TESTSPR_ASSERT(sprout::get<double>(var4) == 1.0);
			}

			// operator=
			{
				auto var3 = var2;
				var3 = sprout::variant<int, double>(1.0);
				TESTSPR_ASSERT(var3.which() == 1);
				TESTSPR_ASSERT(sprout::get<double>(var3) == 1.0);
			}
			{
				auto var3 = var2;
				var3 = 1.0;
				TESTSPR_ASSERT(var3.which() == 1);
				TESTSPR_ASSERT(sprout::get<double>(var3) == 1.0);
			}

			// which
			TESTSPR_BOTH_ASSERT(var1.which() == 1);
			TESTSPR_BOTH_ASSERT(var2.which() == 0);

			// empty
			TESTSPR_BOTH_ASSERT(!var1.empty());
			TESTSPR_BOTH_ASSERT(!var2.empty());

			// operator==
			TESTSPR_BOTH_ASSERT(!(var1 == var2));
			TESTSPR_BOTH_ASSERT((var1 == sprout::variant<int, double>(1.0)));

			// operator!=
			TESTSPR_BOTH_ASSERT(var1 != var2);
			TESTSPR_BOTH_ASSERT(!(var1 != sprout::variant<int, double>(1.0)));

			// operator<
			TESTSPR_BOTH_ASSERT(!(var1 < var2));
			TESTSPR_BOTH_ASSERT(!(var1 < sprout::variant<int, double>(0.0)));
			TESTSPR_BOTH_ASSERT(!(var1 < sprout::variant<int, double>(1.0)));
			TESTSPR_BOTH_ASSERT((var1 < sprout::variant<int, double>(2.0)));
			TESTSPR_BOTH_ASSERT(!(var1 < sprout::variant<int, double>(0)));
			TESTSPR_BOTH_ASSERT(!(var1 < sprout::variant<int, double>(1)));
			TESTSPR_BOTH_ASSERT(!(var1 < sprout::variant<int, double>(2)));

			// operator>
			TESTSPR_BOTH_ASSERT(var1 > var2);
			TESTSPR_BOTH_ASSERT((var1 > sprout::variant<int, double>(0.0)));
			TESTSPR_BOTH_ASSERT(!(var1 > sprout::variant<int, double>(1.0)));
			TESTSPR_BOTH_ASSERT(!(var1 > sprout::variant<int, double>(2.0)));
			TESTSPR_BOTH_ASSERT((var1 > sprout::variant<int, double>(0)));
			TESTSPR_BOTH_ASSERT((var1 > sprout::variant<int, double>(1)));
			TESTSPR_BOTH_ASSERT((var1 > sprout::variant<int, double>(2)));

			// operator<=
			TESTSPR_BOTH_ASSERT(!(var1 <= var2));
			TESTSPR_BOTH_ASSERT(!(var1 <= sprout::variant<int, double>(0.0)));
			TESTSPR_BOTH_ASSERT((var1 <= sprout::variant<int, double>(1.0)));
			TESTSPR_BOTH_ASSERT((var1 <= sprout::variant<int, double>(2.0)));
			TESTSPR_BOTH_ASSERT(!(var1 <= sprout::variant<int, double>(0)));
			TESTSPR_BOTH_ASSERT(!(var1 <= sprout::variant<int, double>(1)));
			TESTSPR_BOTH_ASSERT(!(var1 <= sprout::variant<int, double>(2)));

			// operator>=
			TESTSPR_BOTH_ASSERT(var1 >= var2);
			TESTSPR_BOTH_ASSERT((var1 >= sprout::variant<int, double>(0.0)));
			TESTSPR_BOTH_ASSERT((var1 >= sprout::variant<int, double>(1.0)));
			TESTSPR_BOTH_ASSERT(!(var1 >= sprout::variant<int, double>(2.0)));
			TESTSPR_BOTH_ASSERT((var1 >= sprout::variant<int, double>(0)));
			TESTSPR_BOTH_ASSERT((var1 >= sprout::variant<int, double>(1)));
			TESTSPR_BOTH_ASSERT((var1 >= sprout::variant<int, double>(2)));

			// get_at
			TESTSPR_BOTH_ASSERT(var1.get_at<1>() == 1.0);
			TESTSPR_BOTH_ASSERT(var2.get_at<0>() == 0);
			{
				auto var3 = var1;
				TESTSPR_ASSERT(var3.get_at<1>() == 1.0);
			}
			{
				auto var3 = var2;
				TESTSPR_ASSERT(var3.get_at<0>() == 0);
			}

			// get
			TESTSPR_BOTH_ASSERT(sprout::get<double>(var1) == 1.0);
			TESTSPR_BOTH_ASSERT(sprout::get<int>(var2) == 0);
			{
				auto var3 = var1;
				TESTSPR_ASSERT(sprout::get<double>(var3) == 1.0);
			}
			{
				auto var3 = var2;
				TESTSPR_ASSERT(sprout::get<int>(var3) == 0);
			}

			// apply_visitor
			TESTSPR_BOTH_ASSERT(var1.apply_visitor(testspr::x2_visitor<double>()) == 2.0);
			TESTSPR_BOTH_ASSERT(var2.apply_visitor(testspr::x2_visitor<double>()) == 0.0);
			{
				auto var3 = var1;
				TESTSPR_ASSERT(var3.apply_visitor(testspr::x2_assign_visitor<double>()) == 2.0);
				TESTSPR_ASSERT(var3.which() == 1);
				TESTSPR_ASSERT(sprout::get<double>(var3) == 2.0);
			}
			{
				auto var3 = var2;
				TESTSPR_ASSERT(var3.apply_visitor(testspr::x2_assign_visitor<double>()) == 0.0);
				TESTSPR_ASSERT(var3.which() == 0);
				TESTSPR_ASSERT(sprout::get<int>(var3) == 0);
			}

			// apply_visitor
			TESTSPR_BOTH_ASSERT(sprout::apply_visitor(testspr::x2_visitor<double>(), var1) == 2.0);
			TESTSPR_BOTH_ASSERT(sprout::apply_visitor(testspr::x2_visitor<double>(), var2) == 0.0);
			{
				auto var3 = var1;
				TESTSPR_ASSERT(sprout::apply_visitor(testspr::x2_assign_visitor<double>(), var3) == 2.0);
				TESTSPR_ASSERT(var3.which() == 1);
				TESTSPR_ASSERT(sprout::get<double>(var3) == 2.0);
			}
			{
				auto var3 = var2;
				TESTSPR_ASSERT(sprout::apply_visitor(testspr::x2_assign_visitor<double>(), var3) == 0.0);
				TESTSPR_ASSERT(var3.which() == 0);
				TESTSPR_ASSERT(sprout::get<int>(var3) == 0);
			}
			{
				testspr::x2_visitor<double> visitor1 = {};
				TESTSPR_BOTH_ASSERT(sprout::apply_visitor(visitor1, var1) == 2.0);
				TESTSPR_BOTH_ASSERT(sprout::apply_visitor(visitor1, var2) == 0.0);
			}
			{
				auto var3 = var2;
				testspr::x2_assign_visitor<double> visitor1 = {};
				TESTSPR_ASSERT(sprout::apply_visitor(visitor1, var3) == 0.0);
				TESTSPR_ASSERT(var3.which() == 0);
				TESTSPR_ASSERT(sprout::get<int>(var3) == 0);
			}

			// operator<<
			{
				std::ostringstream os;
				os << var1;
				TESTSPR_ASSERT(os.str() == "1");
			}
			{
				std::ostringstream os;
				os << var2;
				TESTSPR_ASSERT(os.str() == "0");
			}

			// tuples::get
			TESTSPR_BOTH_ASSERT(sprout::tuples::get<1>(var1) == 1.0);
			TESTSPR_BOTH_ASSERT(sprout::tuples::get<0>(var2) == 0);
			{
				auto var3 = var1;
				TESTSPR_ASSERT(sprout::tuples::get<1>(var3) == 1.0);
			}
			{
				auto var3 = var2;
				TESTSPR_ASSERT(sprout::tuples::get<0>(var3) == 0);
			}

			// tuple_size
			TESTSPR_BOTH_ASSERT(sprout::tuples::tuple_size<decltype(var1)>::value == 2);

			// tuple_element
			TESTSPR_BOTH_ASSERT((std::is_same<sprout::tuples::tuple_element<0, decltype(var1)>::type, int const>::value));
			TESTSPR_BOTH_ASSERT((std::is_same<sprout::tuples::tuple_element<1, decltype(var1)>::type, double const>::value));

			// is_variant
			TESTSPR_BOTH_ASSERT(sprout::is_variant<decltype(var1)>::value);
			TESTSPR_BOTH_ASSERT(!sprout::is_variant<int>::value);

			// sprout::to_hash, sprout::hash
			TESTSPR_BOTH_ASSERT(sprout::to_hash(var1) == sprout::hash<decltype(var1)>()(var1));
			TESTSPR_BOTH_ASSERT(sprout::to_hash(var1) != sprout::to_hash(sprout::variant<int, double>()));
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::variant_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_VARIANT_TEST_VARIANT_CPP
