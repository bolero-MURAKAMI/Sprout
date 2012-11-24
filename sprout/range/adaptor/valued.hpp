#ifndef SPROUT_RANGE_ADAPTOR_VALUED_HPP
#define SPROUT_RANGE_ADAPTOR_VALUED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/valued_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// valued_range
		//
		template<typename Range, typename T>
		class valued_range
			: public sprout::range::range_container<
				sprout::valued_iterator<typename sprout::container_traits<Range>::iterator, T>
			>
			, public sprout::detail::container_nosy_static_size<Range>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef Range range_type;
			typedef sprout::range::range_container<
				sprout::valued_iterator<typename sprout::container_traits<Range>::iterator, T>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
			typedef typename iterator::param_type param_type;
		public:
			valued_range() = default;
			valued_range(valued_range const&) = default;
			SPROUT_CONSTEXPR valued_range(param_type param, range_type& range)
				: base_type(
					iterator(sprout::begin(range), param),
					iterator(sprout::end(range), param)
					)
			{}
		};

		//
		// valued_holder
		//
		template<typename T>
		class valued_holder {
		public:
			typedef T content_type;
			typedef sprout::value_holder<T> holder_type;
			typedef typename holder_type::param_type param_type;
			typedef typename holder_type::mutable_or_const_reference get_type;
		private:
			holder_type holder_;
		public:
			valued_holder() = default;
			valued_holder(valued_holder const&) = default;
			explicit SPROUT_CONSTEXPR valued_holder(param_type param)
				: holder_(param)
			{}
			SPROUT_CONSTEXPR get_type get() const {
				return holder_.get();
			}
		};

		//
		// valued_forwarder
		//
		class valued_forwarder {
		public:
			template<typename T>
			SPROUT_CONSTEXPR sprout::adaptors::valued_holder<T>
			operator()(T const& param) {
				return sprout::adaptors::valued_holder<T>(param);
			}
		};

		//
		// valued
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::valued_forwarder valued{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR sprout::adaptors::valued_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			T
		>
		operator|(Range&& lhs, sprout::adaptors::valued_holder<T> const& rhs) {
			return sprout::adaptors::valued_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
				T
			>(
				rhs.get(),
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range, typename T>
	struct container_construct_traits<sprout::adaptors::valued_range<Range, T> > {
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
			typename sprout::container_traits<sprout::adaptors::valued_range<Range, T> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_VALUED_HPP
