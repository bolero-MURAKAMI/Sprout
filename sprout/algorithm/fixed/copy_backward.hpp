#ifndef SPROUT_ALGORITHM_FIXED_COPY_BACKWARD_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_BACKWARD_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_backward_impl_ra(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake_clone<Result, Result>(
					result,
					sprout::size(result),
					(Indexes < offset && Indexes + size >= static_cast<std::size_t>(offset) && Indexes + input_size >= static_cast<std::size_t>(offset)
						? *sprout::next(last, Indexes - offset)
						: *sprout::next(sprout::fixed_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_backward(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::copy_backward_impl_ra(
					first,
					last,
					result,
					typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
					sprout::fixed_end_offset(result),
					sprout::size(result),
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
					);
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_backward_impl_3(
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
			>::type copy_backward_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return copy_backward_impl_3(result, *sprout::prev(sprout::fixed_end(result), sizeof...(Args) + 1), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_backward_impl_2(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_backward_impl_2(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < static_cast<std::size_t>(offset)
					? copy_backward_impl_2(first, sprout::prev(last), result, offset, *sprout::prev(last), args...)
					: copy_backward_impl_3(result, args...)
					;
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_backward_impl_1(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_backward_impl_1(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < static_cast<std::size_t>(offset)
					? copy_backward_impl_1(first, last, result, offset, *sprout::prev(sprout::fixed_end(result), sizeof...(Args) + 1), args...)
					: copy_backward_impl_2(first, last, result, offset + sprout::size(result), args...)
					;
			}
			template<typename BidirectionalIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_backward_impl(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result
				)
			{
				return copy_backward_impl_1(first, last, result, sprout::fixed_end_offset(result));
			}
			template<typename BidirectionalIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_backward(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				void*
				)
			{
				return sprout::fixed::detail::copy_backward_impl(
					first,
					last,
					result
					);
			}
		}	// namespace detail
		//
		// copy_backward
		//
		template<typename BidirectionalIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_backward(
			BidirectionalIterator first,
			BidirectionalIterator last,
			Result const& result
			)
		{
			typedef typename std::iterator_traits<BidirectionalIterator>::iterator_category* category;
			return sprout::fixed::detail::copy_backward(
				first,
				last,
				result,
				category()
				);
		}
	}	// namespace fixed

	using sprout::fixed::copy_backward;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_BACKWARD_HPP
