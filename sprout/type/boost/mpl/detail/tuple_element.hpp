/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_BOOST_MPL_DETAIL_TUPLE_ELEMENT_HPP
#define SPROUT_TYPE_BOOST_MPL_DETAIL_TUPLE_ELEMENT_HPP

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<std::size_t I, typename T, bool = (I < boost::mpl::size<T>::value)>
			struct mpl_tuple_element;
			template<std::size_t I, typename T>
			struct mpl_tuple_element<I, T, false>
				: public sprout::detail::nil_base
			{};
			template<std::size_t I, typename T>
			struct mpl_tuple_element<I, T, true>
				: public boost::mpl::at_c<T, I>
			{};
		}	// namespace detail
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_BOOST_MPL_DETAIL_TUPLE_ELEMENT_HPP
