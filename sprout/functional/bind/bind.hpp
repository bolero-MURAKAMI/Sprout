#ifndef SPROUT_FUNCTIONAL_BIND_BIND_HPP
#define SPROUT_FUNCTIONAL_BIND_BIND_HPP

#include <cstddef>
#include <utility>
#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/tuple/tuple/make_tuple.hpp>
#include <sprout/functional/ref.hpp>
#include <sprout/functional/mem_fn.hpp>
#include <sprout/functional/type_traits/weak_result_type.hpp>
#include <sprout/functional/bind/placeholder.hpp>

namespace sprout {
	// 20.8.9 bind

	//
	// is_bind_expression
	//
	template<typename T>
	struct is_bind_expression
		: public std::false_type
	{};
	template<typename T>
	struct is_bind_expression<T const>
		: public sprout::is_bind_expression<T>
	{};
	template<typename T>
	struct is_bind_expression<T volatile>
		: public sprout::is_bind_expression<T>
	{};
	template<typename T>
	struct is_bind_expression<T const volatile>
		: public sprout::is_bind_expression<T>
	{};

	namespace detail {
		struct no_tuple_element;

		template<std::size_t I, typename Tuple, bool IsSafe>
		struct safe_tuple_element_impl
			: tuple_element<I, Tuple>
		{};
		template<std::size_t I, typename Tuple>
		struct safe_tuple_element_impl<I, Tuple, false> {
		public:
			typedef sprout::detail::no_tuple_element type;
		};
		template<std::size_t I, typename Tuple>
		struct safe_tuple_element
			: public sprout::detail::safe_tuple_element_impl<I, Tuple, (I < sprout::tuples::tuple_size<Tuple>::value)>
		{};

		template<
			typename Arg,
			bool IsBindExp = sprout::is_bind_expression<Arg>::value,
			bool IsPlaceholder = (sprout::is_placeholder<Arg>::value > 0)
		>
		class mu;
		template<typename T>
		class mu<sprout::reference_wrapper<T>, false, false> {
		public:
			typedef T& result_type;
		public:
			template<typename CVRef, typename Tuple>
			SPROUT_CONSTEXPR result_type operator()(CVRef& arg, Tuple&) const volatile {
				//return arg.get();	// ???
				return const_cast<typename std::remove_volatile<typename std::remove_reference<CVRef>::type>::type&>(arg).get();
			}
		};
		template<typename Arg>
		class mu<Arg, true, false> {
		private:
			template<typename CVArg, typename... Args, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR auto call(
				CVArg& arg,
				sprout::tuples::tuple<Args...>& tuple,
				sprout::index_tuple<Indexes...>
				) const volatile
			-> decltype(arg(std::declval<Args>()...))
			{
				return arg(sprout::forward<Args>(sprout::tuples::get<Indexes>(tuple))...);
			}
		public:
			template<typename CVArg, typename... Args>
			SPROUT_CONSTEXPR auto operator()(CVArg& arg, sprout::tuples::tuple<Args...>& tuple) const volatile
			-> decltype(arg(std::declval<Args>()...))
			{
				return call(arg, tuple, sprout::index_pack<Args...>::make());
			}
		};
		template<typename Arg>
		class mu<Arg, false, true> {
		public:
			template<typename Signature>
			class result;
			template<typename CVMu, typename CVArg, typename Tuple>
			class result<CVMu (CVArg, Tuple)> {
			private:
				typedef typename sprout::detail::safe_tuple_element<
					(sprout::is_placeholder<Arg>::value - 1),
					Tuple
				>::type base_type;
			public:
				typedef typename std::add_rvalue_reference<base_type>::type type;
			};
		public:
			template<typename Tuple>
			typename result<mu (Arg, Tuple)>::type
			SPROUT_CONSTEXPR operator()(Arg const volatile&, Tuple& tuple) const volatile {
				return sprout::forward<typename result<mu (Arg, Tuple)>::type>(
					sprout::tuples::get<(sprout::is_placeholder<Arg>::value - 1)>(tuple)
					);
			}
		};
		template<typename Arg>
		class mu<Arg, false, false> {
		public:
			template<typename Signature>
			struct result;
			template<typename CVMu, typename CVArg, typename Tuple>
			struct result<CVMu (CVArg, Tuple)> {
			public:
				typedef typename std::add_lvalue_reference<CVArg>::type type;
			};
		public:
			template<typename CVArg, typename Tuple>
			SPROUT_CONSTEXPR CVArg&& operator()(CVArg&& arg, Tuple&) const volatile {
				return sprout::forward<CVArg>(arg);
			}
		};

