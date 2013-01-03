#ifndef SPROUT_ALGORITHM_FIXED_PREV_PERMUTATION_HPP
#define SPROUT_ALGORITHM_FIXED_PREV_PERMUTATION_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fixed/reverse.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/utility/pair.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename Container, typename Difference>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl_4(Container const& cont, Difference d) {
				return Result(
					sprout::get_internal(sprout::fixed::reverse(sprout::sub_array<Container const&>(cont, d, sprout::size(cont)))),
					true
					);
			}
			template<typename Result, typename Container, typename Compare, typename Iterator>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl_3(Container const& cont, Compare comp, Iterator first, Iterator last, Iterator i, Iterator ii, Iterator j) {
				return !comp(*sprout::prev(j), *i) ? sprout::fixed::detail::prev_permutation_impl_3<Result>(
						cont, comp, first, last,
						i, ii, sprout::prev(j)
						)
					: sprout::fixed::detail::prev_permutation_impl_4<Result>(
						sprout::fixed::swap_element(cont, i, sprout::prev(j)),
						sprout::distance(first, ii)
						)
					;
			}
			template<typename Result, typename Container, typename Compare, typename Iterator>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl_2(Container const& cont, Compare comp, Iterator first, Iterator last, Iterator i, Iterator ii) {
				return comp(*ii, *i) ? sprout::fixed::detail::prev_permutation_impl_3<Result>(
						cont, comp, first, last,
						i, ii, last
						)
					: i == first ? Result(sprout::fixed::reverse_copy(first, last, cont), false)
					: sprout::fixed::detail::prev_permutation_impl_2<Result>(
						cont, comp, first, last,
						sprout::prev(i), i
						)
					;
			}
			template<typename Result, typename Container, typename Compare, typename Iterator>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl_1(Container const& cont, Compare comp, Iterator first, Iterator last, Iterator i) {
				return i == last ? Result(sprout::deep_copy(cont), false)
					: sprout::fixed::detail::prev_permutation_impl_2<Result>(
						cont, comp, first, last,
						sprout::prev(last, 2), sprout::prev(last)
						)
					;
			}
			template<typename Result, typename Container, typename Compare, typename Iterator>
			inline SPROUT_CONSTEXPR Result
			prev_permutation_impl(Container const& cont, Compare comp, Iterator first, Iterator last) {
				return first == last ? Result(sprout::deep_copy(cont), false)
					: sprout::fixed::detail::prev_permutation_impl_1<Result>(
					cont, comp, first, last,
					sprout::next(first)
					);
			}
		}	// namespace detail
		//
		// prev_permutation
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fixed::result_of::algorithm<Container>::type, bool>
		prev_permutation(Container const& cont, Compare comp) {
			typedef sprout::pair<typename sprout::fixed::result_of::algorithm<Container>::type, bool> type;
			return sprout::fixed::detail::prev_permutation_impl<type>(
				cont, comp,
				sprout::begin(cont), sprout::end(cont)
				);
		}
		//
		// prev_permutation
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fixed::result_of::algorithm<Container>::type, bool>
		prev_permutation(Container const& cont) {
			typedef sprout::pair<typename sprout::fixed::result_of::algorithm<Container>::type, bool> type;
			return sprout::fixed::detail::prev_permutation_impl<type>(
				cont, NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::begin(cont), sprout::end(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::prev_permutation;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_PREV_PERMUTATION_HPP
