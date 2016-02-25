/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_REPLACE_COPY_IF_HPP
#define SPROUT_ALGORITHM_FIXED_REPLACE_COPY_IF_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/replace_if_iterator.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, typename Predicate, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			replace_copy_if_impl_ra(
				RandomAccessIterator first, RandomAccessIterator,
				Result const& result, Predicate pred, T const& new_value,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type offset,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake<Result>(
					result, sprout::size(result),
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? pred(first[Indexes - offset]) ? new_value : first[Indexes - offset]
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result, typename Predicate, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			replace_copy_if(
				RandomAccessIterator first, RandomAccessIterator last,
				Result const& result, Predicate pred, T const& new_value,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::replace_copy_if_impl_ra(
					first, last,
					result, pred, new_value,
					sprout::container_indexes<Result>::make(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					sprout::distance(first, last)
					);
			}
			template<typename InputIterator, typename Result, typename Predicate, typename T, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			replace_copy_if_impl(
				InputIterator, InputIterator,
				Result const& result, Predicate, T const&,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename Predicate, typename T, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			replace_copy_if_impl(
				InputIterator first, InputIterator last,
				Result const& result, Predicate pred, T const& new_value,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? replace_copy_if_impl(
						sprout::next(first), last, result, pred, new_value,
						size,
						args..., pred(*first) ? new_value : *first
						)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename Predicate, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			replace_copy_if(
				InputIterator first, InputIterator last,
				Result const& result, Predicate pred, T const& new_value,
				std::input_iterator_tag*
				)
			{
				return sprout::fixed::detail::replace_copy_if_impl(first, last, result, pred, new_value, sprout::size(result));
			}

			template<typename InputIterator, typename Result, typename Predicate, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			replace_copy_if(InputIterator first, InputIterator last, Result const& result, Predicate pred, T const& new_value) {
				typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
				return sprout::fixed::detail::replace_copy_if(first, last, result, pred, new_value, category());
			}

			template<typename InputIterator, typename Result, typename Predicate, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			replace_copy_if(InputIterator first, InputIterator last, Result const& result, Predicate pred, T const& new_value) {
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_replace_if_iterator(first, pred, new_value),
					sprout::make_replace_if_iterator(last, pred, new_value)
					);
			}
		}	// namespace detail
		//
		// replace_copy_if
		//
		template<typename InputIterator, typename Result, typename Predicate, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		replace_copy_if(InputIterator first, InputIterator last, Result const& result, Predicate pred, T const& new_value) {
			return sprout::fixed::detail::replace_copy_if(first, last, result, pred, new_value);
		}

		template<typename Result, typename InputIterator, typename Predicate, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		replace_copy_if(InputIterator first, InputIterator last, Predicate pred, T const& new_value) {
			return sprout::fixed::replace_copy_if(first, last, sprout::pit<Result>(), pred, new_value);
		}
	}	// namespace fixed

	template<
		typename InputIterator, typename Result, typename Predicate, typename T,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	replace_copy_if(InputIterator first, InputIterator last, Result const& result, Predicate pred, T const& new_value) {
		return sprout::fixed::replace_copy_if(first, last, result, pred, new_value);
	}

	template<typename Result, typename InputIterator, typename Predicate, typename T>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	replace_copy_if(InputIterator first, InputIterator last, Predicate pred, T const& new_value) {
		return sprout::fixed::replace_copy_if<Result>(first, last, pred, new_value);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REPLACE_COPY_IF_HPP
