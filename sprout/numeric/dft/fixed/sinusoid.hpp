#ifndef SPROUT_NUMERIC_DFT_FIXED_SINUSOID_HPP
#define SPROUT_NUMERIC_DFT_FIXED_SINUSOID_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/math/comparison.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			sinusoid_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& d,
				typename sprout::container_traits<Container>::value_type const& amplitude,
				typename sprout::container_traits<Container>::value_type const& phase,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				typedef typename sprout::container_traits<Container>::value_type value_type;
				using sprout::sin;
				return sprout::remake<Container>(
					cont, size,
					(Indexes >= offset && Indexes < offset + size
						? amplitude * sin(d * value_type(Indexes) + phase)
						: *sprout::next(sprout::internal_begin(cont), Indexes)
						)...
					);
			}
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			sinusoid(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& frequency,
				typename sprout::container_traits<Container>::value_type const& amplitude,
				typename sprout::container_traits<Container>::value_type const& phase
				)
			{
				typedef typename sprout::container_traits<Container>::value_type value_type;
				return sprout::fixed::detail::sinusoid_impl(
					cont,
					value_type(2) * sprout::math::pi<value_type>() * frequency / value_type(sprout::size(cont)),
					amplitude,
					phase,
					sprout::container_indexes<Container>::make(),
					sprout::internal_begin_offset(cont),
					sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// sinusoid
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		sinusoid(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0
			)
		{
			return sprout::fixed::detail::sinusoid(cont, frequency, amplitude, phase);
		}

		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		sinusoid(
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0
			)
		{
			return sprout::fixed::sinusoid(sprout::pit<Container>(), frequency, amplitude, phase);
		}
	}	// namespace fixed

	using sprout::fixed::sinusoid;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIXED_SINUSOID_HPP
