#ifndef SPROUT_MATH_FLOAT_PROMOTE_HPP
#define SPROUT_MATH_FLOAT_PROMOTE_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T, typename U>
			struct float_promote2
				: public std::conditional<
					(std::is_same<T, long double>::value || std::is_same<U, long double>::value),
					std::common_type<long double>,
					typename std::conditional<
						(std::is_same<T, float>::value && std::is_same<U, float>::value),
						float,
						double
					>
				>::type
			{
				static_assert(std::is_arithmetic<U>::value, "float_promote requires arithmetic type.");
			};

			template<typename Current, typename Head, typename... Tail>
			struct float_promote_impl
				: public sprout::math::detail::float_promote_impl<
					typename sprout::math::detail::float_promote2<Current, Head>::type,
					Tail...
				>
			{};
			template<typename Current, typename Head>
			struct float_promote_impl<Current, Head>
				: public sprout::math::detail::float_promote2<Current, Head>
			{};
		}	// namespace detail

		//
		// float_promote
		//
		template<typename... Types>
		struct float_promote
			: public sprout::math::detail::float_promote_impl<
				float, typename std::remove_cv<Types>::type...
			>
		{};
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT_PROMOTE_HPP
