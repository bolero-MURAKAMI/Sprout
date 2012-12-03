#ifndef SPROUT_RANGE_ADAPTOR_REPLACED_IF_HPP
#define SPROUT_RANGE_ADAPTOR_REPLACED_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		namespace detail {
			template<typename Predicate, typename T>
			class replace_value_if {
			public:
				typedef Predicate predicate_type;
				typedef T const& result_type;
				typedef T const& argument_type;
			private:
				Predicate pred_;
				T new_;
			public:
				SPROUT_CONSTEXPR replace_value_if(Predicate pred, T const& new_value)
					: pred_(pred)
					, new_(new_value)
				{}
				SPROUT_CONSTEXPR T operator()(T const& value) const {
					return pred_(value) ? new_ : value;
				}
			};
		}	// namespace detail
		//
		// replaced_if_range
		//
		template<typename Predicate, typename Range>
		class replaced_if_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					sprout::adaptors::detail::replace_value_if<Predicate, typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef Predicate predicate_type;
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					sprout::adaptors::detail::replace_value_if<Predicate, typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			replaced_if_range() = default;
			replaced_if_range(replaced_if_range const&) = default;
			SPROUT_CONSTEXPR replaced_if_range(range_type& range, Predicate pred, value_type const& new_value)
				: base_type(
					iterator(sprout::begin(range), typename iterator::functor_type(pred, new_value)),
					iterator(sprout::end(range), typename iterator::functor_type(pred, new_value))
					)
			{}
		};

		//
		// replace_if_holder
		//
		template<typename Predicate, typename T>
		class replace_if_holder {
		public:
			typedef Predicate predicate_type;
			typedef T value_type;
		private:
			Predicate pred_;
			value_type new_;
		public:
			SPROUT_CONSTEXPR replace_if_holder(Predicate pred, value_type const& new_value)
				: pred_(pred)
				, new_(new_value)
			{}
			SPROUT_CONSTEXPR Predicate const& predicate() const {
				return pred_;
			}
			SPROUT_CONSTEXPR value_type const& new_value() const {
				return new_;
			}
		};

		//
		// replaced_if_forwarder
		//
		class replaced_if_forwarder {
		public:
			template<typename Predicate, typename T>
			SPROUT_CONSTEXPR sprout::adaptors::replace_if_holder<Predicate, T>
			operator()(Predicate pred, T const& new_value) {
				return sprout::adaptors::replace_if_holder<Predicate, T>(pred, new_value);
			}
		};

		//
		// replaced_if
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::replaced_if_forwarder replaced_if{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Predicate, typename T>
		inline SPROUT_CONSTEXPR sprout::adaptors::replaced_if_range<
			Predicate,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::replace_if_holder<Predicate, T> const& rhs) {
			return sprout::adaptors::replaced_if_range<
				Predicate,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.predicate(),
				rhs.new_value()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Predicate, typename Range>
	struct container_construct_traits<sprout::adaptors::replaced_if_range<Predicate, Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::replaced_if_range<Predicate, Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_REPLACED_IF_HPP
