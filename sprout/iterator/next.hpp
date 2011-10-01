#ifndef SPROUT_ITERATOR_NEXT_HPP
#define SPROUT_ITERATOR_NEXT_HPP
	
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
		>::type next_impl(
			Iterator&& it,
			std::random_access_iterator_tag*
			)
		{
			return sprout::forward<Iterator>(it) + 1;
		}
		template<typename Iterator>
		Iterator next_impl(
			Iterator&& it,
			void*
			)
		{
			return std::next(sprout::forward<Iterator>(it));
		}

		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<typename std::decay<Iterator>::type>::value,
			typename std::decay<Iterator>::type
		>::type next_impl(
			Iterator&& it,
			typename std::iterator_traits<typename std::decay<Iterator>::type>::difference_type n,
			std::random_access_iterator_tag*
			)
		{
			return sprout::forward<Iterator>(it) + n;
		}
		template<typename Iterator>
		Iterator next_impl(
			Iterator it,
			typename std::iterator_traits<typename std::decay<Iterator>::type>::difference_type n,
			void*
			)
		{
			return std::next(sprout::forward<Iterator>(it), n);
		}
	}	// namespace detail
	//
	// next
	//
	template<typename Iterator>
	SPROUT_CONSTEXPR typename std::decay<Iterator>::type next(Iterator&& it) {
		return sprout::detail::next_impl(
			sprout::forward<Iterator>(it),
			static_cast<typename std::iterator_traits<typename std::decay<Iterator>::type>::iterator_category*>(nullptr)
			);
	}
	template<typename Iterator>
	SPROUT_CONSTEXPR typename std::decay<Iterator>::type next(
		Iterator&& it,
		typename std::iterator_traits<typename std::decay<Iterator>::type>::difference_type n
		)
	{
		return sprout::detail::next_impl(
			sprout::forward<Iterator>(it),
			n,
			static_cast<typename std::iterator_traits<typename std::decay<Iterator>::type>::iterator_category*>(nullptr)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_NEXT_HPP
