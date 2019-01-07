/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_TYPEINFO_HPP
#define TESTSPR_TYPEINFO_HPP

//
// TESTSPR_HAS_CXXABI_H
//
#if defined(__clang__)
#	if defined(__has_include) && __has_include(<cxxabi.h>)
#		define TESTSPR_HAS_CXXABI_H
#	endif
#elif defined(__GNUC__) && !defined(__QNX__)
#	define TESTSPR_HAS_CXXABI_H
#endif

#include <string>
#include <utility>
#include <typeinfo>
#ifdef TESTSPR_HAS_CXXABI_H
#	include <cstdlib>
#	include <cxxabi.h>
#endif
#include <sprout/config.hpp>

namespace testspr {
	//
	// id
	//
	template<typename T>
	struct id {
	public:
		typedef T type;
	};

	//
	// demangle
	//
#ifdef TESTSPR_HAS_CXXABI_H
	namespace detail {
		inline SPROUT_NON_CONSTEXPR char*
		demangle_alloc(char const* name) {
			int status = 0;
			return abi::__cxa_demangle(name, 0, 0, &status);
		}
		inline SPROUT_NON_CONSTEXPR void
		demangle_free(char* demangled) {
			std::free(demangled);
		}
		class scoped_demangled_name {
		private:
			char* demangled_;
		public:
			explicit SPROUT_NON_CONSTEXPR scoped_demangled_name(char const* name) SPROUT_NOEXCEPT
				: demangled_(testspr::detail::demangle_alloc(name))
			{}
			~scoped_demangled_name() SPROUT_NOEXCEPT {
				testspr::detail::demangle_free(demangled_);
			}
			SPROUT_NON_CONSTEXPR char const* get() const SPROUT_NOEXCEPT {
				return demangled_;
			}
		};
	}	// namespace detail

	inline SPROUT_NON_CONSTEXPR std::string
	demangle(char const* name) {
		testspr::detail::scoped_demangled_name demangled(name);
		return demangled.get() ? demangled.get() : name;
	}
#else
	inline SPROUT_NON_CONSTEXPR std::string
	demangle(char const* name) {
		return name;
	}
#endif
	inline SPROUT_NON_CONSTEXPR std::string
	demangle(std::string const& name) {
		return testspr::demangle(name.c_str());
	}

	//
	// typename_of
	//
	inline SPROUT_NON_CONSTEXPR std::string
	typename_of(std::type_info const& t) {
		return testspr::demangle(t.name());
	}
	template<typename T>
	inline SPROUT_NON_CONSTEXPR std::string
	typename_of() {
		return testspr::typename_of(typeid(T));
	}
	template<typename T>
	inline SPROUT_NON_CONSTEXPR std::string
	typename_of(T&& t) {
		return testspr::typename_of(typeid(std::forward<T>(t)));
	}

	//
	// strip_outer_template
	//
	inline SPROUT_NON_CONSTEXPR std::string
	strip_outer_template(std::string const& s) {
		std::string::size_type f = s.find('<');
		if (f == std::string::npos) {
			return s;
		}
		std::string::size_type l = s.rfind('>');
		if (l == std::string::npos || f > l) {
			return s;
		}
		return s.substr(f + 1, l - f - 1);
	}

	//
	// qualified_typename_of
	//
	template<typename T>
	inline SPROUT_NON_CONSTEXPR std::string
	qualified_typename_of() {
		return testspr::strip_outer_template(testspr::typename_of<testspr::id<T> >());
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_TYPEINFO_HPP
