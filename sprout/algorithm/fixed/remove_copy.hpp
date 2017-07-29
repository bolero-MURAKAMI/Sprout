/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/remove_iterator.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, typename T, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			remove_copy_impl(
				InputIterator const&, InputIterator const&,
				Result const& result, T const&,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename T, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			remove_copy_impl(
				InputIterator const& first, InputIterator const& last,
				Result const& result, T const& value,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? *first == value
						? sprout::fixed::detail::remove_copy_impl(sprout::next(first), last, result, value, size, args...)
						: sprout::fixed::detail::remove_copy_impl(sprout::next(first), last, result, value, size, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}

			template<typename InputIterator, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			remove_copy(InputIterator const& first, InputIterator const& last, Result const& result, T const& value) {
				return sprout::fixed::detail::remove_copy_impl(first, last, result, value, sprout::size(result));
			}

			template<typename InputIterator, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			remove_copy(InputIterator const& first, InputIterator const& last, Result const& result, T const& value) {
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_remove_iterator(value, first, last),
					sprout::make_remove_iterator(value, last, last)
					);
			}
		}	// namespace detail
		//
		// remove_copy
		//
		template<typename InputIterator, typename Result, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		remove_copy(InputIterator first, InputIterator last, Result const& result, T const& value) {
			return sprout::fixed::detail::remove_copy(first, last, result, value);
		}

		template<typename Result, typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		remove_copy(InputIterator first, InputIterator last, T const& value) {
			return sprout::fixed::remove_copy(first, last, sprout::pit<Result>(), value);
		}
	}	// namespace fixed

	template<
		typename InputIterator, typename Result, typename T,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	remove_copy(InputIterator first, InputIterator last, Result const& result, T const& value) {
		return sprout::fixed::remove_copy(first, last, result, value);
	}

	template<typename Result, typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	remove_copy(InputIterator first, InputIterator last, T const& value) {
		return sprout::fixed::remove_copy<Result>(first, last, value);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP
