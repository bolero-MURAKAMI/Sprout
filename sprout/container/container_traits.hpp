#ifndef SPROUT_CONTAINER_CONTAINER_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_TRAITS_HPP

#include <cstddef>
#include <iterator>
#include <array>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>
#include <sprout/type_traits/inherit_if_xxx.hpp>
#include <sprout/container/detail/array_like.hpp>
#if SPROUT_USE_PTR_INDEX_ITERATOR_IMPLEMENTATION
#	include <sprout/iterator/ptr_index_iterator.hpp>
#endif

namespace sprout {
	template<typename Container>
	struct container_traits;

	namespace detail {
		//
		// has_value_type
		// has_iterator
		// has_const_iterator
		// has_reference
		// has_const_reference
		// has_size_type
		// has_difference_type
		// has_pointer
		// has_const_pointer
		// has_static_size
		//
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(value_type);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(iterator);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(const_iterator);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(reference);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(const_reference);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(size_type);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(difference_type);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(pointer);
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(const_pointer);
		SPROUT_HAS_XXX_VALUE_DEF_LAZY(static_size);

		//
		// inherit_if_value_type
		// inherit_if_iterator
		// inherit_if_const_iterator
		// inherit_if_reference
		// inherit_if_const_reference
		// inherit_if_size_type
		// inherit_if_difference_type
		// inherit_if_pointer
		// inherit_if_const_pointer
		// inherit_if_static_size
		//
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(value_type);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(iterator);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(const_iterator);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(reference);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(const_reference);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(size_type);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(difference_type);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(pointer);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(const_pointer);
		SPROUT_INHERIT_IF_XXX_CONSTANT_DEF_LAZY(static_size);

		//
		// inherit_iterator_if_const_iterator
		// inherit_const_iterator_if_iterator
		// inherit_reference_if_const_reference
		// inherit_const_reference_if_reference
		// inherit_pointer_if_const_pointer
		// inherit_const_pointer_if_pointer
		//
		SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_LAZY(iterator, const_iterator);
		SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_LAZY(const_iterator, iterator);
		SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_LAZY(reference, const_reference);
		SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_LAZY(const_reference, reference);
		SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_LAZY(pointer, const_pointer);
		SPROUT_INHERIT_ALIAS_IF_XXX_TYPE_DEF_LAZY(const_pointer, pointer);

		//
		// has_container_nosy_iterator
		//
		template<typename Container>
		struct has_container_nosy_iterator
			: public std::integral_constant<
				bool,
				sprout::detail::has_iterator<Container>::value
					|| sprout::detail::has_const_iterator<Container>::value
			>
		{};
		//
		// has_container_nosy_value_type
		//
		template<typename Container>
		struct has_container_nosy_value_type
			: public std::integral_constant<
				bool,
				sprout::detail::has_value_type<Container>::value
					|| sprout::detail::has_container_nosy_iterator<Container>::value
			>
		{};
		//
		// has_container_nosy_static_size
		//
		template<typename Container>
		struct has_container_nosy_static_size
			: public std::integral_constant<
				bool,
				sprout::detail::has_static_size<Container>::value
					|| sprout::detail::is_array_like<Container>::value
			>
		{};

