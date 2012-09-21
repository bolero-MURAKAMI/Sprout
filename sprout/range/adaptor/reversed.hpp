#ifndef SPROUT_RANGE_ADAPTOR_REVERSED_HPP
#define SPROUT_RANGE_ADAPTOR_REVERSED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// reversed_range
		//
		template<typename Range>
		class reversed_range
			: public sprout::range::range_container<
				sprout::reverse_iterator<
					typename sprout::container_traits<Range>::iterator
				>
			>
			, public sprout::detail::container_nosy_static_size<Range>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef Range range_type;
			typedef sprout::range::range_container<
				sprout::reverse_iterator<
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
		public:
			reversed_range() = default;
			reversed_range(reversed_range const&) = default;
			explicit SPROUT_CONSTEXPR reversed_range(range_type& range)
				: base_type(
					iterator(sprout::end(range)),
					iterator(sprout::begin(range))
					)
			{}
		};

		//
		// reversed_forwarder
		//
		class reversed_forwarder {};

		//
		// reversed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::reversed_forwarder reversed{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::reversed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::reversed_forwarder) {
			return sprout::adaptors::reversed_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range>
	struct container_construct_traits<sprout::adaptors::reversed_range<Range> > {
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
			typename sprout::container_traits<sprout::adaptors::reversed_range<Range> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_REVERSED_HPP
