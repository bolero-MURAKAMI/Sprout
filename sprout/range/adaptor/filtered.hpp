#ifndef SPROUT_RANGE_ADAPTOR_FILTERED_HPP
#define SPROUT_RANGE_ADAPTOR_FILTERED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/filter_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// filtered_range
		//
		template<typename Predicate, typename Range>
		class filtered_range
			: public sprout::range::range_container<
				sprout::filter_iterator<
					Predicate,
					typename sprout::container_traits<Range>::iterator
				>
			>
			, public sprout::detail::container_nosy_static_size<Range>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef Predicate predicate_type;
			typedef Range range_type;
			typedef sprout::range::range_container<
				sprout::filter_iterator<
					Predicate,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
		public:
			filtered_range() = default;
			filtered_range(filtered_range const&) = default;
			SPROUT_CONSTEXPR filtered_range(predicate_type pred, range_type& range)
				: base_type(
					iterator(pred, sprout::begin(range), sprout::end(range)),
					iterator(pred, sprout::end(range), sprout::end(range))
					)
			{}
		};

		//
		// filter_holder
		//
		template<typename Predicate>
		class filter_holder {
		public:
			typedef Predicate predicate_type;
		private:
			predicate_type pred_;
		public:
			filter_holder() = default;
			filter_holder(filter_holder const&) = default;
			SPROUT_CONSTEXPR filter_holder(predicate_type pred)
				: pred_(pred)
			{}
			SPROUT_CONSTEXPR predicate_type predicate() const {
				return pred_;
			}
		};

		//
		// filtered_forwarder
		//
		class filtered_forwarder {
		public:
			template<typename Predicate>
			SPROUT_CONSTEXPR sprout::adaptors::filter_holder<Predicate>
			operator()(Predicate pred) {
				return sprout::adaptors::filter_holder<Predicate>(pred);
			}
		};

		//
		// filtered
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::filtered_forwarder filtered{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::adaptors::filtered_range<
			Predicate,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::filter_holder<Predicate> const& rhs) {
			return sprout::adaptors::filtered_range<
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
	struct container_construct_traits<sprout::adaptors::filtered_range<Predicate, Range> > {
	public:
		typedef typename sprout::container_construct_traits<Range>::copied_type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return sprout::range::fixed::copy(sprout::forward<Cont>(cont), sprout::pit<copied_type>());
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::make<copied_type>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::adaptors::filtered_range<Predicate, Range> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_FILTERED_HPP
