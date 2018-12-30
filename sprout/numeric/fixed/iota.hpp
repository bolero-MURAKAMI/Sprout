/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FIXED_IOTA_HPP
#define SPROUT_NUMERIC_FIXED_IOTA_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/counting_iterator.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
			iota_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				T value,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::remake<Container>(
					cont,
					sprout::size(cont),
					(Indexes >= offset && Indexes < offset + size
						? static_cast<typename sprout::container_traits<Container>::value_type>(value + (Indexes - offset))
						: *sprout::next(sprout::internal_begin(cont), Indexes)
						)...
					);
			}

			template<typename Container, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Container>::value,
				typename sprout::fixed::results::algorithm<Container>::type
			>::type
			iota(Container const& cont, T value) {
				return sprout::fixed::detail::iota_impl(
					cont, sprout::container_indexes<Container>::make(),
					value,
					sprout::internal_begin_offset(cont),
					sprout::size(cont)
					);
			}

			template<typename Container, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Container>::value,
				typename sprout::fixed::results::algorithm<Container>::type
			>::type
			iota(Container const& cont, T value) {
				return sprout::remake<Container>(
					cont, sprout::size(cont),
					sprout::make_counting_iterator(value),
					sprout::next(sprout::make_counting_iterator(value), sprout::size(cont))
					);
			}
		}	// namespace detail
		//
		// iota
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		iota(Container const& cont, T value) {
			return sprout::fixed::detail::iota(cont, value);
		}

		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		iota(T value) {
			return sprout::fixed::detail::iota(sprout::pit<Container>(), value);
		}
	}	// namespace fixed

	using sprout::fixed::iota;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIXED_IOTA_HPP
