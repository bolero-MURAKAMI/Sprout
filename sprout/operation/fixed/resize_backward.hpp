/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIXED_RESIZE_BACKWARD_HPP
#define SPROUT_OPERATION_FIXED_RESIZE_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/operation/fixed/resize.hpp>

namespace sprout {
	namespace fixed {
		namespace results {
			//
			// resize_backward
			//
			template<std::size_t N, typename Container>
			struct resize_backward
				: public sprout::fixed::results::resize<N, Container>
			{};
		}	// namespace results

		namespace detail {
			template<typename Result, typename Container, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			resize_backward_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type size,
				typename sprout::container_traits<Result>::difference_type offset,
				T const& v
				)
			{
				return sprout::make<Result>(
					(Indexes >= offset && Indexes < offset + size
						? *sprout::next(sprout::begin(cont), Indexes - offset)
						: v
						)...
					);
			}
		}	// namespace detail
		//
		// resize_backward
		//
		template<std::size_t N, typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::resize_backward<N, Container>::type
		resize_backward(Container const& cont, T const& v) {
			return sprout::fixed::detail::resize_backward_impl<typename sprout::fixed::results::resize_backward<N, Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::resize_backward<N, Container>::type>::make(),
				sprout::size(cont),
				static_cast<typename sprout::container_traits<Container>::difference_type>(
					sprout::container_traits<typename sprout::fixed::results::resize_backward<N, Container>::type>::static_size
					)
					- sprout::size(cont),
				v
				);
		}

		namespace detail {
			template<typename Result, typename Container, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			resize_backward_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type size,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::make<Result>(
					(Indexes >= offset && Indexes < offset + size
						? *sprout::next(sprout::begin(cont), Indexes - offset)
						: typename sprout::container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// resize_backward
		//
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::resize_backward<N, Container>::type
		resize_backward(Container const& cont) {
			return sprout::fixed::detail::resize_backward_impl<typename sprout::fixed::results::resize_backward<N, Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::results::resize_backward<N, Container>::type>::make(),
				sprout::size(cont),
				static_cast<typename sprout::container_traits<Container>::difference_type>(
					sprout::container_traits<typename sprout::fixed::results::resize_backward<N, Container>::type>::static_size
					)
					- sprout::size(cont)
				);
		}
	}	// namespace fixed

	namespace results {
		using sprout::fixed::results::resize_backward;
	}	// namespace results

	using sprout::fixed::resize_backward;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_RESIZE_BACKWARD_HPP
