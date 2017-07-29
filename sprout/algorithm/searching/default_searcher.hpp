/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_SEARCHING_DEFAULT_SEARCHER_HPP
#define SPROUT_ALGORITHM_SEARCHING_DEFAULT_SEARCHER_HPP

#include <sprout/config.hpp>
#include <sprout/functional/equal_to.hpp>
#include <sprout/algorithm/search.hpp>

namespace sprout {
	//
	// default_searcher
	//
	template<typename ForwardIterator2, typename BinaryPredicate = sprout::equal_to<> >
	class default_searcher {
	private:
		ForwardIterator2 first2_;
		ForwardIterator2 last2_;
		BinaryPredicate pred_;
	public:
		SPROUT_CONSTEXPR default_searcher(ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
			: first2_(first2), last2_(last2), pred_(pred)
		{}
		SPROUT_CONSTEXPR default_searcher(ForwardIterator2 first2, ForwardIterator2 last2)
			: first2_(first2), last2_(last2), pred_()
		{}
		template<typename ForwardIterator1>
		SPROUT_CONSTEXPR ForwardIterator1
		operator()(ForwardIterator1 first1, ForwardIterator1 last1) const {
			return sprout::search(first1, last1, first2_, last2_, pred_);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_SEARCHING_DEFAULT_SEARCHER_HPP
