#ifndef SPROUT_LIBS_OPTIONAL_TEST_OPTIONAL_CPP
#define SPROUT_LIBS_OPTIONAL_TEST_OPTIONAL_CPP

#include <sstream>
#include <sprout/optional.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void optional_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto opt1 = sprout::optional<int>(1234);
			SPROUT_STATIC_CONSTEXPR auto opt2 = sprout::optional<int>();

			// constructor
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::optional<int>();
				TESTSPR_BOTH_ASSERT(!opt3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::optional<int>(1234);
				TESTSPR_BOTH_ASSERT(!!opt3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::optional<int>(sprout::nullopt);
				TESTSPR_BOTH_ASSERT(!opt3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::optional<int>(sprout::nullopt);
				TESTSPR_BOTH_ASSERT(!opt3);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::optional<int>(false, 1234);
				TESTSPR_BOTH_ASSERT(!opt3);

				SPROUT_STATIC_CONSTEXPR auto opt4 = sprout::optional<int>(true, 1234);
				TESTSPR_BOTH_ASSERT(!!opt4);
				TESTSPR_BOTH_ASSERT(opt4.get() == 1234);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::optional<int>(opt1);
				TESTSPR_BOTH_ASSERT(!!opt3);
				TESTSPR_BOTH_ASSERT(opt3.get() == 1234);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::optional<int>(sprout::optional<unsigned>(1234));
				TESTSPR_BOTH_ASSERT(!!opt3);
				TESTSPR_BOTH_ASSERT(opt3.get() == 1234);
			}

			// operator=
			{
				auto opt3 = sprout::optional<int>(1234);
				opt3 = sprout::nullopt;
				TESTSPR_ASSERT(!opt3);
			}
			{
				auto opt3 = sprout::optional<int>();
				opt3 = 1234;
				TESTSPR_ASSERT(!!opt3);
				TESTSPR_ASSERT(opt3.get() == 1234);
			}
			{
				auto opt3 = sprout::optional<int>();
				opt3 = opt1;
				TESTSPR_ASSERT(!!opt3);
				TESTSPR_ASSERT(opt3.get() == 1234);
			}
			{
				auto opt3 = sprout::optional<int>();
				opt3 = sprout::optional<unsigned>(1234);
				TESTSPR_ASSERT(!!opt3);
				TESTSPR_ASSERT(opt3.get() == 1234);
			}

			// assign
			{
				auto opt3 = sprout::optional<int>(1234);
				opt3.assign(sprout::nullopt);
				TESTSPR_ASSERT(!opt3);
			}
			{
				auto opt3 = sprout::optional<int>();
				opt3.assign(1234);
				TESTSPR_ASSERT(!!opt3);
				TESTSPR_ASSERT(opt3.get() == 1234);
			}
			{
				auto opt3 = sprout::optional<int>();
				opt3.assign(opt1);
				TESTSPR_ASSERT(!!opt3);
				TESTSPR_ASSERT(opt3.get() == 1234);
			}
			{
				auto opt3 = sprout::optional<int>();
				opt3.assign(sprout::optional<unsigned>(1234));
				TESTSPR_ASSERT(!!opt3);
				TESTSPR_ASSERT(opt3.get() == 1234);
			}

			// reset
			{
				auto opt3 = sprout::optional<int>(1234);
				opt3.reset();
				TESTSPR_ASSERT(!opt3);
			}
			{
				auto opt3 = sprout::optional<int>(1234);
				opt3.reset(sprout::nullopt);
				TESTSPR_ASSERT(!opt3);
			}
			{
				auto opt3 = sprout::optional<int>();
				opt3.reset(1234);
				TESTSPR_ASSERT(!!opt3);
				TESTSPR_ASSERT(opt3.get() == 1234);
			}

			// swap
			{
				auto opt3 = sprout::optional<int>(1234);
				auto opt4 = sprout::optional<int>();
				opt3.swap(opt4);
				TESTSPR_ASSERT(!opt3);
				TESTSPR_ASSERT(!!opt4);
				TESTSPR_ASSERT(opt4.get() == 1234);
			}
			{
				auto opt3 = sprout::optional<int>(1234);
				auto opt4 = sprout::optional<int>();
				swap(opt3, opt4);
				TESTSPR_ASSERT(!opt3);
				TESTSPR_ASSERT(!!opt4);
				TESTSPR_ASSERT(opt4.get() == 1234);
			}

			// operator*
			TESTSPR_BOTH_ASSERT(*opt1 == 1234);
			{
				auto opt3 = sprout::optional<int>(1234);
				TESTSPR_ASSERT(*opt3 == 1234);

				*opt3 = 12345;
				TESTSPR_ASSERT(*opt3 == 12345);
			}

			// get
			TESTSPR_BOTH_ASSERT(opt1.get() == 1234);
			{
				auto opt3 = sprout::optional<int>(1234);
				TESTSPR_ASSERT(opt3.get() == 1234);

				opt3.get() = 12345;
				TESTSPR_ASSERT(opt3.get() == 12345);
			}

			// get_value_or
			TESTSPR_BOTH_ASSERT(opt1.get_value_or(12345) == 1234);
			TESTSPR_BOTH_ASSERT(opt2.get_value_or(12345) == 12345);
			{
				auto opt3 = sprout::optional<int>(1234);
				int v = 12345;
				TESTSPR_ASSERT(opt3.get_value_or(v) == 1234);
			}
			{
				auto opt3 = sprout::optional<int>();
				int v = 12345;
				TESTSPR_ASSERT(opt3.get_value_or(v) == 12345);
			}

			// operator->
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::make_optional(testspr::is_odd<int>());
				TESTSPR_BOTH_ASSERT(opt3->operator()(123));
			}
			{
				auto opt3 = sprout::make_optional(testspr::is_odd<int>());
				TESTSPR_ASSERT(opt3->operator()(123));
			}

			// get_pointer
			TESTSPR_BOTH_ASSERT(*opt1.get_pointer() == 1234);
			{
				auto opt3 = sprout::optional<int>(1234);
				TESTSPR_ASSERT(*opt3.get_pointer() == 1234);

				opt3.get() = 12345;
				TESTSPR_ASSERT(*opt3.get_pointer() == 12345);
			}

			// get_ptr
			TESTSPR_BOTH_ASSERT(*opt1.get_ptr() == 1234);
			{
				auto opt3 = sprout::optional<int>(1234);
				TESTSPR_ASSERT(*opt3.get_ptr() == 1234);

				opt3.get() = 12345;
				TESTSPR_ASSERT(*opt3.get_ptr() == 12345);
			}

			// operator bool
			TESTSPR_BOTH_ASSERT(static_cast<bool>(opt1));
			TESTSPR_BOTH_ASSERT(!static_cast<bool>(opt2));

			// operator!
			TESTSPR_BOTH_ASSERT(!!opt1);
			TESTSPR_BOTH_ASSERT(!opt2);

			// is_initialized
			TESTSPR_BOTH_ASSERT(opt1.is_initialized());
			TESTSPR_BOTH_ASSERT(!opt2.is_initialized());

			// make_optional
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::make_optional(1234);
				TESTSPR_BOTH_ASSERT(!!opt3);
				TESTSPR_BOTH_ASSERT(opt3.get() == 1234);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto opt3 = sprout::make_optional(false, 1234);
				TESTSPR_BOTH_ASSERT(!opt3);

				SPROUT_STATIC_CONSTEXPR auto opt4 = sprout::make_optional(true, 1234);
				TESTSPR_BOTH_ASSERT(!!opt4);
				TESTSPR_BOTH_ASSERT(opt4.get() == 1234);
			}

			// operator==
			TESTSPR_BOTH_ASSERT(!(opt1 == opt2));
			TESTSPR_BOTH_ASSERT(opt1 == sprout::optional<int>(1234));

			// operator!=
			TESTSPR_BOTH_ASSERT(opt1 != opt2);
			TESTSPR_BOTH_ASSERT(!(opt1 != sprout::optional<int>(1234)));

			// operator<
			TESTSPR_BOTH_ASSERT(!(opt1 < opt2));
			TESTSPR_BOTH_ASSERT(!(opt1 < sprout::optional<int>()));
			TESTSPR_BOTH_ASSERT(!(opt1 < sprout::optional<int>(123)));
			TESTSPR_BOTH_ASSERT(!(opt1 < sprout::optional<int>(1234)));
			TESTSPR_BOTH_ASSERT(opt1 < sprout::optional<int>(12345));
			TESTSPR_BOTH_ASSERT(!(opt2 < sprout::optional<int>()));
			TESTSPR_BOTH_ASSERT(opt2 < sprout::optional<int>(123));
			TESTSPR_BOTH_ASSERT(opt2 < sprout::optional<int>(1234));
			TESTSPR_BOTH_ASSERT(opt2 < sprout::optional<int>(12345));

			// operator>
			TESTSPR_BOTH_ASSERT(opt1 > opt2);
			TESTSPR_BOTH_ASSERT(opt1 > sprout::optional<int>());
			TESTSPR_BOTH_ASSERT(opt1 > sprout::optional<int>(123));
			TESTSPR_BOTH_ASSERT(!(opt1 > sprout::optional<int>(1234)));
			TESTSPR_BOTH_ASSERT(!(opt1 > sprout::optional<int>(12345)));
			TESTSPR_BOTH_ASSERT(!(opt2 > sprout::optional<int>()));
			TESTSPR_BOTH_ASSERT(!(opt2 > sprout::optional<int>(123)));
			TESTSPR_BOTH_ASSERT(!(opt2 > sprout::optional<int>(1234)));
			TESTSPR_BOTH_ASSERT(!(opt2 > sprout::optional<int>(12345)));

			// operator<=
			TESTSPR_BOTH_ASSERT(!(opt1 <= opt2));
			TESTSPR_BOTH_ASSERT(!(opt1 <= sprout::optional<int>()));
			TESTSPR_BOTH_ASSERT(!(opt1 <= sprout::optional<int>(123)));
			TESTSPR_BOTH_ASSERT(opt1 <= sprout::optional<int>(1234));
			TESTSPR_BOTH_ASSERT(opt1 <= sprout::optional<int>(12345));
			TESTSPR_BOTH_ASSERT(opt2 <= sprout::optional<int>());
			TESTSPR_BOTH_ASSERT(opt2 <= sprout::optional<int>(123));
			TESTSPR_BOTH_ASSERT(opt2 <= sprout::optional<int>(1234));
			TESTSPR_BOTH_ASSERT(opt2 <= sprout::optional<int>(12345));

			// operator>=
			TESTSPR_BOTH_ASSERT(opt1 >= opt2);
			TESTSPR_BOTH_ASSERT(opt1 >= sprout::optional<int>());
			TESTSPR_BOTH_ASSERT(opt1 >= sprout::optional<int>(123));
			TESTSPR_BOTH_ASSERT(opt1 >= sprout::optional<int>(1234));
			TESTSPR_BOTH_ASSERT(!(opt1 >= sprout::optional<int>(12345)));
			TESTSPR_BOTH_ASSERT(opt2 >= sprout::optional<int>());
			TESTSPR_BOTH_ASSERT(!(opt2 >= sprout::optional<int>(123)));
			TESTSPR_BOTH_ASSERT(!(opt2 >= sprout::optional<int>(1234)));
			TESTSPR_BOTH_ASSERT(!(opt2 >= sprout::optional<int>(12345)));

			// operator<<
			{
				std::ostringstream os;
				os << opt1;
				TESTSPR_ASSERT(os.str() == " 1234");
			}
			{
				std::ostringstream os;
				os << opt2;
				TESTSPR_ASSERT(os.str() == "--");
			}

			// operator>>
			{
				std::istringstream is(" 1234");
				auto opt3 = sprout::optional<int>();
				is >> opt3;
				TESTSPR_ASSERT(!!opt3);
				TESTSPR_ASSERT(opt3.get() == 1234);
			}
			{
				std::istringstream is("--");
				auto opt3 = sprout::optional<int>(1234);
				is >> opt3;
				TESTSPR_ASSERT(!opt3);
			}

			// get
			TESTSPR_BOTH_ASSERT(sprout::get(opt1) == 1234);
			{
				auto opt3 = sprout::optional<int>(1234);
				TESTSPR_ASSERT(sprout::get(opt3) == 1234);

				opt3.get() = 12345;
				TESTSPR_ASSERT(sprout::get(opt3) == 12345);
			}

			// get_pointer
			TESTSPR_BOTH_ASSERT(*sprout::get_pointer(opt1) == 1234);
			{
				auto opt3 = sprout::optional<int>(1234);
				TESTSPR_ASSERT(*sprout::get_pointer(opt3) == 1234);

				opt3.get() = 12345;
				TESTSPR_ASSERT(*sprout::get_pointer(opt3) == 12345);
			}

			// get_optional_value_or
			TESTSPR_BOTH_ASSERT(sprout::get_optional_value_or(opt1, 12345) == 1234);
			TESTSPR_BOTH_ASSERT(sprout::get_optional_value_or(opt2, 12345) == 12345);
			{
				auto opt3 = sprout::optional<int>(1234);
				int v = 12345;
				TESTSPR_ASSERT(sprout::get_optional_value_or(opt3, v) == 1234);
			}
			{
				auto opt3 = sprout::optional<int>();
				int v = 12345;
				TESTSPR_ASSERT(sprout::get_optional_value_or(opt3, v) == 12345);
			}

			// sprout::to_hash, sprout::hash
			TESTSPR_BOTH_ASSERT(sprout::to_hash(opt1) == sprout::hash<decltype(opt1)>()(opt1));
			TESTSPR_BOTH_ASSERT(sprout::to_hash(opt1) != sprout::to_hash(opt2));
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::optional_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_OPTIONAL_TEST_OPTIONAL_CPP
