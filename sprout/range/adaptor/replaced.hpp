#ifndef SPROUT_RANGE_ADAPTOR_REPLACED_HPP
#define SPROUT_RANGE_ADAPTOR_REPLACED_HPP

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

namespace sprout {
	namespace adaptors {
		namespace detail {
			template<typename T>
			class replace_value {
			public:
				typedef T const& result_type;
				typedef T const& first_argument_type;
			private:
				T old_;
				T new_;
			public:
				SPROUT_CONSTEXPR replace_value(T const& old_value, T const& new_value)
					: old_(old_value)
					, new_(new_value)
				{}
				SPROUT_CONSTEXPR T const& operator()(T const& value) const {
					return (value == old_) ? new_ : value;
				}
			};
		}	// namespace detail
		//
		// replaced_range
		//
		template<typename Range>
		class replaced_range
			: public sprout::range::range_container<
				sprout::transform_iterator<
					sprout::adaptors::detail::replace_value<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			>
			, public sprout::detail::container_nosy_static_size<Range>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef Range range_type;
			typedef sprout::range::range_container<
				sprout::transform_iterator<
					sprout::adaptors::detail::replace_value<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			replaced_range() = default;
			replaced_range(replaced_range const&) = default;
			explicit SPROUT_CONSTEXPR replaced_range(range_type& range, value_type const& old_value, value_type const& new_value)
				: base_type(
					iterator(sprout::begin(range), typename iterator::functor_type(old_value, new_value)),
					iterator(sprout::end(range), typename iterator::functor_type(old_value, new_value))
					)
			{}
		};

		//
		// replace_holder
		//
		template<typename T>
		class replace_holder {
		public:
			typedef T value_type;
		private:
			value_type old_;
			value_type new_;
		public:
			SPROUT_CONSTEXPR replace_holder(value_type const& old_value, value_type const& new_value)
				: old_(old_value)
				, new_(new_value)
			{}
			SPROUT_CONSTEXPR value_type old_value() const {
				return old_;
			}
			SPROUT_CONSTEXPR value_type new_value() const {
				return new_;
			}
		};

		//
		// replaced_forwarder
		//
		class replaced_forwarder {
		public:
			template<typename T>
			SPROUT_CONSTEXPR sprout::adaptors::replace_holder<T>
			operator()(T const& old_value, T const& new_value) {
				return sprout::adaptors::replace_holder<T>(old_value, new_value);
			}
		};

		//
		// replaced
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::replaced_forwarder replaced{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR sprout::adaptors::replaced_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::replace_holder<T> const& rhs) {
			return sprout::adaptors::replaced_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.old_value(),
				rhs.new_value()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range>
	struct container_construct_traits<sprout::adaptors::replaced_range<Range> > {
	public:
		typedef typename sprout::container_construct_traits<Range>::copied_type copied_type;
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
			typename sprout::container_traits<sprout::adaptors::replaced_range<Range> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_REPLACED_HPP
