/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIXED_SET_HPP
#define SPROUT_OPERATION_FIXED_SET_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace fixed {
		namespace results {
			//
			// set
			//
			template<typename Container, typename T>
			struct set {
			public:
				typedef typename sprout::container_construct_traits<Container>::copied_type type;
			};
		}	// namespace results

		namespace detail {
			template<typename Result, typename Container, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			set_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type pos, T const& v
				)
			{
				return sprout::remake<Result>(
					cont,
					sprout::size(cont),
					(Indexes != pos
						? *sprout::next(sprout::internal_begin(cont), Indexes)
						: v
						)...
					);
			}
		}	// namespace detail
		//
		// set
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::set<Container, T>::type
		set(Container const& cont, typename sprout::container_traits<Container>::const_iterator pos, T const& v) {
			return sprout::fixed::detail::set_impl<typename sprout::fixed::results::set<Container, T>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::set<Container, T>::type>::make(),
				sprout::distance(sprout::internal_begin(cont), pos),
				v
				);
		}
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::set<Container, T>::type
		set(Container const& cont, typename sprout::container_traits<Container>::difference_type pos, T const& v) {
			return sprout::fixed::detail::set_impl<typename sprout::fixed::results::set<Container, T>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::set<Container, T>::type>::make(),
				sprout::distance(sprout::internal_begin(cont), sprout::next(sprout::begin(cont), pos)),
				v
				);
		}
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::set;
	}	// namespace results

	using sprout::fixed::set;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_SET_HPP
