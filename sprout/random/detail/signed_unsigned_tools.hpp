#ifndef SPROUT_RANDOM_DETAIL_SIGNED_UNSIGNED_TOOLS_HPP
#define SPROUT_RANDOM_DETAIL_SIGNED_UNSIGNED_TOOLS_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename T, bool B = std::numeric_limits<T>::is_signed>
			struct subtract {};
			template<typename T>
			struct subtract<T, false> {
			public:
				typedef T result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T x, T y) const {
					return x - y;
				}
			};
			template<typename T>
			struct subtract<T, true> {
			public:
				typedef typename std::make_unsigned<T>::type result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T x, T y) const {
					return y >= 0 ? result_type(x) - result_type(y)
						: x >= 0 ? result_type(x) + result_type(-(y + 1)) + 1
						: result_type(x - y)
						;
				}
			};

			template<typename T1, typename T2, bool B = std::numeric_limits<T2>::is_signed>
			struct add {};
			template<typename T1, typename T2>
			struct add<T1, T2, false> {
			public:
				typedef T2 result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T1 x, T2 y) const {
					return T2(x) + y;
				}
			};
			template<typename T1, typename T2>
			struct add<T1, T2, true> {
			public:
				typedef T2 result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T1 x, T2 y) const {
					return y >= 0 ? T2(x) + y
						: x >= T1(-(y + 1)) ? T2(x - T1(-(y + 1)) - 1)
						: T2(x) + y
						;
				}
			};
		} // namespace detail
	} // namespace random
} // namespace sprout

#endif // SPROUT_RANDOM_DETAIL_SIGNED_UNSIGNED_TOOLS_HPP

