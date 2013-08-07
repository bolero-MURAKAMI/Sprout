#ifndef SPROUT_RANGE_ADAPTOR_FILLED_HPP
#define SPROUT_RANGE_ADAPTOR_FILLED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// filled_range
		//
		template<typename Range>
		class filled_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::value_iterator<typename sprout::container_traits<Range>::value_type>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::value_iterator<typename sprout::container_traits<Range>::value_type>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			filled_range() = default;
			filled_range(filled_range const&) = default;
			SPROUT_CONSTEXPR filled_range(
				range_type& range,
				value_type const& value
				)
				: base_type(
					iterator(value, sprout::size(range)),
					iterator(value, 0)
					)
			{}
		};

		//
		// fill_holder
		//
		template<typename T>
		class fill_holder {
		public:
			typedef T value_type;
		private:
			value_type value_;
		public:
			explicit SPROUT_CONSTEXPR fill_holder(value_type const& value)
				: value_(value)
			{}
			SPROUT_CONSTEXPR value_type const& value() const {
				return value_;
			}
		};

		//
		// filled_forwarder
		//
		class filled_forwarder {
		public:
			template<typename T>
			SPROUT_CONSTEXPR sprout::adaptors::fill_holder<T>
			operator()(T const& value) const {
				return sprout::adaptors::fill_holder<T>(value);
			}
		};

		//
		// filled
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::filled_forwarder filled = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR sprout::adaptors::filled_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::fill_holder<T> const& rhs) {
			return sprout::adaptors::filled_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.value()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range>
	struct container_construct_traits<sprout::adaptors::filled_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::filled_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_FILLED_HPP
