#ifndef SPROUT_ALGORITHM_STRING_JOIN_HPP
#define SPROUT_ALGORITHM_STRING_JOIN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/operation/fixed/append_back.hpp>

namespace sprout {
	namespace algorithm {
		namespace result_of {
			//
			// join
			//
			template<typename ContainerContainer, typename Separator>
			struct join {
			public:
				typedef typename sprout::rebind_fixed_size<
					typename sprout::fixed_container_traits<ContainerContainer>::value_type
				>::template apply<
					sprout::fixed_container_traits<ContainerContainer>::fixed_size != 0
						? (
							sprout::fixed_container_traits<
								typename sprout::fixed_container_traits<ContainerContainer>::value_type
							>::fixed_size
							+ (sprout::fixed_container_traits<ContainerContainer>::fixed_size - 1) * (
								sprout::fixed_container_traits<Separator>::fixed_size
								+ sprout::fixed_container_traits<
									typename sprout::fixed_container_traits<ContainerContainer>::value_type
								>::fixed_size
								)
							)
						: 0
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename ContainerIterator, typename Separator, typename Container>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size == sprout::fixed_container_traits<Result>::fixed_size),
				Result
			>::type join_impl_1(
				ContainerIterator first,
				ContainerIterator last,
				Separator const& separator,
				Container const& current
				)
			{
				return current;
			}
			template<typename Result, typename ContainerIterator, typename Separator, typename Container>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size < sprout::fixed_container_traits<Result>::fixed_size),
				Result
			>::type join_impl_1(
				ContainerIterator first,
				ContainerIterator last,
				Separator const& separator,
				Container const& current
				)
			{
				return sprout::algorithm::detail::join_impl_1<Result>(
					sprout::next(first),
					last,
					separator,
					sprout::fixed::append_back(sprout::fixed::append_back(current, separator), *first)
					);
			}
			template<typename Result, typename ContainerIterator, typename Separator>
			SPROUT_CONSTEXPR inline Result join_impl(
				ContainerIterator first,
				ContainerIterator last,
				Separator const& separator
				)
			{
				return first != last
					? sprout::algorithm::detail::join_impl_1<Result>(
						sprout::next(first),
						last,
						separator,
						*first
						)
					: sprout::make_clone<Result>()
					;
			}
		}	// namespace detail
		//
		// join
		//
		template<typename ContainerContainer, typename Separator>
		SPROUT_CONSTEXPR inline typename sprout::algorithm::result_of::join<ContainerContainer, Separator>::type join(
			ContainerContainer const& cont_cont,
			Separator const& separator
			)
		{
			return sprout::algorithm::detail::join_impl<typename sprout::algorithm::result_of::join<ContainerContainer, Separator>::type>(
				sprout::begin(cont_cont),
				sprout::end(cont_cont),
				separator
				);
		}
	}	// namespace algorithm
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_STRING_JOIN_HPP