		template<typename T>
		struct maybe_wrap_member_pointer {
		public:
			typedef T type;
		public:
			static SPROUT_CONSTEXPR T const& do_wrap(T const& x) {
				return x;
			}
			static SPROUT_CONSTEXPR T&& do_wrap(T&& x) {
				return static_cast<T&&>(x);
			}
		};
		template<typename T, typename Class>
		struct maybe_wrap_member_pointer<T Class::*> {
		public:
			typedef sprout::mem_fn_adaptor<T Class::*> type;
		public:
			static SPROUT_CONSTEXPR type do_wrap(T Class::* pm) {
				return type(pm);
			}
		};
		template<>
		struct maybe_wrap_member_pointer<void> {
		public:
			typedef void type;
		};

		template<std::size_t I, typename... Types>
		inline auto volget(sprout::tuples::tuple<Types...> volatile& tuple)
		-> typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type volatile&
		{
			return sprout::tuples::get<I>(const_cast<sprout::tuples::tuple<Types...>&>(tuple));
		}
		template<std::size_t I, typename... Types>
		inline SPROUT_CONSTEXPR auto volget(sprout::tuples::tuple<Types...> const volatile& tuple)
		-> typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type const volatile&
		{
			return sprout::tuples::get<I>(const_cast<sprout::tuples::tuple<Types...> const&>(tuple));
		}
	}	// namespace detail

	//
	// binder
	//
	template<typename Signature>
	class binder;
	template<typename Functor, typename... BoundArgs>
	class binder<Functor(BoundArgs...)>
		: public sprout::weak_result_type<Functor>
	{
	private:
		typedef binder self_type;
		typedef typename sprout::index_pack<BoundArgs...>::type bound_indexes;
	private:
		Functor f_;
		sprout::tuples::tuple<BoundArgs...> bound_args_;
	private:
		template<typename Result, typename... Args, sprout::index_t... Indexes>
		Result call(sprout::tuples::tuple<Args...>&& args, sprout::index_tuple<Indexes...>) {
			return f_(sprout::detail::mu<BoundArgs>()(sprout::tuples::get<Indexes>(bound_args_), args)...);
		}
		template<typename Result, typename... Args, sprout::index_t... Indexes>
		SPROUT_CONSTEXPR Result call_c(sprout::tuples::tuple<Args...>&& args, sprout::index_tuple<Indexes...>) const {
			return f_(sprout::detail::mu<BoundArgs>()(sprout::tuples::get<Indexes>(bound_args_), args)...);
		}
		template<typename Result, typename... Args, sprout::index_t... Indexes>
		Result call_v(sprout::tuples::tuple<Args...>&& args, sprout::index_tuple<Indexes...>) volatile {
			return f_(sprout::detail::mu<BoundArgs>()(sprout::detail::volget<Indexes>(bound_args_), args)...);
		}
		template<typename Result, typename... Args, sprout::index_t... Indexes>
		SPROUT_CONSTEXPR Result call_cv(sprout::tuples::tuple<Args...>&& args, sprout::index_tuple<Indexes...>) const volatile {
			return f_(sprout::detail::mu<BoundArgs>()(sprout::detail::volget<Indexes>(bound_args_), args)...);
		}
		public:
		template<typename... Args>
		explicit SPROUT_CONSTEXPR binder(Functor const& f, Args&&... args)
			: f_(f)
			, bound_args_(sprout::forward<Args>(args)...)
		{}
		binder(binder const&) = default;
		template<
			typename... Args,
			typename Result = decltype(
				std::declval<Functor>()(
					sprout::detail::mu<BoundArgs>()(
						std::declval<BoundArgs&>(),
						std::declval<sprout::tuples::tuple<Args...>&>()
						)...
					)
				)
		>
		Result operator()(Args&&... args) {
			return call<Result>(
				sprout::tuples::forward_as_tuple(sprout::forward<Args>(args)...),
				bound_indexes()
				);
		}
		template<
			typename... Args,
			typename Result = decltype(
				std::declval<typename std::enable_if<(sizeof...(Args) >= 0), typename std::add_const<Functor>::type>::type>()(
					sprout::detail::mu<BoundArgs>()(
						std::declval<BoundArgs const&>(),
						std::declval<sprout::tuples::tuple<Args...>&>()
						)...
					)
				)
		>
		SPROUT_CONSTEXPR Result operator()(Args&&... args) const {
			return call_c<Result>(
				sprout::tuples::forward_as_tuple(sprout::forward<Args>(args)...),
				bound_indexes()
				);
		}
		template<
			typename... Args,
			typename Result = decltype(
				std::declval<typename std::enable_if<(sizeof...(Args) >= 0), typename std::add_volatile<Functor>::type>::type>()(
					sprout::detail::mu<BoundArgs>()(
						std::declval<BoundArgs volatile&>(),
						std::declval<sprout::tuples::tuple<Args...>&>()
						)...
					)
				)
		>
		Result operator()(Args&&... args) volatile {
			return call_v<Result>(
				sprout::tuples::forward_as_tuple(sprout::forward<Args>(args)...),
				bound_indexes()
				);
		}

		template<
			typename... Args,
			typename Result = decltype(
				std::declval<typename std::enable_if<(sizeof...(Args) >= 0), typename std::add_cv<Functor>::type>::type>()(
					sprout::detail::mu<BoundArgs>()(
						std::declval<BoundArgs const volatile&>(),
						std::declval<sprout::tuples::tuple<Args...>&>()
						)...
					)
				)
		>
		SPROUT_CONSTEXPR Result operator()(Args&&... args) const volatile {
			return call_cv<Result>(
				sprout::tuples::forward_as_tuple(sprout::forward<Args>(args)...),
				bound_indexes()
				);
		}
	};

