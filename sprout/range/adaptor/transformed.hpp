/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_TRANSFORMD_HPP
#define SPROUT_RANGE_ADAPTOR_TRANSFORMD_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>

namespace sprout {
	namespace adaptors {
		//
		// transformed_range
		//
		template<typename BinaryFunction, typename LRange, typename RRange = void>
		class transformed_range
			: public sprout::adaptors::detail::adapted_range_default<
				LRange,
				sprout::transform_iterator<
					BinaryFunction,
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			>
		{
		public:
			typedef BinaryFunction functor_type;
			typedef LRange range1_type;
			typedef RRange range2_type;
			typedef sprout::adaptors::detail::adapted_range_default<
				LRange,
				sprout::transform_iterator<
					BinaryFunction,
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
		public:
			SPROUT_CONSTEXPR transformed_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			transformed_range(transformed_range const&) = default;
			SPROUT_CONSTEXPR transformed_range(BinaryFunction func, range1_type& range1, range2_type& range2)
				: base_type(
					iterator(sprout::begin(range1), sprout::begin(range2), func),
					iterator(sprout::end(range1), sprout::end(range2), func)
					)
			{}
		};

		template<typename UnaryFunction, typename Range>
		class transformed_range<UnaryFunction, Range, void>
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					UnaryFunction,
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef UnaryFunction functor_type;
			typedef Range range1_type;
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					UnaryFunction,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
		public:
			SPROUT_CONSTEXPR transformed_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			transformed_range(transformed_range const&) = default;
			SPROUT_CONSTEXPR transformed_range(UnaryFunction func, range1_type& range)
				: base_type(
					iterator(sprout::begin(range), func),
					iterator(sprout::end(range), func)
					)
			{}
		};

		//
		// transform_holder
		//
		template<typename BinaryFunction, typename RRange = void>
		class transform_holder {
		public:
			typedef BinaryFunction functor_type;
			typedef RRange range2_type;
		private:
			BinaryFunction func_;
			sprout::value_holder<range2_type&> range_;
		public:
			SPROUT_CONSTEXPR transform_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			transform_holder(transform_holder const&) = default;
			SPROUT_CONSTEXPR transform_holder(BinaryFunction func, range2_type& range)
				: func_(func)
				, range_(range)
			{}
			SPROUT_CONSTEXPR BinaryFunction functor() const {
				return func_;
			}
			SPROUT_CONSTEXPR range2_type& range() const {
				return range_;
			}
		};
		template<typename UnaryFunction>
		class transform_holder<UnaryFunction, void> {
		public:
			typedef UnaryFunction functor_type;
		private:
			UnaryFunction func_;
		public:
			SPROUT_CONSTEXPR transform_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			transform_holder(transform_holder const&) = default;
			explicit SPROUT_CONSTEXPR transform_holder(UnaryFunction func)
				: func_(func)
			{}
			SPROUT_CONSTEXPR UnaryFunction functor() const {
				return func_;
			}
		};

		//
		// transformed_forwarder
		//
		class transformed_forwarder {
		public:
			template<typename RRange, typename BinaryFunction>
			SPROUT_CONSTEXPR sprout::adaptors::transform_holder<
				BinaryFunction,
				typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
			>
			operator()(RRange&& range, BinaryFunction func) const {
				return sprout::adaptors::transform_holder<
					BinaryFunction,
					typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
				>(
					func,
					sprout::lvalue_forward<RRange>(range)
					);
			}
			template<typename UnaryFunction>
			SPROUT_CONSTEXPR sprout::adaptors::transform_holder<UnaryFunction>
			operator()(UnaryFunction func) const {
				return sprout::adaptors::transform_holder<UnaryFunction>(func);
			}
		};

		//
		// transformed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::transformed_forwarder transformed = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename LRange, typename BinaryFunction, typename RRange>
		inline SPROUT_CONSTEXPR sprout::adaptors::transformed_range<
			BinaryFunction,
			typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
			RRange
		>
		operator|(LRange&& lhs, sprout::adaptors::transform_holder<BinaryFunction, RRange> const& rhs) {
			return sprout::adaptors::transformed_range<
				BinaryFunction,
				typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
				RRange
			>(
				rhs.functor(),
				sprout::lvalue_forward<LRange>(lhs),
				rhs.range()
				);
		}
		template<typename Range, typename UnaryFunction>
		inline SPROUT_CONSTEXPR sprout::adaptors::transformed_range<
			UnaryFunction,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::transform_holder<UnaryFunction> const& rhs) {
			return sprout::adaptors::transformed_range<
				UnaryFunction,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				rhs.functor(),
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename UnaryOrBinaryFunction, typename LRange, typename RRange>
	struct container_construct_traits<sprout::adaptors::transformed_range<UnaryOrBinaryFunction, LRange, RRange> >
		: public sprout::container_construct_traits<typename sprout::adaptors::transformed_range<UnaryOrBinaryFunction, LRange, RRange>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_TRANSFORMD_HPP
