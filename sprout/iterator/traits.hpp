#ifndef SPROUT_ITERATOR_TRAITS_HPP
#define SPROUT_ITERATOR_TRAITS_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>

namespace sprout {
	namespace detail {
		// has_iterator_category
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(iterator_category);
	}	// namespace detail
	//
	// is_iterator
	//
	template<typename Iterator>
	struct is_iterator
		: sprout::detail::has_iterator_category<std::iterator_traits<Iterator> >
	{};

	namespace detail {
		template<typename Iterator, typename = void>
		struct is_input_iterator_impl
			: std::false_type
		{};
		template<typename Iterator>
		struct is_input_iterator_impl<
			Iterator,
			typename std::enable_if<sprout::is_iterator<Iterator>::value>::type
		>
			: std::is_convertible<
				typename std::iterator_traits<Iterator>::iterator_category,
				std::input_iterator_tag
			>
		{};
	}	// namespace detail
	//
	// is_input_iterator
	//
	template<typename Iterator>
	struct is_input_iterator
		: sprout::detail::is_input_iterator_impl<Iterator>
	{};

	namespace detail {
		template<typename Iterator, typename = void>
		struct is_output_iterator_impl
			: std::false_type
		{};
		template<typename Iterator>
		struct is_output_iterator_impl<
			Iterator,
			typename std::enable_if<sprout::is_iterator<Iterator>::value>::type
		>
			: std::is_convertible<
				typename std::iterator_traits<Iterator>::iterator_category,
				std::output_iterator_tag
			>
		{};
	}	// namespace detail
	//
	// is_output_iterator
	//
	template<typename Iterator>
	struct is_output_iterator
		: sprout::detail::is_output_iterator_impl<Iterator>
	{};

	namespace detail {
		template<typename Iterator, typename = void>
		struct is_forward_iterator_impl
			: std::false_type
		{};
		template<typename Iterator>
		struct is_forward_iterator_impl<
			Iterator,
			typename std::enable_if<sprout::is_iterator<Iterator>::value>::type
		>
			: std::is_convertible<
				typename std::iterator_traits<Iterator>::iterator_category,
				std::forward_iterator_tag
			>
		{};
	}	// namespace detail
	//
	// is_forward_iterator
	//
	template<typename Iterator>
	struct is_forward_iterator
		: sprout::detail::is_forward_iterator_impl<Iterator>
	{};

	namespace detail {
		template<typename Iterator, typename = void>
		struct is_bidirectional_iterator_impl
			: std::false_type
		{};
		template<typename Iterator>
		struct is_bidirectional_iterator_impl<
			Iterator,
			typename std::enable_if<sprout::is_iterator<Iterator>::value>::type
		>
			: std::is_convertible<
				typename std::iterator_traits<Iterator>::iterator_category,
				std::bidirectional_iterator_tag
			>
		{};
	}	// namespace detail
	//
	// is_bidirectional_iterator
	//
	template<typename Iterator>
	struct is_bidirectional_iterator
		: sprout::detail::is_bidirectional_iterator_impl<Iterator>
	{};

	namespace detail {
		template<typename Iterator, typename = void>
		struct is_random_access_iterator_impl
			: std::false_type
		{};
		template<typename Iterator>
		struct is_random_access_iterator_impl<
			Iterator,
			typename std::enable_if<sprout::is_iterator<Iterator>::value>::type
		>
			: std::is_convertible<
				typename std::iterator_traits<Iterator>::iterator_category,
				std::random_access_iterator_tag
			>
		{};
	}	// namespace detail
	//
	// is_random_access_iterator
	//
	template<typename Iterator>
	struct is_random_access_iterator
		: sprout::detail::is_random_access_iterator_impl<Iterator>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TRAITS_HPP
