/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <stdexcept>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/range.hpp>
#include <sprout/iterator.hpp>
#include <sprout/memory.hpp>
#include <sprout/string.hpp>
#include <sprout/algorithm.hpp>

template<typename Char>
struct csv_parser_settings {
public:
	typedef Char value_type;
private:
	value_type delim_;
	value_type quote_;
	value_type escape_;
public:
	constexpr csv_parser_settings(value_type delim = Char(','), value_type quote = Char('\"'))
		: delim_(delim), quote_(quote), escape_(quote)
	{}
	constexpr csv_parser_settings(value_type delim, value_type quote, value_type escape)
		: delim_(delim), quote_(quote), escape_(escape)
	{}
	constexpr value_type delimiter() const {
		return delim_;
	}
	constexpr value_type quote() const {
		return quote_;
	}
	constexpr value_type escape() const {
		return escape_;
	}
};

template<std::size_t N, std::size_t L, typename String, typename ResultString = String>
constexpr sprout::array_sub_t<sprout::array_sub_t<ResultString, N>, L>
parse_csv(String const& src, csv_parser_settings<typename String::value_type> settings = csv_parser_settings<typename String::value_type>()) {
	typedef typename String::value_type value_type;
	sprout::array_sub_t<sprout::array_sub_t<ResultString, N>, L> result = {};
	result.window(0, 1);
	result.back().window(0, 0);
	bool same_escape = settings.quote() == settings.escape();
	auto delimiters = sprout::make_string(settings.delimiter(), value_type('\r'), value_type('\n'));
	auto first = sprout::begin(src), last = sprout::end(src);
	while (first != last) {
		if (*first == settings.quote()) {
			// quoted element
			++first;
			auto end_quote = sprout::find(first, last, settings.quote());
			while (true) {
				if (end_quote == last) {
					throw std::runtime_error("end quote not found");
				}
				auto next = sprout::next(end_quote);
				if (!same_escape && first != end_quote) {
					auto prev = sprout::prev(end_quote);
					if (*prev == settings.escape()) {
						// escaped quote
						end_quote = sprout::find(next, last, settings.quote());
						continue;
					}
				}
				if (next != last) {
					if (*next == settings.quote()) {
						// escaped quote
						++next;
						end_quote = sprout::find(next, last, settings.quote());
						continue;
					}
					if (!sprout::any_of_equal(delimiters.begin(), delimiters.end(), *next)) {
						throw std::runtime_error("invalid quote");
					}
					if (*next == value_type('\r') && sprout::next(next) != last && *sprout::next(next) == value_type('\n')) {
						++next;
					}
				}
				result.back().push_back(
					ResultString(sprout::addressof(*first), sprout::distance(first, end_quote))
					);
				first = next;
				break;
			}
		} else {
			// no quoted element
			auto next = sprout::find_first_of(first, last, delimiters.begin(), delimiters.end());
			if (next != last) {
				if (*next == value_type('\r') && sprout::next(next) != last && *sprout::next(next) == value_type('\n')) {
					++next;
				}
			}
			result.back().push_back(
				ResultString(sprout::addressof(*first), sprout::distance(first, next))
				);
			first = next;
		}
		if (first != last) {
			if ((*first == value_type('\r') || *first == value_type('\n')) && sprout::next(first) != last) {
				result.offset(0, 1);
				result.back().window(0, 0);
			}
			++first;
		}
	}
	return result;
}

#include <iostream>
#include <sprout/utility/string_view.hpp>

int main() {
	using namespace sprout::udl;
	constexpr auto settings = csv_parser_settings<char>(',', '\"', '\\');
	constexpr auto src = R"(
(no quoted),a,b,c
(quoted),"d","e","f"
(escaped),"""g""","\"h\"","""i"""
(comma),"j,k","l,m","n,o"
(new line),"p
q","r
s","t
u"
)"_sv;
	constexpr auto result = parse_csv<16, 16>(src, settings);
	for (auto const& field : result) {
		for (auto const& elem : field) {
			std::cout
				<< elem << std::endl
				<< "----" << std::endl
				;
		}
		std::cout
			<< "----------------------------------------" << std::endl
			;
	}
}
