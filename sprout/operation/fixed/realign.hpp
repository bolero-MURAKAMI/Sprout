#ifndef SPROUT_OPERATION_FIXED_REALIGN_HPP
#define SPROUT_OPERATION_FIXED_REALIGN_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// realign
			//
			template<typename Container>
			struct realign {
			public:
				typedef typename sprout::container_construct_traits<Container>::copied_type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result realign_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type size,
				T const& v
				)
			{
				return sprout::make<Result>(
					(Indexes < size
						? *sprout::next(sprout::begin(cont), Indexes)
						: v
						)...
					);
			}
		}	// namespace detail
		//
		// realign
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::realign<Container>::type realign(
			Container const& cont,
			T const& v
			)
		{
			return sprout::fixed::detail::realign_impl<typename sprout::fixed::result_of::realign<Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::realign<Container>::type>::static_size>::type(),
				sprout::size(cont),
				v
				);
		}

		namespace detail {
			template<typename Result, typename Container, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result realign_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type size
				)
			{
				return sprout::make<Result>(
					(Indexes < size
						? *sprout::next(sprout::begin(cont), Indexes)
						: typename sprout::container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// realign
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::realign<Container>::type realign(
			Container const& cont
			)
		{
			return sprout::fixed::detail::realign_impl<typename sprout::fixed::result_of::realign<Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::realign<Container>::type>::static_size>::type(),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::realign;
	}	// namespace result_of

	using sprout::fixed::realign;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_REALIGN_HPP
