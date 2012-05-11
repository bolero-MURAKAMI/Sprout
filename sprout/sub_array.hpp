#ifndef SPROUT_SUB_ARRAY_HPP
#define SPROUT_SUB_ARRAY_HPP

#include <algorithm>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		struct is_non_reference_array_tag {};
		struct is_not_non_reference_array_tag {};

		template<typename Container>
		class sub_array_impl {
		protected:
			typedef Container container_type;
			typedef typename std::remove_reference<container_type>::type internal_type;
		protected:
			SPROUT_STATIC_CONSTEXPR bool is_reference = std::is_reference<container_type>::value;
			SPROUT_STATIC_CONSTEXPR bool is_const = std::is_const<internal_type>::value;
		protected:
			typedef typename sprout::container_traits<internal_type>::const_iterator impl_const_iterator;
			typedef typename sprout::container_traits<internal_type>::difference_type impl_difference_type;
		protected:
			typedef typename std::conditional<
				is_reference,
				internal_type*,
				typename std::remove_const<internal_type>::type
			>::type holder_type;
			typedef typename std::conditional<
				is_reference,
				internal_type&,
				internal_type const&
			>::type param_type;
			typedef internal_type const& const_param_type;
		protected:
			typedef typename std::conditional<
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
			impl_difference_type first_;
			impl_difference_type last_;
		public:
			sub_array_impl() = default;
		protected:
			template<typename ContainerTag, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				impl_const_iterator first,
				impl_const_iterator last,
				typename std::enable_if<std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_{to_holder<Container>(arr)[Indexes]...}
				, first_(NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::cbegin(arr), first))
				, last_(NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::cbegin(arr), last))
			{}
			template<typename ContainerTag, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				impl_const_iterator first,
				impl_const_iterator last,
				typename std::enable_if<!std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_(to_holder<Container>(arr))
				, first_(NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::cbegin(arr), first))
				, last_(NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::cbegin(arr), last))
			{}
			template<typename ContainerTag, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				impl_difference_type first,
				impl_difference_type last,
				typename std::enable_if<std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_{to_holder<Container>(arr)[Indexes]...}
				, first_(first)
				, last_(last)
			{}
			template<typename ContainerTag, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				impl_difference_type first,
				impl_difference_type last,
				typename std::enable_if<!std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_(to_holder<Container>(arr))
				, first_(first)
				, last_(last)
			{}
		};
	}	// namespace detail

	//
	// sub_array
	//
	template<typename Container>
	class sub_array
		: private sprout::detail::sub_array_impl<Container>
		, public sprout::container_traits_facade<typename std::remove_reference<Container>::type>
	{
	private:
		typedef sprout::detail::sub_array_impl<Container> impl_type;
		typedef sprout::container_traits_facade<typename std::remove_reference<Container>::type> facade_type;
	public:
		typedef typename impl_type::container_type container_type;
		typedef typename impl_type::internal_type internal_type;
	public:
		SPROUT_STATIC_CONSTEXPR bool is_reference = impl_type::is_reference;
		SPROUT_STATIC_CONSTEXPR bool is_const = impl_type::is_const;
	public:
		typedef typename facade_type::iterator iterator;
		typedef typename facade_type::const_iterator const_iterator;
		typedef typename facade_type::reference reference;
		typedef typename facade_type::const_reference const_reference;
		typedef typename facade_type::size_type size_type;
		typedef typename facade_type::difference_type difference_type;
		typedef typename facade_type::pointer pointer;
		typedef typename facade_type::const_pointer const_pointer;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = facade_type::static_size;
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
		// construct/copy/destroy:
		sub_array() = default;
		SPROUT_CONSTEXPR sub_array(param_type arr, const_iterator first, const_iterator last)
			: impl_type(
				array_tag(),
				arr,
				typename sprout::index_range<0, static_size>::type(),
				first,
				last
				)
		{}
		SPROUT_CONSTEXPR sub_array(param_type arr, difference_type first, difference_type last)
			: impl_type(
				array_tag(),
				arr,
				typename sprout::index_range<0, static_size>::type(),
				first,
				last
				)
		{}
		SPROUT_CONSTEXPR sub_array(sub_array<Container> const& other, const_iterator first, const_iterator last)
			: impl_type(
				array_tag(),
				impl_type::template to_param<Container>(other.array_),
				typename sprout::index_range<0, static_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::begin(other.get_array()), first),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::begin(other.get_array()), last)
				)
		{}
		SPROUT_CONSTEXPR sub_array(sub_array<Container> const& other, difference_type first, difference_type last)
			: impl_type(
				array_tag(),
				impl_type::template to_param<Container>(other.array_),
				typename sprout::index_range<0, static_size>::type(),
				first + other.first_,
				last + other.first_
				)
		{}

		void fill(const_reference value) {
			std::fill_n(begin(), size(), value);
		}
		template<typename Container2>
		void swap(sub_array<Container2>& other) {
			using std::swap;
			swap(other.array_, array_);
			swap(other.first_, first_);
			swap(other.last_, last_);
		}
		// iterators:
		iterator begin() {
			return sprout::next(sprout::begin(get_array()), first_);
		}
		SPROUT_CONSTEXPR const_iterator begin() const {
			return sprout::next(sprout::begin(get_array()), first_);
		}
		iterator end() {
			return sprout::next(sprout::begin(get_array()), last_);
		}
		SPROUT_CONSTEXPR const_iterator end() const {
			return sprout::next(sprout::begin(get_array()), last_);
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const {
			return sprout::next(sprout::begin(get_array()), first_);
		}
		SPROUT_CONSTEXPR const_iterator cend() const {
			return sprout::next(sprout::begin(get_array()), last_);
		}
		// capacity:
		SPROUT_CONSTEXPR size_type size() const {
			return last_ - first_;
		}
		SPROUT_CONSTEXPR size_type max_size() const {
			return size();
		}
		SPROUT_CONSTEXPR bool empty() const {
			return first_ == last_;
		}
		// element access:
		reference operator[](size_type i) {
			return *sprout::next(sprout::begin(get_array()), first_ + i);
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return *sprout::next(sprout::begin(get_array()), first_ + i);
		}
		reference at(size_type i) {
			return i < size()
				? *sprout::next(sprout::begin(get_array()), first_ + i)
				: (throw std::out_of_range("sub_array<>: index out of range"), *sprout::next(sprout::begin(get_array()), first_ + i))
				;
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return i < size()
				? *sprout::next(sprout::begin(get_array()), first_ + i)
				: (throw std::out_of_range("sub_array<>: index out of range"), *sprout::next(sprout::begin(get_array()), first_ + i))
				;
		}
		reference front() {
			return *sprout::next(sprout::begin(get_array()), first_);
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return *sprout::next(sprout::begin(get_array()), first_);
		}
		reference back() {
			return *sprout::next(sprout::begin(get_array()), last_ - 1);
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return *sprout::next(sprout::begin(get_array()), last_ - 1);
		}

		pointer data() {
			return get_array().data() + first_;
		}
		SPROUT_CONSTEXPR const_pointer data() const {
			return get_array().data() + first_;
		}
		// others:
		template<typename Container2>
		sub_array<Container>& operator=(sub_array<Container2> const& rhs) {
			array_ = rhs.array_;
			first_ = rhs.first_;
			last_ = rhs.last_;
			return *this;
		}
		template<typename Container2>
		sub_array<Container>& operator=(sub_array<Container2>&& rhs) {
			array_ = std::move(rhs.array_);
			first_ = std::move(rhs.first_);
			last_ = std::move(rhs.last_);
			return *this;
		}
		pointer c_array() {
			return data();
		}
		void assign(const_reference value) {
			fill(value);
		}
		void rangecheck(size_type i) const {
			if (i >= size()) {
				throw std::out_of_range("sub_array<>: index out of range");
			}
		}

		param_type get_internal() {
			return impl_type::template to_param<Container>(array_);
		}
		SPROUT_CONSTEXPR const_param_type get_internal() const {
			return impl_type::template to_const_param<Container>(array_);
		}
		param_type get_array() {
			return impl_type::template to_param<Container>(array_);
		}
		SPROUT_CONSTEXPR const_param_type get_array() const {
			return impl_type::template to_const_param<Container>(array_);
		}
	};
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::sub_array<Container>::size_type sprout::sub_array<Container>::static_size;

	//
	// swap
	//
	template<typename Container>
	inline void swap(sprout::sub_array<Container>& lhs, sprout::sub_array<Container>& rhs) {
		lhs.swap(rhs);
	}

	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT::equal(sprout::begin(lhs), sprout::end(lhs), sprout::begin(rhs));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT::lexicographical_compare(
			sprout::begin(lhs), sprout::end(lhs),
			sprout::begin(rhs), sprout::end(rhs)
			);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return rhs < lhs;
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(lhs < rhs);
	}

	//
	// container_construct_traits
	//
	template<typename Container>
	struct container_construct_traits<sprout::sub_array<Container> > {
	private:
		typedef typename sprout::sub_array<Container>::internal_type internal_type;
		typedef typename sprout::container_construct_traits<internal_type>::copied_type internal_copied_type;
	public:
		typedef sprout::sub_array<internal_copied_type> copied_type;
	private:
		static SPROUT_CONSTEXPR copied_type make_impl(internal_copied_type const& internal_copied) {
			return copied_type(internal_copied, sprout::begin(internal_copied), sprout::end(internal_copied));
		}
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type remake_impl(
			Cont&& cont,
			typename sprout::container_traits<sprout::sub_array<Container> >::difference_type size,
			internal_copied_type const& internal_copied
			)
		{
			return copied_type(
				internal_copied,
				sprout::next(sprout::begin(internal_copied), sprout::internal_begin_offset(cont)),
				sprout::next(sprout::begin(internal_copied), sprout::internal_begin_offset(cont) + size)
				);
		}
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return copied_type(
				sprout::deep_copy(sprout::get_internal(cont)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont)
				);
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return make_impl(
				sprout::make<internal_type>(sprout::forward<Args>(args)...)
				);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::sub_array<Container> >::difference_type size,
			Args&&... args
			)
		{
			return remake_impl(
				sprout::forward<Cont>(cont),
				size,
				sprout::make<internal_type>(sprout::forward<Args>(args)...)
				);
		}
	};

	//
	// container_transform_traits
	//
	template<typename Container>
	struct container_transform_traits<sprout::sub_array<Container> > {
	public:
		template<typename sprout::container_traits<sprout::sub_array<Container> >::size_type Size>
		struct rebind_size {
		public:
			typedef sprout::sub_array<
				typename sprout::container_transform_traits<
					typename std::remove_reference<Container>::type
				>::template rebind_size<Size>::type
			> type;
		};
	};

	//
	// sub_container_traits
	//
	template<typename Container>
	struct sub_container_traits<sprout::sub_array<Container> > {
	private:
		static typename sprout::sub_array<Container>::param_type
		call(sprout::sub_array<Container>& cont) {
			return cont.get_internal();
		}
		static SPROUT_CONSTEXPR typename sprout::sub_array<Container>::const_param_type
		call(sprout::sub_array<Container> const& cont) {
			return cont.get_internal();
		}
	public:
		template<typename Cont>
		struct internal {
		public:
			typedef decltype(call(std::declval<Cont&&>())) type;
		};
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR typename internal<Cont>::type get_internal(Cont&& cont) {
			return call(sprout::forward<Cont>(cont));
		}
	};

	//
	// is_sub_array
	//
	template<typename T>
	struct is_sub_array
		: public std::false_type
	{};
	template<typename T>
	struct is_sub_array<T const>
		: public sprout::is_sub_array<T>
	{};
	template<typename T>
	struct is_sub_array<T const volatile>
		: public sprout::is_sub_array<T>
	{};
	template<typename Container>
	struct is_sub_array<sprout::sub_array<Container> >
		: public std::true_type
	{};

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

namespace std {
	//
	// tuple_size
	//
	template<typename Container>
	struct tuple_size<sprout::sub_array<Container> >
		: public std::tuple_size<typename std::remove_reference<Container>::type>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename Container>
	struct tuple_element<I, sprout::sub_array<Container> >
		: public std::tuple_element<I, typename std::remove_reference<Container>::type>
	{};
}	// namespace std

#endif	// #ifndef SPROUT_SUB_ARRAY_HPP
