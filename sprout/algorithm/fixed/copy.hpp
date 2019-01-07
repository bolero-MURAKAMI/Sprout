/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/math/less.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			copy_impl_ra(
				RandomAccessIterator const& first, RandomAccessIterator const&, Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type offset,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake<Result>(
					result, sprout::size(result),
					(Indexes >= offset && sprout::math::less(Indexes, offset + size) && sprout::math::less(Indexes, offset + input_size)
						? first[Indexes - offset]
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			copy(
				RandomAccessIterator const& first, RandomAccessIterator const& last, Result const& result,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::copy_impl_ra(
					first, last, result,
					sprout::container_indexes<Result>::make(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					sprout::distance(first, last)
					);
			}

			template<typename InputIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy_impl(
				InputIterator const&, InputIterator const&, Result const& result,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy_impl(
				InputIterator const& first, InputIterator const& last, Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? sprout::fixed::detail::copy_impl(sprout::next(first), last, result, size, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			copy(
				InputIterator const& first, InputIterator const& last, Result const& result,
				std::input_iterator_tag*
				)
			{
				return sprout::fixed::detail::copy_impl(first, last, result, sprout::size(result));
			}

			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy(InputIterator const& first, InputIterator const& last, Result const& result) {
				typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
				return sprout::fixed::detail::copy(first, last, result, category());
			}

			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy(InputIterator const& first, InputIterator const& last, Result const& result) {
				return sprout::remake<Result>(
					result, sprout::size(result),
					first, last
					);
			}
		}	// namespace detail
		//
		// copy
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		copy(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fixed::detail::copy(first, last, result);
		}

		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		copy(InputIterator first, InputIterator last) {
			return sprout::fixed::copy(first, last, sprout::pit<Result>());
		}
	}	// namespace fixed

	template<
		typename InputIterator, typename Result,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	copy(InputIterator first, InputIterator last, Result const& result) {
		return sprout::fixed::copy(first, last, result);
	}

	template<typename Result, typename InputIterator>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	copy(InputIterator first, InputIterator last) {
		return sprout::fixed::copy<Result>(first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_HPP
