#ifndef SPROUT_BREED_TRANSFORM_IMPL_HPP
#define SPROUT_BREED_TRANSFORM_IMPL_HPP

#include <sprout/config.hpp>
#include <sprout/breed/breed_fwd.hpp>

namespace sprout {
	namespace breed {
		//
		// SPROUT_BREED_TRANSFORM_
		//
#		define SPROUT_BREED_TRANSFORM_(PrimitiveTransform, X) \
		public: \
			SPROUT_BREED_CALLABLE() \
			typedef X breed_is_transform_; \
			typedef PrimitiveTransform transform_type; \
		public: \
			template<typename Sig> \
			struct result { \
			public: \
				typedef typename sprout::breed::detail::apply_transform<Sig>::result_type type; \
			}; \
			template<typename Expr> \
			SPROUT_CONSTEXPR typename sprout::breed::detail::apply_transform< \
				transform_type(Expr const&) \
			>::result_type operator()(Expr&& e) const { \
				return sprout::breed::detail::apply_transform< \
					transform_type(Expr const&) \
				>()(e, 0, 0); \
			} \
			template<typename Expr, typename State> \
			SPROUT_CONSTEXPR typename sprout::breed::detail::apply_transform< \
				transform_type(Expr const&, State const&) \
			>::result_type operator()(Expr&& e, State&& s) const \
			{ \
				return sprout::breed::detail::apply_transform< \
					transform_type(Expr const&, State const&) \
				>()(e, s, 0); \
			} \
			template<typename Expr, typename State, typename Data> \
			SPROUT_CONSTEXPR typename sprout::breed::detail::apply_transform< \
				transform_type(Expr const&, State const&, Data const&) \
			>::result_type operator()(Expr&& e, State&& s, Data&& d) const { \
				return sprout::breed::detail::apply_transform< \
					transform_type(Expr const&, State const&, Data const&) \
				>()(e, s, d); \
			}
		//
		// SPROUT_BREED_TRANSFORM
		//
#		define SPROUT_BREED_TRANSFORM(PrimitiveTransform) \
			SPROUT_BREED_TRANSFORM_(PrimitiveTransform, void)

		namespace detail {
			template<typename Sig>
			struct apply_transform;
			template<typename PrimitiveTransform, typename Expr>
			struct apply_transform<PrimitiveTransform(Expr)>
				: public PrimitiveTransform::template impl<Expr, int, int>
			{};
			template<typename PrimitiveTransform, typename Expr, typename State>
			struct apply_transform<PrimitiveTransform(Expr, State)>
				: public PrimitiveTransform::template impl<Expr, State, int>
			{};
			template<typename PrimitiveTransform, typename Expr, typename State, typename Data>
			struct apply_transform<PrimitiveTransform(Expr, State, Data)>
				: public PrimitiveTransform::template impl<Expr, State, Data>
			{};
		}	// namespace detail

		//
		// transform
		//
		template<typename PrimitiveTransform, typename X>
		struct transform {
		public:
			SPROUT_BREED_TRANSFORM_(PrimitiveTransform, X);
		};

		//
		// transform_impl
		//
		template<typename Expr, typename State, typename Data>
		struct transform_impl {
		public:
			typedef Expr const expr;
			typedef Expr const& expr_param;
			typedef State const state;
			typedef State const& state_param;
			typedef Data const data;
			typedef Data const& data_param;
		};
		template<typename Expr, typename State, typename Data>
		struct transform_impl<Expr&, State, Data> {
		public:
			typedef Expr expr;
			typedef Expr& expr_param;
			typedef State const state;
			typedef State const& state_param;
			typedef Data const data;
			typedef Data const& data_param;
		};
		template<typename Expr, typename State, typename Data>
		struct transform_impl<Expr, State&, Data> {
		public:
			typedef Expr const expr;
			typedef Expr const& expr_param;
			typedef State state;
			typedef State& state_param;
			typedef Data const data;
			typedef Data const& data_param;
		};
		template<typename Expr, typename State, typename Data>
		struct transform_impl<Expr, State, Data&> {
		public:
			typedef Expr const expr;
			typedef Expr const& expr_param;
			typedef State const state;
			typedef State const& state_param;
			typedef Data data;
			typedef Data& data_param;
		};
		template<typename Expr, typename State, typename Data>
		struct transform_impl<Expr&, State&, Data> {
		public:
			typedef Expr expr;
			typedef Expr& expr_param;
			typedef State state;
			typedef State& state_param;
			typedef Data const data;
			typedef Data const& data_param;
		};
		template<typename Expr, typename State, typename Data>
		struct transform_impl<Expr&, State, Data&> {
		public:
			typedef Expr expr;
			typedef Expr& expr_param;
			typedef State const state;
			typedef State const& state_param;
			typedef Data data;
			typedef Data& data_param;
		};
		template<typename Expr, typename State, typename Data>
		struct transform_impl<Expr, State&, Data&> {
		public:
			typedef Expr const expr;
			typedef Expr const& expr_param;
			typedef State state;
			typedef State& state_param;
			typedef Data data;
			typedef Data& data_param;
		};
		template<typename Expr, typename State, typename Data>
		struct transform_impl<Expr&, State&, Data&> {
		public:
			typedef Expr expr;
			typedef Expr& expr_param;
			typedef State state;
			typedef State& state_param;
			typedef Data data;
			typedef Data& data_param;
		};
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_TRANSFORM_IMPL_HPP
