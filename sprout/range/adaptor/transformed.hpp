#ifndef SPROUT_RANGE_ADAPTOR_TRANSFORMD_HPP
#define SPROUT_RANGE_ADAPTOR_TRANSFORMD_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder.hpp>

namespace sprout {
	namespace adaptors {
		//
		// transformed_range
		//
		template<typename BinaryFunction, typename LRange, typename RRange = void>
		class transformed_range
			: public sprout::range::range_container<
				sprout::transform_iterator<
					BinaryFunction,
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			>
			, public sprout::detail::container_nosy_static_size<LRange>
			, public sprout::detail::container_nosy_fixed_size<LRange>
		{
		public:
			typedef BinaryFunction functor_type;
			typedef LRange range_type;
			typedef RRange range2_type;
			typedef sprout::range::range_container<
				sprout::transform_iterator<
					BinaryFunction,
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::size_type size_type;
		public:
			SPROUT_CONSTEXPR transformed_range() = default;
			SPROUT_CONSTEXPR transformed_range(transformed_range const&) = default;
			SPROUT_CONSTEXPR transformed_range(functor_type func, range_type& range1, range2_type& range2)
				: base_type(
					iterator(sprout::begin(range1), sprout::begin(range2), func),
					iterator(sprout::end(range1), sprout::end(range2), func)
					)
			{}
		};

		template<typename UnaryFunction, typename Range>
		class transformed_range<UnaryFunction, Range, void>
			: public sprout::range::range_container<
				sprout::transform_iterator<
					UnaryFunction,
					typename sprout::container_traits<Range>::iterator
				>
			>
			, public sprout::detail::container_nosy_static_size<Range>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef UnaryFunction functor_type;
			typedef Range range_type;
			typedef sprout::range::range_container<
				sprout::transform_iterator<
					UnaryFunction,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
		public:
			SPROUT_CONSTEXPR transformed_range() = default;
			SPROUT_CONSTEXPR transformed_range(transformed_range const&) = default;
			SPROUT_CONSTEXPR transformed_range(functor_type func, range_type& range)
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
			functor_type func_;
			sprout::value_holder<range2_type&> range_;
		public:
			transform_holder() = default;
			transform_holder(transform_holder const&) = default;
			SPROUT_CONSTEXPR transform_holder(functor_type func, range2_type& range)
				: func_(func)
				, range_(range)
			{}
			SPROUT_CONSTEXPR functor_type functor() const {
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
			functor_type func_;
		public:
			transform_holder() = default;
			transform_holder(transform_holder const&) = default;
			explicit SPROUT_CONSTEXPR transform_holder(functor_type func)
				: func_(func)
			{}
			SPROUT_CONSTEXPR functor_type functor() const {
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
			operator()(RRange&& range, BinaryFunction func) {
				return sprout::adaptors::transform_holder<
					BinaryFunction,
					typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
				> (
					func,
					sprout::lvalue_forward<RRange>(range)
					);
			}
			template<typename UnaryFunction>
			SPROUT_CONSTEXPR sprout::adaptors::transform_holder<UnaryFunction>
			operator()(UnaryFunction func) {
				return sprout::adaptors::transform_holder<UnaryFunction>(func);
			}
		};

		//
		// transformed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::transformed_forwarder transformed{};
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
	struct container_construct_traits<sprout::adaptors::transformed_range<UnaryOrBinaryFunction, LRange, RRange> > {
	public:
		typedef typename sprout::container_construct_traits<LRange>::copied_type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return sprout::range::fixed::copy(sprout::forward<Cont>(cont), sprout::pit<copied_type>());
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::make<copied_type>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::adaptors::transformed_range<UnaryOrBinaryFunction, LRange, RRange> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_TRANSFORMD_HPP
