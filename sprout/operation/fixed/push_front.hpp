/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIXED_PUSH_FRONT_HPP
#define SPROUT_OPERATION_FIXED_PUSH_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/operation/fixed/insert.hpp>

namespace sprout {
	namespace fixed {
		namespace results {
			//
			// push_front
			//
			template<typename Container, typename T, typename... Values>
			struct push_front
				: public sprout::fixed::results::insert<Container, T, Values...>
			{};
		}	// namespace results

		//
		// push_front
		//
		template<typename Container, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::push_front<Container, T, Values...>::type
		push_front(Container const& cont, T const& v, Values const&... values) {
			return sprout::fixed::detail::insert_impl<typename sprout::fixed::results::push_front<Container, T, Values...>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::push_front<Container, T, Values...>::type>::make(),
				sprout::internal_begin_offset(cont),
				v,
				values...
				);
		}
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::push_front;
	}	// namespace results

	using sprout::fixed::push_front;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_PUSH_FRONT_HPP
