#ifndef SPROUT_RANGE_ADAPTOR_OFFSET_HPP
#define SPROUT_RANGE_ADAPTOR_OFFSET_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace adaptors {
		//
		// offset_holder
		//
		template<typename Difference1, typename Difference2 = void>
		class offset_holder {
		public:
			typedef typename sprout::arithmetic_promote<Difference1, Difference2>::type difference_type;
		private:
			difference_type from_begin_;
			difference_type from_end_;
		public:
			SPROUT_CONSTEXPR offset_holder(difference_type from_begin, difference_type from_end)
				: from_begin_(from_begin), from_end_(from_end)
			{}
			SPROUT_CONSTEXPR difference_type const& from_begin() const {
				return from_begin_;
			}
			SPROUT_CONSTEXPR difference_type const& from_end() const {
				return from_end_;
			}
		};
		template<typename Difference>
		class offset_holder<Difference, void> {
		public:
			typedef Difference difference_type;
		private:
			difference_type from_begin_;
		public:
			explicit SPROUT_CONSTEXPR offset_holder(difference_type from_begin)
				: from_begin_(from_begin)
			{}
			SPROUT_CONSTEXPR difference_type const& from_begin() const {
				return from_begin_;
			}
		};

		//
		// offset_forwarder
		//
		class offset_forwarder {
		public:
			template<typename Difference1, typename Difference2>
			SPROUT_CONSTEXPR sprout::adaptors::offset_holder<Difference1, Difference2>
			operator()(Difference1 from_begin, Difference2 from_end) {
				return sprout::adaptors::offset_holder<Difference1, Difference2>(from_begin, from_end);
			}
			template<typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::offset_holder<Difference>
			operator()(Difference from_begin) {
				return sprout::adaptors::offset_holder<Difference>(from_begin);
			}
		};

		//
		// offset
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::offset_forwarder offset = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Difference1, typename Difference2>
		inline SPROUT_CONSTEXPR sprout::adaptors::detail::adapted_range_default<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::offset_holder<Difference1, Difference2> const& rhs) {
			typedef typename sprout::container_traits<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>::difference_type difference_type;
			return sprout::adaptors::detail::adapted_range_default<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>(
				sprout::next(
					sprout::begin(sprout::lvalue_forward<Range>(lhs)),
					NS_SSCRISK_CEL_OR_SPROUT::min<difference_type>(rhs.from_begin(), sprout::size(sprout::lvalue_forward<Range>(lhs)))
					),
				sprout::next(
					sprout::end(sprout::lvalue_forward<Range>(lhs)),
					NS_SSCRISK_CEL_OR_SPROUT::max<difference_type>(
						rhs.from_end(),
						NS_SSCRISK_CEL_OR_SPROUT::min<difference_type>(rhs.from_begin() - sprout::size(sprout::lvalue_forward<Range>(lhs)), 0)
						)
					)
				);
		}
		template<typename Range, typename Difference>
		inline SPROUT_CONSTEXPR sprout::adaptors::detail::adapted_range_default<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::offset_holder<Difference> const& rhs) {
			typedef typename sprout::container_traits<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>::difference_type difference_type;
			return sprout::adaptors::detail::adapted_range_default<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::next(
					sprout::begin(sprout::lvalue_forward<Range>(lhs)),
					NS_SSCRISK_CEL_OR_SPROUT::min<difference_type>(rhs.from_begin(), sprout::size(sprout::lvalue_forward<Range>(lhs)))
					),
				sprout::end(sprout::lvalue_forward<Range>(lhs))
				);
		}
	}	// namespace adaptors
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_OFFSET_HPP
