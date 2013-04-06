#ifndef SPROUT_OPERATION_FIXED_ERASE_HPP
#define SPROUT_OPERATION_FIXED_ERASE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// erase
			//
			template<typename Container>
			struct erase
				: public sprout::container_transform_traits<
					Container
				>::template rebind_size<
					sprout::container_traits<Container>::static_size - 1
				>
			{
				static_assert(sprout::container_traits<Container>::static_size >= 1, "static_size >= 1");
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			erase_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type pos
				)
			{
				return sprout::remake<Result>(
					cont,
					sprout::size(cont) - 1,
					(Indexes < sprout::container_traits<Container>::static_size - 1
						? (Indexes < pos
							? *sprout::next(sprout::internal_begin(cont), Indexes)
							: *sprout::next(sprout::internal_begin(cont), Indexes + 1)
							)
						: typename sprout::container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// erase
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::erase<Container>::type
		erase(Container const& cont, typename sprout::container_traits<Container>::const_iterator pos) {
			return sprout::fixed::detail::erase_impl<typename sprout::fixed::result_of::erase<Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::result_of::erase<Container>::type>::make(),
				sprout::distance(sprout::internal_begin(cont), pos)
				);
		}
		//
		// erase
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::erase<Container>::type
		erase(Container const& cont, typename sprout::container_traits<Container>::difference_type pos) {
			return sprout::fixed::detail::erase_impl<typename sprout::fixed::result_of::erase<Container>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::result_of::erase<Container>::type>::make(),
				sprout::distance(sprout::internal_begin(cont), sprout::next(sprout::begin(cont), pos))
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::erase;
	}	// namespace result_of

	using sprout::fixed::erase;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_ERASE_HPP