		//
		// container_nosy_iterator
		//
		template<typename Container, bool HasIterator, bool HasConstIterator>
		struct container_nosy_iterator_impl {};
		template<typename Container, bool HasConstIterator>
		struct container_nosy_iterator_impl<Container, true, HasConstIterator>
			: public sprout::detail::inherit_if_iterator<Container>
		{};
		template<typename Container>
		struct container_nosy_iterator_impl<Container, false, true>
			: public sprout::detail::inherit_iterator_if_const_iterator<Container>
		{};
		template<typename Container>
		struct container_nosy_iterator
			: public sprout::detail::container_nosy_iterator_impl<
				Container,
				sprout::detail::has_iterator<Container>::value,
				sprout::detail::has_const_iterator<Container>::value
			>
		{};
		//
		// container_nosy_const_iterator
		//
		template<typename Container, bool HasConstIterator, bool HasIterator>
		struct container_nosy_const_iterator_impl {};
		template<typename Container, bool HasIterator>
		struct container_nosy_const_iterator_impl<Container, true, HasIterator>
			: public sprout::detail::inherit_if_const_iterator<Container>
		{};
		template<typename Container>
		struct container_nosy_const_iterator_impl<Container, false, true>
			: public sprout::detail::inherit_const_iterator_if_iterator<Container>
		{};
		template<typename Container>
		struct container_nosy_const_iterator
			: public sprout::detail::container_nosy_const_iterator_impl<
				Container,
				sprout::detail::has_const_iterator<Container>::value,
				sprout::detail::has_iterator<Container>::value
			>
		{};
		//
		// container_nosy_value_type
		//
		template<typename Container, bool HasValueType, bool HasNosyIterator>
		struct container_nosy_value_type_impl {};
		template<typename Container, bool HasNosyIterator>
		struct container_nosy_value_type_impl<Container, true, HasNosyIterator> {
		public:
			typedef typename Container::value_type value_type;
		};
		template<typename Container>
		struct container_nosy_value_type_impl<Container, false, true> {
		public:
			typedef typename std::iterator_traits<
				typename sprout::detail::container_nosy_iterator<Container>::iterator
			>::value_type value_type;
		};
		template<typename Container>
		struct container_nosy_value_type
			: public sprout::detail::container_nosy_value_type_impl<
				Container,
				sprout::detail::has_value_type<Container>::value,
				sprout::detail::has_container_nosy_iterator<Container>::value
			>
		{};
		//
		// container_nosy_reference
		//
		template<typename Container, bool HasReference, bool HasConstReference, bool HasNosyIterator>
		struct container_nosy_reference_impl {};
		template<typename Container, bool HasConstReference, bool HasNosyIterator>
		struct container_nosy_reference_impl<Container, true, HasConstReference, HasNosyIterator> {
		public:
			typedef typename Container::reference reference;
		};
		template<typename Container, bool HasNosyIterator>
		struct container_nosy_reference_impl<Container, false, true, HasNosyIterator> {
		public:
			typedef typename Container::const_reference reference;
		};
		template<typename Container>
		struct container_nosy_reference_impl<Container, false, false, true> {
		public:
			typedef typename std::iterator_traits<
				typename sprout::detail::container_nosy_iterator<Container>::iterator
			>::reference reference;
		};
		template<typename Container>
		struct container_nosy_reference
			: public sprout::detail::container_nosy_reference_impl<
				Container,
				sprout::detail::has_reference<Container>::value,
				sprout::detail::has_const_reference<Container>::value,
				sprout::detail::has_container_nosy_iterator<Container>::value
			>
		{};
		//
		// container_nosy_const_reference
		//
		template<typename Container, bool HasConstReference, bool HasReference, bool HasNosyIterator>
		struct container_nosy_const_reference_impl {};
		template<typename Container, bool HasReference, bool HasNosyIterator>
		struct container_nosy_const_reference_impl<Container, true, HasReference, HasNosyIterator> {
		public:
			typedef typename Container::const_reference const_reference;
		};
		template<typename Container, bool HasNosyIterator>
		struct container_nosy_const_reference_impl<Container, false, true, HasNosyIterator> {
		public:
			typedef typename Container::reference const_reference;
		};
		template<typename Container>
		struct container_nosy_const_reference_impl<Container, false, false, true> {
		public:
			typedef typename std::iterator_traits<
				typename sprout::detail::container_nosy_const_iterator<Container>::const_iterator
			>::reference const_reference;
		};
		template<typename Container>
		struct container_nosy_const_reference
			: public sprout::detail::container_nosy_const_reference_impl<
				Container,
				sprout::detail::has_const_reference<Container>::value,
				sprout::detail::has_reference<Container>::value,
				sprout::detail::has_container_nosy_iterator<Container>::value
			>
		{};
		//
		// container_nosy_difference_type
		//
		template<typename Container, bool HasDifferenceType, bool HasNosyIterator>
		struct container_nosy_difference_type_impl {
		public:
			typedef std::ptrdiff_t difference_type;
		};
		template<typename Container, bool HasNosyIterator>
		struct container_nosy_difference_type_impl<Container, true, HasNosyIterator> {
		public:
			typedef typename Container::difference_type difference_type;
		};
		template<typename Container>
		struct container_nosy_difference_type_impl<Container, false, true> {
		public:
			typedef typename std::iterator_traits<
				typename sprout::detail::container_nosy_iterator<Container>::iterator
			>::difference_type difference_type;
		};
		template<typename Container>
		struct container_nosy_difference_type
			: public sprout::detail::container_nosy_difference_type_impl<
				Container,
				sprout::detail::has_difference_type<Container>::value,
				sprout::detail::has_container_nosy_iterator<Container>::value
			>
		{};
		//
		// container_nosy_size_type
		//
		template<typename Container, bool HasSizeType, bool HasNosyIterator>
		struct container_nosy_size_type_impl {
		public:
			typedef std::size_t size_type;
		};
		template<typename Container, bool HasNosyIterator>
		struct container_nosy_size_type_impl<Container, true, HasNosyIterator> {
		public:
			typedef typename Container::size_type size_type;
		};
		template<typename Container>
		struct container_nosy_size_type_impl<Container, false, true> {
		public:
			typedef typename std::make_unsigned<
				typename std::iterator_traits<
					typename sprout::detail::container_nosy_iterator<Container>::iterator
				>::difference_type
			>::type size_type;
		};
		template<typename Container>
		struct container_nosy_size_type
			: public sprout::detail::container_nosy_size_type_impl<
				Container,
				sprout::detail::has_size_type<Container>::value,
				sprout::detail::has_container_nosy_iterator<Container>::value
			>
		{};
		//
		// container_nosy_pointer
		//
		template<typename Container, bool HasPointer, bool HasConstPointer, bool HasNosyValueType>
		struct container_nosy_pointer_impl {};
		template<typename Container, bool HasConstPointer, bool HasNosyValueType>
		struct container_nosy_pointer_impl<Container, true, HasConstPointer, HasNosyValueType> {
		public:
			typedef typename Container::pointer pointer;
		};
		template<typename Container, bool HasNosyValueType>
		struct container_nosy_pointer_impl<Container, false, true, HasNosyValueType> {
		public:
			typedef typename Container::const_pointer pointer;
		};
		template<typename Container>
		struct container_nosy_pointer_impl<Container, false, false, true> {
		public:
			typedef typename sprout::detail::container_nosy_value_type<Container>::value_type* pointer;
		};
		template<typename Container>
		struct container_nosy_pointer
			: public sprout::detail::container_nosy_pointer_impl<
				Container,
				sprout::detail::has_pointer<Container>::value,
				sprout::detail::has_const_pointer<Container>::value,
				sprout::detail::has_container_nosy_value_type<Container>::value
			>
		{};
		//
		// container_nosy_const_pointer
		//
		template<typename Container, bool HasConstPointer, bool HasPointer, bool HasNosyValueType>
		struct container_nosy_const_pointer_impl {};
		template<typename Container, bool HasPointer, bool HasNosyValueType>
		struct container_nosy_const_pointer_impl<Container, true, HasPointer, HasNosyValueType> {
		public:
			typedef typename Container::const_pointer const_pointer;
		};
		template<typename Container, bool HasNosyValueType>
		struct container_nosy_const_pointer_impl<Container, false, true, HasNosyValueType> {
		public:
			typedef typename Container::pointer const_pointer;
		};
		template<typename Container>
		struct container_nosy_const_pointer_impl<Container, false, false, true> {
		public:
			typedef typename sprout::detail::container_nosy_value_type<Container>::value_type const* const_pointer;
		};
		template<typename Container>
		struct container_nosy_const_pointer
			: public sprout::detail::container_nosy_const_pointer_impl<
				Container,
				sprout::detail::has_const_pointer<Container>::value,
				sprout::detail::has_pointer<Container>::value,
				sprout::detail::has_container_nosy_value_type<Container>::value
			>
		{};
		//
		// container_nosy_static_size
		//
		template<typename Container, bool HasStaticSize, bool IsArrayLike>
		struct container_nosy_static_size_impl {};
		template<typename Container, bool IsArrayLike>
		struct container_nosy_static_size_impl<Container, true, IsArrayLike>
			: public sprout::detail::inherit_if_static_size<Container>
		{};
		template<typename Container>
		struct container_nosy_static_size_impl<Container, false, true>
			: public sprout::detail::inherit_if_static_size<Container>
		{
		public:
			SPROUT_STATIC_CONSTEXPR typename sprout::detail::array_like_static_size<Container>::value_type static_size
				= sprout::detail::array_like_static_size<Container>::value
				;
		};
		template<typename Container>
		SPROUT_CONSTEXPR_OR_CONST typename sprout::detail::array_like_static_size<Container>::value_type
			sprout::detail::container_nosy_static_size_impl<Container, false, true>::static_size
			;
		template<typename Container>
		struct container_nosy_static_size
			: public sprout::detail::container_nosy_static_size_impl<
				Container,
				sprout::detail::has_static_size<Container>::value,
				sprout::detail::is_array_like<Container>::value
			>
		{};

