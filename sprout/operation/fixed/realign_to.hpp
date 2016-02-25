/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIXED_REALIGN_TO_HPP
#define SPROUT_OPERATION_FIXED_REALIGN_TO_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/operation/fixed/realign.hpp>

namespace sprout {
	namespace fixed {
		namespace results {
			//
			// realign_to
			//
			template<typename Result, typename Container>
			struct realign_to {
			public:
				typedef typename sprout::container_construct_traits<Result>::copied_type type;
			};
		}	// namespace results

		//
		// realign_to
		//
		template<typename Result, typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::realign_to<Result, Container>::type
		realign_to(Container const& cont, T const& v) {
			return sprout::fixed::detail::realign_impl<typename sprout::fixed::results::realign_to<Result, Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::realign_to<Result, Container>::type>::make(),
				sprout::size(cont),
				v
				);
		}

		//
		// realign_to
		//
		template<typename Result, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::realign_to<Result, Container>::type
		realign_to(Container const& cont) {
			return sprout::fixed::detail::realign_impl<typename sprout::fixed::results::realign_to<Result, Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::realign_to<Result, Container>::type>::make(),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::realign_to;
	}	// namespace results

	using sprout::fixed::realign_to;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_REALIGN_TO_HPP
