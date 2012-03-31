#ifndef SPROUT_ALGORITHM_FIXED_COPY_N_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_N_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Size, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_n(
				RandomAccessIterator first,
				Size n,
				Result const& result,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::copy(first, sprout::next(first, n), result);
			}
			template<typename InputIterator, typename Size, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_n_impl(
				InputIterator first,
				Size n,
				Result const& result,
				typename sprout::container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Size, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_n_impl(
				InputIterator first,
				Size n,
				Result const& result,
				typename sprout::container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return n != 0 && sizeof...(Args) < static_cast<std::size_t>(offset)
					? sprout::fixed::detail::copy_n_impl(sprout::next(first), n - 1, result, offset, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Size, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_n(
				InputIterator first,
				Size n,
				Result const& result,
				void*
				)
			{
				return sprout::fixed::detail::copy_n_impl(first, n, result, sprout::size(result));
			}
		}	// namespace detail
		//
		// copy_n
		//
		template<typename InputIterator, typename Size, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_n(
			InputIterator first,
			Size n,
			Result const& result
			)
		{
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::fixed::detail::copy_n(first, n, result, category());
		}
	}	// namespace fixed

	using sprout::fixed::copy_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_N_HPP
