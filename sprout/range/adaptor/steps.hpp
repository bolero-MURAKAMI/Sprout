/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_STEPS_HPP
#define SPROUT_RANGE_ADAPTOR_STEPS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/step_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/type_traits/identity.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace adaptors {
		//
		// steps_range
		//
		template<typename Range>
		class steps_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::step_iterator<typename sprout::container_traits<Range>::iterator>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::step_iterator<typename sprout::container_traits<Range>::iterator>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::difference_type difference_type;
		public:
			SPROUT_CONSTEXPR steps_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			steps_range(steps_range const&) = default;
			explicit SPROUT_CONSTEXPR steps_range(range_type& range)
				: base_type(
					iterator(sprout::begin(range), 1, sprout::end(range)),
					iterator(sprout::end(range), 1, sprout::end(range))
					)
			{}
			SPROUT_CONSTEXPR steps_range(difference_type width, range_type& range)
				: base_type(
					iterator(sprout::begin(range), width, sprout::end(range)),
					iterator(sprout::end(range), width, sprout::end(range))
					)
			{}
			SPROUT_CONSTEXPR steps_range(difference_type width, difference_type init, range_type& range)
				: base_type(
					iterator(sprout::next(sprout::begin(range), NS_SSCRISK_CEL_OR_SPROUT::min(init, sprout::size(range))), width, sprout::end(range)),
					iterator(sprout::end(range), width, sprout::end(range))
					)
			{}
		};

		//
		// step_holder
		//
		template<typename Difference>
		class step_holder {
		public:
			typedef Difference difference_type;
		private:
			difference_type width_;
			difference_type init_;
		public:
			SPROUT_CONSTEXPR step_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			step_holder(step_holder const&) = default;
			explicit SPROUT_CONSTEXPR step_holder(difference_type width, difference_type init = 0)
				: width_(width), init_(init)
			{}
			SPROUT_CONSTEXPR difference_type const& width() const {
				return width_;
			}
			SPROUT_CONSTEXPR difference_type const& init() const {
				return init_;
			}
		};

		//
		// steps_forwarder
		//
		class steps_forwarder {
		public:
			template<typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::step_holder<Difference>
			operator()(Difference width) const {
				return sprout::adaptors::step_holder<Difference>(width);
			}
			template<typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::step_holder<Difference>
			operator()(Difference width, typename sprout::identity<Difference>::type init) const {
				return sprout::adaptors::step_holder<Difference>(width, init);
			}
		};

		//
		// steps
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::steps_forwarder steps = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Difference>
		inline SPROUT_CONSTEXPR sprout::adaptors::steps_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::step_holder<Difference> const& rhs) {
			return sprout::adaptors::steps_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				rhs.width(), rhs.init(),
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range>
	struct container_construct_traits<sprout::adaptors::steps_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::steps_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_STEPS_HPP
