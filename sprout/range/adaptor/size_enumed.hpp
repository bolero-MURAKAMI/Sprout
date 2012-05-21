#ifndef SPROUT_RANGE_ADAPTOR_SIZE_ENUMED_HPP
#define SPROUT_RANGE_ADAPTOR_SIZE_ENUMED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/size_enum_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// size_enumed_range
		//
		template<typename Range, bool Separated = false>
		class size_enumed_range
			: public sprout::range::range_container<
				sprout::size_enum_iterator<
					typename sprout::container_traits<Range>::iterator
				>
			>
			, public sprout::detail::container_nosy_static_size<Range>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef Range range_type;
			typedef sprout::range::range_container<
				sprout::size_enum_iterator<
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::iterator iterator;
		public:
			size_enumed_range() = default;
			size_enumed_range(size_enumed_range const&) = default;
			explicit SPROUT_CONSTEXPR size_enumed_range(range_type& range)
				: base_type(
					iterator(sprout::begin(range)),
					iterator(sprout::end(range))
					)
			{}
		};

		template<typename Range>
		class size_enumed_range<Range, true>
			: public sprout::range::range_container<
				sprout::size_enum_iterator<
					typename sprout::container_traits<Range>::iterator, true
				>
			>
			, public sprout::detail::container_nosy_static_size<Range>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef Range range_type;
			typedef sprout::range::range_container<
				sprout::size_enum_iterator<
					typename sprout::container_traits<Range>::iterator, true
				>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			size_enumed_range() = default;
			size_enumed_range(size_enumed_range const&) = default;
			explicit SPROUT_CONSTEXPR size_enumed_range(
				range_type& range,
				value_type sep_size = 0,
				bool omit_last = false
				)
				: base_type(
					iterator(sprout::begin(range), sep_size),
					omit_last
						? sprout::empty(range)
							? iterator(sprout::end(range), sep_size)
							: iterator(sprout::prev(sprout::end(range)), sep_size, true)
						: iterator(sprout::end(range), sep_size)
					)
			{}
		};

		//
		// size_enum_holder
		//
		template<typename Size>
		class size_enum_holder {
		public:
			typedef Size size_type;
		private:
			size_type sep_size_;
			bool omit_last_;
		public:
			size_enum_holder() = default;
			size_enum_holder(size_enum_holder const&) = default;
			explicit SPROUT_CONSTEXPR size_enum_holder(size_type size, bool omit_last = false)
				: sep_size_(size)
				, omit_last_(omit_last)
			{}
			SPROUT_CONSTEXPR size_type separator_size() const {
				return sep_size_;
			}
			SPROUT_CONSTEXPR bool omit_last() const {
				return omit_last_;
			}
		};

		//
		// size_enumed_forwarder
		//
		class size_enumed_forwarder {
		public:
			template<typename Size>
			SPROUT_CONSTEXPR typename sprout::adaptors::size_enum_holder<Size>
			operator()(Size size, bool omit_last = false) {
				return typename sprout::adaptors::size_enum_holder<Size>(size, omit_last);
			}
		};

		//
		// size_enumed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::size_enumed_forwarder size_enumed{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Size>
		inline SPROUT_CONSTEXPR sprout::adaptors::size_enumed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			true
		>
		operator|(Range&& lhs, sprout::adaptors::size_enum_holder<Size> const& rhs) {
			return sprout::adaptors::size_enumed_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
				true
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.separator_size(),
				rhs.omit_last()
				);
		}
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::size_enumed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::size_enumed_forwarder const& rhs) {
			return sprout::adaptors::size_enumed_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range, bool Separated>
	struct container_construct_traits<sprout::adaptors::size_enumed_range<Range, Separated> > {
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
			typename sprout::container_traits<sprout::adaptors::size_enumed_range<Range> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_SIZE_ENUMED_HPP
