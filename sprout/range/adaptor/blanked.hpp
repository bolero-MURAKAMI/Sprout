#ifndef SPROUT_RANGE_ADAPTOR_BLANKED_HPP
#define SPROUT_RANGE_ADAPTOR_BLANKED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// blank_t
	//
	struct blank_t {};

	namespace adaptors {
		//
		// blanked_range
		//
		template<typename T = sprout::blank_t, typename Range = void>
		class blanked_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::value_iterator<T>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::value_iterator<T>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
		public:
			blanked_range() = default;
			blanked_range(blanked_range const&) = default;
			explicit SPROUT_CONSTEXPR blanked_range(range_type& range)
				: base_type(
					iterator(value_type(), sprout::size(range)),
					iterator(value_type(), 0)
					)
			{}
			SPROUT_CONSTEXPR blanked_range(
				range_type& range,
				difference_type n
				)
				: base_type(
					iterator(value_type(), NS_SSCRISK_CEL_OR_SPROUT::min(n, sprout::size(range))),
					iterator(value_type(), 0)
					)
			{}
			SPROUT_CONSTEXPR blanked_range(
				range_type& range,
				difference_type n,
				value_type const& value
				)
				: base_type(
					iterator(value, NS_SSCRISK_CEL_OR_SPROUT::min(n, sprout::size(range))),
					iterator(value, 0)
					)
			{}
		};

		template<typename T>
		class blanked_range<T, void>
			: public sprout::range::range_container<
				sprout::value_iterator<T>
			>
		{
		public:
			typedef sprout::range::range_container<
				sprout::value_iterator<T>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
		public:
			SPROUT_CONSTEXPR blanked_range()
				: base_type(
					iterator(value_type()),
					iterator(value_type(), 0)
					)
			{}
			blanked_range(blanked_range const&) = default;
			explicit SPROUT_CONSTEXPR blanked_range(difference_type n)
				: base_type(
					iterator(value_type(), n),
					iterator(value_type(), 0)
					)
			{}
			SPROUT_CONSTEXPR blanked_range(
				difference_type n,
				value_type const& value
				)
				: base_type(
					iterator(value, n),
					iterator(value, 0)
					)
			{}
		};

		//
		// blanked_forwarder
		//
		class blanked_forwarder {
		public:
			SPROUT_CONSTEXPR sprout::adaptors::blanked_range<>
			operator()() const {
				return sprout::adaptors::blanked_range<>();
			}
			template<typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::blanked_range<>
			operator()(Difference n) const {
				return sprout::adaptors::blanked_range<>(n);
			}
			template<typename T, typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::blanked_range<T>
			operator()(Difference n, T const& value) const {
				return sprout::adaptors::blanked_range<T>(n, value);
			}
		};

		//
		// blanked
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::blanked_forwarder blanked = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR sprout::adaptors::blanked_range<
			T,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::blanked_range<T> const& rhs) {
			return sprout::adaptors::blanked_range<
				T,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				sprout::size(rhs),
				!sprout::empty(rhs) ? *rhs.begin()
					: typename sprout::container_traits<sprout::adaptors::blanked_range<T> >::value_type()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename T, typename Range>
	struct container_construct_traits<sprout::adaptors::blanked_range<T, Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::blanked_range<T, Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_BLANKED_HPP
