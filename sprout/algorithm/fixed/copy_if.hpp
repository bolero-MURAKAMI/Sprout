#ifndef SPROUT_ALGORITHM_FIXED_COPY_IF_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_if_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type copy_if_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::size_type size,
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
		}	// namespace detail
		//
		// copy_if
		//
		template<typename InputIterator, typename Result, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_if(
			InputIterator first,
			InputIterator last,
			Result const& result,
			Predicate pred
			)
		{
			return sprout::fixed::detail::copy_if_impl(first, last, result, pred, sprout::size(result));
		}
	}	// namespace fixed

	using sprout::fixed::copy_if;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_IF_HPP
