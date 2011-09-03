#ifndef SPROUT_OPERATION_FIXED_ERASE_N_HPP
#define SPROUT_OPERATION_FIXED_ERASE_N_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// erase_n
			//
			template<std::size_t N, typename Container>
			struct erase_n {
				static_assert(sprout::fixed_container_traits<Container>::fixed_size >= N, "fixed_size >= N");
			public:
				typedef typename sprout::rebind_fixed_size<
					Container
				>::template apply<
					sprout::fixed_container_traits<Container>::fixed_size - N
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<std::size_t N, typename Result, typename Container, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result erase_n_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Container>::difference_type pos
				)
			{
				return sprout::remake_clone<Result, Container>(
					cont,
					sprout::size(cont) - N,
					(Indexes < sprout::fixed_container_traits<Container>::fixed_size - N
						? (Indexes < pos
							? *(sprout::fixed_begin(cont) + Indexes)
							: *(sprout::fixed_begin(cont) + Indexes + N)
							)
						: typename sprout::fixed_container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// erase_n
		//
		template<std::size_t N, typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::erase_n<N, Container>::type erase_n(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator pos
			)
		{
			return sprout::fixed::detail::erase_n_impl<N, typename sprout::fixed::result_of::erase_n<N, Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::erase_n<N, Container>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), pos)
				);
		}
		//
		// erase_n
		//
		template<std::size_t N, typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::erase_n<N, Container>::type erase_n(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::difference_type pos
			)
		{
			return sprout::fixed::detail::erase_n_impl<N, typename sprout::fixed::result_of::erase_n<N, Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::erase_n<N, Container>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), sprout::begin(cont) + pos)
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::erase_n;
	}	// namespace result_of

	using sprout::fixed::erase_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_ERASE_N_HPP
