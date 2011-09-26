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

		template<typename Container>
		class sub_array_impl {
		protected:
			typedef Container container_type;
			typedef typename std::remove_reference<container_type>::type fixed_container_type;
			typedef typename std::remove_const<fixed_container_type>::type internal_type;
		protected:
			SPROUT_STATIC_CONSTEXPR bool is_reference = std::is_reference<container_type>::value;
			SPROUT_STATIC_CONSTEXPR bool is_const = std::is_const<fixed_container_type>::value;
		protected:
			typedef typename sprout::fixed_container_traits<fixed_container_type>::value_type value_type;
			typedef typename sprout::detail::if_c<
				is_const,
				typename sprout::fixed_container_traits<fixed_container_type>::const_iterator,
				typename sprout::fixed_container_traits<fixed_container_type>::iterator
			>::type iterator;
			typedef typename sprout::fixed_container_traits<fixed_container_type>::const_iterator const_iterator;
			typedef typename sprout::detail::if_c<
				is_const,
				typename sprout::fixed_container_traits<fixed_container_type>::const_reference,
				typename sprout::fixed_container_traits<fixed_container_type>::reference
			>::type reference;
			typedef typename sprout::fixed_container_traits<fixed_container_type>::const_reference const_reference;
			typedef typename sprout::fixed_container_traits<fixed_container_type>::size_type size_type;
			typedef typename sprout::fixed_container_traits<fixed_container_type>::difference_type difference_type;
			typedef typename sprout::detail::if_c<
				is_const,
				typename sprout::fixed_container_traits<fixed_container_type>::const_pointer,
				typename sprout::fixed_container_traits<fixed_container_type>::pointer
			>::type pointer;
			typedef typename sprout::fixed_container_traits<fixed_container_type>::const_pointer const_pointer;
		protected:
			SPROUT_STATIC_CONSTEXPR size_type static_size = sprout::fixed_container_traits<fixed_container_type>::fixed_size;
			SPROUT_STATIC_CONSTEXPR size_type fixed_size = static_size;
		protected:
			typedef typename sprout::detail::if_c<
				is_reference,
				fixed_container_type*,
				typename std::remove_const<fixed_container_type>::type
			>::type holder_type;
			typedef typename sprout::detail::if_c<
				is_reference,
				fixed_container_type&,
				fixed_container_type const&
			>::type param_type;
			typedef fixed_container_type const& const_param_type;
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
			template<typename ContainerTag, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				const_iterator first,
				const_iterator last,
				typename std::enable_if<std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_{to_holder<Container>(arr)[Indexes]...}
				, first_(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::cbegin(arr), first))
				, last_(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::cbegin(arr), last))
			{}
			template<typename ContainerTag, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				const_iterator first,
				const_iterator last,
				typename std::enable_if<!std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_(to_holder<Container>(arr))
				, first_(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::cbegin(arr), first))
				, last_(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::cbegin(arr), last))
			{}
			template<typename ContainerTag, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				difference_type first,
				difference_type last,
				typename std::enable_if<std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_{to_holder<Container>(arr)[Indexes]...}
				, first_(first)
				, last_(last)
			{}
			template<typename ContainerTag, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				difference_type first,
				difference_type last,
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
	{
	private:
		typedef sprout::detail::sub_array_impl<Container> impl_type;
	public:
		typedef typename impl_type::container_type container_type;
		typedef typename impl_type::fixed_container_type fixed_container_type;
		typedef typename impl_type::internal_type internal_type;
		typedef sub_array<typename sprout::fixed_container_traits<internal_type>::clone_type> clone_type;
	public:
		SPROUT_STATIC_CONSTEXPR bool is_reference = impl_type::is_reference;
		SPROUT_STATIC_CONSTEXPR bool is_const = impl_type::is_const;
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
		SPROUT_STATIC_CONSTEXPR size_type static_size = impl_type::static_size;
		SPROUT_STATIC_CONSTEXPR size_type fixed_size = impl_type::fixed_size;
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
		SPROUT_CONSTEXPR sub_array(sub_array<Container> const& other, const_iterator first, const_iterator last)
			: impl_type(
				array_tag(),
				impl_type::template to_param<Container>(other.array_),
				typename sprout::index_range<0, fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(other.get_array()), first),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(other.get_array()), last)
				)
		{}
		SPROUT_CONSTEXPR sub_array(sub_array<Container> const& other, difference_type first, difference_type last)
			: impl_type(
				array_tag(),
				impl_type::template to_param<Container>(other.array_),
				typename sprout::index_range<0, fixed_size>::type(),
				first + other.first_,
				last + other.first_
				)
		{}
		param_type get_fixed() {
			return impl_type::template to_param<Container>(array_);
		}
		SPROUT_CONSTEXPR const_param_type get_fixed() const {
			return impl_type::template to_const_param<Container>(array_);
		}
		SPROUT_CONSTEXPR const_param_type get_cfixed() const {
			return impl_type::template to_const_param<Container>(array_);
		}
		param_type get_array() {
			return impl_type::template to_param<Container>(array_);
		}
		SPROUT_CONSTEXPR const_param_type get_array() const {
			return impl_type::template to_const_param<Container>(array_);
		}
		SPROUT_CONSTEXPR size_type size() const {
			return last_ - first_;
		}
		SPROUT_CONSTEXPR bool empty() const {
			return size() == 0;
		}
		SPROUT_CONSTEXPR size_type max_size() const {
			return size();
		}
		void rangecheck(size_type i) const {
			if (i >= size()) {
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
			return sprout::begin(get_array()) + first_;
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
			return *(sprout::begin(get_array()) + first_);
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return *(sprout::begin(get_array()) + first_);
		}
		reference back() {
			return *(sprout::begin(get_array()) + (last_ - 1));
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return *(sprout::begin(get_array()) + (last_ - 1));
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
		template<typename Container2>
		void swap(sub_array<Container2>& other) {
			using std::swap;
			swap(other.array_, array_);
			swap(other.first_, first_);
			swap(other.last_, last_);
		}
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
	};
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator==(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::equal(sprout::begin(lhs), sprout::end(lhs), sprout::begin(rhs));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator!=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator<(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::lexicographical_compare(sprout::begin(lhs), sprout::end(lhs), sprout::begin(rhs), sprout::end(rhs));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator>(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return rhs < lhs;
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator<=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator>=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(lhs < rhs);
	}

	//
	// swap
	//
	template<typename Container>
	inline void swap(sprout::sub_array<Container>& lhs, sprout::sub_array<Container>& rhs) {
		lhs.swap(rhs);
	}

	//
	// fixed_container_traits
	//
	template<typename Container>
	struct fixed_container_traits<sprout::sub_array<Container> >
		: public sprout::detail::fixed_container_traits_base<sprout::sub_array<Container> >
	{
	public:
		typedef typename sprout::sub_array<Container>::fixed_container_type fixed_container_type;
		typedef typename sprout::sub_array<Container>::internal_type internal_type;
		typedef typename sprout::sub_array<Container>::clone_type clone_type;
	public:
		SPROUT_STATIC_CONSTEXPR typename sprout::detail::fixed_container_traits_base<sprout::sub_array<Container> >::size_type fixed_size
			= std::tuple_size<typename std::remove_const<internal_type>::type>::value
			;
	};

	//
	// rebind_fixed_size
	//
	template<typename Container>
	struct rebind_fixed_size<sprout::sub_array<Container> > {
	public:
		template<typename sprout::fixed_container_traits<sprout::sub_array<Container> >::size_type S>
		struct apply {
			public:
				typedef sprout::sub_array<
					typename sprout::rebind_fixed_size<
						typename sprout::fixed_container_traits<sprout::sub_array<Container> >::internal_type
					>::template apply<S>::type
				> type;
		};
	};

	//
	// get_fixed_functor
	//
	template<typename Container>
	struct get_fixed_functor<sprout::sub_array<Container> > {
	private:
		typedef typename sprout::fixed_container_traits<sprout::sub_array<Container> >::fixed_container_type fixed_container_type;
	public:
		fixed_container_type& operator()(sprout::sub_array<Container>& cont) const {
			return cont.get_fixed();
		}
		SPROUT_CONSTEXPR fixed_container_type const& operator()(sprout::sub_array<Container> const& cont) const {
			return cont.get_fixed();
		}
	};

	//
	// clone_functor
	//
	template<typename Container>
	struct clone_functor<sprout::sub_array<Container> > {
	private:
		typedef typename sprout::fixed_container_traits<sprout::sub_array<Container> >::clone_type clone_type;
	public:
		clone_type operator()(sprout::sub_array<Container>& cont) const {
			return clone_type(sprout::clone(sprout::get_fixed(cont)), sprout::fixed_begin_offset(cont), sprout::fixed_end_offset(cont));
		}
		SPROUT_CONSTEXPR clone_type operator()(sprout::sub_array<Container> const& cont) const {
			return clone_type(sprout::clone(sprout::get_fixed(cont)), sprout::fixed_begin_offset(cont), sprout::fixed_end_offset(cont));
		}
	};

	//
	// make_clone_functor
	//
	template<typename Container>
	struct make_clone_functor<sprout::sub_array<Container> > {
	private:
		typedef typename sprout::fixed_container_traits<sprout::sub_array<Container> >::clone_type clone_type;
		typedef typename sprout::fixed_container_traits<sprout::sub_array<Container> >::internal_type internal_type;
	private:
		SPROUT_CONSTEXPR clone_type make(typename sprout::fixed_container_traits<internal_type>::clone_type const& arr) const {
			return clone_type(arr, sprout::begin(arr), sprout::end(arr));
		}
	public:
		template<typename... Args>
		SPROUT_CONSTEXPR clone_type operator()(Args const&... args) const {
			return make(sprout::make_clone<internal_type>(args...));
		}
	};

	//
	// remake_clone_functor
	//
	template<typename Container>
	struct remake_clone_functor<sprout::sub_array<Container> > {
	private:
		typedef typename sprout::fixed_container_traits<sprout::sub_array<Container> >::clone_type clone_type;
		typedef typename sprout::fixed_container_traits<sprout::sub_array<Container> >::internal_type internal_type;
	private:
		template<typename Other>
		clone_type remake(
			Other& other,
			typename sprout::fixed_container_traits<sprout::sub_array<Container> >::difference_type size,
			typename sprout::fixed_container_traits<internal_type>::clone_type const& cloned
			) const
		{
			return clone_type(
				cloned,
				sprout::begin(cloned) + sprout::fixed_begin_offset(other),
				sprout::begin(cloned) + sprout::fixed_begin_offset(other) + size
				);
		}
		template<typename Other>
		SPROUT_CONSTEXPR clone_type remake(
			Other const& other,
			typename sprout::fixed_container_traits<sprout::sub_array<Container> >::difference_type size,
			typename sprout::fixed_container_traits<internal_type>::clone_type const& cloned
			) const
		{
			return clone_type(
				cloned,
				sprout::begin(cloned) + sprout::fixed_begin_offset(other),
				sprout::begin(cloned) + sprout::fixed_begin_offset(other) + size
				);
		}
	public:
		template<typename Other, typename... Args>
		clone_type operator()(
			Other& other,
			typename sprout::fixed_container_traits<sprout::sub_array<Container> >::difference_type size,
			Args const&... args
			) const
		{
			return remake(other, size, sprout::make_clone<internal_type>(args...));
		}
		template<typename Other, typename... Args>
		SPROUT_CONSTEXPR clone_type operator()(
			Other const& other,
			typename sprout::fixed_container_traits<sprout::sub_array<Container> >::difference_type size,
			Args const&... args
			) const
		{
			return remake(other, size, sprout::make_clone<internal_type>(args...));
		}
	};

	namespace detail {
		template<typename T, typename Enable = void>
		struct is_sub_array_impl {
		public:
			typedef std::integral_constant<bool, false> type;
			SPROUT_STATIC_CONSTEXPR bool value = type::value;
		};
		template<typename T>
		struct is_sub_array_impl<
			T,
			typename std::enable_if<
				std::is_same<
					T,
					sprout::sub_array<typename T::container_type>
				>::value
			>::type
		> {
		public:
			typedef std::integral_constant<bool, true> type;
			SPROUT_STATIC_CONSTEXPR bool value = type::value;
		};
	}	// namespace detail
	//
	// is_sub_array
	//
	template<typename T>
	struct is_sub_array
		: public sprout::detail::is_sub_array_impl<T>
	{};

	//
	// sub
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container&> >::const_iterator first,
		typename sprout::fixed_container_traits<sprout::sub_array<Container&> >::const_iterator last
		)
	{
		return sprout::sub_array<Container&>(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container&> >::difference_type first,
		typename sprout::fixed_container_traits<sprout::sub_array<Container&> >::difference_type last
		)
	{
		return sprout::sub_array<Container&>(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container&> >::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container&> >::difference_type first
		)
	{
		return sprout::sub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type sub(
		Container& arr
		)
	{
		return sprout::sub(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// sub
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::const_iterator first,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::const_iterator last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::difference_type first,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::difference_type last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::difference_type first
		)
	{
		return sprout::sub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type sub(
		Container const& arr
		)
	{
		return sprout::sub(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// sub
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::const_iterator first,
		typename sprout::fixed_container_traits<Container>::const_iterator last
		)
	{
		return Container(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::difference_type first,
		typename sprout::fixed_container_traits<Container>::difference_type last
		)
	{
		return Container(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::difference_type first
		)
	{
		return sprout::sub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type sub(
		Container const& arr
		)
	{
		return sprout::sub(arr, sprout::begin(arr), sprout::end(arr));
	}

	//
	// csub
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::const_iterator first,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::const_iterator last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::difference_type first,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::difference_type last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::const_iterator first
		)
	{
		return sprout::csub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr,
		typename sprout::fixed_container_traits<sprout::sub_array<Container const&> >::difference_type first
		)
	{
		return sprout::csub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type csub(
		Container const& arr
		)
	{
		return sprout::csub(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// csub
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type const&> >::type csub(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::const_iterator first,
		typename sprout::fixed_container_traits<Container>::const_iterator last
		)
	{
		return sprout::sub_array<typename Container::fixed_container_type const&>(arr.get_array(), first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type const&> >::type csub(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::difference_type first,
		typename sprout::fixed_container_traits<Container>::difference_type last
		)
	{
		return sprout::sub_array<typename Container::fixed_container_type const&>(arr.get_array(), sprout::begin(arr) + first, sprout::begin(arr) + last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type const&> >::type csub(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::const_iterator first
		)
	{
		return sprout::csub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type const&> >::type csub(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::difference_type first
		)
	{
		return sprout::csub(arr, first, sprout::size(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type const&> >::type csub(
		Container const& arr
		)
	{
		return sprout::csub(arr, sprout::begin(arr), sprout::end(arr));
	}

	//
	// sub_copy
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::const_iterator first,
		typename sprout::fixed_container_traits<Container>::const_iterator last
		)
	{
		return sprout::sub_array<Container>(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::difference_type first,
		typename sprout::fixed_container_traits<Container>::difference_type last
		)
	{
		return sprout::sub_array<Container>(arr, first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::const_iterator first
		)
	{
		return sprout::sub_copy(arr, first, sprout::end(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::difference_type first
		)
	{
		return sprout::sub_copy(arr, first, sprout::size(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type sub_copy(
		Container const& arr
		)
	{
		return sprout::sub_copy(arr, sprout::begin(arr), sprout::end(arr));
	}
	//
	// sub_copy
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type> >::type sub_copy(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::const_iterator first,
		typename sprout::fixed_container_traits<Container>::const_iterator last
		)
	{
		return sprout::sub_array<typename Container::fixed_container_type>(arr.get_array(), first, last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type> >::type sub_copy(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::difference_type first,
		typename sprout::fixed_container_traits<Container>::difference_type last
		)
	{
		return sprout::sub_array<typename Container::fixed_container_type>(arr.get_array(), sprout::begin(arr) + first, sprout::begin(arr) + last);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type> >::type sub_copy(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::const_iterator first
		)
	{
		return sprout::sub_copy(arr, first, sprout::end(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type> >::type sub_copy(
		Container const& arr,
		typename sprout::fixed_container_traits<Container>::difference_type first
		)
	{
		return sprout::sub_copy(arr, first, sprout::size(arr));
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::fixed_container_type> >::type sub_copy(
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
	struct tuple_size<sprout::sub_array<Container> > {
	public:
		SPROUT_STATIC_CONSTEXPR std::size_t value = std::tuple_size<
			typename std::remove_const<
				typename std::remove_reference<Container>::type
			>::type
		>::value;
	};

	//
	// tuple_element
	//
	template<std::size_t I, typename Container>
	struct tuple_element<I, sprout::sub_array<Container> > {
	public:
		typedef typename std::tuple_element<
			I,
			typename std::remove_const<
				typename std::remove_reference<Container>::type
			>::type
		>::type type;
	};

	//
	// get
	//
	template<std::size_t I, typename T, typename Container>
	T& get(sprout::sub_array<Container>& arr) SPROUT_NOEXCEPT {
		static_assert(I < sprout::fixed_container_traits<sprout::sub_array<Container> >::fixed_size, "tuple_element<>: index out of range");
		return *(sprout::fixed_begin(arr) + I);
	}
	template<std::size_t I, typename T, typename Container>
	SPROUT_CONSTEXPR T const& get(sprout::sub_array<Container> const& arr) SPROUT_NOEXCEPT {
		static_assert(I < sprout::fixed_container_traits<sprout::sub_array<Container> >::fixed_size, "tuple_element<>: index out of range");
		return *(sprout::fixed_begin(arr) + I);
	}
	template<std::size_t I, typename T, typename Container>
	T&& get(sprout::sub_array<Container>&& arr) SPROUT_NOEXCEPT {
		return std::move(get<I>(arr));
	}
}	// namespace std

#endif	// #ifndef SPROUT_SUB_ARRAY_HPP
