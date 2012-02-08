#ifndef SPROUT_BREED_DOMAIN_HPP
#define SPROUT_BREED_DOMAIN_HPP

#include <functional>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/breed/breed_fwd.hpp>
#include <sprout/breed/generate.hpp>
#include <sprout/breed/detail/as_expr.hpp>
#include <sprout/breed/detail/deduce_domain.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			struct not_a_generator {};
			struct not_a_grammar {};
			struct not_a_domain {};
		}	// namespace detail

		namespace domainns_ {
			//
			// domain
			//
			template<
				typename Generator,
				typename Grammar,
				typename Super
			>
			struct domain
				: public Generator
			{
			public:
				typedef Generator breed_generator;
				typedef Grammar breed_grammar;
				typedef Super breed_super_domain;
				typedef domain breed_base_domain;
				typedef void breed_is_domain_;
			public:
				template<typename T, typename IsExpr = void, typename Callable = sprout::breed::callable>
				struct as_expr
					: public detail::as_expr<
						T,
						typename sprout::breed::detail::base_generator<Generator>::type,
						sprout::breed::wants_basic_expr<Generator>::value
					>
				{
				public:
					SPROUT_BREED_CALLABLE()
				};
				template<typename T>
				struct as_expr<T, typename T::breed_is_expr_, sprout::breed::callable> {
				public:
					SPROUT_BREED_CALLABLE()
				public:
					typedef typename std::remove_const<T>::type result_type;
				public:
					SPROUT_CONSTEXPR result_type operator()(T const& e) const {
						return e;
					}
				};
				template<typename T, typename IsExpr = void, typename Callable = sprout::breed::callable>
				struct as_child
					: public detail::as_child<
						T,
						typename sprout::breed::detail::base_generator<Generator>::type,
						sprout::breed::wants_basic_expr<Generator>::value
					>
				{
				public:
					SPROUT_BREED_CALLABLE()
				};
				template<typename T>
				struct as_child<T, typename T::breed_is_expr_, sprout::breed::callable> {
				public:
					SPROUT_BREED_CALLABLE()
				public:
					typedef T &result_type;
				public:
					SPROUT_CONSTEXPR result_type operator()(T const& e) const {
						return e;
					}
				};
			};

			//
			// default_domain
			//
			struct default_domain
				: public sprout::breed::domain<>
			{};

			//
			// basic_default_domain
			//
			struct basic_default_domain
				: public sprout::breed::domain<sprout::breed::basic_default_generator>
			{};

			//
			// deduce_domain
			//
			struct deduce_domain
				: public sprout::breed::domain<
					sprout::breed::detail::not_a_generator,
					sprout::breed::detail::not_a_grammar,
					sprout::breed::detail::not_a_domain
				>
			{};

			//
			// base_expr
			//
			template<typename Domain, typename Tag, typename Args, bool WantsBasicExpr>
			struct base_expr {
			public:
				typedef sprout::breed::expr<Tag, Args, Args::arity> type;
			};
			template<typename Domain, typename Tag, typename Args>
			struct base_expr<Domain, Tag, Args, true> {
			public:
				typedef sprout::breed::basic_expr<Tag, Args, Args::arity> type;
			};
		}	// namespace domainns_

		//
		// is_domain
		//
		template<typename T, typename Void>
		struct is_domain
			: public std::false_type
		{};
		template<typename T>
		struct is_domain<T, typename T::breed_is_domain_>
			: public std::true_type
		{};

		//
		// domain_of
		//
		template<typename T, typename Void>
		struct domain_of {
		public:
			typedef sprout::breed::default_domain type;
		};
		template<typename T>
		struct domain_of<T, typename T::breed_is_expr_> {
		public:
			typedef typename T::breed_domain type;
		};
		template<typename T>
		struct domain_of<T&, void> {
		public:
			typedef typename sprout::breed::domain_of<T>::type type;
		};
		template<typename T>
		struct domain_of<std::reference_wrapper<T>, void> {
		public:
			typedef typename sprout::breed::domain_of<T>::type type;
		};
		template<typename T>
		struct domain_of<std::reference_wrapper<T> const, void> {
			typedef typename sprout::breed::domain_of<T>::type type;
		};

		//
		// is_sub_domain_of
		//
		template<typename SubDomain, typename SuperDomain>
		struct is_sub_domain_of
			: public is_sub_domain_of<typename SubDomain::breed_super_domain, SuperDomain>
		{};
		template<typename SuperDomain>
		struct is_sub_domain_of<sprout::breed::no_super_domain, SuperDomain>
			: public std::false_type
		{};
		template<typename SuperDomain>
		struct is_sub_domain_of<SuperDomain, SuperDomain>
			: public std::true_type
		{};
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_DOMAIN_HPP
