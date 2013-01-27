#ifndef SPROUT_RANGE_ADAPTOR_COUNTING_HPP
#define SPROUT_RANGE_ADAPTOR_COUNTING_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/counting_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// counting_range
		//
		template<typename Incrementable, typename Range = void>
		class counting_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::counting_iterator<Incrementable>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::counting_iterator<Incrementable>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			counting_range() = default;
			counting_range(counting_range const&) = default;
			explicit SPROUT_CONSTEXPR counting_range(range_type& range)
				: base_type(
					iterator(),
					sprout::next(iterator(), sprout::size(range))
					)
			{}
			SPROUT_CONSTEXPR counting_range(
				range_type& range,
				value_type const& first
				)
				: base_type(
					iterator(first),
					sprout::next(iterator(first), sprout::size(range))
					)
			{}
			SPROUT_CONSTEXPR counting_range(
				range_type& range,
				value_type const& first,
				value_type const& last
				)
				: base_type(
					iterator(first),
					sprout::size(range) < last - first ? sprout::next(iterator(first), sprout::size(range))
						: iterator(last)
					)
			{}
		};

		template<typename Incrementable>
		class counting_range<Incrementable, void>
			: public sprout::range::range_container<
				sprout::counting_iterator<Incrementable>
			>
		{
		public:
			typedef sprout::range::range_container<
				sprout::counting_iterator<Incrementable>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			counting_range() = default;
			counting_range(counting_range const&) = default;
			explicit SPROUT_CONSTEXPR counting_range(value_type const& first)
				: base_type(
					iterator(first),
					iterator()
					)
			{}
			SPROUT_CONSTEXPR counting_range(
				value_type const& first,
				value_type const& last
				)
				: base_type(
					iterator(first),
					iterator(last)
					)
			{}
		};

		//
		// counting_forwarder
		//
		class counting_forwarder {
		public:
			template<typename Incrementable>
			SPROUT_CONSTEXPR sprout::adaptors::counting_range<Incrementable>
			operator()(Incrementable const& first) const {
				return sprout::adaptors::counting_range<Incrementable>(first);
			}
			template<typename Incrementable>
			SPROUT_CONSTEXPR sprout::adaptors::counting_range<Incrementable>
			operator()(Incrementable const& first, Incrementable const& last) const {
				return sprout::adaptors::counting_range<Incrementable>(first, last);
			}
		};

		//
		// counting
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::counting_forwarder counting = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Incrementable>
		inline SPROUT_CONSTEXPR sprout::adaptors::counting_range<
			Incrementable,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::counting_range<Incrementable> const& rhs) {
			return sprout::adaptors::counting_range<
				Incrementable,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				*rhs.begin(),
				*rhs.end()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Incrementable, typename Range>
	struct container_construct_traits<sprout::adaptors::counting_range<Incrementable, Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::counting_range<Incrementable, Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_COUNTING_HPP
