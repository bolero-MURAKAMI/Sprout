#ifndef SPROUT_TUPLE_FUSED_HPP
#define SPROUT_TUPLE_FUSED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// fused
		//
		template<typename F>
		class fused {
		public:
			typedef F functor_type;
		private:
			functor_type f_;
		private:
			template<typename Tuple, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR auto
			call(Tuple&& t, sprout::index_tuple<Indexes...>) const
				-> decltype(f_(sprout::tuples::get<Indexes>(sprout::forward<Tuple>(t))...))
			{
				return f_(sprout::tuples::get<Indexes>(sprout::forward<Tuple>(t))...);
			}
		public:
			fused() = default;
			fused(fused const&) = default;
			explicit SPROUT_CONSTEXPR fused(F f)
				: f_(f)
			{}
			SPROUT_CONSTEXPR functor_type functor() const {
				return f_;
			}
			template<typename Tuple>
			SPROUT_CONSTEXPR auto
			operator()(Tuple&& t) const
				-> decltype(this->call(
					sprout::forward<Tuple>(t),
					sprout::index_range<0, sprout::tuples::tuple_size<typename std::decay<Tuple>::type>::value>::make()
					))
			{
				return call(
					sprout::forward<Tuple>(t),
					sprout::index_range<0, sprout::tuples::tuple_size<typename std::decay<Tuple>::type>::value>::make()
					);
			}
		};

		//
		// make_fused
		//
		template<typename F>
		inline SPROUT_CONSTEXPR sprout::tuples::fused<F>
		make_fused(F const& f) {
			return sprout::tuples::fused<F>(f);
		}
	}	// namespace tuples

	using sprout::tuples::fused;
	using sprout::tuples::make_fused;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_FUSED_HPP
