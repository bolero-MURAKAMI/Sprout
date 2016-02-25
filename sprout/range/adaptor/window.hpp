/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_WINDOW_HPP
#define SPROUT_RANGE_ADAPTOR_WINDOW_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace adaptors {
		//
		// window_holder
		//
		template<typename Difference1, typename Difference2 = void>
		class window_holder {
		public:
			typedef typename sprout::arithmetic_promote<Difference1, Difference2>::type difference_type;
		private:
			difference_type to_first_;
			difference_type to_last_;
		public:
			SPROUT_CONSTEXPR window_holder(difference_type to_first, difference_type to_last)
				: to_first_(to_first), to_last_(to_last)
			{}
			SPROUT_CONSTEXPR difference_type const& to_first() const {
				return to_first_;
			}
			SPROUT_CONSTEXPR difference_type const& to_last() const {
				return to_last_;
			}
		};
		template<typename Difference>
		class window_holder<Difference, void> {
		public:
			typedef Difference difference_type;
		private:
			difference_type to_first_;
		public:
			explicit SPROUT_CONSTEXPR window_holder(difference_type to_first)
				: to_first_(to_first)
			{}
			SPROUT_CONSTEXPR difference_type const& to_first() const {
				return to_first_;
			}
		};

		//
		// window_forwarder
		//
		class window_forwarder {
		public:
			template<typename Difference1, typename Difference2>
			SPROUT_CONSTEXPR sprout::adaptors::window_holder<Difference1, Difference2>
			operator()(Difference1 to_first, Difference2 to_last) const {
				return sprout::adaptors::window_holder<Difference1, Difference2>(to_first, to_last);
			}
			template<typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::window_holder<Difference>
			operator()(Difference to_first) const {
				return sprout::adaptors::window_holder<Difference>(to_first);
			}
		};

		//
		// window
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::window_forwarder window = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Difference1, typename Difference2>
		inline SPROUT_CONSTEXPR sprout::adaptors::detail::adapted_range_default<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::window_holder<Difference1, Difference2> const& rhs) {
			typedef typename sprout::container_traits<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>::difference_type difference_type;
			return sprout::adaptors::detail::adapted_range_default<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::next(
					sprout::begin(sprout::lvalue_forward<Range>(lhs)),
					NS_SSCRISK_CEL_OR_SPROUT::min<difference_type>(rhs.to_first(), sprout::size(sprout::lvalue_forward<Range>(lhs)))
					),
				sprout::next(
					sprout::begin(sprout::lvalue_forward<Range>(lhs)),
					NS_SSCRISK_CEL_OR_SPROUT::min<difference_type>(rhs.to_last(), sprout::size(sprout::lvalue_forward<Range>(lhs)))
					)
				);
		}
		template<typename Range, typename Difference>
		inline SPROUT_CONSTEXPR sprout::adaptors::detail::adapted_range_default<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::window_holder<Difference> const& rhs) {
			typedef typename sprout::container_traits<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>::difference_type difference_type;
			return sprout::adaptors::detail::adapted_range_default<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::next(
					sprout::begin(sprout::lvalue_forward<Range>(lhs)),
					NS_SSCRISK_CEL_OR_SPROUT::min<difference_type>(rhs.to_first(), sprout::size(sprout::lvalue_forward<Range>(lhs)))
					),
				sprout::end(sprout::lvalue_forward<Range>(lhs))
				);
		}
	}	// namespace adaptors
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_WINDOW_HPP
