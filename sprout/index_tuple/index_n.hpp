#ifndef SPROUT_INDEX_TUPLE_INDEX_N_HPP
#define SPROUT_INDEX_TUPLE_INDEX_N_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_n.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>

namespace sprout {
	//
	// index_n
	//
	template<sprout::index_t I, std::size_t N>
	struct index_n
		: public sprout::detail::make_indexes_helper<
			typename sprout::integer_n<sprout::index_t, I, N>::type
				::template transfer<sprout::index_tuple<> >::type
		>
	{};
	//
	// uindex_n
	//
	template<sprout::uindex_t I, std::size_t N>
	struct uindex_n
		: public sprout::detail::make_indexes_helper<
			typename sprout::integer_n<sprout::uindex_t, I, N>::type
				::template transfer<sprout::uindex_tuple<> >::type
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_N_HPP
