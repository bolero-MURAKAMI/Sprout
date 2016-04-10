/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP

#include <utility>
#include <type_traits>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/range_functions_fwd.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_begin(...);
	sprout::not_found_via_adl range_end(...);
	sprout::not_found_via_adl range_size(...);
	sprout::not_found_via_adl range_empty(...);
	sprout::not_found_via_adl range_front(...);
	sprout::not_found_via_adl range_back(...);
	sprout::not_found_via_adl range_at(...);
	sprout::not_found_via_adl range_nth(...);
	sprout::not_found_via_adl range_index_of(...);
	sprout::not_found_via_adl range_data(...);
}	// namespace sprout_adl

namespace sprout {
	namespace detail {
		template<typename T>
		struct has_mem_size_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().size())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_size_test<T>::test(0))>::type>
		struct has_mem_size
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_size
			: public sprout::identity<decltype(sprout::detail::has_mem_size_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_size<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_size_impl(Container const& cont) {
			return cont.size();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_size<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_size_impl(Container const& cont) {
			return sprout::distance(sprout::begin(cont), sprout::end(cont));
		}

		template<typename T>
		struct has_mem_empty_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().empty())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_empty_test<T>::test(0))>::type>
		struct has_mem_empty
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_empty
			: public sprout::identity<decltype(sprout::detail::has_mem_empty_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_empty<Container const>::value,
			bool
		>::type
		range_empty_impl(Container const& cont) {
			return cont.empty();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_empty<Container const>::value,
			bool
		>::type
		range_empty_impl(Container const& cont) {
			return sprout::size(cont) == 0;
		}

		template<typename T>
		struct has_mem_front_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().front())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_front_test<T>::test(0))>::type>
		struct has_mem_front
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_front
			: public sprout::identity<decltype(sprout::detail::has_mem_front_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_front<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_front_impl(Container& cont) {
			return cont.front();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_front<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_front_impl(Container& cont) {
			return *sprout::begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_front<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_front_impl(Container const& cont) {
			return cont.front();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_front<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_front_impl(Container const& cont) {
			return *sprout::begin(cont);
		}

		template<typename T>
		struct has_mem_back_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().back())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_back_test<T>::test(0))>::type>
		struct has_mem_back
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_back
			: public sprout::identity<decltype(sprout::detail::has_mem_back_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_back<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_back_impl(Container& cont) {
			return cont.back();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_back<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_back_impl(Container& cont) {
			return *sprout::begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_back<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_back_impl(Container const& cont) {
			return cont.back();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_back<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_back_impl(Container const& cont) {
			return *sprout::next(sprout::begin(cont), sprout::size(cont) - 1);
		}

		template<typename T>
		struct has_mem_at_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().at(std::declval<typename sprout::container_traits<U>::size_type>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_at_test<T>::test(0))>::type>
		struct has_mem_at
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_at
			: public sprout::identity<decltype(sprout::detail::has_mem_at_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_at<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return cont.at(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_at<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return *sprout::next(sprout::begin(cont), i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_at<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return cont.at(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_at<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return *sprout::next(sprout::begin(cont), i);
		}

		template<typename T>
		struct has_mem_nth_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().nth(std::declval<typename sprout::container_traits<U>::size_type>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_nth_test<T>::test(0))>::type>
		struct has_mem_nth
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_nth
			: public sprout::identity<decltype(sprout::detail::has_mem_nth_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_nth<Container>::value,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_nth_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return cont.nth(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_nth<Container>::value,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_nth_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return sprout::next(sprout::begin(cont), i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_nth<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_nth_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return cont.nth(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_nth<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_nth_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return sprout::next(sprout::begin(cont), i);
		}

		template<typename T>
		struct has_mem_index_of_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().index_of(std::declval<typename sprout::container_traits<U>::iterator>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_index_of_test<T>::test(0))>::type>
		struct has_mem_index_of
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_index_of
			: public sprout::identity<decltype(sprout::detail::has_mem_index_of_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_index_of<Container>::value,
			typename sprout::container_traits<Container>::size_type
		>::type
		range_index_of_impl(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			return cont.index_of(p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_index_of<Container>::value,
			typename sprout::container_traits<Container>::size_type
		>::type
		range_index_of_impl(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			return sprout::distance(begin(cont), p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_index_of<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_index_of_impl(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
			return cont.index_of(p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_index_of<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_index_of_impl(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
			return sprout::distance(begin(cont), p);
		}
	}	// namespace detail
}	// namespace sprout

namespace sprout_container_range_detail {
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_begin(Container& cont) {
		return cont.begin();
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_begin(Container const& cont) {
		return cont.begin();
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_end(Container& cont) {
		return cont.end();
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_end(Container const& cont) {
		return cont.end();
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	range_size(Container const& cont) {
		return sprout::detail::range_size_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	range_empty(Container const& cont) {
		return sprout::detail::range_empty_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	range_front(Container& cont) {
		return sprout::detail::range_front_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	range_front(Container const& cont) {
		return sprout::detail::range_front_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	range_back(Container& cont) {
		return sprout::detail::range_back_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	range_back(Container const& cont) {
		return sprout::detail::range_back_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	range_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		return sprout::detail::range_at_impl(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::detail::range_at_impl(cont, i);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_nth(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		return sprout::detail::range_nth_impl(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::detail::range_nth_impl(cont, i);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
	range_index_of(Container& cont, typename sprout::container_traits<Container>::iterator p) {
		return sprout::detail::range_index_of_impl(cont, p);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	range_index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
		return sprout::detail::range_index_of_impl(cont, p);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
	range_data(Container& cont) {
		return cont.data();
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
	range_data(Container const& cont) {
		return cont.data();
	}
}	// namespace sprout_container_range_detail

namespace sprout {
	namespace detail {
		//
		// container_range_traits_default
		//
		template<typename Container>
		struct container_range_traits_default {
		public:
			// iterators:
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
			// capacity:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
			range_size(Container const& cont) {
				using sprout_container_range_detail::range_size;
				using sprout_adl::range_size;
				return range_size(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
			range_empty(Container const& cont) {
				using sprout_container_range_detail::range_empty;
				using sprout_adl::range_empty;
				return range_empty(cont);
			}
			// element access:
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
			// data access:
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
	// container_range_traits
	//
	template<typename Container>
	struct container_range_traits
		: public sprout::detail::container_range_traits_default<Container>
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
		range_at(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
			return arr[i];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return arr[i];
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
	struct container_range_traits<T const[N]> {
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_begin(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_begin(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_end(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_end(arr);
		}
		// capacity:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
		range_size(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_size(arr);
		}
		static SPROUT_CONSTEXPR bool
		range_empty(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_empty(arr);
		}
		// element access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_front(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_front(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_back(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_back(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return sprout::container_range_traits<T[N]>::range_at(arr, i);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_nth(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return sprout::container_range_traits<T[N]>::range_nth(arr, i);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
		range_index_of(T const (& arr)[N], typename sprout::container_traits<T const[N]>::iterator p) {
			return sprout::container_range_traits<T[N]>::range_index_of(arr, p);
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::pointer
		range_data(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_data(arr);
		}
	};
}	// namespace sprout

#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/size.hpp>

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
