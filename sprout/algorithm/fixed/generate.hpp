#ifndef SPROUT_ALGORITHM_FIXED_GENERATE_HPP
#define SPROUT_ALGORITHM_FIXED_GENERATE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/generator/functions.hpp>
#include <sprout/detail/container_complate.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Gen, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Container>::static_size == sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_1(
				Container const& cont, Gen const& gen,
				typename sprout::container_traits<Container>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Container>(cont, size, args..., sprout::generators::generated_value(gen));
			}
			template<typename Container, typename Gen, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Container>::static_size != sizeof...(Args) + 1,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type
			generate_impl_1(
				Container const& cont, Gen const& gen,
				typename sprout::container_traits<Container>::size_type size,
				Args const&... args
				)
			{
				return sizeof...(Args) + 1 < size
					? sprout::fixed::detail::generate_impl_1(
						cont, sprout::generators::next_generator(gen)(), size,
						args..., sprout::generators::generated_value(gen)
						)
					: sprout::detail::container_complate(cont, args..., sprout::generators::generated_value(gen))
					;
			}
			template<typename Container, typename Generator>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Container>::static_size == 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl(
				Container const& cont, Generator gen,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::remake<Container>(cont, size);
			}
			template<typename Container, typename Generator>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Container>::static_size != 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type
			generate_impl(
				Container const& cont, Generator gen,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return size != 0
					? sprout::fixed::detail::generate_impl_1(cont, gen(), size)
					: sprout::detail::container_complate(cont)
					;
			}
		}	// namespace detail
		//
		// generate
		//
		template<typename Container, typename Generator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		generate(Container const& cont, Generator gen) {
			return sprout::fixed::detail::generate_impl(cont, gen, sprout::size(cont));
		}
	}	// namespace fixed

	using sprout::fixed::generate;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_GENERATE_HPP
