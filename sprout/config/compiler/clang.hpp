#ifndef SPROUT_CONFIG_COMPILER_CLANG_HPP
#define SPROUT_CONFIG_COMPILER_CLANG_HPP

#if !__has_feature(cxx_constexpr)
#	define SPROUT_NO_CONSTEXPR
#endif

#if !__has_feature(cxx_defaulted_functions)
#	define SPROUT_NO_DEFAULTED_FUNCTIONS
#endif

#if !__has_feature(cxx_deleted_functions)
#	define SPROUT_NO_DELETED_FUNCTIONS
#endif

#if !__has_feature(cxx_noexcept)
#	define SPROUT_NO_NOEXCEPT
#endif

#if !__has_feature(cxx_alias_templates)
#	define SPROUT_NO_TEMPLATE_ALIASES
#endif

#if !__has_feature(cxx_user_literals)
#	define SPROUT_NO_USER_DEFINED_LITERALS
#endif

#if !__has_feature(cxx_delegating_constructors)
#	define SPROUT_NO_DELEGATING_CONSTRUCTORS
#endif

#if !__has_feature(cxx_unicode_literals)
#	define SPROUT_NO_UNICODE_LITERALS
#endif

#if !defined(SPROUT_NO_CONSTEXPR)
#	define SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
#endif

#endif	// #ifndef SPROUT_CONFIG_COMPILER_CLANG_HPP
