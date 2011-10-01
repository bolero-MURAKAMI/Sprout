#ifndef SPROUT_OPERATION_FIXED_ERASE_HPP
#define SPROUT_OPERATION_FIXED_ERASE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// erase
			//
			template<typename Container>
			struct erase {
				static_assert(sprout::fixed_container_traits<Container>::fixed_size >= 1, "fixed_size >= 1");
			public:
				typedef typename sprout::rebind_fixed_size<
					Container
				>::template apply<
					sprout::fixed_container_traits<Container>::fixed_size - 1
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result erase_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Container>::difference_type pos
				)
			{
				return sprout::remake_clone<Result, Container>(
					cont,
					sprout::size(cont) - 1,
					(Indexes < sprout::fixed_container_traits<Container>::fixed_size - 1
						? (Indexes < pos
							? *sprout::next(sprout::fixed_begin(cont), Indexes)
							: *sprout::next(sprout::fixed_begin(cont), Indexes + 1)
							)
						: typename sprout::fixed_container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// erase
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::erase<Container>::type erase(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator pos
			)
		{
			return sprout::fixed::detail::erase_impl<typename sprout::fixed::result_of::erase<Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::erase<Container>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), pos)
				);
		}
		//
		// erase
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::erase<Container>::type erase(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::difference_type pos
			)
		{
			return sprout::fixed::detail::erase_impl<typename sprout::fixed::result_of::erase<Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::erase<Container>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), sprout::next(sprout::begin(cont), pos))
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::erase;
	}	// namespace result_of

	using sprout::fixed::erase;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_ERASE_HPP
