#ifndef SPROUT_TYPE_BOOST_MPL_STRING_HPP
#define SPROUT_TYPE_BOOST_MPL_STRING_HPP

#include <sprout/config.hpp>
#include <boost/mpl/string.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/next_prior.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/iterator/next.hpp>
#include <sprout/type/iterator/prev.hpp>

namespace sprout {
	namespace types {
		//
		// begin
		//
		template<int... Values>
		struct begin<boost::mpl::string<Values...> >
			: public boost::mpl::begin<boost::mpl::string<Values...> >
		{};
		//
		// end
		//
		template<int... Values>
		struct end<boost::mpl::string<Values...> >
			: public boost::mpl::end<boost::mpl::string<Values...> >
		{};

		//
		// tuple_size
		//
		template<int... Values>
		struct tuple_size<boost::mpl::string<Values...> >
			: public boost::mpl::size<boost::mpl::string<Values...> >
		{};
		//
		// tuple_element
		//
		template<std::size_t I, int... Values>
		struct tuple_element<I, boost::mpl::string<Values...> >
			: public boost::mpl::at_c<boost::mpl::string<Values...>, I>
		{};

		//
		// next
		//
		template<typename Sequence, int I, int J>
		struct next<boost::mpl::string_iterator<Sequence, I, J> >
			: public boost::mpl::next<boost::mpl::string_iterator<Sequence, I, J> >
		{};
		//
		// prev
		//
		template<typename Sequence, int I, int J>
		struct prev<boost::mpl::string_iterator<Sequence, I, J> >
			: public boost::mpl::prior<boost::mpl::string_iterator<Sequence, I, J> >
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_BOOST_MPL_STRING_HPP
