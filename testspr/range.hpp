#ifndef TESTSPR_RANGE_HPP
#define TESTSPR_RANGE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <testspr/iterator.hpp>

namespace testspr {
	namespace range {
		//
		// reducted_range
		//
		template<typename Range, typename Category = typename testspr::reduct_iterator<typename sprout::container_traits<Range>::iterator>::iterator_category>
		class reducted_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				testspr::reduct_iterator<typename sprout::container_traits<Range>::iterator, Category>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				testspr::reduct_iterator<typename sprout::container_traits<Range>::iterator, Category>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
		public:
			reducted_range() = default;
			reducted_range(reducted_range const&) = default;
			explicit SPROUT_CONSTEXPR reducted_range(range_type& range)
				: base_type(
					iterator(sprout::end(range)),
					iterator(sprout::begin(range))
					)
			{}
		};

		//
		// make_reduct_range
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR testspr::range::reducted_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		make_reduct_range(Range&& rng) {
			return testspr::range::reducted_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(rng)
				);
		}
		template<typename Category, typename Range>
		inline SPROUT_CONSTEXPR testspr::range::reducted_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			Category
		>
		make_reduct_range(Range&& rng) {
			return testspr::range::reducted_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
				Category
			>(
				sprout::lvalue_forward<Range>(rng)
				);
		}

		//
		// reduct_input
		// reduct_forward
		// reduct_bidirectional
		// reduct_random_access
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR testspr::range::reducted_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			std::input_iterator_tag
		>
		reduct_input(Range&& rng) {
			return testspr::range::make_reduct_range<std::input_iterator_tag>(sprout::forward<Range>(rng));
		}
		template<typename Range>
		inline SPROUT_CONSTEXPR testspr::range::reducted_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			std::forward_iterator_tag
		>
		reduct_forward(Range&& rng) {
			return testspr::range::make_reduct_range<std::forward_iterator_tag>(sprout::forward<Range>(rng));
		}
		template<typename Range>
		inline SPROUT_CONSTEXPR testspr::range::reducted_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			std::bidirectional_iterator_tag
		>
		reduct_bidirectional(Range&& rng) {
			return testspr::range::make_reduct_range<std::bidirectional_iterator_tag>(sprout::forward<Range>(rng));
		}
		template<typename Range>
		inline SPROUT_CONSTEXPR testspr::range::reducted_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			std::random_access_iterator_tag
		>
		reduct_random_access(Range&& rng) {
			return testspr::range::make_reduct_range<std::random_access_iterator_tag>(sprout::forward<Range>(rng));
		}
	}	// namespace range
}	// namespace testspr

namespace sprout {
	//
	// container_construct_traits
	//
	template<typename Range, typename Category>
	struct container_construct_traits<testspr::range::reducted_range<Range, Category> >
		: public sprout::container_construct_traits<typename testspr::range::reducted_range<Range, Category>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef TESTSPR_RANGE_HPP
