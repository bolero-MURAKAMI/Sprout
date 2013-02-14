#ifndef SPROUT_COMPOST_UTILITY_IIR_FILTER_HPP
#define SPROUT_COMPOST_UTILITY_IIR_FILTER_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/math/tan.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/math/constants.hpp>

namespace sprout {
	namespace compost {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR typename sprout::float_promote<T>::type
			iir_fc(T const& fc) {
				typedef typename sprout::float_promote<T>::type type;
				using sprout::tan;
				return tan(sprout::math::pi<type>() * fc) / sprout::math::two_pi<type>();
			}
			template<typename T>
			inline SPROUT_CONSTEXPR typename sprout::float_promote<T>::type
			iir_g(T const& g) {
				typedef typename sprout::float_promote<T>::type type;
				return g + 1;
			}
		}	// namespace detail

		namespace detail {
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_lpf_impl_2(T const& fc, T const& q, A const& a, B const& b, T const& x, T const& x2, T const& y) {
				return Result(
					sprout::remake<A>(
						a, 3,
						T(1),
						(2 * x2 - 2) / y,
						(1 - x / q + x2) / y
						),
					sprout::remake<B>(
						b, 3,
						x2 / y,
						2 * x2 / y,
						x2 / y
						)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_lpf_impl_1(T const& fc, T const& q, A const& a, B const& b, T const& x) {
				return sprout::compost::detail::iir_lpf_impl_2<Result>(
					fc, q, a, b,
					x, x * x, 1 + x / q + x * x
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_lpf_impl(T const& fc, T const& q, A const& a, B const& b) {
				return sprout::compost::detail::iir_lpf_impl_1<Result>(
					fc, q, a, b,
					sprout::math::two_pi<T>() * fc
					);
			}
		}	// namespace detail
		//
		// iir_lpf
		//
		template<typename T, typename A, typename B>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::fixed::result_of::algorithm<A>::type,
			typename sprout::fixed::result_of::algorithm<B>::type
		>
		iir_lpf(T const& fc, T const& q, A const& a, B const& b) {
			typedef sprout::pair<
				typename sprout::fixed::result_of::algorithm<A>::type,
				typename sprout::fixed::result_of::algorithm<B>::type
			> result_type;
			return sprout::compost::detail::iir_lpf_impl<result_type>(sprout::compost::detail::iir_fc(fc), q, a, b);
		}

		namespace detail {
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_hpf_impl_2(T const& fc, T const& q, A const& a, B const& b, T const& x, T const& x2, T const& y) {
				return Result(
					sprout::remake<A>(
						a, 3,
						T(1),
						(2 * x2 - 2) / y,
						(1 - x / q + x2) / y
						),
					sprout::remake<B>(
						b, 3,
						1 / y,
						-2 / y,
						1 / y
						)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_hpf_impl_1(T const& fc, T const& q, A const& a, B const& b, T const& x) {
				return sprout::compost::detail::iir_hpf_impl_2<Result>(
					fc, q, a, b,
					x, x * x, 1 + x / q + x * x
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_hpf_impl(T const& fc, T const& q, A const& a, B const& b) {
				return sprout::compost::detail::iir_hpf_impl_1<Result>(
					fc, q, a, b,
					sprout::math::two_pi<T>() * fc
					);
			}
		}	// namespace detail
		//
		// iir_hpf
		//
		template<typename T, typename A, typename B>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::fixed::result_of::algorithm<A>::type,
			typename sprout::fixed::result_of::algorithm<B>::type
		>
		iir_hpf(T const& fc, T const& q, A const& a, B const& b) {
			typedef sprout::pair<
				typename sprout::fixed::result_of::algorithm<A>::type,
				typename sprout::fixed::result_of::algorithm<B>::type
			> result_type;
			return sprout::compost::detail::iir_hpf_impl<result_type>(sprout::compost::detail::iir_fc(fc), q, a, b);
		}

		namespace detail {
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_bpf_impl_2(T const& fc, T const& q, A const& a, B const& b, T const& x, T const& x2, T const& y) {
				return Result(
					sprout::remake<A>(
						a, 3,
						T(1),
						(2 * x2 - 2) / y,
						(1 - x + x2) / y
						),
					sprout::remake<B>(
						b, 3,
						x / y,
						T(0),
						-x / y
						)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_bpf_impl_1(T const& fc, T const& q, A const& a, B const& b, T const& x, T const& x2) {
				return sprout::compost::detail::iir_bpf_impl_2<Result>(
					fc, q, a, b,
					x, x2, 1 + x + x2
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_bpf_impl(T const& fc1, T const& fc2, A const& a, B const& b) {
				return sprout::compost::detail::iir_bpf_impl_1<Result>(
					fc1, fc2, a, b,
					sprout::math::two_pi<T>() * (fc2 - fc1),
					sprout::math::four_pi<T>() * fc1 * fc2
					);
			}
		}	// namespace detail
		//
		// iir_bpf
		//
		template<typename T, typename A, typename B>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::fixed::result_of::algorithm<A>::type,
			typename sprout::fixed::result_of::algorithm<B>::type
		>
		iir_bpf(T const& fc1, T const& fc2, A const& a, B const& b) {
			typedef sprout::pair<
				typename sprout::fixed::result_of::algorithm<A>::type,
				typename sprout::fixed::result_of::algorithm<B>::type
			> result_type;
			return sprout::compost::detail::iir_bpf_impl<result_type>(
				sprout::compost::detail::iir_fc(fc1), sprout::compost::detail::iir_fc(fc2),
				a, b
				);
		}

		namespace detail {
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_bef_impl_2(T const& fc, T const& q, A const& a, B const& b, T const& x, T const& x2, T const& y) {
				return Result(
					sprout::remake<A>(
						a, 3,
						T(1),
						(2 * x2 - 2) / y,
						(1 - x + x2) / y
						),
					sprout::remake<B>(
						b, 3,
						(x2 + 1) / y,
						(2 * x2 - 2) / y,
						(x2 + 1) / y
						)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_bef_impl_1(T const& fc, T const& q, A const& a, B const& b, T const& x, T const& x2) {
				return sprout::compost::detail::iir_bef_impl_2<Result>(
					fc, q, a, b,
					x, x2, 1 + x + x2
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_bef_impl(T const& fc1, T const& fc2, A const& a, B const& b) {
				return sprout::compost::detail::iir_bef_impl_1<Result>(
					fc1, fc2, a, b,
					sprout::math::two_pi<T>() * (fc2 - fc1),
					sprout::math::four_pi<T>() * fc1 * fc2
					);
			}
		}	// namespace detail
		//
		// iir_bef
		//
		template<typename T, typename A, typename B>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::fixed::result_of::algorithm<A>::type,
			typename sprout::fixed::result_of::algorithm<B>::type
		>
		iir_bef(T const& fc1, T const& fc2, A const& a, B const& b) {
			typedef sprout::pair<
				typename sprout::fixed::result_of::algorithm<A>::type,
				typename sprout::fixed::result_of::algorithm<B>::type
			> result_type;
			return sprout::compost::detail::iir_bef_impl<result_type>(
				sprout::compost::detail::iir_fc(fc1), sprout::compost::detail::iir_fc(fc2),
				a, b
				);
		}

		namespace detail {
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_resonator_impl_2(T const& fc, T const& q, A const& a, B const& b, T const& x, T const& x2, T const& y) {
				return Result(
					sprout::remake<A>(
						a, 3,
						T(1),
						(2 * x2 - 2) / y,
						(1 - x / q + x2) / y
						),
					sprout::remake<B>(
						b, 3,
						x / q / y,
						T(0),
						-x / q / y
						)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_resonator_impl_1(T const& fc, T const& q, A const& a, B const& b, T const& x) {
				return sprout::compost::detail::iir_resonator_impl_2<Result>(
					fc, q, a, b,
					x, x * x, 1 + x / q + x * x
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_resonator_impl(T const& fc, T const& q, A const& a, B const& b) {
				return sprout::compost::detail::iir_resonator_impl_1<Result>(
					fc, q, a, b,
					sprout::math::two_pi<T>() * fc
					);
			}
		}	// namespace detail
		//
		// iir_resonator
		//
		template<typename T, typename A, typename B>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::fixed::result_of::algorithm<A>::type,
			typename sprout::fixed::result_of::algorithm<B>::type
		>
		iir_resonator(T const& fc, T const& q, A const& a, B const& b) {
			typedef sprout::pair<
				typename sprout::fixed::result_of::algorithm<A>::type,
				typename sprout::fixed::result_of::algorithm<B>::type
			> result_type;
			return sprout::compost::detail::iir_resonator_impl<result_type>(sprout::compost::detail::iir_fc(fc), q, a, b);
		}

		namespace detail {
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_notch_impl_2(T const& fc, T const& q, A const& a, B const& b, T const& x, T const& x2, T const& y) {
				return Result(
					sprout::remake<A>(
						a, 3,
						T(1),
						(2 * x2 - 2) / y,
						(1 - x / q + x2) / y
						),
					sprout::remake<B>(
						b, 3,
						(x2 + 1) / y,
						(2 * x2 + 2) / y,
						(x2 + 1) / y
						)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_notch_impl_1(T const& fc, T const& q, A const& a, B const& b, T const& x) {
				return sprout::compost::detail::iir_notch_impl_2<Result>(
					fc, q, a, b,
					x, x * x, 1 + x / q + x * x
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_notch_impl(T const& fc, T const& q, A const& a, B const& b) {
				return sprout::compost::detail::iir_notch_impl_1<Result>(
					fc, q, a, b,
					sprout::math::two_pi<T>() * fc
					);
			}
		}	// namespace detail
		//
		// iir_notch
		//
		template<typename T, typename A, typename B>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::fixed::result_of::algorithm<A>::type,
			typename sprout::fixed::result_of::algorithm<B>::type
		>
		iir_notch(T const& fc, T const& q, A const& a, B const& b) {
			typedef sprout::pair<
				typename sprout::fixed::result_of::algorithm<A>::type,
				typename sprout::fixed::result_of::algorithm<B>::type
			> result_type;
			return sprout::compost::detail::iir_notch_impl<result_type>(sprout::compost::detail::iir_fc(fc), q, a, b);
		}

		namespace detail {
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_low_shelving_impl_2(T const& fc, T const& q, T const& g, A const& a, B const& b, T const& x, T const& x2, T const& y, T const& g_) {
				return Result(
					sprout::remake<A>(
						a, 3,
						T(1),
						(2 * x2 - 2) / y,
						(1 - x / q + x2) / y
						),
					sprout::remake<B>(
						b, 3,
						(1 + g_ * x / q + g * x2) / y,
						(2 * g * x2 - 2) / y,
						(1 + g_ * x / q + g * x2) / y
						)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_low_shelving_impl_1(T const& fc, T const& q, T const& g, A const& a, B const& b, T const& x) {
				using sprout::sqrt;
				return sprout::compost::detail::iir_low_shelving_impl_2<Result>(
					fc, q, g, a, b,
					x, x * x, 1 + x / q + x * x, sqrt(g)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_low_shelving_impl(T const& fc, T const& q, T const& g, A const& a, B const& b) {
				return sprout::compost::detail::iir_low_shelving_impl_1<Result>(
					fc, q, a, b,
					sprout::math::two_pi<T>() * fc
					);
			}
		}	// namespace detail
		//
		// iir_low_shelving
		//
		template<typename T, typename A, typename B>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::fixed::result_of::algorithm<A>::type,
			typename sprout::fixed::result_of::algorithm<B>::type
		>
		iir_low_shelving(T const& fc, T const& q, T const& g, A const& a, B const& b) {
			typedef sprout::pair<
				typename sprout::fixed::result_of::algorithm<A>::type,
				typename sprout::fixed::result_of::algorithm<B>::type
			> result_type;
			return sprout::compost::detail::iir_low_shelving_impl<result_type>(
				sprout::compost::detail::iir_fc(fc), q, sprout::compost::detail::iir_g(g),
				a, b
				);
		}

		namespace detail {
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_high_shelving_impl_2(T const& fc, T const& q, T const& g, A const& a, B const& b, T const& x, T const& x2, T const& y, T const& g_) {
				return Result(
					sprout::remake<A>(
						a, 3,
						T(1),
						(2 * x2 - 2) / y,
						(1 - x / q + x2) / y
						),
					sprout::remake<B>(
						b, 3,
						(g + g_ * x / q + x2) / y,
						(2 * x2 - 2 * g) / y,
						(g + g_ * x / q + x2) / y
						)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_high_shelving_impl_1(T const& fc, T const& q, T const& g, A const& a, B const& b, T const& x) {
				using sprout::sqrt;
				return sprout::compost::detail::iir_high_shelving_impl_2<Result>(
					fc, q, g, a, b,
					x, x * x, 1 + x / q + x * x, sqrt(g)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_high_shelving_impl(T const& fc, T const& q, T const& g, A const& a, B const& b) {
				return sprout::compost::detail::iir_high_shelving_impl_1<Result>(
					fc, q, a, b,
					sprout::math::two_pi<T>() * fc
					);
			}
		}	// namespace detail
		//
		// iir_high_shelving
		//
		template<typename T, typename A, typename B>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::fixed::result_of::algorithm<A>::type,
			typename sprout::fixed::result_of::algorithm<B>::type
		>
		iir_high_shelving(T const& fc, T const& q, T const& g, A const& a, B const& b) {
			typedef sprout::pair<
				typename sprout::fixed::result_of::algorithm<A>::type,
				typename sprout::fixed::result_of::algorithm<B>::type
			> result_type;
			return sprout::compost::detail::iir_high_shelving_impl<result_type>(
				sprout::compost::detail::iir_fc(fc), q, sprout::compost::detail::iir_g(g),
				a, b
				);
		}

		namespace detail {
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_peaking_impl_2(T const& fc, T const& q, T const& g, A const& a, B const& b, T const& x, T const& x2, T const& y) {
				return Result(
					sprout::remake<A>(
						a, 3,
						T(1),
						(2 * x2 - 2) / y,
						(1 - x / q + x2) / y
						),
					sprout::remake<B>(
						b, 3,
						(1 + x / q + g + x2) / y,
						(2 * x2 - 2) / y,
						(1 + x / q + g + x2) / y
						)
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_peaking_impl_1(T const& fc, T const& q, T const& g, A const& a, B const& b, T const& x) {
				return sprout::compost::detail::iir_peaking_impl_2<Result>(
					fc, q, g, a, b,
					x, x * x, 1 + x / q + x * x
					);
			}
			template<typename Result, typename T, typename A, typename B>
			inline SPROUT_CONSTEXPR Result
			iir_peaking_impl(T const& fc, T const& q, T const& g, A const& a, B const& b) {
				return sprout::compost::detail::iir_peaking_impl_1<Result>(
					fc, q, a, b,
					sprout::math::two_pi<T>() * fc
					);
			}
		}	// namespace detail
		//
		// iir_peaking
		//
		template<typename T, typename A, typename B>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::fixed::result_of::algorithm<A>::type,
			typename sprout::fixed::result_of::algorithm<B>::type
		>
		iir_peaking(T const& fc, T const& q, T const& g, A const& a, B const& b) {
			typedef sprout::pair<
				typename sprout::fixed::result_of::algorithm<A>::type,
				typename sprout::fixed::result_of::algorithm<B>::type
			> result_type;
			return sprout::compost::detail::iir_peaking_impl<result_type>(
				sprout::compost::detail::iir_fc(fc), q, sprout::compost::detail::iir_g(g),
				a, b
				);
		}

		namespace detail {
			template<typename Result, typename T, typename DelayA, typename DelayB>
			inline SPROUT_CONSTEXPR Result
			apply_iir_impl(T const& base, DelayA const& da, DelayB const& db, T const& sample) {
				return Result(
					sample,
					typename Result::second_type(
						sprout::remake<DelayA>(da, 2, sample, sprout::tuples::get<0>(da)),
						sprout::remake<DelayB>(db, 2, base, sprout::tuples::get<0>(db))
						)
					);
			}
		}	// namespace detail
		//
		// apply_iir
		//
		template<typename T, typename A, typename B, typename DelayA, typename DelayB>
		inline SPROUT_CONSTEXPR sprout::pair<
			T,
			sprout::pair<
				typename sprout::fixed::result_of::algorithm<DelayA>::type,
				typename sprout::fixed::result_of::algorithm<DelayB>::type
			>
		>
		apply_iir(T const& base, A const& a, B const& b, DelayA const& da, DelayB const& db) {
			typedef sprout::pair<
				T,
				sprout::pair<
					typename sprout::fixed::result_of::algorithm<DelayA>::type,
					typename sprout::fixed::result_of::algorithm<DelayB>::type
				>
			> result_type;
			return sprout::compost::detail::apply_iir_impl<result_type>(
				base, da, db,
				sprout::tuples::get<0>(b) * base
					+ sprout::tuples::get<1>(b) * sprout::tuples::get<0>(db)
					+ sprout::tuples::get<2>(b) * sprout::tuples::get<1>(db)
					- sprout::tuples::get<1>(a) * sprout::tuples::get<0>(da)
					- sprout::tuples::get<2>(a) * sprout::tuples::get<1>(da)
				);
		}
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_UTILITY_IIR_FILTER_HPP
