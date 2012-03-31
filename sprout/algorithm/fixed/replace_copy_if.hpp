#ifndef SPROUT_ALGORITHM_FIXED_REPLACE_COPY_IF_HPP
#define SPROUT_ALGORITHM_FIXED_REPLACE_COPY_IF_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/detail/container_complate.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, typename T, typename Predicate, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy_if_impl_ra(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				Predicate pred,
				T const& new_value,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type offset,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake<Result>(
					result,
					sprout::size(result),
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? pred(*sprout::next(first, Indexes - offset)) ? new_value : *sprout::next(first, Indexes - offset)
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result, typename T, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy_if(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				Predicate pred,
				T const& new_value,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::replace_copy_if_impl_ra(
					first,
					last,
					result,
					pred,
					new_value,
					typename sprout::index_range<0, sprout::container_traits<Result>::static_size>::type(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
					);
			}
			template<typename InputIterator, typename Result, typename T, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type replace_copy_if_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				Predicate pred,
				T const& new_value,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename T, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type replace_copy_if_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				Predicate pred,
				T const& new_value,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? replace_copy_if_impl(sprout::next(first), last, result, pred, new_value, size, args..., pred(*first) ? new_value : *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename T, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy_if(
				InputIterator first,
				InputIterator last,
				Result const& result,
				Predicate pred,
				T const& new_value,
				void*
				)
			{
				return sprout::fixed::detail::replace_copy_if_impl(first, last, result, pred, new_value, sprout::size(result));
			}
		}	// namespace detail
		//
		// replace_copy_if
		//
		template<typename InputIterator, typename Result, typename T, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy_if(
			InputIterator first,
			InputIterator last,
			Result const& result,
			Predicate pred,
			T const& new_value
			)
		{
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::fixed::detail::replace_copy_if(first, last, result, pred, new_value, category());
		}
	}	// namespace fixed

	using sprout::fixed::replace_copy_if;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REPLACE_COPY_IF_HPP
