/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIXED_POP_BACK_HPP
#define SPROUT_OPERATION_FIXED_POP_BACK_HPP

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
			// pop_back
			//
			template<typename Container>
			struct pop_back
				: public sprout::fixed::results::erase<Container>
			{};
		}	// namespace results

		//
		// pop_back
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::pop_back<Container>::type
		pop_back(Container const& cont) {
			return sprout::fixed::detail::erase_impl<typename sprout::fixed::results::pop_back<Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::pop_back<Container>::type>::make(),
				sprout::internal_end_offset(cont) - 1
				);
		}
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::pop_back;
	}	// namespace results

	using sprout::fixed::pop_back;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_POP_BACK_HPP
