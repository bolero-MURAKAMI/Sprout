#ifndef SPROUT_BREED_DETAIL_POLY_FUNCTION_HPP
#define SPROUT_BREED_DETAIL_POLY_FUNCTION_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/breed/breed_fwd.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			template<typename T>
			struct normalize_arg {
			public:
				typedef T type;
				typedef T const& reference;
			};
			template<typename T>
			struct normalize_arg<T&> {
			public:
				typedef T type;
				typedef T const& reference;
			};
			template<typename T>
			struct normalize_arg<T const&> {
			public:
				typedef T type;
				typedef T const& reference;
			};

			template<typename T>
			struct arg {
			public:
				typedef T const& type;
			private:
				type value;
			public:
				SPROUT_CONSTEXPR arg(type t)
					: value(t)
				{}
				SPROUT_CONSTEXPR operator type() const {
					return this->value;
				}
				SPROUT_CONSTEXPR type operator()() const {
					return *this;
				}
			private:
				arg& operator=(arg const&) SPROUT_DELETED_FUNCTION_DECL
			};
			template<typename T>
			struct arg<T&> {
			public:
				typedef T& type;
			private:
				type value;
			public:
				SPROUT_CONSTEXPR arg(type t)
					: value(t)
				{}
				SPROUT_CONSTEXPR operator type() const {
					return this->value;
				}
				SPROUT_CONSTEXPR type operator()() const {
					return *this;
				}
			private:
				arg& operator=(arg const&) SPROUT_DELETED_FUNCTION_DECL
			};

			template<typename T, typename Void = void>
			struct is_poly_function
				: public std::false_type
			{};
			template<typename T>
			struct is_poly_function<T, typename T::is_poly_function_base_>
				: public std::true_type
			{};

#			define SPROUT_BREED_POLY_FUNCTION() \
			typedef void is_poly_function_base_;

			struct poly_function_base {
			public:
				SPROUT_BREED_POLY_FUNCTION();
			};

			template<typename Derived, typename NullaryResult = void>
			struct poly_function
				: public psprout::breed::detail::poly_function_base
			{
			public:
				template<typename Sig>
				struct result;
				template<typename This>
				struct result<This()>
					: public Derived::template impl<>
				{
				public:
					typedef typename result::result_type type;
				};
				template<typename This, typename... Args>
				struct result<This(Args...)>
					: public Derived::template impl<
						typename normalize_arg<Args>::type...
					>
				{
				public:
					typedef typename result::result_type type;
				};
			public:
				SPROUT_CONSTEXPR NullaryResult operator()() const {
					return result<Derived const()>().operator()();
				}
				template<typename... Args>
				SPROUT_CONSTEXPR typename result<Derived const(Args const&...)>::type
				operator()(Args const&... args) const {
					return result<Derived const(Args const&...)>().operator()(
						static_cast<typename normalize_arg<Args const&>::reference>(args)...
						);
				}
			};

			template<typename T>
			struct wrap_t;

			typedef char poly_function_t;
			typedef char (&mono_function_t)[2];
			typedef char (&unknown_function_t)[3];

			template<typename T> sprout::breed::detail::poly_function_t test_poly_function(
				T const*,
				sprout::breed::detail::wrap_t<typename T::is_poly_function_base_> const* = 0
				);
			template<typename T> sprout::breed::detail::mono_function_t test_poly_function(
				T const*,
				sprout::breed::detail::wrap_t<typename T::result_type> const* = 0
				);
			template<typename T> sprout::breed::detail::unknown_function_t test_poly_function(
				T const*,
				...
				);

			template<
				typename Fun,
				typename Sig,
				typename Switch = std::integral_constant<
					std::size_t,
					sizeof(sprout::breed::detail::test_poly_function<Fun>(0, 0))
				>
			>
			struct poly_function_traits {
			public:
				typedef typename Fun::template result<Sig>::type result_type;
				typedef Fun function_type;
			};
			template<typename Fun, typename Sig>
			struct poly_function_traits<
				Fun,
				Sig,
				std::integral_constant<
					std::size_t,
					sizeof(sprout::breed::detail::mono_function_t)
				>
			> {
			public:
				typedef typename Fun::result_type result_type;
				typedef Fun function_type;
			};
			template<typename PolyFun, typename... Args>
			struct poly_function_traits<
				PolyFun,
				PolyFun(
					Args...,
					std::integral_constant<std::size_t, sizeof(sprout::breed::detail::poly_function_t)
					)
			> {
			public:
				typedef typename PolyFun::template impl<Args...> function_type;
				typedef typename function_type::result_type result_type;
			};

			template<typename PolyFunSig, bool IsPolyFunction>
			struct as_mono_function_impl;
			template<typename PolyFun, typename... Args>
			struct as_mono_function_impl<PolyFun(Args...), true> {
			public:
				typedef typename PolyFun::template impl<Args const...> type;
			};
			template<typename PolyFun, typename... Args>
			struct as_mono_function_impl<PolyFun(Args...), false> {
			public:
				typedef PolyFun type;
			};

			template<typename PolyFunSig>
			struct as_mono_function;
			template<typename PolyFun, typename... Args>
			struct as_mono_function<PolyFun(Args...)>
				: public sprout::breed::detail::as_mono_function_impl<
					PolyFun(Args...),
					sprout::breed::detail::is_poly_function<PolyFun>::value
				>
			{};
		}	// namespace detail
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_DETAIL_POLY_FUNCTION_HPP
