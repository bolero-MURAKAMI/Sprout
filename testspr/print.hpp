/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
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
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <sprout/config.hpp>
#include <sprout/preprocessor/config.hpp>
#include <sprout/preprocessor/stringize.hpp>
#include <sprout/utility/swallow.hpp>
#include <sprout/container.hpp>
#include <sprout/detail/io/ios_state.hpp>
#include <testspr/typeinfo.hpp>

namespace testspr {
	namespace detail {
		inline SPROUT_NON_CONSTEXPR std::ostream&
		output(std::ostream& os) {
			return os;
		}
		template<typename Head, typename... Tail>
		inline SPROUT_NON_CONSTEXPR std::ostream&
		output(std::ostream& os, Head const& head, Tail const&... tail) {
			return testspr::detail::output(os << head, tail...);
		}
	}	// namespace detail

	//
	// to_string
	//
	template<typename Head, typename... Tail>
	inline SPROUT_NON_CONSTEXPR std::string
	to_string(Head const& head, Tail const&... tail) {
		std::ostringstream os;
		testspr::detail::output(os, head, tail...);
		return os.str();
	}

	//
	// endl
	//
	class endl_t {};
	template<typename Elem, typename Traits>
	inline SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& lhs, testspr::endl_t) {
		return lhs << std::endl;
	}
	namespace {
		SPROUT_STATIC_CONSTEXPR endl_t endl = {};
	}	// anonymous-namespace
	//
	// ends
	//
	class ends_t {};
	template<typename Elem, typename Traits>
	inline SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& lhs, testspr::ends_t) {
		return lhs << std::ends;
	}
	namespace {
		SPROUT_STATIC_CONSTEXPR ends_t ends = {};
	}	// anonymous-namespace
	//
	// flush
	//
	class flush_t {};
	template<typename Elem, typename Traits>
	inline SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& lhs, testspr::flush_t) {
		return lhs << std::flush;
	}
	namespace {
		SPROUT_STATIC_CONSTEXPR flush_t flush = {};
	}	// anonymous-namespace

	//
	// ios_all_saver
	//
	class ios_all_saver {
	private:
		sprout::detail::io::ios_all_saver saver_;
	public:
		SPROUT_NON_CONSTEXPR ios_all_saver()
			: saver_(std::cout)
		{}
		SPROUT_NON_CONSTEXPR ios_all_saver(std::ostream& os)
			: saver_(os)
		{}
	};

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
		testspr::print(testspr::endl);
	}
	template<typename... Args>
	inline SPROUT_NON_CONSTEXPR void
	print_ln(Args const&... args) {
		testspr::ios_all_saver saver;
		testspr::print(args..., testspr::endl);
	}

	//
	// print_tokens_d
	//
	template<typename T>
	inline SPROUT_NON_CONSTEXPR void
	print_tokens_d(T const&) {
		testspr::print_ln();
	}
	template<typename T, typename Head, typename... Tail>
	inline SPROUT_NON_CONSTEXPR void
	print_tokens_d(T const& delim, Head const& head, Tail const&... tail) {
		testspr::ios_all_saver saver;
		testspr::print(head);
		sprout::swallow({(testspr::print(delim, tail), 0)...});
		testspr::print_ln();
	}
	//
	// print_tokens
	//
	template<typename... Args>
	inline SPROUT_NON_CONSTEXPR void
	print_tokens(Args const&... args) {
		print_tokens_d(' ', args...);
	}

	//
	// print_quotes_d
	//
	template<typename T>
	inline SPROUT_NON_CONSTEXPR void
	print_quotes_d(T const&) {
		testspr::print_ln();
	}
	template<typename T, typename Head, typename... Tail>
	inline SPROUT_NON_CONSTEXPR void
	print_quotes_d(T const& delim, Head const& head, Tail const&... tail) {
		testspr::ios_all_saver saver;
		testspr::print('\"', head, '\"');
		sprout::swallow({(testspr::print(delim, '\"', tail, '\"'), 0)...});
		testspr::print_ln();
	}
	//
	// print_quotes
	//
	template<typename... Args>
	inline SPROUT_NON_CONSTEXPR void
	print_quotes(Args const&... args) {
		print_quotes_d(' ', args...);
	}

	//
	// print_range_d
	//
	template<typename T, typename InputIterator>
	inline SPROUT_NON_CONSTEXPR void
	print_range_d(T const& delim, InputIterator first, InputIterator last) {
		testspr::ios_all_saver saver;
		if (first != last) {
			testspr::print(*first);
		}
		++first;
		for (; first != last; ++first) {
			testspr::print(delim, *first);
		}
		testspr::print_ln();
	}
	template<typename T, typename InputRange>
	inline SPROUT_NON_CONSTEXPR void
	print_range_d(T const& delim, InputRange const& range) {
		testspr::print_range_d(delim, sprout::begin(range), sprout::end(range));
	}
	//
	// print_range
	//
	template<typename InputIterator>
	inline SPROUT_NON_CONSTEXPR void
	print_range(InputIterator first, InputIterator last) {
		print_range_d(' ', first, last);
	}
	template<typename InputRange>
	inline SPROUT_NON_CONSTEXPR void
	print_range(InputRange const& range) {
		print_range_d(' ', range);
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
	template<typename T>
	inline SPROUT_NON_CONSTEXPR void
	print_typename(T&& t) {
		testspr::print_ln(testspr::typename_of(std::forward<T>(t)));
	}

	//
	// print_type
	//
	template<typename T>
	inline SPROUT_NON_CONSTEXPR void
	print_type() {
		testspr::print_ln(testspr::qualified_typename_of<T>());
	}

	//
	// print_hl
	//
	inline SPROUT_NON_CONSTEXPR void
	print_hl() {
		testspr::print_ln("--------------------------------------------------------------------------------");
	}
	template<typename T>
	inline SPROUT_NON_CONSTEXPR void
	print_hl(char c) {
		for (std::string::size_type i = 0, last = 80; i != last; ++i) {
			testspr::print(c);
		}
		testspr::print_ln();
	}
	template<typename T>
	inline SPROUT_NON_CONSTEXPR void
	print_hl(T const& t) {
		std::string s(testspr::to_string(t));
		for (std::string::size_type i = 0, n = 80 / s.size(); i != n; ++i) {
			testspr::print(s);
		}
		for (std::string::const_iterator it = s.begin(), last = s.begin() + 80 % s.size(); it != last; ++it) {
			testspr::print(*it);
		}
		testspr::print_ln();
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
	inline SPROUT_NON_CONSTEXPR T&
	manip(T& t) {
		return t;
	}
	template<typename T>
	inline SPROUT_NON_CONSTEXPR T const&
	manip(T const& t) {
		return t;
	}
	inline SPROUT_NON_CONSTEXPR testspr::manip_holder<std::ostream& (*)(std::ostream&)>
	manip(std::ostream& (*pf)(std::ostream&)) {
		return pf;
	}
	template<typename Elem, typename Traits>
	inline SPROUT_NON_CONSTEXPR testspr::manip_holder<std::ios& (*)(std::ios&)>
	manip(std::ios& (*pf)(std::ios&)) {
		return pf;
	}
	inline SPROUT_NON_CONSTEXPR testspr::manip_holder<std::ios_base& (*)(std::ios_base&)>
	manip(std::ios_base& (*pf)(std::ios_base&)) {
		return pf;
	}
}	// namespace testspr

//
// TESTSPR_PRINT_EXPR
//
#if SPROUT_PP_VARIADICS
#	define TESTSPR_PRINT_EXPR(...) \
		::testspr::print_ln(SPROUT_PP_STRINGIZE((__VA_ARGS__)), " => ", __VA_ARGS__)
#else
#	define TESTSPR_PRINT_EXPR(EXPR) \
		::testspr::print_ln(SPROUT_PP_STRINGIZE((EXPR)), " => ", EXPR)
#endif

#endif	// #ifndef TESTSPR_PRINT_HPP
