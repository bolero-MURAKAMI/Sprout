#ifndef SPROUT_OPERATION_FIXED_PUSH_BACK_HPP
#define SPROUT_OPERATION_FIXED_PUSH_BACK_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/operation/fixed/insert.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// push_back
			//
			template<typename Container, typename T, typename... Values>
			struct push_back
				: public sprout::fixed::result_of::insert<Container, T, Values...>
			{};
		}	// namespace result_of

		//
		// push_back
		//
		template<typename Container, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::push_back<Container, T, Values...>::type
		push_back(Container const& cont, T const& v, Values const&... values) {
			return sprout::fixed::detail::insert_impl<typename sprout::fixed::result_of::push_back<Container, T, Values...>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::result_of::push_back<Container, T, Values...>::type>::make(),
				sprout::internal_end_offset(cont),
				v,
				values...
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::push_back;
	}	// namespace result_of

	using sprout::fixed::push_back;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_PUSH_BACK_HPP
