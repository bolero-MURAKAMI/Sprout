/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_BOOST_MPL_VECTOR_HPP
#define SPROUT_TYPE_BOOST_MPL_VECTOR_HPP

#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/boost/mpl/v_iter.hpp>
#include <sprout/type/boost/mpl/detail/tuple_element.hpp>

namespace sprout {
	namespace types {
		//
		// begin
		//
		template<typename... Types>
		struct begin<boost::mpl::vector<Types...> >
			: public boost::mpl::begin<boost::mpl::vector<Types...> >
		{};
		//
		// end
		//
		template<typename... Types>
		struct end<boost::mpl::vector<Types...> >
			: public boost::mpl::end<boost::mpl::vector<Types...> >
		{};

		//
		// tuple_size
		//
		template<typename... Types>
		struct tuple_size<boost::mpl::vector<Types...> >
			: public boost::mpl::size<boost::mpl::vector<Types...> >
		{};
		//
		// tuple_element
		//
		template<std::size_t I, typename... Types>
		struct tuple_element<I, boost::mpl::vector<Types...> >
			: public sprout::types::detail::mpl_tuple_element<I, boost::mpl::vector<Types...> >
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_BOOST_MPL_VECTOR_HPP
