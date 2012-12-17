#ifndef SPROUT_RANGE_ADAPTOR_OUTDIRECTED_HPP
#define SPROUT_RANGE_ADAPTOR_OUTDIRECTED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/counting_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// outdirected_range
		//
		template<typename Range>
		class outdirected_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::counting_iterator<typename sprout::container_traits<Range>::iterator>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::counting_iterator<typename sprout::container_traits<Range>::iterator>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
		public:
			outdirected_range() = default;
			outdirected_range(outdirected_range const&) = default;
			explicit SPROUT_CONSTEXPR outdirected_range(range_type& range)
				: base_type(
					iterator(sprout::begin(range)),
					iterator(sprout::end(range))
					)
			{}
		};

		//
		// outdirected_forwarder
		//
		class outdirected_forwarder {};

		//
		// outdirected
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::outdirected_forwarder outdirected = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::outdirected_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::outdirected_forwarder const& rhs) {
			return sprout::adaptors::outdirected_range<
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
	struct container_construct_traits<sprout::adaptors::outdirected_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::outdirected_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_OUTDIRECTED_HPP
