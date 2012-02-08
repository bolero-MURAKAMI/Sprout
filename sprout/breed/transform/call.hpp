#ifndef SPROUT_BREED_TRANSFORM_CALL_HPP
#define SPROUT_BREED_TRANSFORM_CALL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/breed/breed_fwd.hpp>
#include <sprout/breed/traits.hpp>
#include <sprout/breed/transform/impl.hpp>
#include <sprout/breed/detail/std_result_of.hpp>
#include <sprout/breed/detail/as_lvalue.hpp>
#include <sprout/breed/detail/poly_function.hpp>

namespace sprout {
	namespace breed {
		//
		// call
		//
		template<typename PrimitiveTransform>
		struct call
			: public PrimitiveTransform
		{};
		template<typename Fun>
		struct call<Fun()>
			: public sprout::breed::transform<sprout::breed::call<Fun()> >
		{
		public:
			template<typename Expr, typename State, typename Data, bool B>
			struct impl2
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			public:
				typedef typename sprout::breed::detail::std_result_of<Fun()>::type result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(
					typename impl2::expr_param,
					typename impl2::state_param,
					typename impl2::data_param
					) const
				{
					return Fun()();
				}
			};
			template<typename Expr, typename State, typename Data>
			struct impl2<Expr, State, Data, true>
				: public Fun::template impl<Expr, State, Data>
			{};
			template<typename Expr, typename State, typename Data>
			struct impl
				: public impl2<Expr, State, Data, sprout::breed::detail::is_transform_<Fun>::value>
			{};
		};
		template<typename Fun, typename A0>
		struct call<Fun(A0)>
			: public sprout::breed::transform<sprout::breed::call<Fun(A0)> >
		{
		public:
			template<typename Expr, typename State, typename Data, bool B>
			struct impl2
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			private:
				template<typename A>
				struct a_ {
				public:
					typedef typename sprout::breed::when<sprout::breed::_, A>::template impl<
						Expr,
						State,
						Data
					> type;
				};
				template<typename... Args>
				struct fun_ {
				public:
					typedef Fun type(typename a_<Args>::type::result_type...);
				};
				template<typename... Args>
				struct function_
					: public sprout::breed::detail::poly_function_traits<
						Fun,
						typename fun_<Args...>::type
					>
				{};
			public:
				template<long N>
				struct a {
				public:
					typedef typename a_<typename sprout::tppack_at<N, A0>::type>::type::result_type type;
				};
				typedef function_<A0> function_traits;
				typedef typename function_traits::result_type result_type;
				SPROUT_CONSTEXPR result_type operator ()(
					typename impl2::expr_param e,
					typename impl2::state_param s,
					typename impl2::data_param d
					) const
				{
					return typename function_traits::function_type()(
						sprout::breed::detail::as_lvalue(a_<A0>()(e, s, d))
					);
				}
			};
			template<typename Expr, typename State, typename Data>
			struct impl2<Expr, State, Data, true>
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			private:
				template<typename A>
				struct a_ {
				public:
					typedef typename sprout::breed::when<sprout::breed::_, A>::template impl<
						Expr,
						State,
						Data
					> type;
				};
				typedef Fun::template impl<typename a_<A0>::type, State, Data> function_;
			public:
				template<long N>
				struct a {
				public:
					typedef typename a_<typename sprout::tppack_at<N, A0>::type>::type::result_type type;
				};
				typedef template function_::result_type result_type;
				SPROUT_CONSTEXPR result_type operator ()(
					typename impl2::expr_param e,
					typename impl2::state_param s,
					typename impl2::data_param d
					) const
				{
					return function_()(
						typename a_<A0>::type()(e, s, d),
						s,
						d
					);
				}
			};
			template<typename Expr, typename State, typename Data>
			struct impl
				: public impl2<Expr, State, Data, sprout::breed::detail::is_transform_<Fun>::value>
			{};
		};
		template<typename Fun, typename A0, typename A1>
		struct call<Fun(A0, A1)>
			: public sprout::breed::transform<sprout::breed::call<Fun(A0, A1)> >
		{
		public:
			template<typename Expr, typename State, typename Data, bool B>
			struct impl2
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			private:
				template<typename A>
				struct a_ {
				public:
					typedef typename sprout::breed::when<sprout::breed::_, A>::template impl<
						Expr,
						State,
						Data
					> type;
				};
				template<typename... Args>
				struct fun_ {
				public:
					typedef Fun type(typename a_<Args>::type::result_type...);
				};
				template<typename... Args>
				struct function_
					: public sprout::breed::detail::poly_function_traits<
						Fun,
						typename fun_<Args...>::type
					>
				{};
			public:
				template<long N>
				struct a {
				public:
					typedef typename a_<typename sprout::tppack_at<N, A0, A1>::type>::type::result_type type;
				};
				typedef function_<A0, A1> function_traits;
				typedef typename function_traits::result_type result_type;
				SPROUT_CONSTEXPR result_type operator ()(
					typename impl2::expr_param e,
					typename impl2::state_param s,
					typename impl2::data_param d
					) const
				{
					return typename function_traits::function_type()(
						sprout::breed::detail::as_lvalue(a_<A0>()(e, s, d)),
						sprout::breed::detail::as_lvalue(a_<A1>()(e, s, d))
					);
				}
			};
			template<typename Expr, typename State, typename Data>
			struct impl2<Expr, State, Data, true>
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			private:
				template<typename A>
				struct a_ {
				public:
					typedef typename sprout::breed::when<sprout::breed::_, A>::template impl<
						Expr,
						State,
						Data
					> type;
				};
				typedef Fun::template impl<typename a_<A0>::type, typename a_<A1>::type, Data> function_;
			public:
				template<long N>
				struct a {
				public:
					typedef typename a_<typename sprout::tppack_at<N, A0, A1>::type>::type::result_type type;
				};
				typedef template function_::result_type result_type;
				SPROUT_CONSTEXPR result_type operator ()(
					typename impl2::expr_param e,
					typename impl2::state_param s,
					typename impl2::data_param d
					) const
				{
					return function_()(
						typename a_<A0>::type()(e, s, d),
						typename a_<A1>::type()(e, s, d),
						d
					);
				}
			};
			template<typename Expr, typename State, typename Data>
			struct impl
				: public impl2<Expr, State, Data, sprout::breed::detail::is_transform_<Fun>::value>
			{};
		};
		template<typename Fun, typename A0, typename A1, typename A2>
		struct call<Fun(A0, A1, A2)>
			: public sprout::breed::transform<sprout::breed::call<Fun(A0, A1, A2)> >
		{
		public:
			template<typename Expr, typename State, typename Data, bool B>
			struct impl2
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			private:
				template<typename A>
				struct a_ {
				public:
					typedef typename sprout::breed::when<sprout::breed::_, A>::template impl<
						Expr,
						State,
						Data
					> type;
				};
				template<typename... Args>
				struct fun_ {
				public:
					typedef Fun type(typename a_<Args>::type::result_type...);
				};
				template<typename... Args>
				struct function_
					: public sprout::breed::detail::poly_function_traits<
						Fun,
						typename fun_<Args...>::type
					>
				{};
			public:
				template<long N>
				struct a {
				public:
					typedef typename a_<typename sprout::tppack_at<N, A0, A1, A2>::type>::type::result_type type;
				};
				typedef function_<A0, A1, A2> function_traits;
				typedef typename function_traits::result_type result_type;
				SPROUT_CONSTEXPR result_type operator ()(
					typename impl2::expr_param e,
					typename impl2::state_param s,
					typename impl2::data_param d
					) const
				{
					return typename function_traits::function_type()(
						sprout::breed::detail::as_lvalue(a_<A0>()(e, s, d)),
						sprout::breed::detail::as_lvalue(a_<A1>()(e, s, d)),
						sprout::breed::detail::as_lvalue(a_<A2>()(e, s, d))
					);
				}
			};
			template<typename Expr, typename State, typename Data>
			struct impl2<Expr, State, Data, true>
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			private:
				template<typename A>
				struct a_ {
				public:
					typedef typename sprout::breed::when<sprout::breed::_, A>::template impl<
						Expr,
						State,
						Data
					> type;
				};
				typedef Fun::template impl<typename a_<A0>::type, typename a_<A1>::type, typename a_<A2>::type> function_;
			public:
				template<long N>
				struct a {
				public:
					typedef typename a_<typename sprout::tppack_at<N, A0, A1, A2>::type>::type::result_type type;
				};
				typedef template function_::result_type result_type;
				SPROUT_CONSTEXPR result_type operator ()(
					typename impl2::expr_param e,
					typename impl2::state_param s,
					typename impl2::data_param d
					) const
				{
					return function_()(
						typename a_<A0>::type()(e, s, d),
						typename a_<A1>::type()(e, s, d),
						typename a_<A2>::type()(e, s, d)
					);
				}
			};
			template<typename Expr, typename State, typename Data>
			struct impl
				: public impl2<Expr, State, Data, sprout::breed::detail::is_transform_<Fun>::value>
			{};
		};
		template<typename Fun, typename... Args>
		struct call<Fun(Args...)>
			: public sprout::breed::transform<sprout::breed::call<Fun(Args...)> >
		{
		public:
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			private:
				template<typename A>
				struct a_ {
				public:
					typedef typename sprout::breed::when<sprout::breed::_, A>::template impl<
						Expr,
						State,
						Data
					> type;
				};
				template<typename... Args>
				struct fun_ {
				public:
					typedef Fun type(typename a_<Args>::type::result_type...);
				};
				template<typename... Args>
				struct function_
					: public sprout::breed::detail::poly_function_traits<
						Fun,
						typename fun_<Args...>::type
					>
				{};
			public:
				template<long N>
				struct a {
				public:
					typedef typename a_<typename sprout::tppack_at<N, Args...>::type>::type type;
				};
				template<long N>
				struct b {
				public:
					typedef typename a_<typename sprout::tppack_at<N, Args...>::type>::type::result_type type;
				};
				typedef function_<Args...> function_traits;
				typedef typename function_traits::result_type result_type;
				SPROUT_CONSTEXPR result_type operator ()(
					typename impl2::expr_param e,
					typename impl2::state_param s,
					typename impl2::data_param d
					) const
				{
					return typename function_traits::function_type()(
						sprout::breed::detail::as_lvalue(typename a_<Args>::type()(e, s, d))...
					);
				}
			};
		};
		//
		// is_callable
		//
		template<typename Fun>
		struct is_callable<sprout::breed::call<Fun> >
			: public std::true_type
		{};
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_TRANSFORM_CALL_HPP
