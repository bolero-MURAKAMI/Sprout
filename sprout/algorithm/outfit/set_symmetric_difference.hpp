#ifndef SPROUT_ALGORITHM_OUTFIT_SET_SYMMETRIC_DIFFERENCE_HPP
#define SPROUT_ALGORITHM_OUTFIT_SET_SYMMETRIC_DIFFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/set_symmetric_difference.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Iterator1, typename Iterator2, typename Result, typename Compare>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> set_symmetric_difference_impl(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Iterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::set_symmetric_difference(first1, last1, first2, last2, result, comp),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// set_symmetric_difference
		//
		template<typename Iterator1, typename Iterator2, typename Result, typename Compare>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> set_symmetric_difference(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Iterator2 last2,
			Result const& result,
			Compare comp
			)
		{
			return sprout::outfit::detail::set_symmetric_difference_impl(first1, last1, first2, last2, result, comp, sprout::fixed_begin_offset(result));
		}

		namespace detail {
			template<typename Iterator1, typename Iterator2, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> set_symmetric_difference_impl(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Iterator2 last2,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::set_symmetric_difference(first1, last1, first2, last2, result),
					offset,
					offset + sprout::size(result)
					);
			}
		}	// namespace detail
		//
		// set_symmetric_difference
		//
		template<typename Iterator1, typename Iterator2, typename Result>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> set_symmetric_difference(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Iterator2 last2,
			Result const& result
			)
		{
			return sprout::outfit::detail::set_symmetric_difference_impl(first1, last1, first2, last2, result, sprout::fixed_begin_offset(result));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_SET_SYMMETRIC_DIFFERENCE_HPP
