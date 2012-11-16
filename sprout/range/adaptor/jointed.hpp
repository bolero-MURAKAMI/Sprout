#ifndef SPROUT_RANGE_ADAPTOR_JOINTED_HPP
#define SPROUT_RANGE_ADAPTOR_JOINTED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/joint_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder.hpp>

namespace sprout {
	namespace adaptors {
		//
		// jointed_range
		//
		template<typename LRange, typename RRange>
		class jointed_range
			: public sprout::range::range_container<
				sprout::joint_iterator<
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
				sprout::joint_iterator<
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
		public:
			jointed_range() = default;
			jointed_range(jointed_range const&) = default;
			SPROUT_CONSTEXPR jointed_range(range_type& range1, range2_type& range2)
				: base_type(
					iterator(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::begin(range2)),
					iterator(sprout::end(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2))
					)
			{}
		};

		//
		// joint_holder
		//
		template<typename RRange>
		class joint_holder {
		public:
			typedef RRange range2_type;
		private:
			sprout::value_holder<range2_type&> range_;
		public:
			joint_holder() = default;
			joint_holder(joint_holder const&) = default;
			explicit SPROUT_CONSTEXPR joint_holder(range2_type& range)
				: range_(range)
			{}
			SPROUT_CONSTEXPR range2_type& range() const {
				return range_;
			}
		};

		//
		// jointed_forwarder
		//
		class jointed_forwarder {
		public:
			template<typename RRange>
			SPROUT_CONSTEXPR sprout::adaptors::joint_holder<
				typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
			>
			operator()(RRange&& range) {
				return sprout::adaptors::joint_holder<
					typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
				>(
					sprout::lvalue_forward<RRange>(range)
					);
			}
		};

		//
		// jointed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::jointed_forwarder jointed{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename LRange, typename RRange>
		inline SPROUT_CONSTEXPR sprout::adaptors::jointed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
			RRange
		>
		operator|(LRange&& lhs, sprout::adaptors::joint_holder<RRange> const& rhs) {
			return sprout::adaptors::jointed_range<
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
	struct container_construct_traits<sprout::adaptors::jointed_range<LRange, RRange> > {
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
			typename sprout::container_traits<sprout::adaptors::jointed_range<LRange, RRange> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_JOINTED_HPP
