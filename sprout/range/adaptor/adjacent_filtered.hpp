#ifndef SPROUT_RANGE_ADAPTOR_ADJACENT_FILTERED_HPP
#define SPROUT_RANGE_ADAPTOR_ADJACENT_FILTERED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/adjacent_filter_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// adjacent_filtered_range
		//
		template<typename Predicate, typename Range>
		class adjacent_filtered_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::adjacent_filter_iterator<
					Predicate,
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef Predicate predicate_type;
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::adjacent_filter_iterator<
					Predicate,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
		public:
			adjacent_filtered_range() = default;
			adjacent_filtered_range(adjacent_filtered_range const&) = default;
			SPROUT_CONSTEXPR adjacent_filtered_range(Predicate pred, range_type& range)
				: base_type(
					iterator(pred, sprout::begin(range), sprout::end(range)),
					iterator(pred, sprout::end(range), sprout::end(range))
					)
			{}
		};

		//
		// adjacent_filter_holder
		//
		template<typename Predicate>
		class adjacent_filter_holder {
		public:
			typedef Predicate predicate_type;
		private:
			Predicate pred_;
		public:
			adjacent_filter_holder() = default;
			adjacent_filter_holder(adjacent_filter_holder const&) = default;
			SPROUT_CONSTEXPR adjacent_filter_holder(Predicate pred)
				: pred_(pred)
			{}
			SPROUT_CONSTEXPR Predicate predicate() const {
				return pred_;
			}
		};

		//
		// adjacent_filtered_forwarder
		//
		class adjacent_filtered_forwarder {
		public:
			template<typename Predicate>
			SPROUT_CONSTEXPR sprout::adaptors::adjacent_filter_holder<Predicate>
			operator()(Predicate pred) const {
				return sprout::adaptors::adjacent_filter_holder<Predicate>(pred);
			}
		};

		//
		// adjacent_filtered
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::adjacent_filtered_forwarder adjacent_filtered = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::adaptors::adjacent_filtered_range<
			Predicate,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::adjacent_filter_holder<Predicate> const& rhs) {
			return sprout::adaptors::adjacent_filtered_range<
				Predicate,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				rhs.predicate(),
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Predicate, typename Range>
	struct container_construct_traits<sprout::adaptors::adjacent_filtered_range<Predicate, Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::adjacent_filtered_range<Predicate, Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_ADJACENT_FILTERED_HPP
