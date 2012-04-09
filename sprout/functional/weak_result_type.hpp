#ifndef SPROUT_FUNCTIONAL_WEAK_RESULT_TYPE_HPP
#define SPROUT_FUNCTIONAL_WEAK_RESULT_TYPE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>
#include <sprout/type_traits/inherit_if_xxx.hpp>

namespace sprout {
	namespace detail {
		//
		// has_result_type
		// has_argument_type
		// has_first_argument_type
		// has_second_argument_type
		//
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(result_type);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(argument_type);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(first_argument_type);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(second_argument_type);

		//
		// inherit_if_result_type
		// inherit_if_argument_type
		// inherit_if_first_argument_type
		// inherit_if_second_argument_type
		//
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(result_type);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(argument_type);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(first_argument_type);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(second_argument_type);

		template<typename F>
		struct weak_result_type_impl
			: public sprout::detail::inherit_if_result_type<F>
		{};
		template<typename F>
		struct weak_result_type_impl<F const>
			: public sprout::detail::weak_result_type_impl<F>
		{};
		template<typename F>
		struct weak_result_type_impl<F volatile>
			: public sprout::detail::weak_result_type_impl<F>
		{};
		template<typename F>
		struct weak_result_type_impl<F const volatile>
			: public sprout::detail::weak_result_type_impl<F>
		{};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (Args...)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (Args......)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (&)(Args...)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (&)(Args......)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (*)(Args...)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (*)(Args......)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename Class, typename... Args>
		struct weak_result_type_impl<R (Class::*)(Args...)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename Class, typename... Args>
		struct weak_result_type_impl<R (Class::*)(Args......)> {
		public:
			typedef R result_type;
		};
	}	// namespace detail

	//
	// weak_result_type
	//
	template<typename F>
	struct weak_result_type
		: public sprout::detail::weak_result_type_impl<typename std::remove_cv<F>::type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_WEAK_RESULT_TYPE_HPP
