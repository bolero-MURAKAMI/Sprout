#ifndef SPROUT_TYPE_BOOST_MPL_V_ITER_HPP
#define SPROUT_TYPE_BOOST_MPL_V_ITER_HPP

#include <sprout/config.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/next_prior.hpp>
#include <sprout/type/iterator/next.hpp>
#include <sprout/type/iterator/prev.hpp>

namespace sprout {
	namespace types {
		//
		// next
		//
		template<typename Seq, long N>
		struct next<boost::mpl::v_iter<Seq, N> >
			: public boost::mpl::next<boost::mpl::v_iter<Seq, N> >
		{};
		//
		// prev
		//
		template<typename Seq, long N>
		struct prev<boost::mpl::v_iter<Seq, N> >
			: public boost::mpl::prior<boost::mpl::v_iter<Seq, N> >
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_BOOST_MPL_V_ITER_HPP
