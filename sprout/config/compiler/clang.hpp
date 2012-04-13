#ifndef SPROUT_CONFIG_COMPILER_CLANG_HPP
#define SPROUT_CONFIG_COMPILER_CLANG_HPP

#if !__has_feature(cxx_constexpr)
#	define SPROUT_NO_CONSTEXPR
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

#endif	// #ifndef SPROUT_CONFIG_COMPILER_CLANG_HPP
