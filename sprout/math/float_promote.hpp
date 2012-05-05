#ifndef SPROUT_MATH_FLOAT_PROMOTE_HPP
#define SPROUT_MATH_FLOAT_PROMOTE_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<bool IsArithmetic, typename Current, typename Head, typename... Tail>
			struct float_promote_impl {};
			template<typename Current, typename Head>
			struct float_promote_impl<true, Current, Head>
				: public std::conditional<
					(std::is_same<Current, long double>::value || std::is_same<Head, long double>::value),
					long double,
					double
				>
			{};
			template<typename Current, typename Head, typename... Tail>
			struct float_promote_impl<true, Current, Head, Tail...>
				: public sprout::math::detail::float_promote_impl<
					std::is_arithmetic<Head>::value,
					typename std::conditional<
						(std::is_same<Current, long double>::value || std::is_same<Head, long double>::value),
						long double,
						double
					>::type,
					Tail...
				>
			{};

			template<typename Head, typename... Tail>
			struct float_promote
				: public sprout::math::detail::float_promote_impl<
					std::is_arithmetic<Head>::value,
					double,
					Head, Tail...
				>
			{};
		}	// namespace detail

		//
		// float_promote
		//
		template<typename... Types>
		struct float_promote
			: public sprout::math::detail::float_promote<
				typename std::remove_cv<Types>::type...
			>
		{};
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT_PROMOTE_HPP
