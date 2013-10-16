/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_FILL_N_HPP
#define SPROUT_ALGORITHM_FIXED_FILL_N_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/fill.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Size, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Container>::value,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type
			fill_n(Container const& cont, Size n, T const& value) {
				return sprout::fixed::detail::fill_impl(
					cont, value,
					sprout::container_indexes<Container>::make(),
					sprout::internal_begin_offset(cont),
					n
					);
			}

			template<typename Container, typename Size, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Container>::value,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type
			fill_n(Container const& cont, Size n, T const& value) {
				return sprout::remake<Container>(
					cont, n,
					sprout::value_iterator<T const&>(value, n),
					sprout::value_iterator<T const&>(value, 0)
					);
			}
		}	// namespace detail
		//
		// fill_n
		//
		template<typename Container, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		fill_n(Container const& cont, Size n, T const& value) {
			return sprout::fixed::detail::fill_n(cont, n, value);
		}

		template<typename Container, typename Size, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		fill_n(Size n, T const& value) {
			return sprout::fixed::fill_n(sprout::pit<Container>(), n, value);
		}
	}	// namespace fixed

	template<
		typename Container, typename Size, typename T,
		typename sprout::enabler_if<!sprout::is_output_iterator<Container>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
	fill_n(Container const& cont, Size n, T const& value) {
		return sprout::fixed::fill_n(cont, n, value);
	}

	template<typename Container, typename Size, typename T>
	inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
	fill_n(Size n, T const& value) {
		return sprout::fixed::fill_n<Container>(n, value);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_FILL_N_HPP
