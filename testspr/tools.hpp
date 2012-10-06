#ifndef TESTSPR_TOOLS_HPP
#define TESTSPR_TOOLS_HPP

#include <cassert>
#include <iterator>
#include <sprout/config.hpp>
#include <sprout/container.hpp>
#ifdef TESTSPR_CONFIG_ENABLE_STATIC_WARNING
#	include <boost/serialization/static_warning.hpp>
#endif

//
// TESTSPR_STATIC_ASSERT
// TESTSPR_ASSERT
// TESTSPR_BOTH_ASSERT
//
#define TESTSPR_STATIC_ASSERT(expr) static_assert(expr, #expr)
#define TESTSPR_ASSERT(expr) assert(expr)
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define TESTSPR_BOTH_ASSERT(expr) TESTSPR_STATIC_ASSERT(expr); TESTSPR_ASSERT(expr)
#else	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define TESTSPR_BOTH_ASSERT(expr) TESTSPR_ASSERT(expr)
#endif	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

//
// TESTSPR_STATIC_WARNING
//
#ifdef TESTSPR_CONFIG_ENABLE_STATIC_WARNING
#	define TESTSPR_STATIC_WARNING(expr) BOOST_STATIC_WARNING(expr)
#else
#	define TESTSPR_STATIC_WARNING(expr)
#endif

//
// TESTSPR_STATIC_UNCHECKED
// TESTSPR_UNCHECKED
// TESTSPR_BOTH_UNCHECKED
//
#define TESTSPR_STATIC_UNCHECKED(expr) TESTSPR_STATIC_WARNING(expr)
#define TESTSPR_UNCHECKED(expr) (expr)
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define TESTSPR_BOTH_UNCHECKED(expr) TESTSPR_STATIC_UNCHECKED(expr); TESTSPR_UNCHECKED(expr)
#else	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define TESTSPR_BOTH_UNCHECKED(expr) TESTSPR_UNCHECKED(expr)
#endif	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

namespace testspr {
	//
	// is_even
	//
	template<typename T>
	struct is_even {
	public:
		typedef T argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& t) const { return t % 2 == 0; }
	};
	//
	// is_odd
	//
	template<typename T>
	struct is_odd {
	public:
		typedef T argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& t) const { return t % 2 != 0; }
	};
	//
	// is_multiple_of
	//
	template<typename T, typename U = T>
	struct is_multiple_of {
	public:
		typedef T first_argument_type;
		typedef U second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& t, U const& u) const { return t % u == 0; }
	};

	//
	// less
	//
	template<typename T>
	struct less {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs < rhs; }
	};
	//
	// greater
	//
	template<typename T>
	struct greater {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs > rhs; }
	};
	//
	// equal_to
	//
	template<typename T>
	struct equal_to {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs == rhs; }
	};
	//
	// mod_less
	//
	template<typename T, T mod>
	struct mod_less {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs % mod < rhs % mod; }
	};

	//
	// x2
	//
	template<typename T>
	struct x2 {
	public:
		typedef T argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& t) const { return t + t; }
	};

	//
	// plus
	//
	template<typename T>
	struct plus {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& lhs, T const& rhs) const { return lhs + rhs; }
	};

	//
	// gen_iota
	//
	template<typename T>
	struct gen_iota {
	public:
		struct result {
		public:
			T val;
			gen_iota gen;
		public:
			SPROUT_CONSTEXPR T const& generated_value() const { return val; }
			SPROUT_CONSTEXPR gen_iota const& next_generator() const { return gen; }
		};
	private:
		T val;
	public:
		explicit SPROUT_CONSTEXPR gen_iota(T const& val = T())
			: val(val)
		{}
		SPROUT_CONSTEXPR result operator()() const { return result{val, gen_iota(val + 1)}; }
	};
	//
	// unf_iota
	//
	template<typename T>
	struct unf_iota {
	public:
		struct result {
		public:
			T val;
		public:
			SPROUT_CONSTEXPR T const& generated_value() const { return val; }
			SPROUT_CONSTEXPR T next_generator() const { return val + 1; }
		};
	public:
		SPROUT_CONSTEXPR result operator()(T const& val) const { return result{val}; }
	};

	//
	// distance
	//
	template<typename InputIterator>
	SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		return first == last ? 0
			: 1 + testspr::distance(first + 1, last)
			;
	}

	//
	// equal
	//
	template<typename InputIterator1, typename InputIterator2>
	inline SPROUT_CONSTEXPR bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		return first1 == last1 ? first2 == last2
			: first2 == last2 ? false
			: !(*first1 == *first2) ? false
			: testspr::equal(first1 + 1, last1, first2 + 1, last2)
			;
	}
	template<typename Range1, typename Range2>
	SPROUT_CONSTEXPR bool
	equal(Range1 const& range1, Range2 const& range2) {
		return testspr::equal(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2));
	}

	//
	// is_found
	//
	template<class InputIterator, typename T>
	SPROUT_CONSTEXPR bool
	is_found(InputIterator first, InputIterator last, T const& value) {
		return first == last ? false
			: *first == value ? true
			: testspr::is_found(first + 1, last, value)
			;
	}
	template<typename Range, typename T>
	SPROUT_CONSTEXPR bool
	is_found(Range const& range, T const& value) {
		return testspr::is_found(sprout::begin(range), sprout::end(range), value);
	}

	//
	// count
	//
	template<typename InputIterator, typename T>
	SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	count(InputIterator first, InputIterator last, T const& value) {
		return first == last ? 0
			: (*first == value ? 1 : 0) + testspr::count(first + 1, last, value)
			;
	}
	template<typename Range, typename T>
	SPROUT_CONSTEXPR typename std::iterator_traits<typename Range::const_iterator>::difference_type
	count(Range const& range, T const& value) {
		return testspr::count(sprout::begin(range), sprout::end(range), value);
	}

	namespace detail {
		template<typename ForwardIterator1, typename ForwardIterator2>
		SPROUT_CONSTEXPR bool
		is_permutation_impl(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			ForwardIterator1 first1_, ForwardIterator2 first2_
			)
		{
			return first1_ == last1 && first2_ == last2 ? true
				: testspr::count(first1, last1, *first1_) != testspr::count(first2, first2 + testspr::distance(first1, last1), *first1_) ? false
				: testspr::detail::is_permutation_impl(first1, last1, first2, last2, first1_ + 1, first2_ + 1)
				;
		}
	}	// namespace detail
	//
	// is_permutation
	//
	template<typename ForwardIterator1, typename ForwardIterator2>
	SPROUT_CONSTEXPR bool
	is_permutation(
		ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2
		)
	{
		return testspr::detail::is_permutation_impl(first1, last1, first2, last2, first1, first2);
	}
	template<typename Range1, typename Range2>
	SPROUT_CONSTEXPR bool
	is_permutation(Range1 const& range1, Range2 const& range2) {
		return testspr::is_permutation(
			sprout::begin(range1), sprout::end(range1),
			sprout::begin(range2), sprout::end(range2)
			);
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_TOOLS_HPP
