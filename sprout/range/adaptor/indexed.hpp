#ifndef SPROUT_RANGE_ADAPTOR_INDEXED_HPP
#define SPROUT_RANGE_ADAPTOR_INDEXED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/indexed_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// indexed_range
		//
		template<typename Range>
		class indexed_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::indexed_iterator<typename sprout::container_traits<Range>::iterator>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::indexed_iterator<typename sprout::container_traits<Range>::iterator>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename iterator::index_type index_type;
		public:
			indexed_range() = default;
			indexed_range(indexed_range const&) = default;
			explicit SPROUT_CONSTEXPR indexed_range(range_type& range)
				: base_type(
					iterator(sprout::begin(range)),
					iterator(sprout::end(range))
					)
			{}
			SPROUT_CONSTEXPR indexed_range(index_type index, range_type& range)
				: base_type(
					iterator(sprout::begin(range), index),
					iterator(sprout::end(range), index)
					)
			{}
		};

		//
		// indexed_holder
		//
		template<typename Index>
		class indexed_holder {
		public:
			typedef Index index_type;
		private:
			index_type index_;
		public:
			indexed_holder() = default;
			indexed_holder(indexed_holder const&) = default;
			explicit SPROUT_CONSTEXPR indexed_holder(index_type index)
				: index_(index)
			{}
			SPROUT_CONSTEXPR index_type const& index() const {
				return index_;
			}
		};

		//
		// indexed_forwarder
		//
		class indexed_forwarder {
		public:
			template<typename Index>
			SPROUT_CONSTEXPR sprout::adaptors::indexed_holder<Index>
			operator()(Index index) {
				return sprout::adaptors::indexed_holder<Index>(index);
			}
		};

		//
		// indexed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::indexed_forwarder indexed = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::indexed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::indexed_forwarder const& rhs) {
			return sprout::adaptors::indexed_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs)
				);
		}
		template<typename Range, typename Index>
		inline SPROUT_CONSTEXPR sprout::adaptors::indexed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::indexed_holder<Index> const& rhs) {
			return sprout::adaptors::indexed_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				rhs.index(),
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range>
	struct container_construct_traits<sprout::adaptors::indexed_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::indexed_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_INDEXED_HPP
