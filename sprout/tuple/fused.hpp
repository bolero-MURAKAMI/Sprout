/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_FUSED_HPP
#define SPROUT_TUPLE_FUSED_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/apply.hpp>
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
		public:
			template<typename Tuple>
			struct result
				: public sprout::tuples::apply_result<functor_type const&, Tuple>
			{};
		private:
			functor_type f_;
		public:
			SPROUT_CONSTEXPR fused() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			fused(fused const&) = default;
			explicit SPROUT_CONSTEXPR fused(F f)
				: f_(f)
			{}
			SPROUT_CONSTEXPR functor_type functor() const {
				return f_;
			}
			template<typename Tuple>
			SPROUT_CONSTEXPR typename result<Tuple>::type
			operator()(Tuple&& t) const {
				return sprout::tuples::apply(f_, SPROUT_FORWARD(Tuple, t));
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
