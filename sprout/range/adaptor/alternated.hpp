#ifndef SPROUT_RANGE_ADAPTOR_ALTERNATED_HPP
#define SPROUT_RANGE_ADAPTOR_ALTERNATED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/alternate_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace adaptors {
		//
		// alternated_range
		//
		template<typename LRange, typename RRange>
		class alternated_range
			: public sprout::range::range_container<
				sprout::alternate_iterator<
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			>
			, public sprout::detail::container_nosy_static_size<LRange>
			, public sprout::detail::container_nosy_fixed_size<LRange>
		{
		public:
			typedef LRange range_type;
			typedef RRange range2_type;
			typedef sprout::range::range_container<
				sprout::alternate_iterator<
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
		public:
			alternated_range() = default;
			alternated_range(alternated_range const&) = default;
			SPROUT_CONSTEXPR alternated_range(range_type& range1, range2_type& range2)
				: base_type(
					iterator(sprout::begin(range1), sprout::begin(range2)),
					iterator(
						sprout::next(sprout::begin(range1), NS_SSCRISK_CEL_OR_SPROUT::min(sprout::size(range1), sprout::size(range2))),
						sprout::next(sprout::begin(range2), NS_SSCRISK_CEL_OR_SPROUT::min(sprout::size(range1), sprout::size(range2)))
						)
					)
			{}
		};

		//
		// alternate_holder
		//
		template<typename RRange>
		class alternate_holder {
		public:
			typedef RRange range2_type;
		private:
			sprout::value_holder<range2_type&> range_;
		public:
			alternate_holder() = default;
			alternate_holder(alternate_holder const&) = default;
			explicit SPROUT_CONSTEXPR alternate_holder(range2_type& range)
				: range_(range)
			{}
			SPROUT_CONSTEXPR range2_type& range() const {
				return range_;
			}
		};

		//
		// alternated_forwarder
		//
		class alternated_forwarder {
		public:
			template<typename RRange>
			SPROUT_CONSTEXPR sprout::adaptors::alternate_holder<
				typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
			>
			operator()(RRange&& range) {
				return sprout::adaptors::alternate_holder<
					typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
				>(
					sprout::lvalue_forward<RRange>(range)
					);
			}
		};

		//
		// alternated
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::alternated_forwarder alternated{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename LRange, typename RRange>
		inline SPROUT_CONSTEXPR sprout::adaptors::alternated_range<
			typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
			RRange
		>
		operator|(LRange&& lhs, sprout::adaptors::alternate_holder<RRange> const& rhs) {
			return sprout::adaptors::alternated_range<
				typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
				RRange
			>(
				sprout::lvalue_forward<LRange>(lhs),
				rhs.range()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename LRange, typename RRange>
	struct container_construct_traits<sprout::adaptors::alternated_range<LRange, RRange> > {
	public:
		typedef typename sprout::container_construct_traits<LRange>::copied_type copied_type;
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
			typename sprout::container_traits<sprout::adaptors::alternated_range<LRange, RRange> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_ALTERNATED_HPP
