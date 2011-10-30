#ifndef SPROUT_OPERATION_FIXED_APPEND_HPP
#define SPROUT_OPERATION_FIXED_APPEND_HPP

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
			// append
			//
			template<typename Container, typename Input>
			struct append {
			public:
				typedef typename sprout::rebind_fixed_size<
					Container
				>::template apply<
					sprout::fixed_container_traits<Container>::fixed_size + sprout::fixed_container_traits<Input>::fixed_size
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename Input, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result append_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Container>::difference_type pos,
				typename sprout::fixed_container_traits<Container>::difference_type size,
				Input const& input
				)
			{
				return sprout::remake_clone<Result>(
					cont,
					sprout::size(cont) + sprout::size(input),
					(Indexes < sprout::fixed_container_traits<Container>::fixed_size + size
						? (Indexes < pos
							? *sprout::next(sprout::fixed_begin(cont), Indexes)
							: Indexes < pos + size
							? *sprout::next(sprout::begin(input), Indexes - pos)
							: *sprout::next(sprout::fixed_begin(cont), Indexes - size)
							)
						: typename sprout::fixed_container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// append
		//
		template<typename Container, typename Input>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::append<Container, Input>::type append(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator pos,
			Input const& input
			)
		{
			return sprout::fixed::detail::append_impl<typename sprout::fixed::result_of::append<Container, Input>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::append<Container, Input>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), pos),
				sprout::size(input),
				input
				);
		}
		//
		// append
		//
		template<typename Container, typename Input>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::append<Container, Input>::type append(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::difference_type pos,
			Input const& input
			)
		{
			return sprout::fixed::detail::append_impl<typename sprout::fixed::result_of::append<Container, Input>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::append<Container, Input>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), sprout::next(sprout::begin(cont), pos)),
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
