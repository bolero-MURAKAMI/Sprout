#ifndef SPROUT_SUB_ARRAY_HPP
#define SPROUT_SUB_ARRAY_HPP

#include <algorithm>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/detail/if.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace detail {
		struct is_non_reference_array_tag {};
		struct is_not_non_reference_array_tag {};

		template<typename Array>
		class sub_array_impl {
		protected:
			typedef Array array_type;
			typedef typename std::remove_reference<array_type>::type container_type;
			typedef typename std::remove_const<container_type>::type fixed_container_type;
		protected:
			static constexpr bool is_reference = std::is_reference<array_type>::value;
			static constexpr bool is_const = std::is_const<container_type>::value;
		protected:
			typedef typename sprout::fixed_container_traits<container_type>::value_type value_type;
			typedef typename sprout::detail::if_c<
				is_const,
				typename sprout::fixed_container_traits<container_type>::const_iterator,
				typename sprout::fixed_container_traits<container_type>::iterator
			>::type iterator;
			typedef typename sprout::fixed_container_traits<container_type>::const_iterator const_iterator;
			typedef typename sprout::detail::if_c<
				is_const,
				typename sprout::fixed_container_traits<container_type>::const_reference,
				typename sprout::fixed_container_traits<container_type>::reference
			>::type reference;
			typedef typename sprout::fixed_container_traits<container_type>::const_reference const_reference;
			typedef typename sprout::fixed_container_traits<container_type>::size_type size_type;
			typedef typename sprout::fixed_container_traits<container_type>::difference_type difference_type;
			typedef typename sprout::detail::if_c<
				is_const,
				typename sprout::fixed_container_traits<container_type>::const_pointer,
				typename sprout::fixed_container_traits<container_type>::pointer
			>::type pointer;
			typedef typename sprout::fixed_container_traits<container_type>::const_pointer const_pointer;
		protected:
			static constexpr size_type static_size = sprout::fixed_container_traits<container_type>::fixed_size;
			static constexpr size_type fixed_size = static_size;
		protected:
			typedef typename sprout::detail::if_c<
				is_reference,
				container_type*,
				typename std::remove_const<container_type>::type
			>::type holder_type;
			typedef typename sprout::detail::if_c<
				is_reference,
				container_type&,
				container_type const&
			>::type param_type;
			typedef container_type const& const_param_type;
		protected:
			typedef typename sprout::detail::if_c<
				std::is_array<holder_type>::value,
				sprout::detail::is_non_reference_array_tag,
				sprout::detail::is_not_non_reference_array_tag
			>::type array_tag;
		protected:
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				std::is_reference<Arr>::value,
				holder_type
			>::type to_holder(param_type arr) {
				return &arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				holder_type const&
			>::type to_holder(param_type arr) {
				return arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				std::is_reference<Arr>::value,
				param_type
			>::type to_param(holder_type arr) {
				return *arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				param_type
			>::type to_param(holder_type& arr) {
				return arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				param_type
			>::type to_param(holder_type const& arr) {
				return arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				std::is_reference<Arr>::value,
				const_param_type
			>::type to_const_param(holder_type arr) {
				return *arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				const_param_type
			>::type to_const_param(holder_type const& arr) {
				return arr;
			}
		protected:
			holder_type array_;
			difference_type first_;
			difference_type last_;
		public:
			sub_array_impl() = default;
		protected:
			template<typename ArrayTag, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ArrayTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				const_iterator first,
				const_iterator last,
				typename std::enable_if<std::is_same<ArrayTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_{to_holder<Array>(arr)[Indexes]...}
				, first_(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::cbegin(arr), first))
				, last_(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::cbegin(arr), last))
			{}
			template<typename ArrayTag, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ArrayTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				const_iterator first,
				const_iterator last,
				typename std::enable_if<!std::is_same<ArrayTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_(to_holder<Array>(arr))
				, first_(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::cbegin(arr), first))
				, last_(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::cbegin(arr), last))
			{}
			template<typename ArrayTag, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ArrayTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				difference_type first,
				difference_type last,
				typename std::enable_if<std::is_same<ArrayTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_{to_holder<Array>(arr)[Indexes]...}
				, first_(first)
				, last_(last)
			{}
			template<typename ArrayTag, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ArrayTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				difference_type first,
				difference_type last,
				typename std::enable_if<!std::is_same<ArrayTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_(to_holder<Array>(arr))
				, first_(first)
				, last_(last)
			{}
		};
	}	// namespace detail

	//
	// sub_array
	//
	template<typename Array>
	class sub_array
		: private sprout::detail::sub_array_impl<Array>
	{
	private:
		typedef sprout::detail::sub_array_impl<Array> impl_type;
	public:
		typedef typename impl_type::array_type array_type;
		typedef typename impl_type::container_type container_type;
		typedef typename impl_type::fixed_container_type fixed_container_type;
	public:
		static constexpr bool is_reference = impl_type::is_reference;
		static constexpr bool is_const = impl_type::is_const;
	public:
		typedef typename impl_type::value_type value_type;
		typedef typename impl_type::iterator iterator;
		typedef typename impl_type::const_iterator const_iterator;
		typedef typename impl_type::reference reference;
		typedef typename impl_type::const_reference const_reference;
		typedef typename impl_type::size_type size_type;
		typedef typename impl_type::difference_type difference_type;
		typedef typename impl_type::pointer pointer;
		typedef typename impl_type::const_pointer const_pointer;
	public:
		static constexpr size_type static_size = impl_type::static_size;
		static constexpr size_type fixed_size = impl_type::fixed_size;
	public:
		typedef typename impl_type::holder_type holder_type;
		typedef typename impl_type::param_type param_type;
		typedef typename impl_type::const_param_type const_param_type;
	private:
		typedef typename impl_type::array_tag array_tag;
	private:
		using impl_type::array_;
		using impl_type::first_;
		using impl_type::last_;
	public:
		sub_array() = default;
		SPROUT_CONSTEXPR sub_array(param_type arr, const_iterator first, const_iterator last)
			: impl_type(
				array_tag(),
				arr,
				typename sprout::index_range<0, fixed_size>::type(),
				first,
				last
				)
		{}
		SPROUT_CONSTEXPR sub_array(param_type arr, difference_type first, difference_type last)
			: impl_type(
				array_tag(),
				arr,
				typename sprout::index_range<0, fixed_size>::type(),
				first,
				last
				)
		{}
		SPROUT_CONSTEXPR sub_array(sub_array<Array> const& other, const_iterator first, const_iterator last)
			: impl_type(
				array_tag(),
				impl_type::template to_param<Array>(other.array_),
				typename sprout::index_range<0, fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(other.get_array()), first),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(other.get_array()), last)
				)
		{}
		SPROUT_CONSTEXPR sub_array(sub_array<Array> const& other, difference_type first, difference_type last)
			: impl_type(
				array_tag(),
				impl_type::template to_param<Array>(other.array_),
				typename sprout::index_range<0, fixed_size>::type(),
				first + other.first_,
				last + other.first_
				)
		{}
		param_type get_fixed() {
			return impl_type::template to_param<Array>(array_);
		}
		SPROUT_CONSTEXPR const_param_type get_fixed() const {
			return impl_type::template to_const_param<Array>(array_);
		}
		SPROUT_CONSTEXPR const_param_type get_cfixed() const {
			return impl_type::template to_const_param<Array>(array_);
		}
		param_type get_array() {
			return impl_type::template to_param<Array>(array_);
		}
		SPROUT_CONSTEXPR const_param_type get_array() const {
			return impl_type::template to_const_param<Array>(array_);
		}
		SPROUT_CONSTEXPR size_type size() const {
			return last_ - first_;
		}
		SPROUT_CONSTEXPR bool empty() const {
			return size() != 0;
		}
		SPROUT_CONSTEXPR size_type max_size() const {
			return size();
		}
		void rangecheck(size_type i) const {
			if (i >= size()) {
				//boost::throw_exception(std::out_of_range("sub_array<>: index out of range"));
				throw std::out_of_range("sub_array<>: index out of range");
			}
		}
		iterator begin() {
			return sprout::begin(get_array()) + first_;
		}
		SPROUT_CONSTEXPR const_iterator begin() const {
			return sprout::begin(get_array()) + first_;
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const {
			return first_;
		}
		iterator end() {
			return sprout::begin(get_array()) + last_;
		}
		SPROUT_CONSTEXPR const_iterator end() const {
			return sprout::begin(get_array()) + last_;
		}
		SPROUT_CONSTEXPR const_iterator cend() const {
			return sprout::begin(get_array()) + last_;
		}
		reference operator[](size_type i) {
			return *(sprout::begin(get_array()) + first_ + i);
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return *(sprout::begin(get_array()) + first_ + i);
		}
		reference at(size_type i) {
			rangecheck(i);
			return *(sprout::begin(get_array()) + first_ + i);
		}
		const_reference at(size_type i) const {
			rangecheck(i);
			return *(sprout::begin(get_array()) + first_ + i);
		}
		reference front() {
			return get_array()[first_];
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return get_array()[first_];
		}
		reference back() {
			return get_array()[last_ - 1];
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return get_array()[last_ - 1];
		}
		pointer data() {
			return get_array().data() + first_;
		}
		SPROUT_CONSTEXPR const_pointer data() const {
			return get_array().data() + first_;
		}
		pointer c_array() {
			return data();
		}
		void assign (const_reference value) {
			fill(value);
		}
		void fill(const_reference value) {
			std::fill_n(begin(), size(), value);
		}
		template<typename Array2>
		void swap(sub_array<Array2>& other) {
			using std::swap;
			swap(other.array_, array_);
			swap(other.first_, first_);
			swap(other.last_, last_);
		}
		template<typename Array2>
		sub_array<Array>& operator=(sub_array<Array2> const& rhs) {
			array_ = rhs.array_;
			first_ = rhs.first_;
			last_ = rhs.last_;
			return *this;
		}
		template<typename Array2>
		sub_array<Array>& operator=(sub_array<Array2>&& rhs) {
			array_ = std::move(rhs.array_);
			first_ = std::move(rhs.first_);
			last_ = std::move(rhs.last_);
			return *this;
		}
	};
	template<typename Array>
	SPROUT_CONSTEXPR inline bool operator==(sprout::sub_array<Array> const& lhs, sprout::sub_array<Array> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::equal(sprout::begin(lhs), sprout::end(lhs), sprout::begin(rhs));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline bool operator!=(sprout::sub_array<Array> const& lhs, sprout::sub_array<Array> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline bool operator<(sprout::sub_array<Array> const& lhs, sprout::sub_array<Array> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::lexicographical_compare(sprout::begin(lhs), sprout::end(lhs), sprout::begin(rhs), sprout::end(rhs));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline bool operator>(sprout::sub_array<Array> const& lhs, sprout::sub_array<Array> const& rhs) {
		return rhs < lhs;
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline bool operator<=(sprout::sub_array<Array> const& lhs, sprout::sub_array<Array> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline bool operator>=(sprout::sub_array<Array> const& lhs, sprout::sub_array<Array> const& rhs) {
		return !(lhs < rhs);
	}

	//
	// swap
	//
	template<typename Array>
	SPROUT_CONSTEXPR inline void swap(sprout::sub_array<Array>& lhs, sprout::sub_array<Array>& rhs) {
		lhs.swap(rhs);
	}

	//
	// fixed_container_traits
	//
	template<typename Array>
	struct fixed_container_traits<sprout::sub_array<Array> >
		: public sprout::detail::fixed_container_traits_base<sprout::sub_array<Array> >
	{
	public:
		typedef typename sprout::sub_array<Array>::fixed_container_type fixed_container_type;
	public:
		static constexpr typename sprout::detail::fixed_container_traits_base<sprout::sub_array<Array> >::size_type fixed_size
			= std::tuple_size<typename std::remove_const<fixed_container_type>::type>::value
			;
	};

	//
	// rebind_fixed_size
	//
	template<typename Array>
	struct rebind_fixed_size<sprout::sub_array<Array> > {
	public:
		template<typename sprout::fixed_container_traits<sprout::sub_array<Array> >::size_type S>
		struct apply {
			public:
				typedef sprout::sub_array<
					typename sprout::rebind_fixed_size<
						typename sprout::fixed_container_traits<sprout::sub_array<Array> >::fixed_container_type
					>::template apply<S>::type
				> type;
		};
	};

	//
	// get_fixed_functor
	//
	template<typename Array>
	struct get_fixed_functor<sprout::sub_array<Array> > {
	public:
		typename sprout::fixed_container_traits<sprout::sub_array<Array> >::fixed_container_type& operator()(sprout::sub_array<Array>& cont) const {
			return cont.get_fixed();
		}
		SPROUT_CONSTEXPR typename sprout::fixed_container_traits<sprout::sub_array<Array> >::fixed_container_type const& operator()(sprout::sub_array<Array> const& cont) const {
			return cont.get_fixed();
		}
	};

	//
	// is_sub_array
	//
	template<typename T, typename Enable = void>
	struct is_sub_array {
	public:
		typedef std::integral_constant<bool, false> type;
		static constexpr bool value = type::value;
	};
	template<typename T>
	struct is_sub_array<
		T,
		typename std::enable_if<
			std::is_same<
				T,
				sprout::sub_array<typename T::array_type>
			>::value
		>::type
	> {
	public:
		typedef std::integral_constant<bool, true> type;
		static constexpr bool value = type::value;
	};

	//
	// sub
	//
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array&> >::type sub(
		Array& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array&> >::const_iterator first,
		typename sprout::fixed_container_traits<sprout::sub_array<Array&> >::const_iterator last
		)
	{
		return sprout::sub_array<Array&>(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array&> >::type sub(
		Array& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array&> >::difference_type first,
		typename sprout::fixed_container_traits<sprout::sub_array<Array&> >::difference_type last
		)
	{
		return sprout::sub_array<Array&>(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array&> >::type sub(
		Array& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array&> >::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array&> >::type sub(
		Array& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array&> >::difference_type first
		)
	{
		return sprout::sub(arr, first, sprout::size(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array&> >::type sub(
		Array& arr
		)
	{
		return sprout::sub(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// sub
	//
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type sub(
		Array const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::const_iterator first,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::const_iterator last
		)
	{
		return sprout::sub_array<Array const&>(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type sub(
		Array const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::difference_type first,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::difference_type last
		)
	{
		return sprout::sub_array<Array const&>(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type sub(
		Array const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type sub(
		Array const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::difference_type first
		)
	{
		return sprout::sub(arr, first, sprout::size(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type sub(
		Array const& arr
		)
	{
		return sprout::sub(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// sub
	//
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, Array>::type sub(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::const_iterator first,
		typename sprout::fixed_container_traits<Array>::const_iterator last
		)
	{
		return Array(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, Array>::type sub(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::difference_type first,
		typename sprout::fixed_container_traits<Array>::difference_type last
		)
	{
		return Array(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, Array>::type sub(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, Array>::type sub(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::difference_type first
		)
	{
		return sprout::sub(arr, first, sprout::size(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, Array>::type sub(
		Array const& arr
		)
	{
		return sprout::sub(arr, sprout::begin(arr), sprout::end(arr));
	}

	//
	// csub
	//
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type csub(
		Array const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::const_iterator first,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::const_iterator last
		)
	{
		return sprout::sub_array<Array const&>(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type csub(
		Array const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::difference_type first,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::difference_type last
		)
	{
		return sprout::sub_array<Array const&>(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type csub(
		Array const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::const_iterator first
		)
	{
		return sprout::csub(arr, first, sprout::end(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type csub(
		Array const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Array const&> >::difference_type first
		)
	{
		return sprout::csub(arr, first, sprout::size(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array const&> >::type csub(
		Array const& arr
		)
	{
		return sprout::csub(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// csub
	//
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type const&> >::type csub(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::const_iterator first,
		typename sprout::fixed_container_traits<Array>::const_iterator last
		)
	{
		return sprout::sub_array<typename Array::container_type const&>(arr.get_array(), first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type const&> >::type csub(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::difference_type first,
		typename sprout::fixed_container_traits<Array>::difference_type last
		)
	{
		return sprout::sub_array<typename Array::container_type const&>(arr.get_array(), sprout::begin(arr) + first, sprout::begin(arr) + last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type const&> >::type csub(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::const_iterator first
		)
	{
		return sprout::csub(arr, first, sprout::end(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type const&> >::type csub(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::difference_type first
		)
	{
		return sprout::csub(arr, first, sprout::size(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type const&> >::type csub(
		Array const& arr
		)
	{
		return sprout::csub(arr, sprout::begin(arr), sprout::end(arr));
	}

	//
	// sub_copy
	//
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array> >::type sub_copy(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::const_iterator first,
		typename sprout::fixed_container_traits<Array>::const_iterator last
		)
	{
		return sprout::sub_array<Array>(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array> >::type sub_copy(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::difference_type first,
		typename sprout::fixed_container_traits<Array>::difference_type last
		)
	{
		return sprout::sub_array<Array>(arr, first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array> >::type sub_copy(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::const_iterator first
		)
	{
		return sprout::sub_copy(arr, first, sprout::end(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array> >::type sub_copy(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::difference_type first
		)
	{
		return sprout::sub_copy(arr, first, sprout::size(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Array>::value, sprout::sub_array<Array> >::type sub_copy(
		Array const& arr
		)
	{
		return sprout::sub_copy(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// sub_copy
	//
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type> >::type sub_copy(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::const_iterator first,
		typename sprout::fixed_container_traits<Array>::const_iterator last
		)
	{
		return sprout::sub_array<typename Array::container_type>(arr.get_array(), first, last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type> >::type sub_copy(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::difference_type first,
		typename sprout::fixed_container_traits<Array>::difference_type last
		)
	{
		return sprout::sub_array<typename Array::container_type>(arr.get_array(), sprout::begin(arr) + first, sprout::begin(arr) + last);
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type> >::type sub_copy(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::const_iterator first
		)
	{
		return sprout::sub_copy(arr, first, sprout::end(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type> >::type sub_copy(
		Array const& arr,
		typename sprout::fixed_container_traits<Array>::difference_type first
		)
	{
		return sprout::sub_copy(arr, first, sprout::size(arr));
	}
	template<typename Array>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Array>::value, sprout::sub_array<typename Array::container_type> >::type sub_copy(
		Array const& arr
		)
	{
		return sprout::sub_copy(arr, sprout::begin(arr), sprout::end(arr));
	}
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename Array>
	struct tuple_size<sprout::sub_array<Array> > {
	public:
		static constexpr std::size_t value = std::tuple_size<
			typename std::remove_const<
				typename std::remove_reference<Array>::type
			>::type
		>::value;
	};

	//
	// tuple_element
	//
	template<std::size_t I, typename Array>
	struct tuple_element<I, sprout::sub_array<Array> > {
	public:
		typedef typename std::tuple_element<
			I,
			typename std::remove_const<
				typename std::remove_reference<Array>::type
			>::type
		>::type type;
	};

	//
	// get
	//
	template<std::size_t I, typename T, typename Array>
	T& get(sprout::sub_array<Array>& arr) SPROUT_NOEXCEPT {
		static_assert(I < sprout::fixed_container_traits<sprout::sub_array<Array> >::fixed_size, "tuple_element<>: index out of range");
		return *(sprout::fixed_begin(arr) + I);
	}
	template<std::size_t I, typename T, typename Array>
	SPROUT_CONSTEXPR T const& get(sprout::sub_array<Array> const& arr) SPROUT_NOEXCEPT {
		static_assert(I < sprout::fixed_container_traits<sprout::sub_array<Array> >::fixed_size, "tuple_element<>: index out of range");
		return *(sprout::fixed_begin(arr) + I);
	}
	template<std::size_t I, typename T, typename Array>
	T&& get(sprout::sub_array<Array>&& arr) SPROUT_NOEXCEPT {
		return std::move(get<I>(arr));
	}
}	// namespace std

#endif	// #ifndef SPROUT_SUB_ARRAY_HPP
