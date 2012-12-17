#ifndef SPROUT_RANGE_ADAPTOR_CLAMPED_HPP
#define SPROUT_RANGE_ADAPTOR_CLAMPED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/clamp_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace adaptors {
		//
		// clamped_range
		//
		template<
			typename Range,
			typename Compare = NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Range>::value_type>
		>
		class clamped_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::clamp_iterator<typename sprout::container_traits<Range>::iterator, Compare>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::clamp_iterator<typename sprout::container_traits<Range>::iterator, Compare>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
			typedef typename iterator::compare_type compare_type;
		public:
			clamped_range() = default;
			clamped_range(clamped_range const&) = default;
			explicit SPROUT_CONSTEXPR clamped_range(
				range_type& range,
				value_type const& low,
				value_type const& up,
				Compare comp = Compare()
				)
				: base_type(
					iterator(sprout::begin(range), low, up, comp),
					iterator(sprout::end(range), low, up, comp)
					)
			{}
			SPROUT_CONSTEXPR Compare compare() const {
				return base_type::begin().compare();
			}
			SPROUT_CONSTEXPR value_type lower() const {
				return base_type::begin().lower();
			}
			SPROUT_CONSTEXPR value_type upper() const {
				return base_type::begin().upper();
			}
		};

		//
		// clamp_holder
		//
		template<typename Value, typename Compare = NS_SSCRISK_CEL_OR_SPROUT::less<Value> >
		class clamp_holder {
		public:
			typedef Value value_type;
			typedef Compare compare_type;
		private:
			Compare comp_;
			value_type low_;
			value_type up_;
		public:
			SPROUT_CONSTEXPR clamp_holder(value_type const& low, value_type const& up, Compare comp = Compare())
				: comp_(comp), low_(low), up_(up)
			{}
			SPROUT_CONSTEXPR Compare const& compare() const {
				return comp_;
			}
			SPROUT_CONSTEXPR value_type const& lower() const {
				return low_;
			}
			SPROUT_CONSTEXPR value_type const& upper() const {
				return up_;
			}
		};

		//
		// clamped_forwarder
		//
		class clamped_forwarder {
		public:
			template<typename Value, typename Compare>
			SPROUT_CONSTEXPR sprout::adaptors::clamp_holder<Value, Compare>
			operator()(Value const& low, Value const& up, Compare comp) {
				return sprout::adaptors::clamp_holder<Value, Compare>(low, up, comp);
			}
			template<typename Value>
			SPROUT_CONSTEXPR sprout::adaptors::clamp_holder<Value>
			operator()(Value const& low, Value const& up) {
				return sprout::adaptors::clamp_holder<Value>(low, up);
			}
		};

		//
		// clamped
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::clamped_forwarder clamped = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Value, typename Compare>
		inline SPROUT_CONSTEXPR sprout::adaptors::clamped_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			Compare
		>
		operator|(Range&& lhs, sprout::adaptors::clamp_holder<Value, Compare> const& rhs) {
			return sprout::adaptors::clamped_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
				Compare
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.lower(), rhs.upper(), rhs.compare()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range, typename Compare>
	struct container_construct_traits<sprout::adaptors::clamped_range<Range, Compare> >
		: public sprout::container_construct_traits<typename sprout::adaptors::clamped_range<Range, Compare>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_CLAMPED_HPP
