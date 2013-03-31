#ifndef SPROUT_OPERATION_FIXED_PUSH_FRONT_N_HPP
#define SPROUT_OPERATION_FIXED_PUSH_FRONT_N_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/operation/fixed/insert_n.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// push_front_n
			//
			template<std::size_t N, typename Container, typename T, typename... Values>
			struct push_front_n
				: public sprout::fixed::result_of::insert_n<N, Container, T, Values...>
			{};
		}	// namespace result_of

		//
		// push_front_n
		//
		template<std::size_t N, typename Container, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::push_front_n<N, Container, T, Values...>::type
		push_front_n(Container const& cont, T const& v, Values const&... values) {
			return sprout::fixed::detail::insert_n_impl<N, typename sprout::fixed::result_of::push_front_n<N, Container, T, Values...>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::result_of::push_front_n<N, Container, T, Values...>::type>::make(),
				sprout::internal_begin_offset(cont),
				v,
				values...
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::push_front_n;
	}	// namespace result_of

	using sprout::fixed::push_front_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_PUSH_FRONT_N_HPP