		//
		// container_nosy_fixed_size
		//
		template<typename Container, bool HasContainerNosyStaticSize>
		struct container_nosy_fixed_size_impl {};
		template<typename Container>
		struct container_nosy_fixed_size_impl<Container, true> {
		public:
			static SPROUT_CONSTEXPR decltype(sprout::detail::container_nosy_static_size<Container>::static_size)
			fixed_size() SPROUT_NOEXCEPT {
				return sprout::detail::container_nosy_static_size<Container>::static_size;
			}
		};
		template<typename Container>
		struct container_nosy_fixed_size
			: public sprout::detail::container_nosy_fixed_size_impl<
				Container,
				sprout::detail::has_container_nosy_static_size<Container>::value
			>
		{};

		//
		// container_traits_default
		//
		template<typename Container>
		struct container_traits_default
			: public sprout::detail::container_nosy_value_type<Container>
			, public sprout::detail::container_nosy_iterator<Container>
			, public sprout::detail::container_nosy_const_iterator<Container>
			, public sprout::detail::container_nosy_reference<Container>
			, public sprout::detail::container_nosy_const_reference<Container>
			, public sprout::detail::container_nosy_size_type<Container>
			, public sprout::detail::container_nosy_difference_type<Container>
			, public sprout::detail::container_nosy_pointer<Container>
			, public sprout::detail::container_nosy_const_pointer<Container>
			, public sprout::detail::container_nosy_static_size<Container>
			, public sprout::detail::container_nosy_fixed_size<Container>
		{};
		template<typename T, std::size_t N>
		struct container_traits_default<T[N]> {
		public:
			typedef T value_type;
#if SPROUT_USE_PTR_INDEX_ITERATOR_IMPLEMENTATION
			typedef sprout::ptr_index_iterator<T> iterator;
			typedef sprout::ptr_index_iterator<T const> const_iterator;
#else
			typedef T* iterator;
			typedef T const* const_iterator;
#endif
			typedef T& reference;
			typedef T const& const_reference;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T const* const_pointer;
		public:
			SPROUT_STATIC_CONSTEXPR size_type static_size = N ;
		public:
			static SPROUT_CONSTEXPR size_type
			fixed_size() SPROUT_NOEXCEPT {
				return static_size;
			}
		};
		template<typename T, std::size_t N>
		SPROUT_CONSTEXPR_OR_CONST typename sprout::detail::container_traits_default<T[N]>::size_type
		sprout::detail::container_traits_default<T[N]>::static_size;

