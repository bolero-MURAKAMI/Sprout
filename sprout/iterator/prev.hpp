#ifndef SPROUT_ITERATOR_PREV_HPP
#define SPROUT_ITERATOR_PREV_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace detail {
		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<typename std::decay<Iterator>::type>::value,
			typename std::decay<Iterator>::type
		>::type prev_impl(
			Iterator&& it,
			std::random_access_iterator_tag*
			)
		{
			return sprout::forward<Iterator>(it) - 1;
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::decay<Iterator>::type prev_impl(
			Iterator&& it,
			void*
			)
		{
			using std::prev;
			return prev(sprout::forward<Iterator>(it));
		}

		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<typename std::decay<Iterator>::type>::value,
			typename std::decay<Iterator>::type
		>::type prev_impl(
			Iterator&& it,
			typename std::iterator_traits<typename std::decay<Iterator>::type>::difference_type n,
			std::random_access_iterator_tag*
			)
		{
			return sprout::forward<Iterator>(it) - n;
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::decay<Iterator>::type prev_impl(
			Iterator it,
			typename std::iterator_traits<typename std::decay<Iterator>::type>::difference_type n,
			void*
			)
		{
			using std::prev;
			return prev(sprout::forward<Iterator>(it), n);
		}
	}	// namespace detail
	//
	// prev
	//
	template<typename Iterator>
	SPROUT_CONSTEXPR typename std::decay<Iterator>::type prev(Iterator&& it) {
		typedef typename std::iterator_traits<typename std::decay<Iterator>::type>::iterator_category* category;
		return sprout::detail::prev_impl(
			sprout::forward<Iterator>(it),
			category()
			);
	}
	template<typename Iterator>
	SPROUT_CONSTEXPR typename std::decay<Iterator>::type prev(
		Iterator&& it,
		typename std::iterator_traits<typename std::decay<Iterator>::type>::difference_type n
		)
	{
		typedef typename std::iterator_traits<typename std::decay<Iterator>::type>::iterator_category* category;
		return sprout::detail::prev_impl(
			sprout::forward<Iterator>(it),
			n,
			category()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_PREV_HPP
