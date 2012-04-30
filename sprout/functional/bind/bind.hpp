#ifndef SPROUT_FUNCTIONAL_BIND_BIND_HPP
#define SPROUT_FUNCTIONAL_BIND_BIND_HPP

#include <cstddef>
#include <utility>
#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/functional/ref.hpp>
#include <sprout/functional/mem_fn.hpp>
#include <sprout/functional/weak_result_type.hpp>

namespace sprout {
	// 20.8.9 bind

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

	template<typename T>
	struct is_placeholder
		: public std::integral_constant<int, 0>
	{};
	template<typename T>
	struct is_placeholder<T const>
		: public sprout::is_placeholder<T>
	{};
	template<typename T>
	struct is_placeholder<T volatile>
		: public sprout::is_placeholder<T>
	{};
	template<typename T>
	struct is_placeholder<T const volatile>
		: public sprout::is_placeholder<T>
	{};

	//
	// placeholder
	//
	template<int N>
	struct placeholder {};

	namespace placeholders {
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<1> _1{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<2> _2{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<3> _3{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<4> _4{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<5> _5{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<6> _6{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<7> _7{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<8> _8{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<9> _9{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<10> _10{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<11> _11{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<12> _12{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<13> _13{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<14> _14{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<15> _15{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<16> _16{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<17> _17{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<18> _18{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<19> _19{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<20> _20{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<21> _21{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<22> _22{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<23> _23{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<24> _24{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<25> _25{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<26> _26{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<27> _27{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<28> _28{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<29> _29{};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<30> _30{};
		}	// anonymous-namespace
	}	// namespace placeholders
	using sprout::placeholders::_1;
	using sprout::placeholders::_2;
	using sprout::placeholders::_3;
	using sprout::placeholders::_4;
	using sprout::placeholders::_5;
	using sprout::placeholders::_6;
	using sprout::placeholders::_7;
	using sprout::placeholders::_8;
	using sprout::placeholders::_9;
	using sprout::placeholders::_10;
	using sprout::placeholders::_11;
	using sprout::placeholders::_12;
	using sprout::placeholders::_13;
	using sprout::placeholders::_14;
	using sprout::placeholders::_15;
	using sprout::placeholders::_16;
	using sprout::placeholders::_17;
	using sprout::placeholders::_18;
	using sprout::placeholders::_19;
	using sprout::placeholders::_20;
	using sprout::placeholders::_21;
	using sprout::placeholders::_2;
	using sprout::placeholders::_23;
	using sprout::placeholders::_24;
	using sprout::placeholders::_25;
	using sprout::placeholders::_26;
	using sprout::placeholders::_27;
	using sprout::placeholders::_28;
	using sprout::placeholders::_29;
	using sprout::placeholders::_30;

	template<int N>
	struct is_placeholder<sprout::placeholder<N> >
		: public std::integral_constant<int, N>
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
				// !!!
				//return arg.get();
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
				return call(arg, tuple, typename sprout::index_range<0, sizeof...(Args)>::type());
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
	struct binder;
	template<typename Functor, typename... BoundArgs>
	class binder<Functor(BoundArgs...)>
		: public sprout::weak_result_type<Functor>
	{
	private:
		typedef binder self_type;
		typedef typename sprout::index_range<0, sizeof...(BoundArgs)>::type bound_indexes;
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
	// bind_result
	//
	template<typename Result, typename Signature>
	struct bind_result;
	template<typename Result, typename Functor, typename... BoundArgs>
	class bind_result<Result, Functor(BoundArgs...)> {
	private:
		typedef bind_result self_type;
		typedef typename sprout::index_range<0, sizeof...(BoundArgs)>::type bound_indexes;
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
			f_(sprout::detail::mu<BoundArgs>()(get<Indexes>(bound_args_), args)...);
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
		explicit bind_result(Functor const& f, Args&&... args)
			: f_(f)
			, bound_args_(sprout::forward<Args>(args)...)
		{}
		bind_result(bind_result const&) = default;
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

	template<typename Signature>
	struct is_bind_expression<sprout::binder<Signature> >
		: public std::true_type
	{};
	template<typename Result, typename Signature>
	struct is_bind_expression<sprout::bind_result<Result, Signature> >
		: public std::true_type
	{};

	namespace detail {
		template<typename Func, typename... BoundArgs>
		struct bind_helper {
		public:
			typedef sprout::detail::maybe_wrap_member_pointer<typename std::decay<Func>::type> maybe_type;
			typedef typename maybe_type::type func_type;
			typedef sprout::binder<func_type (typename std::decay<BoundArgs>::type...)> type;
		};

		template<typename Result, typename Func, typename... BoundArgs>
		struct bindres_helper {
		public:
			typedef sprout::detail::maybe_wrap_member_pointer<typename std::decay<Func>::type> maybe_type;
			typedef typename maybe_type::type functor_type;
			typedef sprout::bind_result<Result, functor_type (typename std::decay<BoundArgs>::type...)> type;
		};
	}	// namespace detail

	//
	// bind
	//
	template<typename F, typename... BoundArgs>
	inline SPROUT_CONSTEXPR typename sprout::detail::bind_helper<F, BoundArgs...>::type
	bind(F&& f, BoundArgs&&... args) {
		typedef sprout::detail::bind_helper<F, BoundArgs...> helper_type;
		typedef typename helper_type::maybe_type maybe_type;
		typedef typename helper_type::type result_type;
		return result_type(maybe_type::do_wrap(sprout::forward<F>(f)), sprout::forward<BoundArgs>(args)...);
	}
	template<typename R, typename F, typename... BoundArgs>
	inline SPROUT_CONSTEXPR typename sprout::detail::bindres_helper<R, F, BoundArgs...>::type
	bind(F&& f, BoundArgs&&... args) {
		typedef sprout::detail::bindres_helper<R, F, BoundArgs...> helper_type;
		typedef typename helper_type::maybe_type maybe_type;
		typedef typename helper_type::type result_type;
		return result_type(maybe_type::do_wrap(sprout::forward<F>(f)), sprout::forward<BoundArgs>(args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND_BIND_HPP
