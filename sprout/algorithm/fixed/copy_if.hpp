/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_COPY_IF_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/filter_iterator.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy_if_impl(InputIterator const&, InputIterator const&, Result const& result, Predicate,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy_if_impl(
				InputIterator const& first, InputIterator const& last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? pred(*first)
						? sprout::fixed::detail::copy_if_impl(sprout::next(first), last, result, pred, size, args..., *first)
						: sprout::fixed::detail::copy_if_impl(sprout::next(first), last, result, pred, size, args...)
					: sprout::detail::container_complate(result, args...)
					;
			}

			template<typename InputIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy_if(InputIterator const& first, InputIterator const& last, Result const& result, Predicate pred) {
				return sprout::fixed::detail::copy_if_impl(first, last, result, pred, sprout::size(result));
			}

			template<typename InputIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			copy_if(InputIterator const& first, InputIterator const& last, Result const& result, Predicate pred) {
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_filter_iterator(pred, first, last),
					sprout::make_filter_iterator(pred, last, last)
					);
			}
		}	// namespace detail
		//
		// copy_if
		//
		template<typename InputIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		copy_if(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			return sprout::fixed::detail::copy_if(first, last, result, pred);
		}

		template<typename Result, typename InputIterator, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		copy_if(InputIterator first, InputIterator last, Predicate pred) {
			return sprout::fixed::copy_if(first, last, sprout::pit<Result>(), pred);
		}
	}	// namespace fixed

	template<
		typename InputIterator, typename Result, typename Predicate,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	copy_if(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
		return sprout::fixed::copy_if(first, last, result, pred);
	}

	template<typename Result, typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	copy_if(InputIterator first, InputIterator last, Predicate pred) {
		return sprout::fixed::copy_if<Result>(first, last, pred);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_IF_HPP
