/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIXED_POP_FRONT_HPP
#define SPROUT_OPERATION_FIXED_POP_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/operation/fixed/erase.hpp>

namespace sprout {
	namespace fixed {
		namespace results {
			//
			// pop_front
			//
			template<typename Container>
			struct pop_front
				: public sprout::fixed::results::erase<Container>
			{};
		}	// namespace results

		//
		// pop_front
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::pop_front<Container>::type
		pop_front(Container const& cont) {
			return sprout::fixed::detail::erase_impl<typename sprout::fixed::results::pop_front<Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::pop_front<Container>::type>::make(),
				sprout::internal_begin_offset(cont)
				);
		}
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::pop_front;
	}	// namespace results

	using sprout::fixed::pop_front;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_POP_FRONT_HPP