	//
	// res_binder
	//
	template<typename Result, typename Signature>
	class res_binder;
	template<typename Result, typename Functor, typename... BoundArgs>
	class res_binder<Result, Functor(BoundArgs...)> {
	private:
		typedef res_binder self_type;
		typedef typename sprout::index_pack<BoundArgs...>::type bound_indexes;
	private:
		template<typename Res>
		struct enable_if_void
			: public std::enable_if<std::is_void<Res>::value, int>
		{};
		template<typename Res>
		struct disable_if_void
			: public std::enable_if<!std::is_void<Res>::value, int>
		{};
	private:
		Functor f_;
		sprout::tuples::tuple<BoundArgs...> bound_args_;
	private:
		template<typename Res, typename... Args, sprout::index_t... Indexes>
		Result call(
			sprout::tuples::tuple<Args...>&& args,
			sprout::index_tuple<Indexes...>,
			typename disable_if_void<Res>::type = 0
			)
		{
			return f_(sprout::detail::mu<BoundArgs>()(sprout::tuples::get<Indexes>(bound_args_), args)...);
		}
		template<typename Res, typename... Args, sprout::index_t... Indexes>
		Result call(
			sprout::tuples::tuple<Args...>&& args,
			sprout::index_tuple<Indexes...>,
			typename enable_if_void<Res>::type = 0
			)
		{
			f_(sprout::detail::mu<BoundArgs>()(sprout::tuples::get<Indexes>(bound_args_), args)...);
		}
		template<typename Res, typename... Args, sprout::index_t... Indexes>
		SPROUT_CONSTEXPR Result call(
			sprout::tuples::tuple<Args...>&& args,
			sprout::index_tuple<Indexes...>,
			typename disable_if_void<Res>::type = 0
			) const
		{
			return f_(sprout::detail::mu<BoundArgs>()(sprout::tuples::get<Indexes>(bound_args_), args)...);
		}
		template<typename Res, typename... Args, sprout::index_t... Indexes>
		Result call(
			sprout::tuples::tuple<Args...>&& args,
			sprout::index_tuple<Indexes...>,
			typename enable_if_void<Res>::type = 0
			) const
		{
			f_(sprout::detail::mu<BoundArgs>()(sprout::tuples::get<Indexes>(bound_args_), args)...);
		}
		template<typename Res, typename... Args, sprout::index_t... Indexes>
		Result call(
			sprout::tuples::tuple<Args...>&& args,
			sprout::index_tuple<Indexes...>,
			typename disable_if_void<Res>::type = 0
			) volatile
		{
			return f_(sprout::detail::mu<BoundArgs>()(sprout::detail::volget<Indexes>(bound_args_), args)...);
		}
		template<typename Res, typename... Args, sprout::index_t... Indexes>
		Result call(
			sprout::tuples::tuple<Args...>&& args,
			sprout::index_tuple<Indexes...>,
			typename enable_if_void<Res>::type = 0
			) volatile
		{
			f_(sprout::detail::mu<BoundArgs>()(sprout::detail::volget<Indexes>(bound_args_), args)...);
		}
		template<typename Res, typename... Args, sprout::index_t... Indexes>
		SPROUT_CONSTEXPR Result call(
			sprout::tuples::tuple<Args...>&& args,
			sprout::index_tuple<Indexes...>,
			typename disable_if_void<Res>::type = 0
			) const volatile
		{
			return f_(sprout::detail::mu<BoundArgs>()(sprout::detail::volget<Indexes>(bound_args_), args)...);
		}
		template<typename Res, typename... Args, sprout::index_t... Indexes>
		Result call(
			sprout::tuples::tuple<Args...>&& args,
			sprout::index_tuple<Indexes...>,
			typename enable_if_void<Res>::type = 0
			) const volatile
		{
			f_(sprout::detail::mu<BoundArgs>()(sprout::detail::volget<Indexes>(bound_args_), args)...);
		}
	public:
		typedef Result result_type;
		template<typename... Args>
		explicit res_binder(Functor const& f, Args&&... args)
			: f_(f)
			, bound_args_(sprout::forward<Args>(args)...)
		{}
		res_binder(res_binder const&) = default;
		template<typename... Args>
		result_type operator()(Args&&... args) {
			return call<Result>(
				sprout::tuples::forward_as_tuple(sprout::forward<Args>(args)...),
				bound_indexes()
				);
		}
		template<typename... Args>
		SPROUT_CONSTEXPR result_type operator()(Args&&... args) const {
			return call<Result>(
				sprout::tuples::forward_as_tuple(sprout::forward<Args>(args)...),
				bound_indexes()
				);
		}
		template<typename... Args>
		result_type operator()(Args&&... args) volatile {
			return call<Result>(
				sprout::tuples::forward_as_tuple(sprout::forward<Args>(args)...),
				bound_indexes()
				);
		}
		template<typename... Args>
		SPROUT_CONSTEXPR result_type operator()(Args&&... args) const volatile {
			return call<Result>(
				sprout::tuples::forward_as_tuple(sprout::forward<Args>(args)...),
				bound_indexes()
				);
		}
	};

