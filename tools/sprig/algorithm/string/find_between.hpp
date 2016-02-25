/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TOOLS_SPRIG_ALGORITHM_STRING_FIND_BETWEEN_HPP
#define TOOLS_SPRIG_ALGORITHM_STRING_FIND_BETWEEN_HPP

#include <boost/range/functions.hpp>
#include <boost/range/metafunctions.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string/find.hpp>

namespace sprig {
	//
	// between_finder
	//
	template<typename Finder1, typename Finder2>
	struct between_finderF {
	private:
		Finder1 finder1_;
		Finder2 finder2_;
	public:
		between_finderF(Finder1 const& finder1, Finder2 const& finder2)
			: finder1_(finder1), finder2_(finder2)
		{}
		template<typename ForwardIterator>
		boost::iterator_range<ForwardIterator>
		operator()(ForwardIterator first, ForwardIterator last) const {
			first = boost::end(finder1_(first, last));
			return boost::iterator_range<ForwardIterator>(first, boost::begin(finder2_(first, last)));
		}
	};
	template<typename Finder1, typename Finder2>
	inline sprig::between_finderF<Finder1, Finder2>
	between_finder(Finder1 const& finder1, Finder2 const& finder2) {
		return sprig::between_finderF<Finder1, Finder2>(finder1, finder2);
	}
	//
	// find_between
	//
	template<typename Range, typename Finder1, typename Finder2>
	inline boost::iterator_range<typename boost::range_iterator<Range>::type>
	find_between(Range& input, Finder1 const& finder1, Finder2 const& finder2) {
		return boost::algorithm::find(input, sprig::between_finder(finder1, finder2));
	}
}	// namespace sprig

#endif	// #ifndef TOOLS_SPRIG_ALGORITHM_STRING_FIND_BETWEEN_HPP
