#ifndef SPROUT_ALGORITHM_FIXED_COPY_WHILE_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_WHILE_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy.hpp>
#include <sprout/detail/container_complate.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_while(
				RandomAccessIterator first, RandomAccessIterator last, Result const& result, Predicate pred,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::copy(first, NS_SSCRISK_CEL_OR_SPROUT::find_if_not(first, last, pred), result);
			}
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			copy_while_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			copy_while_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size && pred(*first)
					? sprout::fixed::detail::copy_while_impl(sprout::next(first), last, result, pred, size, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_while(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				void*
				)
			{
				return sprout::fixed::detail::copy_while_impl(first, last, result, pred, sprout::size(result));
			}
		}	// namespace detail
		//
		// copy_while
		//
		template<typename InputIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		copy_while(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::fixed::detail::copy_while(first, last, result, pred, category());
		}
	}	// namespace fixed

	using sprout::fixed::copy_while;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_WHILE_HPP