		//
		// container_traits_const_default
		//
		template<typename Container>
		struct container_traits_const_default
			: public sprout::detail::inherit_if_value_type<sprout::container_traits<Container> >
			, public sprout::detail::inherit_if_const_iterator<sprout::container_traits<Container> >
			, public sprout::detail::inherit_if_const_reference<sprout::container_traits<Container> >
			, public sprout::detail::inherit_if_size_type<sprout::container_traits<Container> >
			, public sprout::detail::inherit_if_difference_type<sprout::container_traits<Container> >
			, public sprout::detail::inherit_if_const_pointer<sprout::container_traits<Container> >
			, public sprout::detail::inherit_if_static_size<sprout::container_traits<Container> >
			, public sprout::detail::container_nosy_fixed_size<sprout::container_traits<Container> >
			, public sprout::detail::inherit_iterator_if_const_iterator<sprout::container_traits<Container> >
			, public sprout::detail::inherit_reference_if_const_reference<sprout::container_traits<Container> >
			, public sprout::detail::inherit_pointer_if_const_pointer<sprout::container_traits<Container> >
		{};
	}	// namespace detail

	//
	// container_traits
	//
	template<typename Container>
	struct container_traits
		: public sprout::detail::container_traits_default<Container>
	{};
	template<typename Container>
	struct container_traits<Container const>
		: public sprout::detail::container_traits_const_default<Container>
	{};

