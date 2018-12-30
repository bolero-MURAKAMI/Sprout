/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIXED_RESIZE_HPP
#define SPROUT_OPERATION_FIXED_RESIZE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace fixed {
		namespace results {
			//
			// resize
			//
			template<std::size_t N, typename Container>
			struct resize
				: public sprout::container_transform_traits<
					Container
				>::template rebind_size<
					N
				>
			{};
		}	// namespace results

		namespace detail {
			template<typename Result, typename Container, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			resize_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type size, T const& v
				)
			{
				return sprout::make<Result>(
					(Indexes < size
						? *sprout::next(sprout::begin(cont), Indexes)
						: v
						)...
					);
			}
		}	// namespace detail
		//
		// resize
		//
		template<std::size_t N, typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::resize<N, Container>::type
		resize(Container const& cont, T const& v) {
			return sprout::fixed::detail::resize_impl<typename sprout::fixed::results::resize<N, Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::resize<N, Container>::type>::make(),
				sprout::size(cont),
				v
				);
		}

		namespace detail {
			template<typename Result, typename Container, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			resize_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type size
				)
			{
				return sprout::make<Result>(
					(Indexes < size
						? *sprout::next(sprout::begin(cont), Indexes)
						: typename sprout::container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// resize
		//
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::resize<N, Container>::type
		resize(Container const& cont) {
			return sprout::fixed::detail::resize_impl<typename sprout::fixed::results::resize<N, Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::resize<N, Container>::type>::make(),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::resize;
	}	// namespace results

	using sprout::fixed::resize;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_RESIZE_HPP
