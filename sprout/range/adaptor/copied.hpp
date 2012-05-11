#ifndef SPROUT_RANGE_ADAPTOR_COPIED_HPP
#define SPROUT_RANGE_ADAPTOR_COPIED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/sinusoid_iterator.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder.hpp>

namespace sprout {
	namespace adaptors {
		//
		// copied_range
		//
		template<typename Range>
		class copied_range
			: public sprout::range::range_container<
				typename sprout::container_traits<Range>::iterator
			>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef Range range_type;
			typedef sprout::range::range_container<
				typename sprout::container_traits<Range>::iterator
			> base_type;
			typedef typename base_type::iterator iterator;
		public:
			copied_range() = default;
			copied_range(copied_range const&) = default;
			explicit SPROUT_CONSTEXPR copied_range(range_type& range)
				: base_type(
					sprout::begin(range),
					sprout::end(range)
					)
			{}
			template<typename Result>
			SPROUT_CONSTEXPR operator Result() const {
				return sprout::range::fixed::copy(*this, sprout::pit<Result>());
			}
		};

		//
		// copy_holder
		//
		template<typename Result>
		class copy_holder {
		public:
			typedef Result result_type;
		private:
			sprout::value_holder<result_type&> result_;
		public:
			copy_holder() = default;
			copy_holder(copy_holder const&) = default;
			explicit SPROUT_CONSTEXPR copy_holder(result_type& result)
				: result_(result)
			{}
			SPROUT_CONSTEXPR result_type result() const {
				return result_;
			}
		};

		//
		// copied_forwarder
		//
		class copied_forwarder {
		public:
			template<typename Result>
			SPROUT_CONSTEXPR typename sprout::adaptors::copy_holder<Result const>
			operator()(Result const& result) {
				return typename sprout::adaptors::copy_holder<Result const>(result);
			}
		};

		//
		// copied
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::copied_forwarder copied{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Result>
		SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<sprout::pit<Result> >::type
		operator|(Range&& lhs, sprout::adaptors::copy_holder<Result> const& rhs) {
			return sprout::range::fixed::copy(sprout::lvalue_forward<Range>(lhs), sprout::pit<Result>());
		}
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::copied_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::copied_forwarder const& rhs) {
			return sprout::adaptors::copied_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range>
	struct container_construct_traits<sprout::adaptors::copied_range<Range> > {
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
			typename sprout::container_traits<sprout::adaptors::copied_range<Range> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_COPIED_HPP
