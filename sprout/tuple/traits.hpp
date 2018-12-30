/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TRAITS_HPP
#define SPROUT_TUPLE_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/remove_cvref.hpp>
#include <sprout/container/detail/array_like.hpp>

namespace sprout {
	namespace tuples {
		//
		// rebind_types
		//
		template<typename Tuple>
		struct rebind_types
			: public sprout::types::rebind_types<Tuple>
		{};

		//
		// tuple_construct_traits
		//
		template<typename Tuple>
		struct tuple_construct_traits;

		namespace detail {
			template<typename Tuple, typename IndexTuple>
			struct default_copied;
			template<typename Tuple, sprout::index_t... Indexes>
			struct default_copied<Tuple, sprout::index_tuple<Indexes...> >
				: public sprout::types::apply<
					sprout::tuples::rebind_types<Tuple>,
					typename sprout::remove_cvref<
						typename sprout::tuples::tuple_element<Indexes, Tuple>::type
					>::type...
				>
			{};

			template<typename Tuple, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::detail::is_array_like<Tuple>::value,
				typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type
			>::type
			default_make_tuple(Args&&... args) {
				typedef typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type copied_type;
				return copied_type{{SPROUT_FORWARD(Args, args)...}};
			}
			template<typename Tuple, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::detail::is_array_like<Tuple>::value,
				typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type
			>::type
			default_make_tuple(Args&&... args) {
				typedef typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type copied_type;
				return copied_type(SPROUT_FORWARD(Args, args)...);
			}
		}	// namespace detail

		template<typename Tuple>
		struct tuple_construct_traits {
		public:
			typedef typename sprout::tuples::detail::default_copied<
				Tuple,
				typename sprout::tuple_indexes<Tuple>::type
			>::type copied_type;
		public:
			template<typename Tup>
			static SPROUT_CONSTEXPR copied_type deep_copy(Tup&& tup) {
				return SPROUT_FORWARD(Tup, tup);
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
				return sprout::tuples::detail::default_make_tuple<Tuple>(SPROUT_FORWARD(Args, args)...);
			}
			template<typename Tup, typename... Args>
			static SPROUT_CONSTEXPR copied_type remake(
				Tup&&,
				Args&&... args
				)
			{
				return make(SPROUT_FORWARD(Args, args)...);
			}
		};
		template<typename Tuple>
		struct tuple_construct_traits<Tuple const>
			: public sprout::tuples::tuple_construct_traits<Tuple>
		{};
	}	// namespace tuples

	using sprout::tuples::tuple_construct_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TRAITS_HPP
