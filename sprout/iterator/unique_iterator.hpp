/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_UNIQUE_ITERATOR_HPP
#define SPROUT_ITERATOR_UNIQUE_ITERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/adjacent_filter_iterator.hpp>
#include <sprout/functional/equal_to.hpp>

namespace sprout {
	//
	// unique_filter
	//
	template<typename Predicate = sprout::equal_to<> >
	class unique_filter {
	public:
		typedef bool result_type;
	private:
		Predicate pred_;
	public:
		SPROUT_CONSTEXPR unique_filter()
			: pred_()
		{}
		explicit SPROUT_CONSTEXPR unique_filter(Predicate pred)
			: pred_(pred)
		{}
		template<typename T, typename U>
		SPROUT_CONSTEXPR bool operator()(T const& lhs, U const& rhs) const {
			return !pred_(lhs, rhs);
		}
	};

	//
	// make_unique_iterator
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::adjacent_filter_iterator<sprout::unique_filter<Predicate>, Iterator>
	make_unique_iterator(Predicate pred, Iterator it, Iterator last = Iterator()) {
		return sprout::adjacent_filter_iterator<sprout::unique_filter<Predicate>, Iterator>(
			sprout::unique_filter<Predicate>(pred), it, last
			);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::adjacent_filter_iterator<sprout::unique_filter<>, Iterator>
	make_unique_iterator(Iterator it, Iterator last = Iterator()) {
		return sprout::adjacent_filter_iterator<sprout::unique_filter<>, Iterator>(
			sprout::unique_filter<>(), it, last
			);
	}
}	// namespace sprout

#endif	// SPROUT_ITERATOR_UNIQUE_ITERATOR_HPP
