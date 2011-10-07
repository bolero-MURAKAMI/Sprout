#ifndef SPROUT_ALGORITHM_FIXED_COPY_N_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_N_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy.hpp>

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
				return sprout::fixed::copy(
					first,
					sprout::next(first, n),
					result
					);
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_n_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_n_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return copy_n_impl_3(result, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)));
			}
			template<typename InputIterator, typename Size, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_n_impl_2(
				InputIterator first,
				Size n,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Size, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_n_impl_2(
				InputIterator first,
				Size n,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return n != 0 && sizeof...(Args) < static_cast<std::size_t>(offset)
					? copy_n_impl_2(sprout::next(first), n - 1, result, offset, args..., *first)
					: copy_n_impl_3(result, args...)
					;
			}
			template<typename InputIterator, typename Size, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_n_impl_1(
				InputIterator first,
				Size n,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Size, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_n_impl_1(
				InputIterator first,
				Size n,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < static_cast<std::size_t>(offset)
					? copy_n_impl_1(first, n, result, offset, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)))
					: copy_n_impl_2(first, n, result, offset + sprout::size(result), args...)
					;
			}
			template<typename InputIterator, typename Size, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_n_impl(
				InputIterator first,
				Size n,
				Result const& result
				)
			{
				return copy_n_impl_1(first, n, result, sprout::fixed_begin_offset(result));
			}
			template<typename InputIterator, typename Size, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_n(
				InputIterator first,
				Size n,
				Result const& result,
				void*
				)
			{
				return sprout::fixed::detail::copy_n_impl(
					first,
					n,
					result
					);
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
			return sprout::fixed::detail::copy_n(
				first,
				n,
				result,
				category()
				);
		}
	}	// namespace fixed

	using sprout::fixed::copy_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_N_HPP
