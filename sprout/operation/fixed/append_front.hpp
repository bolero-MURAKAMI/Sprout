#ifndef SPROUT_OPERATION_FIXED_APPEND_FRONT_HPP
#define SPROUT_OPERATION_FIXED_APPEND_FRONT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/operation/fixed/append.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// append_front
			//
			template<typename Container, typename Input>
			struct append_front
				: public sprout::fixed::result_of::append<Container, Input>
			{};
		}	// namespace result_of

		//
		// append_front
		//
		template<typename Container, typename Input>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::append_front<Container, Input>::type
		append_front(Container const& cont, Input const& input) {
			return sprout::fixed::detail::append_impl<typename sprout::fixed::result_of::append_front<Container, Input>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::result_of::append_front<Container, Input>::type>::make(),
				sprout::internal_begin_offset(cont),
				sprout::size(input),
				input
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::append_front;
	}	// namespace result_of

	using sprout::fixed::append_front;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_APPEND_FRONT_HPP
