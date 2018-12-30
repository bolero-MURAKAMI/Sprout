/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TOOLS_SPRIG_ALGORITHM_STRING_FIND_SKIP_HPP
#define TOOLS_SPRIG_ALGORITHM_STRING_FIND_SKIP_HPP

#include <boost/range/functions.hpp>
#include <boost/range/metafunctions.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string/find.hpp>

namespace sprig {
	//
	// skip_finder
	//
	template<typename Finder>
	struct skip_finderF {
	private:
		Finder finder_;
	public:
		explicit skip_finderF(Finder const& finder)
			: finder_(finder)
		{}
		template<typename ForwardIterator>
		boost::iterator_range<ForwardIterator>
		operator()(ForwardIterator first, ForwardIterator last) const {
			return boost::iterator_range<ForwardIterator>(boost::end(finder_(first, last)), last);
		}
	};
	template<typename Finder>
	inline sprig::skip_finderF<Finder>
	skip_finder(Finder const& finder) {
		return sprig::skip_finderF<Finder>(finder);
	}
	//
	// find_skip
	//
	template<typename Range, typename Finder>
	inline boost::iterator_range<typename boost::range_iterator<Range>::type>
	find_skip(Range& input, Finder const& finder) {
		return boost::algorithm::find(input, sprig::skip_finder(finder));
	}

	//
	// skip_backward_finder
	//
	template<typename Finder>
	struct skip_backward_finderF {
	private:
		Finder finder_;
	public:
		explicit skip_backward_finderF(Finder const& finder)
			: finder_(finder)
		{}
		template<typename ForwardIterator>
		boost::iterator_range<ForwardIterator>
		operator()(ForwardIterator first, ForwardIterator last) const {
			return boost::iterator_range<ForwardIterator>(first, boost::begin(finder_(first, last)));
		}
	};
	template<typename Finder>
	inline sprig::skip_backward_finderF<Finder>
	skip_backward_finder(Finder const& finder) {
		return sprig::skip_backward_finderF<Finder>(finder);
	}
	//
	// find_skip_backward
	//
	template<typename Range, typename Finder>
	inline boost::iterator_range<typename boost::range_iterator<Range>::type>
	find_skip_backward(Range& input, Finder const& finder) {
		return boost::algorithm::find(input, sprig::skip_backward_finder(finder));
	}
}	// namespace sprig

#endif	// #ifndef TOOLS_SPRIG_ALGORITHM_STRING_FIND_SKIP_HPP
