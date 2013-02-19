#ifndef SPROUT_RANGE_ADAPTOR_TAKEN_END_HPP
#define SPROUT_RANGE_ADAPTOR_TAKEN_END_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace adaptors {
		//
		// take_end_holder
		//
		template<typename Difference>
		class take_end_holder {
		public:
			typedef Difference difference_type;
		private:
			difference_type distance_;
		public:
			explicit SPROUT_CONSTEXPR take_end_holder(difference_type distance)
				: distance_(distance)
			{}
			SPROUT_CONSTEXPR difference_type const& distance() const {
				return distance_;
			}
		};

		//
		// taken_end_forwarder
		//
		class taken_end_forwarder {
		public:
			template<typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::take_end_holder<Difference>
			operator()(Difference distance) {
				return sprout::adaptors::take_end_holder<Difference>(distance);
			}
		};

		//
		// taken_end
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::taken_end_forwarder taken_end = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Difference>
		inline SPROUT_CONSTEXPR sprout::adaptors::detail::adapted_range_default<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::take_end_holder<Difference> const& rhs) {
			typedef typename sprout::container_traits<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>::difference_type difference_type;
			return sprout::adaptors::detail::adapted_range_default<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::next(
					sprout::end(sprout::lvalue_forward<Range>(lhs)),
					NS_SSCRISK_CEL_OR_SPROUT::max<difference_type>(rhs.distance(), -sprout::size(sprout::lvalue_forward<Range>(lhs)))
					),
				sprout::end(sprout::lvalue_forward<Range>(lhs))
				);
		}
	}	// namespace adaptors
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_TAKEN_END_HPP
