#ifndef SPROUT_BREED_ARGS_HPP
#define SPROUT_BREED_ARGS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/breed/breed_fwd.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			template<typename T>
			struct ref_only
				: public std::integral_constant<
					bool,
					std::is_function<T>::value
				>
			{};

			template<typename Expr>
			struct expr_traits {
			public:
				typedef Expr value_type;
				typedef Expr& reference;
				typedef Expr const& const_reference;
			};
			template<typename Expr>
			struct expr_traits<Expr&> {
			public:
				typedef Expr value_type;
				typedef Expr& reference;
				typedef Expr& const_reference;
			};
			template<typename Expr>
			struct expr_traits<Expr const&> {
			public:
				typedef Expr value_type;
				typedef Expr const& reference;
				typedef Expr const& const_reference;
			};

			template<typename T>
			struct term_traits {
			public:
				typedef T value_type;
				typedef T& reference;
				typedef T const& const_reference;
			};
			template<typename T>
			struct term_traits<T&> {
			public:
				typedef typename std::conditional<sprout::breed::detail::ref_only<T>::value, T&, T>::type value_type;
				typedef T& reference;
				typedef T& const_reference;
			};
			template<typename T>
			struct term_traits<T const&> {
			public:
				typedef T value_type;
				typedef T const& reference;
				typedef T const& const_reference;
			};
			template<typename T, std::size_t N>
			struct term_traits<T (&)[N]> {
			public:
				typedef T value_type[N];
				typedef T (&reference)[N];
				typedef T (&const_reference)[N];
			};
			template<typename T, std::size_t N>
			struct term_traits<T const (&)[N]> {
			public:
				typedef T value_type[N];
				typedef T const (&reference)[N];
				typedef T const (&const_reference)[N];
			};
			template<typename T, std::size_t N>
			struct term_traits<T[N]> {
			public:
				typedef T value_type[N];
				typedef T (&reference)[N];
				typedef T const (&const_reference)[N];
			};
			template<typename T, std::size_t N>
			struct term_traits<T const[N]> {
			public:
				typedef T value_type[N];
				typedef T const (&reference)[N];
				typedef T const (&const_reference)[N];
			};
		}	// namespace detail

		namespace argsns_ {
			//
			// term
			//
			template<typename Arg>
			struct term {
			public:
				SPROUT_STATIC_CONSTEXPR long arity = 0;
			public:
				template<long N>
				struct child
					: public sprout::tppack_at<N, Arg>
				{};
			public:
				typedef Arg back_;
			};
			//
			// list
			//
			template<typename... Args>
			struct list {
			public:
				SPROUT_STATIC_CONSTEXPR long arity = sizeof...(Args);
			public:
				template<long N>
				struct child
					: public sprout::tppack_at<N, Args...>
				{};
			public:
				typedef typename child<sizeof...(Args) - 1>::type back_;
			};
		}	// namespace argsns_ {
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_ARGS_HPP