	//
	// is_bind_expression
	//
	template<typename Signature>
	struct is_bind_expression<sprout::binder<Signature> >
		: public std::true_type
	{};
	template<typename Result, typename Signature>
	struct is_bind_expression<sprout::res_binder<Result, Signature> >
		: public std::true_type
	{};

	namespace detail {
		template<sprout::index_t Index, typename BoundArg, typename = void>
		struct complete_placeholder {
		public:
			typedef BoundArg type;
		};
		template<sprout::index_t Index, typename BoundArg>
		struct complete_placeholder<
			Index, BoundArg,
			typename std::enable_if<(sprout::is_placeholder<BoundArg>::value == -1)>::type
		> {
		public:
			typedef sprout::placeholder<Index + 1> type;
		};

		template<typename Func, typename IndexTuple, typename... BoundArgs>
		struct binder_complete_placeholders_impl;
		template<typename Func, typename... BoundArgs, sprout::index_t... Indexes>
		struct binder_complete_placeholders_impl<Func, sprout::index_tuple<Indexes...>, BoundArgs...> {
		public:
			typedef sprout::binder<Func (typename sprout::detail::complete_placeholder<Indexes, BoundArgs>::type...)> type;
		};
		template<typename Func, typename... BoundArgs>
		struct binder_complete_placeholders
			: public sprout::detail::binder_complete_placeholders_impl<Func, typename sprout::index_pack<BoundArgs...>::type, BoundArgs...>
		{};

