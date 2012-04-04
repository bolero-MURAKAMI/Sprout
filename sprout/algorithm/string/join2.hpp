#ifndef SPROUT_ALGORITHM_STRING_JOIN2_HPP
#define SPROUT_ALGORITHM_STRING_JOIN2_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/operation/fixed/append_back.hpp>

namespace sprout {
	namespace algorithm {
		namespace result_of {
			//
			// join2
			//
			template<typename ContainerContainer, typename Separator>
			struct join2 {
			public:
				typedef typename sprout::container_transform_traits<
					typename sprout::container_traits<ContainerContainer>::value_type
				>::template rebind_size<
					sprout::container_traits<ContainerContainer>::static_size != 0
						? (
							sprout::container_traits<
								typename sprout::container_traits<ContainerContainer>::value_type
							>::static_size
							+ (sprout::container_traits<ContainerContainer>::static_size - 1) * (
								sprout::container_traits<Separator>::static_size
								+ sprout::container_traits<
									typename sprout::container_traits<ContainerContainer>::value_type
								>::static_size
								)
							)
						: 0
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename ContainerIterator, typename Separator, typename Container>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				(sprout::container_traits<Container>::static_size == sprout::container_traits<Result>::static_size),
				Result
			>::type join2_impl_1(
				ContainerIterator first,
				ContainerIterator last,
				Separator const& separator,
				Container const& current
				)
			{
				return current;
			}
			template<typename Result, typename ContainerIterator, typename Separator, typename Container>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				(sprout::container_traits<Container>::static_size < sprout::container_traits<Result>::static_size),
				Result
			>::type join2_impl_1(
				ContainerIterator first,
				ContainerIterator last,
				Separator const& separator,
				Container const& current
				)
			{
				return sprout::algorithm::detail::join2_impl_1<Result>(
					sprout::next(first),
					last,
					separator,
					sprout::fixed::append_back(sprout::fixed::append_back(current, separator), *first)
					);
			}
			template<typename Result, typename ContainerIterator, typename Separator>
			inline SPROUT_CONSTEXPR Result join2_impl(
				ContainerIterator first,
				ContainerIterator last,
				Separator const& separator
				)
			{
				return first != last
					? sprout::algorithm::detail::join2_impl_1<Result>(
						sprout::next(first),
						last,
						separator,
						*first
						)
					: sprout::make<Result>()
					;
			}
		}	// namespace detail
		//
		// join2
		//
		template<typename ContainerContainer, typename Separator>
		inline SPROUT_CONSTEXPR typename sprout::algorithm::result_of::join2<ContainerContainer, Separator>::type join2(
			ContainerContainer const& cont_cont,
			Separator const& separator
			)
		{
			return sprout::algorithm::detail::join2_impl<typename sprout::algorithm::result_of::join2<ContainerContainer, Separator>::type>(
				sprout::begin(cont_cont),
				sprout::end(cont_cont),
				separator
				);
		}
	}	// namespace algorithm
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_STRING_JOIN2_HPP
