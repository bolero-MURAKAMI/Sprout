#ifndef SPROUT_CTYPE_FUNCTOR_HPP
#define SPROUT_CTYPE_FUNCTOR_HPP

#include <sprout/config.hpp>
#include <sprout/ctype/mask.hpp>
#include <sprout/ctype/ascii.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace ctypes {
		//
		// is_alnum
		//
		template<typename T = void>
		struct is_alnum {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isalnum(x);
			}
		};
		template<>
		struct is_alnum<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_alnum<T>()(x);
			}
		};

		//
		// is_alpha
		//
		template<typename T = void>
		struct is_alpha {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isalpha(x);
			}
		};
		template<>
		struct is_alpha<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_alpha<T>()(x);
			}
		};

		//
		// is_blank
		//
		template<typename T = void>
		struct is_blank {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isblank(x);
			}
		};
		template<>
		struct is_blank<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_blank<T>()(x);
			}
		};

		//
		// is_cntrl
		//
		template<typename T = void>
		struct is_cntrl {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::iscntrl(x);
			}
		};
		template<>
		struct is_cntrl<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_cntrl<T>()(x);
			}
		};

		//
		// is_digit
		//
		template<typename T = void>
		struct is_digit {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isdigit(x);
			}
		};
		template<>
		struct is_digit<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_digit<T>()(x);
			}
		};

		//
		// is_graph
		//
		template<typename T = void>
		struct is_graph {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isgraph(x);
			}
		};
		template<>
		struct is_graph<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_graph<T>()(x);
			}
		};

		//
		// is_lower
		//
		template<typename T = void>
		struct is_lower {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::islower(x);
			}
		};
		template<>
		struct is_lower<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_lower<T>()(x);
			}
		};

		//
		// is_print
		//
		template<typename T = void>
		struct is_print {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isprint(x);
			}
		};
		template<>
		struct is_print<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_print<T>()(x);
			}
		};

		//
		// is_punct
		//
		template<typename T = void>
		struct is_punct {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ispunct(x);
			}
		};
		template<>
		struct is_punct<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_punct<T>()(x);
			}
		};

		//
		// is_space
		//
		template<typename T = void>
		struct is_space {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isspace(x);
			}
		};
		template<>
		struct is_space<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_space<T>()(x);
			}
		};

		//
		// is_upper
		//
		template<typename T = void>
		struct is_upper {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isupper(x);
			}
		};
		template<>
		struct is_upper<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_upper<T>()(x);
			}
		};

		//
		// is_xdigit
		//
		template<typename T = void>
		struct is_xdigit {
		public:
			typedef T argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isxdigit(x);
			}
		};
		template<>
		struct is_xdigit<void> {
		public:
			typedef bool result_type;
		public:
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_xdigit<T>()(x);
			}
		};

		//
		// to_lower
		//
		template<typename T = void>
		struct to_lower {
		public:
			typedef T argument_type;
			typedef T result_type;
		public:
			SPROUT_CONSTEXPR T
			operator()(T const& x) const {
				return sprout::tolower(x);
			}
		};
		template<>
		struct to_lower<void> {
		public:
			template<typename T>
			SPROUT_CONSTEXPR T
			operator()(T const& x) const {
				return sprout::ctypes::to_lower<T>()(x);
			}
		};

		//
		// to_upper
		//
		template<typename T = void>
		struct to_upper {
		public:
			typedef T argument_type;
			typedef T result_type;
		public:
			SPROUT_CONSTEXPR T
			operator()(T const& x) const {
				return sprout::toupper(x);
			}
		};
		template<>
		struct to_upper<void> {
		public:
			template<typename T>
			SPROUT_CONSTEXPR T
			operator()(T const& x) const {
				return sprout::ctypes::to_upper<T>()(x);
			}
		};

		//
		// is_classified
		//
		template<typename T = void>
		struct is_classified {
		public:
			typedef T argument_type;
			typedef bool result_type;
		private:
			sprout::ctypes::mask_t m_;
		public:
			explicit SPROUT_CONSTEXPR is_classified(sprout::ctypes::mask_t m)
				: m_(m)
			{}
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::isclassified(m_, x);
			}
		};
		template<>
		struct is_classified<void> {
		public:
			typedef bool result_type;
		private:
			sprout::ctypes::mask_t m_;
		public:
			explicit SPROUT_CONSTEXPR is_classified(sprout::ctypes::mask_t m)
				: m_(m)
			{}
			template<typename T>
			SPROUT_CONSTEXPR bool
			operator()(T const& x) const {
				return sprout::ctypes::is_classified<T>(m_)(x);
			}
		};

		//
		// nocase_equal_to
		//
		template<typename T = void>
		struct nocase_equal_to {
		public:
			typedef T first_argument_type;
			typedef T second_argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool operator()(T const& x, T const& y) const {
					return sprout::tolower(x) == sprout::tolower(y);
			}
		};
		template<>
		struct nocase_equal_to<void> {
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(sprout::tolower(std::declval<T>()) == sprout::tolower(std::declval<U>()))
			operator()(T&& x, U&& y)
			const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tolower(std::declval<T>()) == sprout::tolower(std::declval<U>())))
			{
				return sprout::tolower(sprout::forward<T>(x)) == sprout::tolower(sprout::forward<U>(y));
			}
		};

		//
		// nocase_not_equal_to
		//
		template<typename T = void>
		struct nocase_not_equal_to {
		public:
			typedef T first_argument_type;
			typedef T second_argument_type;
			typedef bool result_type;
		public:
			SPROUT_CONSTEXPR bool operator()(T const& x, T const& y) const {
					return sprout::tolower(x) != sprout::tolower(y);
			}
		};
		template<>
		struct nocase_not_equal_to<void> {
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(sprout::tolower(std::declval<T>()) != sprout::tolower(std::declval<U>()))
			operator()(T&& x, U&& y)
			const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::tolower(std::declval<T>()) != sprout::tolower(std::declval<U>())))
			{
				return sprout::tolower(sprout::forward<T>(x)) != sprout::tolower(sprout::forward<U>(y));
			}
		};
	}	// namespace ctypes
}	// namespace sprout

#endif	// #ifndef SPROUT_CTYPE_FUNCTOR_HPP
