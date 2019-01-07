/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_SET_DIFFERENCE_HPP
#define SPROUT_ALGORITHM_FIXED_SET_DIFFERENCE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/set_difference_iterator.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			set_difference_impl(
				InputIterator1, InputIterator1,
				InputIterator2, InputIterator2,
				Result const& result, Compare,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			set_difference_impl(
				InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Result const& result, Compare comp,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sizeof...(Args) < size
					? first1 != last1
						? first2 != last2
							? comp(*first1, *first2)
								? sprout::fixed::detail::set_difference_impl(
									sprout::next(first1), last1, first2, last2, result, comp,
									size, args..., *first1
									)
								: comp(*first2, *first1)
									? sprout::fixed::detail::set_difference_impl(
										first1, last1, sprout::next(first2), last2, result, comp,
										size, args...
										)
									: sprout::fixed::detail::set_difference_impl(
										sprout::next(first1), last1, sprout::next(first2), last2, result, comp,
										size, args...
										)
							: sprout::fixed::detail::set_difference_impl(
								sprout::next(first1), last1, first2, last2, result, comp,
								size, args..., *first1
								)
						: sprout::detail::container_complate(result, args...)
					: sprout::detail::container_complate(result, args...)
					;
			}

			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			set_difference(
				InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Result const& result, Compare comp
				)
			{
				return sprout::fixed::detail::set_difference_impl(
					first1, last1,
					first2, last2,
					result, comp,
					sprout::size(result)
					);
			}

			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			set_difference(
				InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2,
				Result const& result, Compare comp
				)
			{
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_set_difference_iterator(first1, last1, first2, last2, comp),
					sprout::make_set_difference_iterator(last1, last1, last2, last2, comp)
					);
			}
		}	// namespace detail
		//
		// set_difference
		//
		template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		set_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Result const& result, Compare comp
			)
		{
			return sprout::fixed::detail::set_difference(first1, last1, first2, last2, result, comp);
		}
		template<typename InputIterator1, typename InputIterator2, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		set_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Result const& result
			)
		{
			return sprout::fixed::set_difference(first1, last1, first2, last2, result, sprout::less<>());
		}

		template<typename Result, typename InputIterator1, typename InputIterator2, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		set_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp
			)
		{
			return sprout::fixed::set_difference(first1, last1, first2, last2, sprout::pit<Result>(), comp);
		}
		template<typename Result, typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		set_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2
			)
		{
			return sprout::fixed::set_difference(first1, last1, first2, last2, sprout::pit<Result>());
		}
	}	// namespace fixed

	template<
		typename InputIterator1, typename InputIterator2, typename Result, typename Compare,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	set_difference(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Result const& result, Compare comp
		)
	{
		return sprout::fixed::set_difference(first1, last1, first2, last2, result, comp);
	}
	template<
		typename InputIterator1, typename InputIterator2, typename Result,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	set_difference(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Result const& result
		)
	{
		return sprout::fixed::set_difference(first1, last1, first2, last2, result);
	}

	template<typename Result, typename InputIterator1, typename InputIterator2, typename Compare>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	set_difference(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Compare comp
		)
	{
		return sprout::fixed::set_difference<Result>(first1, last1, first2, last2, comp);
	}
	template<typename Result, typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	set_difference(
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2
		)
	{
		return sprout::fixed::set_difference<Result>(first1, last1, first2, last2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SET_DIFFERENCE_HPP
