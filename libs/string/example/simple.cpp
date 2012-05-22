//
// Sprout C++ Library
//
// Copyright (c) 2012
// bolero-MURAKAMI : http://d.hatena.ne.jp/boleros/
// osyo-manga : http://d.hatena.ne.jp/osyo-manga/
// 
// Readme:
// https://github.com/osyo-manga/cpp-half/blob/master/README
//
// License:
// Boost Software License - Version 1.0
// <http://www.boost.org/LICENSE_1_0.txt>
//
#include <sprout/string.hpp>
#include <sstream>
#include <cassert>


//
// Sprout.String is constexpr string object
//
int
main(){
	
	//
	// String literal to Sprout.String
	//
	static constexpr sprout::string<4> str1 = sprout::to_string("homu");
	static constexpr auto              str2 = sprout::to_string("mado");
	static constexpr auto              str3 = sprout::to_string(42);

	//
	// Comparison
	//
	static_assert(str1 == sprout::to_string("homu"), "");
	static_assert(str2 == "mado", "");
	static_assert(str3 == "42", "");
	static_assert(str1 != str2, "");

	//
	// Accessor
	//
	static_assert(str1.front() == 'h', "");
	static_assert(str1[1]      == 'o', "");
	static_assert(str1.at(2)   == 'm', "");
	static_assert(str1.back()  == 'u', "");

	//
	// String concatenation
	//
	static_assert((str1 + "homu") == "homuhomu", "");
	static_assert((str1 + str2)   == "homumado", "");
	static_assert((str1 + sprout::to_string("42"))   == "homu42", "");

	//
	// C style string
	//
	constexpr char const* cp = str1.c_str();
	static_assert(cp[0] == 'h', "");

	//
	// Iterator
	//
	static_assert(*str1.begin()        == 'h', "");
	static_assert(*(str1.end() - 1)    == 'u', "");
	static_assert(*(str1.rbegin() + 1) == 'm', "");
	static_assert(*(str1.rend() - 2)   == 'o', "");
	
	//
	// IOStream
	//
	{
		std::ostringstream os;
		os << str1;
		assert(os.str() == "homu");
	}
	{
		std::istringstream is("mami");
		sprout::string<4> str;
		is >> str;
		assert(str == "mami");
	}

	return 0;
}
