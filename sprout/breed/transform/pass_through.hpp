#ifndef SPROUT_BREED_TRANSFORM_PASS_THROUGH_HPP
#define SPROUT_BREED_TRANSFORM_PASS_THROUGH_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/breed/breed_fwd.hpp>
#include <sprout/breed/args.hpp>
#include <sprout/breed/transform/impl.hpp>
#include <sprout/breed/detail/std_result_of.hpp>

namespace sprout {
	namespace breed {
	    namespace detail {
			template<
				typename Grammar,
				typename Expr,
				typename State,
				typename Data,
				long Arity = sprout::breed::arity_of<Expr>::value
			>
			struct pass_through_impl
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			public:
				typedef typename pass_through_impl::expr unref_expr;
			private:
				template<typename IndexTuple>
				struct list_impl {};
				template<sprout::index_t... Indexes>
				struct list_impl<sprout::index_tuple<Indexes...> > {
				public:
					typedef sprout::breed::list<
						typename Grammar::template breed_child<Indexes>::type::template impl<
				            typename sprout::breed::result_of::child_c<Expr, Indexes>::type,
				        	State,
				        	Data
				        >::result_type...
					> type;
				};
			public:
				typedef typename sprout::breed::base_expr<
					typename unref_expr::breed_domain,
					typename unref_expr::breed_tag,
					typename list_impl<typename sprout::index_range<0, Arity>::type>::type
				>::type expr_type;
				typedef typename unref_expr::breed_generator breed_generator;
				typedef typename sprout::breed::detail::std_result_of<
					breed_generator(expr_type)
				>::type result_type;
			private:
				template<sprout::index_t... Indexes>
				SPROUT_CONSTEXPR result_type call_impl(
					typename pass_through_impl::expr_param e,
					typename pass_through_impl::state_param s,
					typename pass_through_impl::data_param d,
					sprout::index_tuple<Indexes...>
					) const
				{
					return breed_generator()(
						expr_type(
							typename Grammar::template breed_child<Indexes>::type::template impl<
							typename sprout::breed::result_of::child_c<Expr, Indexes>::type,
								State,
								Data
							>()(e.proto_base().template child<Indexes>(), s, d)...
							)
						);
				}
			public:
				SPROUT_CONSTEXPR result_type operator()(
					typename pass_through_impl::expr_param e,
					typename pass_through_impl::state_param s,
					typename pass_through_impl::data_param d
					) const
				{
					return call_impl(e, s, d, sprout::index_range<0, Arity>::make());
				}
			};
			template<typename Grammar, typename Expr, typename State, typename Data>
			struct pass_through_impl<Grammar, Expr, State, Data, 0>
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			public:
				typedef Expr result_type;
			public:
#ifdef SPROUT_BREED_STRICT_RESULT_OF
				SPROUT_CONSTEXPR result_type
#else
				SPROUT_CONSTEXPR typename pass_through_impl::expr_param
#endif
				operator()(
					typename pass_through_impl::expr_param e,
					typename pass_through_impl::state_param,
					typename pass_through_impl::data_param
					) const
				{
					return e;
				}
			};

		}	// namespace detail

		//
		// pass_through
		//
		template<typename Grammar>
		struct pass_through
			: public sprout::breed::transform<sprout::breed::pass_through<Grammar> >
		{
		public:
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::detail::pass_through_impl<Grammar, Expr, State, Data>
			{};
		};

		//
		// is_callable
		//
		template<typename Grammar>
		struct is_callable<sprout::breed::pass_through<Grammar> >
			: public std::true_type
		{};
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_TRANSFORM_PASS_THROUGH_HPP
