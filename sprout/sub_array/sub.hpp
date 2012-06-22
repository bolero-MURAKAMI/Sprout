#ifndef SPROUT_SUB_ARRAY_SUB_HPP
#define SPROUT_SUB_ARRAY_SUB_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/container.hpp>
#include <sprout/sub_array/type_traits.hpp>

namespace sprout {

	//
	// sub
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::const_iterator first,
		typename sprout::container_traits<sprout::sub_array<Container&> >::const_iterator last
		)
	{
		return sprout::sub_array<Container&>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type first,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type last
		)
	{
		return sprout::sub_array<Container&>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type first
		)
	{
		return sprout::sub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr
		)
	{
		return sprout::sub(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// sub
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type first
		)
	{
		return sprout::sub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr
		)
	{
		return sprout::sub(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// sub
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first,
		typename sprout::container_traits<Container>::const_iterator last
		)
	{
		return Container(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type first,
		typename sprout::container_traits<Container>::difference_type last
		)
	{
		return Container(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type first
		)
	{
		return sprout::sub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr
		)
	{
		return sprout::sub(arr, sprout::begin(arr), sprout::end(arr));
	}

	//
	// csub
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator first
		)
	{
		return sprout::csub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type first
		)
	{
		return sprout::csub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr
		)
	{
		return sprout::csub(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// csub
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type csub(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first,
		typename sprout::container_traits<Container>::const_iterator last
		)
	{
		return sprout::sub_array<typename Container::internal_type const&>(arr.get_array(), first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type csub(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type first,
		typename sprout::container_traits<Container>::difference_type last
		)
	{
		return sprout::sub_array<typename Container::internal_type const&>(
			arr.get_array(),
			sprout::next(sprout::begin(arr), first),
			sprout::next(sprout::begin(arr), last)
		);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type csub(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first
		)
	{
		return sprout::csub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type csub(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type first
		)
	{
		return sprout::csub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type csub(
		Container const& arr
		)
	{
		return sprout::csub(arr, sprout::begin(arr), sprout::end(arr));
	}

	//
	// sub_copy
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first,
		typename sprout::container_traits<Container>::const_iterator last
		)
	{
		return sprout::sub_array<Container>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type first,
		typename sprout::container_traits<Container>::difference_type last
		)
	{
		return sprout::sub_array<Container>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first
		)
	{
		return sprout::sub_copy(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type first
		)
	{
		return sprout::sub_copy(arr, first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr
		)
	{
		return sprout::sub_copy(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// sub_copy
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first,
		typename sprout::container_traits<Container>::const_iterator last
		)
	{
		return sprout::sub_array<typename Container::internal_type>(arr.get_array(), first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type first,
		typename sprout::container_traits<Container>::difference_type last
		)
	{
		return sprout::sub_array<typename Container::internal_type>(
			arr.get_array(),
			sprout::next(sprout::begin(arr), first),
			sprout::next(sprout::begin(arr), last)
			);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first
		)
	{
		return sprout::sub_copy(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type first
		)
	{
		return sprout::sub_copy(arr, first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type sub_copy(
		Container const& arr
		)
	{
		return sprout::sub_copy(arr, sprout::begin(arr), sprout::end(arr));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_SUB_HPP
