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


int
main(){
	
	//
	// String literal to Sprout.String
	//
	{
		static constexpr auto str1 = sprout::to_string("homu");
		static_assert(str1 == "homu", "");
		static_assert(std::is_same<decltype(str1), sprout::string<4> const>{}, "");

		static constexpr auto str2 = sprout::to_string(L"ほむほむ");
		static_assert(str2 == L"ほむほむ", "");
		static_assert(std::is_same<decltype(str2), sprout::wstring<4> const>{}, "");
	}
	
	//
	// Integer literal to Sprout.String
	//
	{
		static constexpr auto str = sprout::to_string(42);
		static_assert(str == "42", "");
	}
	
	//
	// Float literal to Sprout.String
	//
	{
		static constexpr auto str = sprout::to_string(3.14f);
		static_assert(str == "3.140000", "");
	}

	//
	// Char literal to Sprout.String
	//
	{
		static constexpr auto str = sprout::make_string('m', 'a', 'd', 'o');
		static_assert(str == "mado", "");
		static_assert(std::is_same<decltype(str), sprout::string<4> const>{}, "");
	}

	return 0;
}
