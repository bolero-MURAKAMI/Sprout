/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_STRING_TEST_STRING_CPP
#define SPROUT_LIBS_STRING_TEST_STRING_CPP

#include <sstream>
#include <type_traits>
#include <sprout/string.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void string_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char cstr[] = "foobar1234";
			SPROUT_STATIC_CONSTEXPR auto str1 = sprout::to_string(cstr);
			SPROUT_STATIC_CONSTEXPR auto str2 = sprout::to_string("hogehoge");

			TESTSPR_BOTH_ASSERT((std::is_same<decltype(str1), sprout::basic_string<char, 10> const>::value));
			TESTSPR_BOTH_ASSERT((std::is_same<decltype(str2), sprout::basic_string<char, 8> const>::value));

			// constructor
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = sprout::string_t<10>::type();
				TESTSPR_BOTH_ASSERT(s1.size() == 0);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = str1;
				TESTSPR_BOTH_ASSERT(s1 == str1);
			}
			{
				SPROUT_STATIC_CONSTEXPR std::decay<decltype(str1)>::type s1 = str2;
				TESTSPR_BOTH_ASSERT(s1 == str2);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = std::decay<decltype(str1)>::type(str1, 6);
				TESTSPR_BOTH_ASSERT(s1 == "1234");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = std::decay<decltype(str1)>::type(str1, 0, 6);
				TESTSPR_BOTH_ASSERT(s1 == "foobar");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = std::decay<decltype(str1)>::type(str2, 4);
				TESTSPR_BOTH_ASSERT(s1 == "hoge");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = std::decay<decltype(str1)>::type(str2, 0, 4);
				TESTSPR_BOTH_ASSERT(s1 == "hoge");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = sprout::string_t<10>::type(cstr);
				TESTSPR_BOTH_ASSERT(s1 == cstr);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = sprout::string_t<10>::type(cstr, 6);
				TESTSPR_BOTH_ASSERT(s1 == "foobar");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = sprout::string_t<10>::type(static_cast<char const*>(cstr));
				TESTSPR_BOTH_ASSERT(s1 == cstr);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = sprout::string_t<10>::type(static_cast<char const*>(cstr), 6);
				TESTSPR_BOTH_ASSERT(s1 == "foobar");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = sprout::string_t<10>::type(cstr, cstr + 6);
				TESTSPR_BOTH_ASSERT(s1 == "foobar");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = sprout::string_t<10>::type(6, 'f');
				TESTSPR_BOTH_ASSERT(s1 == "ffffff");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = sprout::string_t<10>::type(6, int('f'));
				TESTSPR_BOTH_ASSERT(s1 == "ffffff");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto s1 = sprout::string_t<10>::type(testspr::reduce_input(str1.begin()), testspr::reduce_input(str1.begin() + 6));
				TESTSPR_BOTH_ASSERT(s1 == "foobar");
			}
			{
				auto s1 = sprout::string_t<10>::type({'f', 'o', 'o', 'b', 'a', 'r'});
				TESTSPR_ASSERT(s1 == "foobar");
			}

			// begin
			TESTSPR_BOTH_ASSERT(cstr[0] == *str1.begin());

			// cbegin
			TESTSPR_BOTH_ASSERT(cstr[0] == *str1.cbegin());

			// end
			TESTSPR_BOTH_ASSERT(cstr[9] == *(str1.end() - 1));

			// cend
			TESTSPR_BOTH_ASSERT(cstr[9] == *(str1.cend() - 1));

			// rbegin
			TESTSPR_BOTH_ASSERT(cstr[9] == *str1.rbegin());

			// crbegin
			TESTSPR_BOTH_ASSERT(cstr[9] == *str1.crbegin());

			// rend
			TESTSPR_BOTH_ASSERT(cstr[0] == *(str1.rend() - 1));

			// crend
			TESTSPR_BOTH_ASSERT(cstr[0] == *(str1.crend() - 1));

			// size
			TESTSPR_BOTH_ASSERT(str1.size() == 10);

			// empty
			TESTSPR_BOTH_ASSERT(!str1.empty());
			TESTSPR_BOTH_ASSERT((sprout::string_t<0>::type().empty()));

			// max_size
			TESTSPR_BOTH_ASSERT(str1.max_size() == 10);

			// operator[]
			TESTSPR_BOTH_ASSERT(cstr[0] == str1[0]);

			// at
			TESTSPR_BOTH_ASSERT(cstr[0] == str1.at(0));

			// front
			TESTSPR_BOTH_ASSERT(cstr[0] == str1.front());

			// back
			TESTSPR_BOTH_ASSERT(cstr[9] == str1.back());

			// data
			TESTSPR_BOTH_ASSERT(cstr[0] == *str1.data());

			// c_str
			TESTSPR_BOTH_ASSERT(cstr[0] == *str1.c_str());

			// swap
			{
				auto s1 = sprout::to_string("abc");
				auto s2 = sprout::to_string("ABC");
				s1.swap(s2);
				TESTSPR_ASSERT(s1[0] == 'A');
			}

			// assign
			{
				auto s = sprout::to_string("abc");
				s.assign(sprout::to_string("ABC"));
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = sprout::to_string("abc");
				s.assign(sprout::to_string("ABC"), 0, 2);
				TESTSPR_ASSERT(s.size() == 2);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = sprout::to_string("abc");
				s.assign("ABC", 2);
				TESTSPR_ASSERT(s.size() == 2);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = sprout::to_string("abc");
				s.assign("ABC");
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = sprout::to_string("abc");
				s.assign(1, 'A');
				TESTSPR_ASSERT(s.size() == 1);
				TESTSPR_ASSERT(s[0] == 'A');
			}

			// operator=
			{
				auto s = sprout::to_string("abc");
				s = sprout::to_string("ABC");
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = sprout::to_string("abc");
				s = "ABC";
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = sprout::to_string("abc");
				s = 'A';
				TESTSPR_ASSERT(s.size() == 1);
				TESTSPR_ASSERT(s[0] == 'A');
			}

			// find
			TESTSPR_BOTH_ASSERT(str1.find(str2) == npos);
			TESTSPR_BOTH_ASSERT(str1.find(sprout::to_string("bar")) == 3);
			TESTSPR_BOTH_ASSERT(str1.find(str2.c_str()) == npos);
			TESTSPR_BOTH_ASSERT(str1.find("bar") == 3);
			TESTSPR_BOTH_ASSERT(str1.find(str2.c_str(), 0, 3) == npos);
			TESTSPR_BOTH_ASSERT(str1.find("barbar", 0, 3) == 3);
			TESTSPR_BOTH_ASSERT(str1.find('b') == 3);

			// rfind
			TESTSPR_BOTH_ASSERT(str1.rfind(str2) == npos);
			TESTSPR_BOTH_ASSERT(str1.rfind(sprout::to_string("bar")) == 3);
			TESTSPR_BOTH_ASSERT(str1.rfind(str2.c_str()) == npos);
			TESTSPR_BOTH_ASSERT(str1.rfind("bar") == 3);
			TESTSPR_BOTH_ASSERT(str1.rfind(str2.c_str(), npos, 3) == npos);
			TESTSPR_BOTH_ASSERT(str1.rfind("barbar", npos, 3) == 3);
			TESTSPR_BOTH_ASSERT(str1.rfind('b') == 3);

			// find_first_of
			TESTSPR_BOTH_ASSERT(str1.find_first_of(sprout::to_string("vwxyz")) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_of(sprout::to_string("rab")) == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_of("vwxyz") == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_of("rab") == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_of("vwxyz", 0, 3) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_of("rabrab", 0, 3) == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_of('b') == 3);

			// find_last_of
			TESTSPR_BOTH_ASSERT(str1.find_last_of(sprout::to_string("vwxyz")) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_of(sprout::to_string("rab")) == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_of("vwxyz") == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_of("rab") == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_of("vwxyz", npos, 3) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_of("rabrab", npos, 3) == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_of('r') == 5);

			// find_first_not_of
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of(str1) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of(sprout::to_string("foo")) == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of(str1.c_str()) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of("foo") == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of(str1.c_str(), 0, 10) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of("foofoo", 0, 3) == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of('f') == 1);

			// find_last_not_of
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of(str1) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of(sprout::to_string("4321")) == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of(str1.c_str()) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of("4321") == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of(str1.c_str(), npos, 10) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of("43214321", npos, 4) == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of('4') == 8);

			// substr
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = str1.substr();
				TESTSPR_BOTH_ASSERT(str3 == "foobar1234");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = str1.substr(6);
				TESTSPR_BOTH_ASSERT(str3 == "1234");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = str1.substr(0, 6);
				TESTSPR_BOTH_ASSERT(str3 == "foobar");
			}

			// compare
			TESTSPR_BOTH_ASSERT(str1.compare(str1) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(sprout::to_string("zzzz")) < 0);
			TESTSPR_BOTH_ASSERT(str2.compare(sprout::to_string("aaaa")) > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, sprout::to_string("foo")) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, sprout::to_string("zzzz")) < 0);
			TESTSPR_BOTH_ASSERT(str2.compare(0, 3, sprout::to_string("aaaa")) > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, sprout::to_string("foo"), 0, 3) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, sprout::to_string("zzzz"), 0, 3) < 0);
			TESTSPR_BOTH_ASSERT(str2.compare(0, 3, sprout::to_string("aaaa"), 0, 3) > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(str1.c_str()) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare("zzzz") < 0);
			TESTSPR_BOTH_ASSERT(str1.compare("aaaa") > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "foo") == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "zzzz") < 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "aaaa") > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "foo", 3) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "zzzz", 3) < 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "aaaa", 3) > 0);

			// operator==
			TESTSPR_BOTH_ASSERT(!(str1 == str2));

			// operator!=
			TESTSPR_BOTH_ASSERT(str1 != str2);

			// operator<
			TESTSPR_BOTH_ASSERT(str1 < str2);

			// operator>
			TESTSPR_BOTH_ASSERT(!(str1 > str2));

			// operator<=
			TESTSPR_BOTH_ASSERT(str1 <= str2);

			// operator>=
			TESTSPR_BOTH_ASSERT(!(str1 >= str2));

			// operator+
			{
#ifdef SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
				// ! Error in GCC4.7
				SPROUT_STATIC_CONSTEXPR auto str3 = str1 + sprout::to_string("hogehoge");
				TESTSPR_BOTH_ASSERT(str3 == "foobar1234hogehoge");
#endif

				SPROUT_STATIC_CONSTEXPR auto str4 = str1 + str2;
				TESTSPR_BOTH_ASSERT(str4 == "foobar1234hogehoge");
			}

			// operator<<
			{
				std::ostringstream os;
				os << str1;
				TESTSPR_ASSERT(os.str() == cstr);
			}

			// operator>>
			{
				std::istringstream is("hogehoge piyopiyo");
				auto str3 = str1;
				is >> str3;
				TESTSPR_ASSERT(str3 == "hogehoge");
			}

			// string_from_c_str
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = string_from_c_str<10>(cstr);
				TESTSPR_BOTH_ASSERT(str3 == "foobar1234");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = string_from_c_str<10>(cstr, 6);
				TESTSPR_BOTH_ASSERT(str3 == "foobar");
			}

			// make_string
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = make_string('f', 'o', 'o', 'b', 'a', 'r');
				TESTSPR_BOTH_ASSERT(str3 == "foobar");
				TESTSPR_BOTH_ASSERT(str3.size() == 6);
			}

			// operator basic_string
			{
				SPROUT_STATIC_CONSTEXPR string_t<10>::type str3 = sprout::to_string("foobar");
				TESTSPR_BOTH_ASSERT(str3 == "foobar");
				TESTSPR_BOTH_ASSERT(str3.size() == 6);
			}

			// get
			TESTSPR_BOTH_ASSERT(sprout::tuples::get<0>(str1) == 'f');
			TESTSPR_BOTH_ASSERT(sprout::tuples::get<1>(str1) == 'o');
			{
				auto str3 = str1;
				TESTSPR_ASSERT(sprout::tuples::get<0>(str3) == 'f');
				TESTSPR_ASSERT(sprout::tuples::get<1>(str3) == 'o');
			}

			// tuple_size
			TESTSPR_BOTH_ASSERT(sprout::tuples::tuple_size<decltype(str1)>::value == 10);

			// tuple_element
			TESTSPR_BOTH_ASSERT((std::is_same<sprout::tuples::tuple_element<0, decltype(str1)>::type, char const>::value));
			TESTSPR_BOTH_ASSERT((std::is_same<sprout::tuples::tuple_element<1, decltype(str1)>::type, char const>::value));

			// is_string
			TESTSPR_BOTH_ASSERT(sprout::is_string<decltype(str1)>::value);
			TESTSPR_BOTH_ASSERT(!sprout::is_string<int>::value);

			// sprout::to_hash, sprout::hash
			TESTSPR_BOTH_ASSERT(sprout::to_hash(str1) == sprout::hash<decltype(str1)>()(str1));
			TESTSPR_BOTH_ASSERT(sprout::to_hash(str1) != sprout::to_hash(str2));
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::string_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_STRING_TEST_STRING_CPP
