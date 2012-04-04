#ifndef SPROUT_OPERATION_FIXED_APPEND_HPP
#define SPROUT_OPERATION_FIXED_APPEND_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// append
			//
			template<typename Container, typename Input>
			struct append {
			public:
				typedef typename sprout::container_transform_traits<
					Container
				>::template rebind_size<
					sprout::container_traits<Container>::static_size + sprout::container_traits<Input>::static_size
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename Input, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result append_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type pos,
				typename sprout::container_traits<Container>::difference_type size,
				Input const& input
				)
			{
				return sprout::remake<Result>(
					cont,
					sprout::size(cont) + sprout::size(input),
					(Indexes < sprout::container_traits<Container>::static_size + size
						? (Indexes < pos
							? *sprout::next(sprout::internal_begin(cont), Indexes)
							: Indexes < pos + size
							? *sprout::next(sprout::begin(input), Indexes - pos)
							: *sprout::next(sprout::internal_begin(cont), Indexes - size)
							)
						: typename sprout::container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// append
		//
		template<typename Container, typename Input>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::append<Container, Input>::type append(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator pos,
			Input const& input
			)
		{
			return sprout::fixed::detail::append_impl<typename sprout::fixed::result_of::append<Container, Input>::type>(
				cont,
				typename sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::append<Container, Input>::type>::static_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::internal_begin(cont), pos),
				sprout::size(input),
				input
				);
		}
		//
		// append
		//
		template<typename Container, typename Input>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::append<Container, Input>::type append(
			Container const& cont,
			typename sprout::container_traits<Container>::difference_type pos,
			Input const& input
			)
		{
			return sprout::fixed::detail::append_impl<typename sprout::fixed::result_of::append<Container, Input>::type>(
				cont,
				typename sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::append<Container, Input>::type>::static_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::internal_begin(cont), sprout::next(sprout::begin(cont), pos)),
				sprout::size(input),
				input
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::append;
	}	// namespace result_of

	using sprout::fixed::append;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_APPEND_HPP
