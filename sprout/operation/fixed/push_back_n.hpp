#ifndef SPROUT_OPERATION_FIXED_PUSH_BACK_N_HPP
#define SPROUT_OPERATION_FIXED_PUSH_BACK_N_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/insert_n.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// push_back_n
			//
			template<std::size_t N, typename Container, typename T, typename... Values>
			struct push_back_n
				: public insert_n<N, Container, T, Values...>
			{};
		}	// namespace result_of

		//
		// push_back_n
		//
		template<std::size_t N, typename Container, typename T, typename... Values>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::push_back_n<N, Container, T, Values...>::type push_back_n(
			Container const& cont,
			T const& v,
			Values const&... values
			)
		{
			return sprout::fixed::detail::insert_n_impl<N, typename sprout::fixed::result_of::push_back_n<N, Container, T, Values...>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::push_back_n<N, Container, T, Values...>::type>::fixed_size>::type(),
				sprout::fixed_end_offset(cont),
				v,
				values...
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_PUSH_BACK_N_HPP
