#ifndef SPROUT_BREED_TRANSFORM_WHEN_HPP
#define SPROUT_BREED_TRANSFORM_WHEN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/type/iterator/deref.hpp>
#include <sprout/type/seq/algorithm/find_if.hpp>
#include <sprout/breed/breed_fwd.hpp>
#include <sprout/breed/traits.hpp>
#include <sprout/breed/transform/call.hpp>
#include <sprout/breed/transform/make.hpp>
#include <sprout/breed/transform/impl.hpp>

namespace sprout {
	namespace breed {
		//
		// when
		//
		template<typename Grammar, typename PrimitiveTransform>
		struct when
			: public PrimitiveTransform
		{
		public:
			typedef Grammar first;
			typedef PrimitiveTransform second;
			typedef typename Grammar::breed_grammar breed_grammar;
		};
		template<typename Grammar, typename Fun>
		struct when<Grammar, Fun*>
			: public sprout::breed::when<Grammar, Fun>
		{};
		template<typename Grammar>
		struct when<Grammar, sprout::breed::external_transform>
			: public sprout::breed::transform<when<Grammar, sprout::breed::external_transform> >
		{
		public:
			typedef Grammar first;
			typedef external_transform second;
			typedef typename Grammar::breed_grammar breed_grammar;
		public:
			template<typename Expr, typename State, typename Data>
			struct impl
				: public Data::template when<Grammar>::template impl<Expr, State, Data>
			{};
			template<typename Expr, typename State, typename Data>
			struct impl<Expr, State, Data&>
				: public Data::template when<Grammar>::template impl<Expr, State, Data&>
			{};
		};
		template<typename Grammar, typename R, typename... Args>
		struct when<Grammar, R(Args...)>
			: public sprout::breed::transform<when<Grammar, R(Args...)> >
		{
		public:
			typedef Grammar first;
			typedef R second(Args...);
			typedef typename Grammar::breed_grammar breed_grammar;
		public:
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			public:
				typedef typename std::conditional<
					sprout::breed::is_callable<R>::value,
					sprout::breed::call<R(Args...)>,
					sprout::breed::make<R(Args...)>
				>::type which;
				typedef typename which::template impl<Expr, State, Data>::result_type result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(
					typename impl::expr_param e,
					typename impl::state_param s,
					typename impl::data_param d
					) const
				{
					return typename which::template impl<Expr, State, Data>()(e, s, d);
				}
			};
		};
		//
		// is_callable
		//
		template<typename Grammar, typename Transform>
		struct is_callable<sprout::breed::when<Grammar, Transform> >
			: public std::true_type
		{};
		//
		// otherwise
		//
		template<typename Fun>
		struct otherwise
			: public sprout::breed::when<sprout::breed::_, Fun>
		{};
		//
		// external_transforms
		//
		template<typename... Args>
		struct external_transforms {
		public:
			typedef sprout::types::type_tuple<Args...> map_type;
		private:
			template<typename Rule>
			struct map_pred {
			public:
				template<typename T>
				struct apply
					: public std::is_same<Rule, typename T::first>
				{};
			};
		public:
			template<typename Rule>
			struct when
				: public sprout::breed::when<
					sprout::breed::_,
					sprout::types::deref<
						typename sprout::types::find_if<map_type, map_pred<Rule> >::type
					>::type
				>
			{};
		};
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_TRANSFORM_WHEN_HPP
