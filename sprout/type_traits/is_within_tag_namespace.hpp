/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_TAG_NAMESPACE_HPP
#define SPROUT_TYPE_TRAITS_IS_WITHIN_TAG_NAMESPACE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/preprocessor/cat.hpp>
#include <sprout/preprocessor/empty.hpp>
#include <sprout/adl/not_found.hpp>
#include <sprout/detail/do_nothing_statement.hpp>

//
// SPROUT_ADL_TEST_TAG_DECL
//
#define SPROUT_ADL_TEST_TAG_DECL(NAME) \
	namespace sprout_adl_test { \
		struct SPROUT_PP_CAT(NAME, _tag); \
	} SPROUT_DETAIL_DO_NOTHING_STATEMENT_WITHIN_NAMESPACE
//
// SPROUT_ADL_TESTER_DECL
//
#define SPROUT_ADL_TESTER_DECL(NAME) \
	SPROUT_ADL_TEST_TAG_DECL(NAME); \
	template<typename T> \
	void sprout_adl_tester(sprout_adl_test::SPROUT_PP_CAT(NAME, _tag)*&&, T&&)

//
// SPROUT_ADL_TEST_TAG
//
#define SPROUT_ADL_TEST_TAG(NAME) \
	sprout_adl_test::SPROUT_PP_CAT(NAME, _tag)

//
// SPROUT_IS_WITHIN_NAMESPACE_DECL
//
#define SPROUT_IS_WITHIN_NAMESPACE_DECL(NAME, NAMESPACE) \
	template<typename T> \
	struct SPROUT_PP_CAT(is_within_namespace_, NAME) \
		: public sprout::is_within_tag_namespace<NAMESPACE::SPROUT_ADL_TEST_TAG(NAME), T> \
	{}; \
	SPROUT_IS_WITHIN_NAMESPACE_V(NAME, NAMESPACE)
#if SPROUT_USE_VARIABLE_TEMPLATES
#	define SPROUT_IS_WITHIN_NAMESPACE_V(NAME, NAMESPACE) \
		template<typename T> \
		SPROUT_STATIC_CONSTEXPR bool SPROUT_PP_CAT(SPROUT_PP_CAT(is_within_namespace_, NAME), _v) = SPROUT_PP_CAT(is_within_namespace_, NAME)<T>::value
#else	// #if SPROUT_USE_VARIABLE_TEMPLATES
#	define SPROUT_IS_WITHIN_NAMESPACE_V(NAME, NAMESPACE) \
		SPROUT_DETAIL_DO_NOTHING_STATEMENT_WITHIN_NAMESPACE
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES

namespace sprout_adl {
	sprout::not_found_via_adl sprout_adl_tester(...);
}	// namespace sprout_adl

namespace sprout_adl_tester_detail {
	using sprout_adl::sprout_adl_tester;

	template<typename Tag, typename T>
	struct is_within_namespace_test {
	public:
		template<
			typename Tag0 = Tag, typename U = T,
			typename R = typename sprout::identity<decltype(sprout_adl_tester(std::declval<Tag0*>(), std::declval<U>()))>::type
		>
		static sprout::is_found_via_adl<R> test(int);
		static sprout::false_type test(...);
	};
}	// namespace sprout_adl_tester_detail

namespace sprout {
	//
	// is_within_tag_namespace
	//
#if defined(_MSC_VER) && (_MSC_VER > 1900)
	namespace detail {
		template<typename Tag, typename T, typename Base_ = typename sprout::identity<decltype(sprout_adl_tester_detail::is_within_namespace_test<Tag, T>::test(0))>::type>
		struct is_within_tag_namespace_impl
			: public Base_
		{};
	}	// namespace detail
	template<typename Tag, typename T>
	struct is_within_tag_namespace
		: public sprout::detail::is_within_tag_namespace_impl<Tag, T>
	{};
#else
	template<typename Tag, typename T>
	struct is_within_tag_namespace
		: public sprout::identity<decltype(sprout_adl_tester_detail::is_within_namespace_test<Tag, T>::test(0))>::type
	{};
#endif

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename Tag, typename T>
	SPROUT_STATIC_CONSTEXPR bool is_within_tag_namespace_v = sprout::is_within_tag_namespace<Tag, T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_TAG_NAMESPACE_HPP
