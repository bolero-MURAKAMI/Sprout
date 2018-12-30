/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/range_functions_fwd.hpp>
#include <sprout/container/detail/range_begin.hpp>
#include <sprout/container/detail/range_end.hpp>
#include <sprout/container/detail/range_size.hpp>
#include <sprout/container/detail/range_empty.hpp>
#include <sprout/container/detail/range_front.hpp>
#include <sprout/container/detail/range_back.hpp>
#include <sprout/container/detail/range_subscript_at.hpp>
#include <sprout/container/detail/range_at.hpp>
#include <sprout/container/detail/range_nth.hpp>
#include <sprout/container/detail/range_index_of.hpp>
#include <sprout/container/detail/range_data.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace detail {
		//
		// container_range_traits_const_default
		//
		template<typename Container>
		struct container_range_traits_const_default {
		public:
			// iterators:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
			range_begin(Container const& cont) {
				return sprout::container_range_traits<Container>::range_begin(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
			range_end(Container const& cont) {
				return sprout::container_range_traits<Container>::range_end(cont);
			}
			// capacity:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
			range_size(Container const& cont) {
				return sprout::container_range_traits<Container>::range_size(cont);
			}
			static SPROUT_CONSTEXPR bool
			range_empty(Container const& cont) {
				return sprout::container_range_traits<Container>::range_empty(cont);
			}
			// element access:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_front(Container const& cont) {
				return sprout::container_range_traits<Container>::range_front(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_back(Container const& cont) {
				return sprout::container_range_traits<Container>::range_back(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_subscript_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				return sprout::container_range_traits<Container>::range_subscript_at(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				return sprout::container_range_traits<Container>::range_at(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
			range_nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				return sprout::container_range_traits<Container>::range_nth(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
			range_index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
				return sprout::container_range_traits<Container>::range_index_of(cont, p);
			}
			// data access:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
			range_data(Container const& cont) {
				return sprout::container_range_traits<Container>::range_data(cont);
			}
		};
	}	// namespace detail

	//
	// container_range_begin_default
	//
	template<typename Container>
	struct container_range_begin_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_begin(Container& cont) {
			using sprout_container_range_detail::range_begin;
			using sprout_adl::range_begin;
			return range_begin(cont);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_begin(Container const& cont) {
			using sprout_container_range_detail::range_begin;
			using sprout_adl::range_begin;
			return range_begin(cont);
		}
	};
	//
	// container_range_end_default
	//
	template<typename Container>
	struct container_range_end_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_end(Container& cont) {
			using sprout_container_range_detail::range_end;
			using sprout_adl::range_end;
			return range_end(cont);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_end(Container const& cont) {
			using sprout_container_range_detail::range_end;
			using sprout_adl::range_end;
			return range_end(cont);
		}
	};
	//
	// container_range_size_default
	//
	template<typename Container>
	struct container_range_size_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
		range_size(Container const& cont) {
			using sprout_container_range_detail::range_size;
			using sprout_adl::range_size;
			return range_size(cont);
		}
	};
	//
	// container_range_empty_default
	//
	template<typename Container>
	struct container_range_empty_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
		range_empty(Container const& cont) {
			using sprout_container_range_detail::range_empty;
			using sprout_adl::range_empty;
			return range_empty(cont);
		}
	};
	//
	// container_range_front_default
	//
	template<typename Container>
	struct container_range_front_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
		range_front(Container& cont) {
			using sprout_container_range_detail::range_front;
			using sprout_adl::range_front;
			return range_front(cont);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_front(Container const& cont) {
			using sprout_container_range_detail::range_front;
			using sprout_adl::range_front;
			return range_front(cont);
		}
	};
	//
	// container_range_back_default
	//
	template<typename Container>
	struct container_range_back_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
		range_back(Container& cont) {
			using sprout_container_range_detail::range_back;
			using sprout_adl::range_back;
			return range_back(cont);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_back(Container const& cont) {
			using sprout_container_range_detail::range_back;
			using sprout_adl::range_back;
			return range_back(cont);
		}
	};
	//
	// container_range_subscript_at_default
	//
	template<typename Container>
	struct container_range_subscript_at_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
		range_subscript_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			using sprout_container_range_detail::range_subscript_at;
			using sprout_adl::range_subscript_at;
			return range_subscript_at(cont, i);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_subscript_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			using sprout_container_range_detail::range_subscript_at;
			using sprout_adl::range_subscript_at;
			return range_subscript_at(cont, i);
		}
	};
	//
	// container_range_at_default
	//
	template<typename Container>
	struct container_range_at_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
		range_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			using sprout_container_range_detail::range_at;
			using sprout_adl::range_at;
			return range_at(cont, i);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			using sprout_container_range_detail::range_at;
			using sprout_adl::range_at;
			return range_at(cont, i);
		}
	};
	//
	// container_range_nth_default
	//
	template<typename Container>
	struct container_range_nth_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_nth(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			using sprout_container_range_detail::range_nth;
			using sprout_adl::range_nth;
			return range_nth(cont, i);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			using sprout_container_range_detail::range_nth;
			using sprout_adl::range_nth;
			return range_nth(cont, i);
		}
	};
	//
	// container_range_index_of_default
	//
	template<typename Container>
	struct container_range_index_of_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
		range_index_of(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			using sprout_container_range_detail::range_index_of;
			using sprout_adl::range_index_of;
			return range_index_of(cont, p);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
		range_index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
			using sprout_container_range_detail::range_index_of;
			using sprout_adl::range_index_of;
			return range_index_of(cont, p);
		}
	};
	//
	// container_range_data_default
	//
	template<typename Container>
	struct container_range_data_default {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
		range_data(Container& cont) {
			using sprout_container_range_detail::range_data;
			using sprout_adl::range_data;
			return range_data(cont);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
		range_data(Container const& cont) {
			using sprout_container_range_detail::range_data;
			using sprout_adl::range_data;
			return range_data(cont);
		}
	};

	//
	// container_range_traits_default
	//
	template<typename Container>
	struct container_range_traits_default
		: public sprout::container_range_begin_default<Container>
		, public sprout::container_range_end_default<Container>
		, public sprout::container_range_size_default<Container>
		, public sprout::container_range_front_default<Container>
		, public sprout::container_range_back_default<Container>
		, public sprout::container_range_subscript_at_default<Container>
		, public sprout::container_range_at_default<Container>
		, public sprout::container_range_nth_default<Container>
		, public sprout::container_range_index_of_default<Container>
		, public sprout::container_range_data_default<Container>
	{};

	//
	// container_range_traits
	//
	template<typename Container>
	struct container_range_traits
		: public sprout::container_range_traits_default<Container>
	{};
	template<typename Container>
	struct container_range_traits<Container const>
		: public sprout::detail::container_range_traits_const_default<Container>
	{};

	template<typename T, std::size_t N>
	struct container_range_traits<T[N]> {
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_begin(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_begin(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_end(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr) + N;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_end(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr) + N;
		}
		// capacity:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::size_type
		range_size(T const (&)[N]) {
			return N;
		}
		static SPROUT_CONSTEXPR bool
		range_empty(T const (&)[N]) {
			return false;
		}
		// element access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_front(T (& arr)[N]) {
			return arr[0];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_front(T const (& arr)[N]) {
			return arr[0];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_back(T (& arr)[N]) {
			return arr[N - 1];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_back(T const (& arr)[N]) {
			return arr[N - 1];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_subscript_at(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
			return arr[i];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_subscript_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return arr[i];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_at(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
			return arr[sprout::range_index_check(arr, i)];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return arr[sprout::range_index_check(arr, i)];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_nth(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr) + i;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_nth(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr) + i;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::size_type
		range_index_of(T (& arr)[N], typename sprout::container_traits<T[N]>::iterator p) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return sprout::distance(type(arr), p);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
		range_index_of(T const (& arr)[N], typename sprout::container_traits<T const[N]>::iterator p) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return sprout::distance(type(arr), p);
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::pointer
		range_data(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::pointer type;
			return type(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::pointer
		range_data(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::pointer type;
			return type(arr);
		}
	};
	template<typename T, std::size_t N>
	struct container_range_traits<T const[N]>
		: public sprout::detail::container_range_traits_const_default<T[N]>
	{};
}	// namespace sprout

#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/size.hpp>
#include <sprout/container/front.hpp>
#include <sprout/container/back.hpp>
#include <sprout/container/subscript_at.hpp>
#include <sprout/container/at.hpp>
#include <sprout/container/nth.hpp>
#include <sprout/container/index_of.hpp>
#include <sprout/container/data.hpp>
#include <sprout/container/range_index_check.hpp>

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
