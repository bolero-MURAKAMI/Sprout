#ifndef TESTSPR_TYPEINFO_HPP
#define TESTSPR_TYPEINFO_HPP

#if defined(__GNUC__)
#	include <cstdlib>
#endif
#include <string>
#include <typeinfo>
#if defined(__GNUC__)
#	include <cxxabi.h>
#endif

namespace testspr {
	//
	// typename_of
	//
#if defined(__GNUC__)
	namespace detail {
		std::string gcc_demangle(char const* mangled) {
			int status;
			char* demangled = abi::__cxa_demangle(mangled, 0, 0, &status);
			std::string result(demangled);
			std::free(demangled);
			return result;
		}
	}	// namespace detail
	template<typename T>
	std::string typename_of() {
		return testspr::detail::gcc_demangle(typeid(T).name());
	}
#else
	template<typename T>
	std::string typename_of() {
		return std::string(typeid(T).name());
	}
#endif
}	// namespace testspr

#endif	// #ifndef TESTSPR_TYPEINFO_HPP
