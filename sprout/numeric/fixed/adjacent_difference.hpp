#ifndef SPROUT_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP
#define SPROUT_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result>(result, sprout::size(result), args...);
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return adjacent_difference_impl_3(result, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)));
			}
			template<typename InputIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_2(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::value_type const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_2(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::value_type const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < static_cast<std::size_t>(offset)
					? adjacent_difference_impl_2(sprout::next(first), last, result, *first, offset, args..., *first - value)
					: adjacent_difference_impl_3(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_1(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_1(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < static_cast<std::size_t>(offset)
					? adjacent_difference_impl_1(first, last, result, offset, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)))
					: first != last
						? adjacent_difference_impl_2(sprout::next(first), last, result, *first, offset + sprout::size(result), args..., *first)
						: adjacent_difference_impl_3(result, args...)
					;
			}
			template<typename InputIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type adjacent_difference_impl(
				InputIterator first,
				InputIterator last,
				Result const& result
				)
			{
				return adjacent_difference_impl_1(first, last, result, sprout::fixed_begin_offset(result));
			}
		}	// namespace detail
		//
		// adjacent_difference
		//
		template<typename InputIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type adjacent_difference(
			InputIterator first,
			InputIterator last,
			Result const& result
			)
		{
			return sprout::fixed::detail::adjacent_difference_impl(first, last, result);
		}

		namespace detail {
			template<typename Result, typename BinaryOperation, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result>(result, sprout::size(result), args...);
			}
			template<typename Result, typename BinaryOperation, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return adjacent_difference_impl_3(result, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)));
			}
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_2(
				InputIterator first,
				InputIterator last,
				Result const& result,
				BinaryOperation binary_op,
				typename sprout::fixed_container_traits<Result>::value_type const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_2(
				InputIterator first,
				InputIterator last,
				Result const& result,
				BinaryOperation binary_op,
				typename sprout::fixed_container_traits<Result>::value_type const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < static_cast<std::size_t>(offset)
					? adjacent_difference_impl_2(sprout::next(first), last, result, binary_op, *first, offset, args..., binary_op(*first, value))
					: adjacent_difference_impl_3(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_1(
				InputIterator first,
				InputIterator last,
				Result const& result,
				BinaryOperation binary_op,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type adjacent_difference_impl_1(
				InputIterator first,
				InputIterator last,
				Result const& result,
				BinaryOperation binary_op,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < static_cast<std::size_t>(offset)
					? adjacent_difference_impl_1(first, last, result, binary_op, offset, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)))
					: first != last
						? adjacent_difference_impl_2(sprout::next(first), last, result, binary_op, *first, offset + sprout::size(result), args..., *first)
						: adjacent_difference_impl_3(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename BinaryOperation>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type adjacent_difference_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				BinaryOperation binary_op
				)
			{
				return adjacent_difference_impl_1(first, last, result, binary_op, sprout::fixed_begin_offset(result));
			}
		}	// namespace detail
		//
		// adjacent_difference
		//
		template<typename InputIterator, typename Result, typename BinaryOperation>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type adjacent_difference(
			InputIterator first,
			InputIterator last,
			Result const& result,
			BinaryOperation binary_op
			)
		{
			return sprout::fixed::detail::adjacent_difference_impl(first, last, result, binary_op);
		}
	}	// namespace fixed

	using sprout::fixed::adjacent_difference;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP
