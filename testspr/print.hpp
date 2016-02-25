/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_PRINT_HPP
#define TESTSPR_PRINT_HPP

#include <algorithm>
#include <iterator>
#include <bitset>
#include <utility>
#include <iostream>
#include <iomanip>
#include <sprout/config.hpp>
#include <sprout/container.hpp>
#include <sprout/detail/io/ios_state.hpp>
#include <testspr/typeinfo.hpp>

namespace testspr {
	//
	// print
	//
	inline SPROUT_NON_CONSTEXPR void
	print() {}
	template<typename Head, typename... Tail>
	inline SPROUT_NON_CONSTEXPR void
	print(Head const& head, Tail const&... tail) {
		std::cout << head;
		testspr::print(tail...);
	}

	//
	// print_ln
	//
	inline SPROUT_NON_CONSTEXPR void
	print_ln() {
		std::cout << std::endl;
	}
	template<typename... Args>
	inline SPROUT_NON_CONSTEXPR void
	print_ln(Args const&... args) {
		sprout::detail::io::ios_all_saver saver(std::cout);
		testspr::print(args...);
		std::cout << std::endl;
	}

	//
	// print_tokens
	//
	inline SPROUT_NON_CONSTEXPR void
	print_tokens() {
		testspr::print_ln();
	}
	template<typename Head, typename... Tail>
	inline SPROUT_NON_CONSTEXPR void
	print_tokens(Head const& head, Tail const&... tail) {
		sprout::detail::io::ios_all_saver saver(std::cout);
		testspr::print(head, ' ');
		testspr::print_tokens(tail...);
	}

	//
	// print_quotes
	//
	inline SPROUT_NON_CONSTEXPR void
	print_quotes() {
		testspr::print_ln();
	}
	template<typename Head, typename... Tail>
	inline SPROUT_NON_CONSTEXPR void
	print_quotes(Head const& head, Tail const&... tail) {
		sprout::detail::io::ios_all_saver saver(std::cout);
		testspr::print('\"', head, "\" ");
		testspr::print_quotes(tail...);
	}

	//
	// print_range
	//
	template<typename InputIterator>
	inline SPROUT_NON_CONSTEXPR void
	print_range(InputIterator first, InputIterator last) {
		sprout::detail::io::ios_all_saver saver(std::cout);
		for (; first != last; ++first) {
			std::cout << *first << ' ';
		}
		std::cout << std::endl;
	}
	template<typename InputRange>
	inline SPROUT_NON_CONSTEXPR void
	print_range(InputRange const& range) {
		testspr::print_range(sprout::begin(range), sprout::end(range));
	}

	//
	// print_bits
	//
	template<typename T>
	inline SPROUT_NON_CONSTEXPR void
	print_bits(T const& t) {
		testspr::print_ln(std::bitset<sizeof(T) * 8>(t).template to_string<char>());
	}

	//
	// print_typename
	//
	template<typename T>
	inline SPROUT_NON_CONSTEXPR void
	print_typename() {
		testspr::print_ln(testspr::typename_of<T>());
	}

	//
	// print_type
	//
	template<typename T>
	inline SPROUT_NON_CONSTEXPR void
	print_type() {
		testspr::print_typename<testspr::id<T> >();
	}

	//
	// print_hl
	//
	inline SPROUT_NON_CONSTEXPR void
	print_hl() {
		testspr::print_ln("--------------------------------------------------------------------------------");
	}

	//
	// manip_holder
	//
	template<typename T>
	class manip_holder {
	public:
		typedef T value_type;
	private:
		value_type m_;
	public:
		SPROUT_CONSTEXPR manip_holder(value_type const& m)
			: m_(m)
		{}
		SPROUT_CONSTEXPR value_type const& get() const {
			return m_;
		}
	};
	template<typename T, typename Elem, typename Traits>
	inline SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& lhs, testspr::manip_holder<T> const& rhs) {
		return lhs << rhs.get();
	}
	template<typename T, typename Elem, typename Traits>
	inline SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>&
	operator>>(std::basic_istream<Elem, Traits>& lhs, testspr::manip_holder<T> const& rhs) {
		return lhs >> rhs.get();
	}
	//
	// manip
	//
	template<typename T>
	inline SPROUT_NON_CONSTEXPR T&&
	manip(T&& t) {
		return std::forward<T>(t);
	}
	template<typename Elem, typename Traits>
	inline SPROUT_NON_CONSTEXPR testspr::manip_holder<std::basic_ostream<Elem, Traits>& (*)(std::basic_ostream<Elem, Traits>&)>
	manip(std::basic_ostream<Elem, Traits>& (*pf)(std::basic_ostream<Elem, Traits>&)) {
		return pf;
	}
	template<typename Elem, typename Traits>
	inline SPROUT_NON_CONSTEXPR testspr::manip_holder<std::basic_ios<Elem, Traits>& (*)(std::basic_ios<Elem, Traits>&)>
	manip(std::basic_ios<Elem, Traits>& (*pf)(std::basic_ios<Elem, Traits>&)) {
		return pf;
	}
	inline SPROUT_NON_CONSTEXPR testspr::manip_holder<std::ios_base& (*)(std::ios_base&)>
	manip(std::ios_base& (*pf)(std::ios_base&)) {
		return pf;
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_PRINT_HPP
