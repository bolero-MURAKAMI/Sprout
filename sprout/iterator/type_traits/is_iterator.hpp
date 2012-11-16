#ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP
#define SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>

namespace sprout {
	namespace detail {
		//
		// has_iterator_category
		//
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(iterator_category);
	}	// namespace detail
	//
	// is_iterator
	//
	template<typename Iterator>
	struct is_iterator
		: public sprout::detail::has_iterator_category<std::iterator_traits<Iterator> >
	{};

	//
	// is_input_iterator_category
	//
	template<typename Category>
	struct is_input_iterator_category
		: public std::is_convertible<Category, std::input_iterator_tag>
	{};
	//
	// is_output_iterator_category
	//
	template<typename Category>
	struct is_output_iterator_category
		: public std::is_convertible<Category, std::output_iterator_tag>
	{};
	//
	// is_forward_iterator_category
	//
	template<typename Category>
	struct is_forward_iterator_category
		: public std::is_convertible<Category, std::forward_iterator_tag>
	{};
	//
	// is_bidirectional_iterator_category
	//
	template<typename Category>
	struct is_bidirectional_iterator_category
		: public std::is_convertible<Category, std::bidirectional_iterator_tag>
	{};
	//
	// is_random_access_iterator_category
	//
	template<typename Category>
	struct is_random_access_iterator_category
		: public std::is_convertible<Category, std::random_access_iterator_tag>
	{};

	//
	// is_input_iterator
	//
	template<typename Iterator>
	struct is_input_iterator
		: public sprout::is_input_iterator_category<typename std::iterator_traits<Iterator>::iterator_category>
	{};
	//
	// is_output_iterator
	//
	template<typename Iterator>
	struct is_output_iterator
		: public sprout::is_output_iterator_category<typename std::iterator_traits<Iterator>::iterator_category>
	{};
	//
	// is_forward_iterator
	//
	template<typename Iterator>
	struct is_forward_iterator
		: public sprout::is_forward_iterator_category<typename std::iterator_traits<Iterator>::iterator_category>
	{};
	//
	// is_bidirectional_iterator
	//
	template<typename Iterator>
	struct is_bidirectional_iterator
		: public sprout::is_bidirectional_iterator_category<typename std::iterator_traits<Iterator>::iterator_category>
	{};
	//
	// is_random_access_iterator
	//
	template<typename Iterator>
	struct is_random_access_iterator
		: public sprout::is_random_access_iterator_category<typename std::iterator_traits<Iterator>::iterator_category>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP
