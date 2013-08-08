/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_NOT2_HPP
#define SPROUT_FUNCTIONAL_NOT2_HPP

#include <functional>
#include <sprout/config.hpp>

namespace sprout {
	// 20.8.8 negators
	template<typename Predicate>
	class binary_negate {
	public:
		typedef typename Predicate::first_argument_type first_argument_type;
		typedef typename Predicate::second_argument_type second_argument_type;
		typedef bool result_type;
	protected:
		Predicate fn;
	public:
		explicit SPROUT_CONSTEXPR binary_negate(Predicate const& pred)
			: fn(pred)
		{}
		SPROUT_CONSTEXPR bool operator()(typename Predicate::first_argument_type const& x, typename Predicate::second_argument_type const& y) const {
			return !fn(x, y);
		}
	};

	template<typename Predicate>
	inline SPROUT_CONSTEXPR sprout::binary_negate<Predicate>
	not2(Predicate const& pred) {
		return sprout::binary_negate<Predicate>(pred);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_NOT2_HPP
