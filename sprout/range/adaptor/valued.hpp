/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_VALUED_HPP
#define SPROUT_RANGE_ADAPTOR_VALUED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/valued_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
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
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::valued_iterator<typename sprout::container_traits<Range>::iterator, T>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::valued_iterator<typename sprout::container_traits<Range>::iterator, T>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename iterator::param_type param_type;
		public:
			SPROUT_CONSTEXPR valued_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
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
			SPROUT_CONSTEXPR valued_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
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
			operator()(T const& param) const {
				return sprout::adaptors::valued_holder<T>(param);
			}
		};

		//
		// valued
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::valued_forwarder valued = {};
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
	struct container_construct_traits<sprout::adaptors::valued_range<Range, T> >
		: public sprout::container_construct_traits<typename sprout::adaptors::valued_range<Range, T>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_VALUED_HPP
