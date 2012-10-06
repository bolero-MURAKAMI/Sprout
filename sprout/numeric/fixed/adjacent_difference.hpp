#ifndef SPROUT_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP
#define SPROUT_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::value_type const& value,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::value_type const& value,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? adjacent_difference_impl_1(sprout::next(first), last, result, size, *first, args..., *first - value)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 0,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			adjacent_difference_impl(
				InputIterator first, InputIterator last, Result const& result,
				typename sprout::container_traits<Result>::size_type size
				)
			{
				return sprout::remake<Result>(result, sprout::size(result));
			}
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != 0,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result,
				typename sprout::container_traits<Result>::size_type size
				)
			{
				return first != last
					? adjacent_difference_impl_1(sprout::next(first), last, result, size, *first, *first)
					: sprout::detail::container_complate(result)
					;
			}
		}	// namespace detail
		//
		// adjacent_difference
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		adjacent_difference(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fixed::detail::adjacent_difference_impl(first, last, result, sprout::size(result));
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::value_type const& value,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::value_type const& value,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? adjacent_difference_impl_1(sprout::next(first), last, result, binary_op, size, *first, args..., binary_op(*first, value))
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 0,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			adjacent_difference_impl(
				InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::size_type size
				)
			{
				return sprout::remake<Result>(result, sprout::size(result));
			}
			template<typename InputIterator, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != 0,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::size_type size
				)
			{
				return first != last
					? adjacent_difference_impl_1(sprout::next(first), last, result, binary_op, size, *first, *first)
					: sprout::detail::container_complate(result)
					;
			}
		}	// namespace detail
		//
		// adjacent_difference
		//
		template<typename InputIterator, typename Result, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		adjacent_difference(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op) {
			return sprout::fixed::detail::adjacent_difference_impl(first, last, result, binary_op, sprout::size(result));
		}
	}	// namespace fixed

	using sprout::fixed::adjacent_difference;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP
