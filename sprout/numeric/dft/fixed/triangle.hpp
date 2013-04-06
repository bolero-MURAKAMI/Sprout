#ifndef SPROUT_NUMERIC_DFT_FIXED_TRINAGLE_HPP
#define SPROUT_NUMERIC_DFT_FIXED_TRINAGLE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/math/comparison.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/asin.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			triangle_value(T const& t) {
				using sprout::sin;
				using sprout::asin;
				return T(sprout::math::two_div_pi<double>()) * asin(sin(T(sprout::math::two_pi<double>()) * t));
			}

			template<typename Container, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			triangle_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& frequency,
				typename sprout::container_traits<Container>::value_type const& amplitude,
				typename sprout::container_traits<Container>::value_type const& phase,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				typedef typename sprout::container_traits<Container>::value_type value_type;
				return sprout::remake<Container>(
					cont, size,
					(Indexes >= offset && Indexes < offset + size
						? amplitude * sprout::fixed::detail::triangle_value(frequency * value_type(Indexes) + phase)
						: *sprout::next(sprout::internal_begin(cont), Indexes)
						)...
					);
			}
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			triangle(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& frequency,
				typename sprout::container_traits<Container>::value_type const& amplitude,
				typename sprout::container_traits<Container>::value_type const& phase
				)
			{
				return sprout::fixed::detail::triangle_impl(
					cont,
					frequency,
					amplitude,
					phase,
					sprout::container_indexes<Container>::make(),
					sprout::internal_begin_offset(cont),
					sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// triangle
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		triangle(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0
			)
		{
			return sprout::fixed::detail::triangle(cont, frequency, amplitude, phase);
		}

		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		triangle(
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0
			)
		{
			return sprout::fixed::triangle(sprout::pit<Container>(), frequency, amplitude, phase);
		}
	}	// namespace fixed

	using sprout::fixed::triangle;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIXED_TRINAGLE_HPP
