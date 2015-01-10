/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_APPLY_HPP
#define SPROUT_TUPLE_APPLY_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// apply_result
		//
		namespace detail {
			template<typename F, typename Tuple, typename IndexTuple>
			struct apply_result_impl;
			template<typename F, typename Tuple, sprout::index_t... Indexes>
			struct apply_result_impl<F, Tuple, sprout::index_tuple<Indexes...> > {
			public:
				typedef decltype(
					std::declval<F>()(
						sprout::tuples::get<Indexes>(std::declval<Tuple>())...
						)
				) type;
			};
		}	// namespace detail
		template<typename F, typename Tuple>
		struct apply_result
			: public sprout::tuples::detail::apply_result_impl<
				F, Tuple,
				typename sprout::tuple_indexes<typename std::remove_reference<Tuple>::type>::type
			>
		{};

		//
		// apply
		//
		namespace detail {
			template<typename Result, typename F, typename Tuple, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			apply_impl(F&& f, Tuple&& t, sprout::index_tuple<Indexes...>) {
				return SPROUT_FORWARD(F, f)(sprout::tuples::get<Indexes>(SPROUT_FORWARD(Tuple, t))...);
			}
		}	// namespace detail
		template<typename F, typename Tuple>
		inline SPROUT_CONSTEXPR typename sprout::tuples::apply_result<F, Tuple>::type
		apply(F&& f, Tuple&& t) {
			return sprout::tuples::detail::apply_impl<typename sprout::tuples::apply_result<F, Tuple>::type>(
				SPROUT_FORWARD(F, f), SPROUT_FORWARD(Tuple, t),
				sprout::tuple_indexes<typename std::remove_reference<Tuple>::type>::make()
				);
		}
	}	// namespace tuples

	using sprout::tuples::apply_result;
	using sprout::tuples::apply;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_APPLY_HPP
