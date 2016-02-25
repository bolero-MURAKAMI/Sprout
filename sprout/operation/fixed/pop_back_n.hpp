/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIXED_POP_BACK_N_HPP
#define SPROUT_OPERATION_FIXED_POP_BACK_N_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/operation/fixed/erase_n.hpp>

namespace sprout {
	namespace fixed {
		namespace results {
			//
			// pop_back_n
			//
			template<std::size_t N, typename Container>
			struct pop_back_n
				: public sprout::fixed::results::erase_n<N, Container>
			{};
		}	// namespace results

		//
		// pop_back_n
		//
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::pop_back_n<N, Container>::type
		pop_back_n(Container const& cont) {
			return sprout::fixed::detail::erase_n_impl<N, typename sprout::fixed::results::pop_back_n<N, Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::pop_back_n<N, Container>::type>::make(),
				sprout::internal_end_offset(cont) - N
				);
		}
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::pop_back_n;
	}	// namespace results

	using sprout::fixed::pop_back_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_POP_BACK_N_HPP
