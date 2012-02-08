#ifndef SPROUT_BREED_EVAL_HPP
#define SPROUT_BREED_EVAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/breed/breed_fwd.hpp>

namespace sprout {
	namespace breed {
		namespace result_of {
			//
			// eval
			//
			template<typename Expr, typename Context>
			struct eval {
			public:
				typedef typename Context::template eval<Expr>::result_type type;
			};
		}	// namespace result_of

		namespace functional {
			//
			// eval
			//
			struct eval {
			public:
				SPROUT_BREED_CALLABLE();
			public:
				template<typename Sig>
				struct result;
				template<typename This, typename Expr, typename Context>
				struct result<This(Expr, Context)> {
					typedef typename sprout::breed::result_of::eval<
						typename std::remove_reference<Expr>::type,
						typename std::remove_reference<Context>::type
					>::type type;
				};
				template<typename Expr, typename Context>
				typename sprout::breed::result_of::eval<Expr, Context>::type
				operator()(Expr& e, Context& ctx) const {
					return typename Context::template eval<Expr>()(e, ctx);
				}
				template<typename Expr, typename Context>
				typename sprout::breed::result_of::eval<Expr, Context>::type
				operator()(Expr& e, Context const& ctx) const {
					return typename Context::template eval<Expr>()(e, ctx);
				}
				template<typename Expr, typename Context>
				typename sprout::breed::result_of::eval<Expr const, Context>::type
				operator()(Expr const& e, Context& ctx) const {
					return typename Context::template eval<Expr const>()(e, ctx);
				}
				template<typename Expr, typename Context>
				SPROUT_CONSTEXPR typename sprout::breed::result_of::eval<Expr const, Context>::type
				operator()(Expr const& e, Context const& ctx) const {
					return typename Context::template eval<Expr const>()(e, ctx);
				}
			};
		}	// namespace functional

		//
		// eval
		//
		template<typename Expr, typename Context>
		typename sprout::breed::result_of::eval<Expr, Context>::type
		eval(Expr& e, Context& ctx) {
			return typename Context::template eval<Expr>()(e, ctx);
		}
		template<typename Expr, typename Context>
		typename sprout::breed::result_of::eval<Expr, Context>::type
		eval(Expr& e, Context const& ctx) {
			return typename Context::template eval<Expr>()(e, ctx);
		}
		template<typename Expr, typename Context>
		typename sprout::breed::result_of::eval<Expr const, Context>::type
		eval(Expr const& e, Context& ctx) {
			return typename Context::template eval<Expr const>()(e, ctx);
		}
		template<typename Expr, typename Context>
		typename sprout::breed::result_of::eval<Expr const, Context>::type
		SPROUT_CONSTEXPR eval(Expr const& e, Context const& ctx) {
			return typename Context::template eval<Expr const>()(e, ctx);
		}
		}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_EVAL_HPP
