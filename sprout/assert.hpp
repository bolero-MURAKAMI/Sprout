#ifndef SPROUT_ASEERT_HPP
#define SPROUT_ASEERT_HPP

#if defined(SPROUT_DISABLE_ASSERTS) || defined(NDEBUG)
#	include <sprout/config.hpp>
#elif defined(SPROUT_ENABLE_ASSERT_HANDLER)
#	include <sprout/config.hpp>
#	include <sprout/adl/not_found.hpp>
#else
#	include <cstdlib>
#	include <iostream>
#	include <sprout/config.hpp>
#endif
#if !(defined(SPROUT_DISABLE_ASSERTS) || defined(NDEBUG))
#	include <sprout/preprocessor/stringize.hpp>
#endif

#if !(defined(SPROUT_DISABLE_ASSERTS) || defined(NDEBUG))
	//
	// SPROUT_ASSERTION_FAILED_FORMAT
	//
#	ifndef SPROUT_ASSERTION_FAILED_FORMAT
#		define SPROUT_ASSERTION_FAILED_FORMAT(expr, file, line) \
			"***** Internal Program Error - assertion (" #expr ") failed: " file "(" SPROUT_PP_STRINGIZE(line) ")"
#	endif
#endif

//
// SPROUT_ASSERT
//

#if defined(SPROUT_DISABLE_ASSERTS) || defined(NDEBUG)

namespace sprout {
	namespace detail {
		inline SPROUT_CONSTEXPR bool
		assertion_disabled() SPROUT_NOEXCEPT {
			return true;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_ASSERT(expr) \
		(sprout::detail::assertion_disabled())

#elif defined(SPROUT_ENABLE_ASSERT_HANDLER)

namespace sprout_adl {
	SPROUT_CONSTEXPR sprout::not_found_via_adl assertion_failed(...);
}	// namespace sprout_adl

namespace sprout_assertion_detail {
	using sprout_adl::assertion_failed;

	//template<typename Dummy>
	inline SPROUT_CONSTEXPR bool
	call_assertion_failed(bool cond, char const* formatted, char const* expr, char const* function, char const* file, long line) {
		return cond ? true
			: (assertion_failed(expr, function, file, line), false)
			;
	}
}	// namespace sprout

namespace sprout {
//	//
//	// assertion_failed
//	//	* user defined
//	//
//	void
//	assertion_failed(char const* expr, char const* function, char const* file, long line);

	namespace detail {
		inline SPROUT_CONSTEXPR bool
		assertion_check(bool cond, char const* formatted, char const* expr, char const* function, char const* file, long line) {
			return cond ? true
				: sprout_assertion_detail::call_assertion_failed(cond, formatted, expr, function, file, line)
				;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_ASSERT(expr) ( \
		sprout::detail::assertion_check( \
			(expr), SPROUT_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__), \
			#expr, "(unknown)"/*SPROUT_CURRENT_FUNCTION*/, __FILE__, __LINE__) \
		)

#else

namespace sprout {
	namespace detail {
		inline bool
		assertion_failed(char const* formatted) {
			return (std::cerr << formatted << std::endl), std::abort(), false;
		}
		inline SPROUT_CONSTEXPR bool
		assertion_check(bool cond, char const* formatted) {
			return cond ? true
				: sprout::detail::assertion_failed(formatted)
				;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_ASSERT(expr) \
		(sprout::detail::assertion_check((expr), SPROUT_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__)))

#endif

//
// SPROUT_ASSERT_MSG
//

#if defined(SPROUT_DISABLE_ASSERTS) || defined(NDEBUG)

#	define SPROUT_ASSERT_MSG(expr, msg) \
		(sprout::detail::assertion_disabled())

#elif defined(SPROUT_ENABLE_ASSERT_HANDLER)

namespace sprout {
	//
	// assertion_failed_msg
	//	* user defined
	//
	void
	assertion_failed_msg(char const* expr, char const* msg, char const* function, char const* file, long line);

	namespace detail {
		inline bool
		assertion_failed_msg(char const* formatted, char const* expr, char const* msg, char const* function, char const* file, long line) {
			return sprout::assertion_failed_msg(expr, msg, function, file, line), false;
		}
		inline SPROUT_CONSTEXPR bool
		assertion_check_msg(bool cond, char const* formatted, char const* expr, char const* msg, char const* function, char const* file, long line) {
			return cond ? true
				: sprout::detail::assertion_failed_msg(formatted, expr, msg, function, file, line)
				;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_ASSERT_MSG(expr, msg) ( \
		sprout::detail::assertion_check_msg( \
			(expr), SPROUT_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__), \
			#expr, msg, "(unknown)"/*SPROUT_CURRENT_FUNCTION*/, __FILE__, __LINE__) \
		)

#else

namespace sprout {
	namespace detail {
		inline bool
		assertion_failed_msg(char const* formatted, char const* msg) {
			return (std::cerr << formatted << ": " << msg << std::endl), std::abort(), false;
		}
		inline SPROUT_CONSTEXPR bool
		assertion_check_msg(bool cond, char const* formatted, char const* msg) {
			return cond ? true
				: sprout::detail::assertion_failed_msg(formatted, msg)
				;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_ASSERT_MSG(expr, msg) \
		(sprout::detail::assertion_check_msg((expr), SPROUT_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__), msg))

#endif

//
// SPROUT_VERIFY
//

#if defined(SPROUT_DISABLE_ASSERTS) || (!defined(SPROUT_ENABLE_ASSERT_HANDLER) && defined(NDEBUG))

namespace sprout {
	namespace detail {
		inline SPROUT_CONSTEXPR bool
		verification_disabled(bool) SPROUT_NOEXCEPT {
			return true;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_VERIFY(expr) \
		(sprout::detail::verification_disabled((expr)))

#else

#	define SPROUT_VERIFY(expr) SPROUT_ASSERT(expr)

#endif

#endif	// #ifndef SPROUT_ASEERT_HPP
