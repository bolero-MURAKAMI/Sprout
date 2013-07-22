#ifndef SPROUT_RANGE_RANGE_RETURN_HPP
#define SPROUT_RANGE_RANGE_RETURN_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/type_traits/lvalue_iterator.hpp>
#include <sprout/range/type_traits/lvalue_range.hpp>

namespace sprout {
	namespace range {
		//
		// range_return_value
		//
		enum range_return_value {
			return_found,
			return_found_end,
			return_begin_found
		};

		//
		// range_return
		//
		template<typename Range, sprout::range::range_return_value RetV = sprout::range::return_found>
		struct range_return;

		template<typename Range>
		struct range_return<Range, sprout::range::return_found> {
		public:
			typedef typename sprout::range::lvalue_iterator<Range>::type type;
		public:
			static SPROUT_CONSTEXPR type pack(
				typename sprout::range::lvalue_iterator<Range>::type found,
				Range&&
				)
			{
				return found;
			}
		};
		template<typename Range>
		struct range_return<Range, sprout::range::return_found_end> {
		public:
			typedef typename sprout::range::lvalue_range<Range>::type type;
		public:
			static SPROUT_CONSTEXPR type pack(
				typename sprout::range::lvalue_iterator<Range>::type found,
				Range&& range
				)
			{
				return type(found, sprout::end(sprout::forward<Range>(range)));
			}
		};
		template<typename Range>
		struct range_return<Range, sprout::range::return_begin_found> {
		public:
			typedef typename sprout::range::lvalue_range<Range>::type type;
		public:
			static SPROUT_CONSTEXPR type pack(
				typename sprout::range::lvalue_iterator<Range>::type found,
				Range&& range
				)
			{
				return type(sprout::begin(sprout::forward<Range>(range)), found);
			}
		};
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_RANGE_RETURN_HPP
