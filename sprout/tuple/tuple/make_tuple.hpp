/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_MAKE_TUPLE_HPP
#define SPROUT_TUPLE_TUPLE_MAKE_TUPLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/functional/ref.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/type/operation/tuple_cat.hpp>

namespace sprout {
	namespace tuples {
		//
		// make_tuple
		//
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<typename sprout::strip_reference<typename std::decay<Types>::type>::type...>
		make_tuple(Types&&... args) {
			return sprout::tuples::tuple<typename std::decay<Types>::type...>(SPROUT_FORWARD(Types, args)...);
		}

		//
		// forward_as_tuple
		//
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types&&...>
		forward_as_tuple(Types&&... args) SPROUT_NOEXCEPT {
			return sprout::tuples::tuple<Types&&...>(SPROUT_FORWARD(Types, args)...);
		}

		//
		// tie
		//
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types&...>
		tie(Types&... args) SPROUT_NOEXCEPT {
			return sprout::tuples::tuple<Types&...>(args...);
		}

		//
		// tuple_cat
		//
		namespace detail {
			template<typename PackIndexTuple, std::size_t... TupleSizes>
			struct tuple_cat_indexes_impl;
			template<sprout::index_t... PackIndexes, std::size_t... TupleSizes>
			struct tuple_cat_indexes_impl<sprout::index_tuple<PackIndexes...>, TupleSizes...> {
			public:
				typedef typename sprout::types::tuple_cat<typename sprout::index_n<PackIndexes, TupleSizes>::type...>::type for_pack;
				typedef typename sprout::types::tuple_cat<typename sprout::make_index_tuple<TupleSizes>::type...>::type for_element;
			};
			template<typename... Tuples>
			struct tuple_cat_indexes
				: public sprout::tuples::detail::tuple_cat_indexes_impl<
					typename sprout::make_index_tuple<sizeof...(Tuples)>::type,
					sprout::tuples::tuple_size<typename std::decay<Tuples>::type>::value...
				>
			{};

			template<typename Result, sprout::index_t... PackIndexes, sprout::index_t... ElemIndexes, typename... Tuples>
			static SPROUT_CONSTEXPR Result
			tuple_cat_impl(sprout::index_tuple<PackIndexes...>, sprout::index_tuple<ElemIndexes...>, Tuples&&... tuples) {
				return Result(sprout::tuples::get<ElemIndexes>(sprout::pack_get<PackIndexes>(SPROUT_FORWARD(Tuples, tuples)...))...);
			};
		}	// namespace detail
		template<typename... Tuples>
		inline SPROUT_CONSTEXPR typename sprout::types::tuple_cat<typename std::decay<Tuples>::type...>::type
		tuple_cat(Tuples&&... tuples) {
			typedef typename sprout::types::tuple_cat<typename std::decay<Tuples>::type...>::type type;
			typedef sprout::tuples::detail::tuple_cat_indexes<Tuples...> indexes;
			return sprout::tuples::detail::tuple_cat_impl<type>(indexes::for_pack::make(), indexes::for_element::make(), SPROUT_FORWARD(Tuples, tuples)...);
		}
	}	// namespace tuples

	using sprout::tuples::make_tuple;
	using sprout::tuples::forward_as_tuple;
	using sprout::tuples::tie;
	using sprout::tuples::tuple_cat;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_MAKE_TUPLE_HPP
