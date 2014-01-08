/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_FUSED_HPP
#define SPROUT_TUPLE_FUSED_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/tuple/indexes.hpp>
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
			template<typename Tuple, typename IndexTuple>
			struct result_impl;
			template<typename Tuple, sprout::index_t... Indexes>
			struct result_impl<Tuple, sprout::index_tuple<Indexes...> > {
			public:
				typedef decltype(
					std::declval<functor_type const&>()(
						sprout::tuples::get<Indexes>(std::declval<Tuple>())...
						)
				) type;
			};
		public:
			template<typename Tuple>
			struct result
				: public result_impl<
					Tuple,
					typename sprout::tuple_indexes<typename std::remove_reference<Tuple>::type>::type
				>
			{};
		private:
			functor_type f_;
		private:
			template<typename Result, typename Tuple, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR Result
			call(Tuple&& t, sprout::index_tuple<Indexes...>) const {
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
			SPROUT_CONSTEXPR typename result<Tuple>::type
			operator()(Tuple&& t) const {
				return call<typename result<Tuple>::type>(
					sprout::forward<Tuple>(t),
					sprout::tuple_indexes<typename std::remove_reference<Tuple>::type>::make()
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
