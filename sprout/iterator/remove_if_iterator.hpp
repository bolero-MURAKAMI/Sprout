/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_REMOVE_IF_ITERATOR_HPP
#define SPROUT_ITERATOR_REMOVE_IF_ITERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/filter_iterator.hpp>

namespace sprout {
	//
	// remove_if_filter
	//
	template<typename Predicate>
	class remove_if_filter {
	public:
		typedef bool result_type;
	private:
		Predicate pred_;
	public:
		explicit SPROUT_CONSTEXPR remove_if_filter(Predicate pred)
			: pred_(pred)
		{}
		template<typename U>
		SPROUT_CONSTEXPR bool operator()(U const& value) const {
			return !pred_(value);
		}
	};

	//
	// make_remove_if_iterator
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::filter_iterator<sprout::remove_if_filter<Predicate>, Iterator>
	make_remove_if_iterator(Predicate pred, Iterator it, Iterator last = Iterator()) {
		return sprout::filter_iterator<sprout::remove_if_filter<Predicate>, Iterator>(
			sprout::remove_if_filter<Predicate>(pred), it, last
			);
	}
}	// namespace sprout

#endif	// SPROUT_ITERATOR_REMOVE_IF_ITERATOR_HPP
