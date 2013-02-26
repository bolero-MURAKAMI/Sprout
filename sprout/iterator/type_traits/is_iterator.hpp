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
	template<typename MaybeIterator>
	struct is_iterator
		: public sprout::detail::has_iterator_category<std::iterator_traits<MaybeIterator> >
	{};

	//
	// is_iterator_category_of
	//
	template<typename MaybeCategory, typename Category>
	struct is_iterator_category_of
		: public std::is_convertible<MaybeCategory, Category>
	{};

	//
	// is_input_iterator_category
	//
	template<typename MaybeCategory>
	struct is_input_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::input_iterator_tag>
	{};
	//
	// is_output_iterator_category
	//
	template<typename MaybeCategory>
	struct is_output_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::output_iterator_tag>
	{};
	//
	// is_forward_iterator_category
	//
	template<typename MaybeCategory>
	struct is_forward_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::forward_iterator_tag>
	{};
	//
	// is_bidirectional_iterator_category
	//
	template<typename MaybeCategory>
	struct is_bidirectional_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::bidirectional_iterator_tag>
	{};
	//
	// is_random_access_iterator_category
	//
	template<typename MaybeCategory>
	struct is_random_access_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::random_access_iterator_tag>
	{};

	namespace detail {
		template<typename MaybeIterator, typename Category, typename = void>
		struct is_iterator_of_impl
			: public std::false_type
		{};
		template<typename MaybeIterator, typename Category>
		struct is_iterator_of_impl<
			MaybeIterator, Category,
			typename std::enable_if<sprout::is_iterator<MaybeIterator>::value>::type
		>
			: public sprout::is_iterator_category_of<typename std::iterator_traits<MaybeIterator>::iterator_category, Category>
		{};
	}	// namespace detail

	//
	// is_iterator_of
	//
	template<typename MaybeIterator, typename Category>
	struct is_iterator_of
		: public sprout::detail::is_iterator_of_impl<MaybeIterator, Category>
	{};

	//
	// is_input_iterator
	//
	template<typename MaybeIterator>
	struct is_input_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::input_iterator_tag>
	{};
	//
	// is_output_iterator
	//
	template<typename MaybeIterator>
	struct is_output_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::output_iterator_tag>
	{};
	//
	// is_forward_iterator
	//
	template<typename MaybeIterator>
	struct is_forward_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::forward_iterator_tag>
	{};
	//
	// is_bidirectional_iterator
	//
	template<typename MaybeIterator>
	struct is_bidirectional_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::bidirectional_iterator_tag>
	{};
	//
	// is_random_access_iterator
	//
	template<typename MaybeIterator>
	struct is_random_access_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::random_access_iterator_tag>
	{};

	//
	// is_constant_distance_iterator
	//
	template<typename MaybeIterator>
	struct is_constant_distance_iterator
		: public std::integral_constant<
			bool,
			sprout::is_random_access_iterator<MaybeIterator>::value && !std::is_pointer<MaybeIterator>::value
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP
