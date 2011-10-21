#ifndef SPROUT_ALGORITHM_FIXED_SORT_HPP
#define SPROUT_ALGORITHM_FIXED_SORT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_lr(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type start,
				typename sprout::fixed_container_traits<Container>::difference_type end,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type l,
				typename sprout::fixed_container_traits<Container>::difference_type r,
				typename sprout::fixed_container_traits<Container>::value_type const& p
				);
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_start(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type start,
				typename sprout::fixed_container_traits<Container>::difference_type end,
				Compare comp
				);

			template<typename Container, typename Iterator>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::value_type const& sort_select_pivot(
				Iterator origin,
				typename sprout::fixed_container_traits<Container>::difference_type start,
				typename sprout::fixed_container_traits<Container>::difference_type end
				)
			{	// pivot を選ぶ（中央の要素）
				return *sprout::next(origin, (end + start) / 2);
			}
			template<typename Container, typename Iterator, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::difference_type sort_find_l(
				Iterator origin,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type l,
				typename sprout::fixed_container_traits<Container>::value_type const& p
				)
			{	// left を見つける
				return comp(*sprout::next(origin, l), p) ? sort_find_l<Container>(origin, comp, l + 1, p) : l;
			}
			template<typename Container, typename Iterator, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::difference_type sort_find_r(
				Iterator origin,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type r,
				typename sprout::fixed_container_traits<Container>::value_type const& p
				)
			{	// right を見つける
				return comp(p, *sprout::next(origin, r)) ? sort_find_r<Container>(origin, comp, r - 1, p) : r;
			}
			template<typename Container>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type swap_lr(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type l,
				typename sprout::fixed_container_traits<Container>::difference_type r
				);
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_part_l(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type start,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type l
				)
			{	// 左側をソート
				return start < l - 1 ? sort_start(cont, start, l - 1, comp) : sprout::clone(cont);
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_part_r(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type end,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type r
				)
			{	// 右側をソート
				return r + 1 < end ? sort_start(cont, r + 1, end, comp) : sprout::clone(cont);
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_part_lr(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type start,
				typename sprout::fixed_container_traits<Container>::difference_type end,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type l,
				typename sprout::fixed_container_traits<Container>::difference_type r
				)
			{	// 左右に分けてソート
				return sort_part_r(sort_part_l(cont, start, comp, l), end, comp, r);
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_next(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type start,
				typename sprout::fixed_container_traits<Container>::difference_type end,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type l,
				typename sprout::fixed_container_traits<Container>::difference_type r,
				typename sprout::fixed_container_traits<Container>::value_type const& p
				)
			{	// left と right 比較して、左右に分けてソートするか、またはスワップしてこの範囲のソートを続ける
				return l >= r
					? sort_part_lr(cont, start, end, comp, l, r)
					: sort_lr(sprout::fixed::swap_element(cont, sprout::next(sprout::fixed_begin(cont), l), sprout::next(sprout::fixed_begin(cont), r)), start, end, comp, l + 1, r - 1, p)
					;
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_lr(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type start,
				typename sprout::fixed_container_traits<Container>::difference_type end,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type l,
				typename sprout::fixed_container_traits<Container>::difference_type r,
				typename sprout::fixed_container_traits<Container>::value_type const& p
				)
			{	// left と right を検索
				return sort_next(
					cont,
					start,
					end,
					comp,
					sort_find_l<Container>(sprout::fixed_begin(cont), comp, l, p),
					sort_find_r<Container>(sprout::fixed_begin(cont), comp, r, p),
					p
					);
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_start(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type start,
				typename sprout::fixed_container_traits<Container>::difference_type end,
				Compare comp
				)
			{	// pivot を選択してソートを開始
				return sort_lr(cont, start, end, comp, start, end, sort_select_pivot<Container>(sprout::fixed_begin(cont), start, end));
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size <= 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type sort(
				Container const& cont,
				Compare comp
				)
			{
				return sprout::clone(cont);
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size > 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type sort(
				Container const& cont,
				Compare comp
				)
			{
				return sprout::fixed::detail::sort_start(
					cont,
					sprout::fixed_begin_offset(cont),
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), sprout::end(cont) - 1),
					comp
					);
			}
			template<typename Container>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size <= 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type sort(
				Container const& cont
				)
			{
				return sprout::clone(cont);
			}
			template<typename Container>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size > 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type sort(
				Container const& cont
				)
			{
				return sprout::fixed::detail::sort_start(
					cont,
					sprout::fixed_begin_offset(cont),
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), sprout::end(cont) - 1),
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Container>::value_type>()
					);
			}
		}	// namespace detail
		//

		// sort
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fixed::detail::sort(cont, comp);
		}
		//
		// sort
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort(
			Container const& cont
			)
		{
			return sprout::fixed::detail::sort(cont);
		}
	}	// namespace fixed

	using sprout::fixed::sort;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SORT_HPP
