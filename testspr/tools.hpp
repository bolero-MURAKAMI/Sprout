#ifndef TESTSPR_TOOLS_HPP
#define TESTSPR_TOOLS_HPP

#include <cassert>
#include <iterator>
#include <sprout/config.hpp>
#include <sprout/fixed_container.hpp>
#ifdef TESTSPR_CONFIG_ENABLE_STATIC_WARNING
#	include <boost/serialization/static_warning.hpp>
#endif

//
// TESTSPR_PP_CAT
//
#define TESTSPR_PP_CAT(a, b) TESTSPR_PP_CAT_I(a, b)
#define TESTSPR_PP_CAT_I(a, b) a ## b

//
// TESTSPR_STATIC_ASSERT
//
#define TESTSPR_STATIC_ASSERT(expr) static_assert(expr, #expr)
//
// TESTSPR_ASSERT
//
#define TESTSPR_ASSERT(expr) assert(expr)
//
// TESTSPR_DOUBLE_ASSERT
//
#define TESTSPR_DOUBLE_ASSERT(expr) TESTSPR_STATIC_ASSERT(expr); TESTSPR_ASSERT(expr)

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
//
#define TESTSPR_STATIC_UNCHECKED(expr) TESTSPR_STATIC_WARNING(expr)
//
// TESTSPR_UNCHECKED
//
#define TESTSPR_UNCHECKED(expr) (expr)
//
// TESTSPR_DOUBLE_UNCHECKED
//
#define TESTSPR_DOUBLE_UNCHECKED(expr) TESTSPR_STATIC_UNCHECKED(expr); TESTSPR_UNCHECKED(expr)

namespace testspr {
	//
	// is_even
	//
	template<typename T>
	struct is_even {
		SPROUT_CONSTEXPR bool operator()(T const& t) const { return t % 2 == 0; }
	};
	//
	// is_odd
	//
	template<typename T>
	struct is_odd {
		SPROUT_CONSTEXPR bool operator()(T const& t) const { return t % 2 != 0; }
	};

	//
	// less
	//
	template<typename T>
	struct less {
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs < rhs; }
	};
	//
	// greater
	//
	template<typename T>
	struct greater {
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs > rhs; }
	};
	//
	// equal_to
	//
	template<typename T>
	struct equal_to {
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs == rhs; }
	};
	//
	// mod_less
	//
	template<typename T, T mod>
	struct mod_less {
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs % mod < rhs % mod; }
	};

	//
	// x2
	//
	template<typename T>
	struct x2 {
		SPROUT_CONSTEXPR T operator()(T const& t) const { return t + t; }
	};
	//
	// plus
	//
	template<typename T>
	struct plus {
		SPROUT_CONSTEXPR T operator()(T const& lhs, T const& rhs) const { return lhs + rhs; }
	};

	//
	// distance
	//
	template<typename Iterator>
	SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last) {
		return first == last ? 0
			: 1 + testspr::distance(first + 1, last)
			;
	}

	//
	// equal
	//
	template<typename Iterator1, typename Iterator2>
	SPROUT_CONSTEXPR bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2) {
		return first1 == last1 ? first2 == last2
			: first2 == last2 ? false
			: !(*first1 == *first2) ? false
			: testspr::equal(first1 + 1, last1, first2 + 1, last2)
			;
	}
	template<typename Range1, typename Range2>
	SPROUT_CONSTEXPR bool equal(Range1 const& range1, Range2 const& range2) {
		return testspr::equal(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2));
	}

	//
	// is_found
	//
	template<class Iterator, typename T>
	SPROUT_CONSTEXPR bool is_found(Iterator first, Iterator last, T const& value) {
		return first == last ? false
			: *first == value ? true
			: testspr::is_found(first + 1, last, value)
			;
	}
	template<typename Range, typename T>
	SPROUT_CONSTEXPR bool is_found(Range const& range, T const& value) {
		return testspr::is_found(sprout::begin(range), sprout::end(range), value);
	}

	//
	// count
	//
	template<typename Iterator, typename T>
	SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type
	count(Iterator first, Iterator last, T const& value) {
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
		template<typename Iterator1, typename Iterator2>
		SPROUT_CONSTEXPR bool is_permutation_impl(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2, Iterator1 first1_, Iterator2 first2_)
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
	template<typename Iterator1, typename Iterator2>
	SPROUT_CONSTEXPR bool is_permutation(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2) {
		return testspr::detail::is_permutation_impl(first1, last1, first2, last2, first1, first2);
	}
	template<typename Range1, typename Range2>
	SPROUT_CONSTEXPR bool is_permutation(Range1 const& range1, Range2 const& range2) {
		return testspr::is_permutation(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2));
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_TOOLS_HPP
