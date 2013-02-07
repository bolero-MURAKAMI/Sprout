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
#include <sprout/pit/pit.hpp>
#include <sprout/math/comparison.hpp>
#include <sprout/detail/container_complate.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Size, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_n(
				RandomAccessIterator first, Size n, Result const& result,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::copy(first, sprout::next(first, n), result);
			}

			template<typename InputIterator, typename Size, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			copy_n_impl(InputIterator first, Size n, Result const& result,
				typename sprout::container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Size, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			copy_n_impl(
				InputIterator first, Size n, Result const& result,
				typename sprout::container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return n != 0 && sprout::math::less(sizeof...(Args), offset)
					? sprout::fixed::detail::copy_n_impl(sprout::next(first), n - 1, result, offset, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Size, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_n(
				InputIterator first, Size n, Result const& result,
				void*
				)
			{
				return sprout::fixed::detail::copy_n_impl(first, n, result, sprout::size(result));
			}

			template<typename InputIterator, typename Size, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			copy_n(InputIterator first, Size n, Result const& result) {
				typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
				return sprout::fixed::detail::copy_n(first, n, result, category());
			}

			template<typename InputIterator, typename Size, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			copy_n(InputIterator first, Size n, Result const& result) {
				static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
				return sprout::fixed::copy(first, sprout::next(first, n), result);
			}
		}	// namespace detail
		//
		// copy_n
		//
		template<typename InputIterator, typename Size, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		copy_n(InputIterator first, Size n, Result const& result) {
			return sprout::fixed::detail::copy_n(first, n, result);
		}

		template<typename Result, typename InputIterator, typename Size>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		copy_n(InputIterator first, Size n) {
			return sprout::fixed::copy_n(first, n, sprout::pit<Result>());
		}
	}	// namespace fixed

	using sprout::fixed::copy_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_N_HPP
