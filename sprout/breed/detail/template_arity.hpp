#ifndef SPROUT_BREED_DETAIL_TEMPLATE_ARITY_HPP
#define SPROUT_BREED_DETAIL_TEMPLATE_ARITY_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			template<typename F>
			struct template_arity_impl;
			template<template<typename...> class F, typename... Args>
			struct template_arity_impl<F<Args...> >
				: public std::integral_constant<int, sizeof...(Args)>
			{};

			template<typename F>
			struct template_arity
				: public sprout::breed::detail::template_arity_impl<F>
			{};
		}	// namespace detail
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_DETAIL_TEMPLATE_ARITY_HPP