		template<typename Result, typename Func, typename IndexTuple, typename... BoundArgs>
		struct res_binder_complete_placeholders_impl;
		template<typename Result, typename Func, typename... BoundArgs, sprout::index_t... Indexes>
		struct res_binder_complete_placeholders_impl<Result, Func, sprout::index_tuple<Indexes...>, BoundArgs...> {
		public:
			typedef sprout::res_binder<Result, Func (typename sprout::detail::complete_placeholder<Indexes, BoundArgs>::type...)> type;
		};
		template<typename Result, typename Func, typename... BoundArgs>
		struct res_binder_complete_placeholders
			: public sprout::detail::res_binder_complete_placeholders_impl<Result, Func, typename sprout::index_pack<BoundArgs...>::type, BoundArgs...>
		{};

		template<typename Func, typename... BoundArgs>
		struct bind_helper {
		public:
			typedef sprout::detail::maybe_wrap_member_pointer<typename std::decay<Func>::type> maybe_type;
			typedef typename maybe_type::type func_type;
			typedef typename sprout::detail::binder_complete_placeholders<func_type, typename std::decay<BoundArgs>::type...>::type type;
//			typedef sprout::binder<func_type (typename std::decay<BoundArgs>::type...)> type;
		};
		template<typename Result, typename Func, typename... BoundArgs>
		struct res_bind_helper {
		public:
			typedef sprout::detail::maybe_wrap_member_pointer<typename std::decay<Func>::type> maybe_type;
			typedef typename maybe_type::type functor_type;
			typedef typename sprout::detail::res_binder_complete_placeholders<Result, functor_type, typename std::decay<BoundArgs>::type...>::type type;
//			typedef sprout::res_binder<Result, functor_type (typename std::decay<BoundArgs>::type...)> type;
		};
	}	// namespace detail

	//
	// bind_result
	// res_bind_result
	//
	template<typename F, typename... BoundArgs>
	struct bind_result {
	public:
		typedef typename sprout::detail::bind_helper<F, BoundArgs...>::type type;
	};
	template<typename R, typename F, typename... BoundArgs>
	struct res_bind_result {
	public:
		typedef typename sprout::detail::res_bind_helper<R, F, BoundArgs...>::type type;
	};

	//
	// bind
	//
	template<typename F, typename... BoundArgs>
	inline SPROUT_CONSTEXPR typename sprout::bind_result<F, BoundArgs...>::type
	bind(F&& f, BoundArgs&&... args) {
		typedef sprout::detail::bind_helper<F, BoundArgs...> helper_type;
		typedef typename helper_type::maybe_type maybe_type;
		typedef typename helper_type::type result_type;
		return result_type(maybe_type::do_wrap(sprout::forward<F>(f)), sprout::forward<BoundArgs>(args)...);
	}
	template<typename R, typename F, typename... BoundArgs>
	inline SPROUT_CONSTEXPR typename sprout::res_bind_result<R, F, BoundArgs...>::type
	bind(F&& f, BoundArgs&&... args) {
		typedef sprout::detail::res_bind_helper<R, F, BoundArgs...> helper_type;
		typedef typename helper_type::maybe_type maybe_type;
		typedef typename helper_type::type result_type;
		return result_type(maybe_type::do_wrap(sprout::forward<F>(f)), sprout::forward<BoundArgs>(args)...);
	}

	//
	// cbind
	//
	template<typename F, typename... BoundArgs>
	inline SPROUT_CONSTEXPR typename sprout::detail::bind_helper<F, BoundArgs...>::type const
	cbind(F&& f, BoundArgs&&... args) {
		return sprout::bind(sprout::forward<F>(f), sprout::forward<BoundArgs>(args)...);
	}
	template<typename R, typename F, typename... BoundArgs>
	inline SPROUT_CONSTEXPR typename sprout::detail::res_bind_helper<R, F, BoundArgs...>::type const
	cbind(F&& f, BoundArgs&&... args) {
		return sprout::bind<R>(sprout::forward<F>(f), sprout::forward<BoundArgs>(args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND_BIND_HPP
