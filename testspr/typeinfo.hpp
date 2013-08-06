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
#include <typeinfo>
#ifdef TESTSPR_HAS_CXXABI_H
#	include <cstdlib>
#	include <cxxabi.h>
#endif

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
	// typename_of
	//
#ifdef TESTSPR_HAS_CXXABI_H
	namespace detail {
		std::string cxa_demangle(char const* mangled) {
			int status;
			char* demangled = abi::__cxa_demangle(mangled, 0, 0, &status);
			std::string result(demangled);
			std::free(demangled);
			return result;
		}
	}	// namespace detail
	template<typename T>
	inline std::string typename_of() {
		return testspr::detail::cxa_demangle(typeid(T).name());
	}
#else
	template<typename T>
	inline std::string typename_of() {
		return std::string(typeid(T).name());
	}
#endif
}	// namespace testspr

#endif	// #ifndef TESTSPR_TYPEINFO_HPP