	template<typename T, std::size_t N>
	struct container_traits<T[N]>
		: public sprout::detail::container_traits_default<T[N]>
	{};
	template<typename T, std::size_t N>
	struct container_traits<T const[N]>
		: public sprout::detail::container_traits_const_default<T[N]>
	{};

	//
	// container_traits_facade
	//
	template<typename Container>
	struct container_traits_facade
		: public sprout::detail::inherit_if_value_type<sprout::container_traits<Container> >
		, public sprout::detail::inherit_if_iterator<sprout::container_traits<Container> >
		, public sprout::detail::inherit_if_const_iterator<sprout::container_traits<Container> >
		, public sprout::detail::inherit_if_reference<sprout::container_traits<Container> >
		, public sprout::detail::inherit_if_const_reference<sprout::container_traits<Container> >
		, public sprout::detail::inherit_if_size_type<sprout::container_traits<Container> >
		, public sprout::detail::inherit_if_difference_type<sprout::container_traits<Container> >
		, public sprout::detail::inherit_if_pointer<sprout::container_traits<Container> >
		, public sprout::detail::inherit_if_const_pointer<sprout::container_traits<Container> >
		, public sprout::detail::inherit_if_static_size<sprout::container_traits<Container> >
		, public sprout::detail::container_nosy_fixed_size<sprout::container_traits<Container> >
	{};

	//
	// is_fixed_container
	//
	template<typename Container>
	struct is_fixed_container
		: public sprout::detail::has_static_size<sprout::container_traits<Container> >
	{};

	namespace detail {
		//
		// static_size_or_zero
		//
		template<typename Container, typename = void>
		struct static_size_or_zero;
		template<typename Container>
		struct static_size_or_zero<
			Container,
			typename std::enable_if<sprout::is_fixed_container<sprout::container_traits<Container> >::value>::type
		>
			: public std::integral_constant<
				typename sprout::container_traits<Container>::size_type,
				sprout::container_traits<Container>::static_size
			>
		{};
		template<typename Container>
		struct static_size_or_zero<
			Container,
			typename std::enable_if<!sprout::is_fixed_container<sprout::container_traits<Container> >::value>::type
		>
			: public std::integral_constant<
				typename sprout::container_traits<Container>::size_type,
				0
			>
		{};
	}	// namespace sprout
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_TRAITS_HPP
