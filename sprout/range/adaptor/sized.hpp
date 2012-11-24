#ifndef SPROUT_RANGE_ADAPTOR_SIZED_HPP
#define SPROUT_RANGE_ADAPTOR_SIZED_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/metafunctions.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		namespace detail {
			template<typename Range, typename sprout::container_traits<Range>::size_type Size, typename = void>
			class sized_impl;

			template<typename Range, typename sprout::container_traits<Range>::size_type Size>
			class sized_impl<
				Range, Size,
				typename std::enable_if<sprout::detail::has_static_size<sprout::container_traits<Range> >::value>::type
			> {
			public:
				SPROUT_STATIC_CONSTEXPR typename sprout::container_traits<Range>::size_type
				static_size = Size < sprout::container_traits<Range>::static_size ? Size
					: sprout::container_traits<Range>::static_size
					;
				static SPROUT_CONSTEXPR typename sprout::container_traits<Range>::size_type fixed_size() {
					return static_size;
				}
			};
			template<typename Range, typename sprout::container_traits<Range>::size_type Size>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::container_traits<Range>::size_type sized_impl<
				Range, Size,
				typename std::enable_if<sprout::detail::has_static_size<sprout::container_traits<Range> >::value>::type
			>::static_size;

			template<typename Range, typename sprout::container_traits<Range>::size_type Size>
			class sized_impl<
				Range, Size,
				typename std::enable_if<!sprout::detail::has_static_size<sprout::container_traits<Range> >::value>::type
			> {
			public:
				SPROUT_STATIC_CONSTEXPR typename sprout::container_traits<Range>::size_type static_size = Size;
				static SPROUT_CONSTEXPR typename sprout::container_traits<Range>::size_type fixed_size() {
					return static_size;
				}
			};
			template<typename Range, typename sprout::container_traits<Range>::size_type Size>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::container_traits<Range>::size_type sized_impl<
				Range, Size,
				typename std::enable_if<!sprout::detail::has_static_size<sprout::container_traits<Range> >::value>::type
			>::static_size;
		}	// namespace detail

		//
		// sized_range
		//
		template<typename Range, typename sprout::container_traits<Range>::size_type Size>
		class sized_range
			: public sprout::range::range_container<
				typename sprout::container_traits<Range>::iterator
			>
			, public sprout::adaptors::detail::sized_impl<Range, Size>
		{
		public:
			typedef Range range_type;
			typedef sprout::range::range_container<
				typename sprout::container_traits<Range>::iterator
			> base_type;
		private:
			typedef sprout::adaptors::detail::sized_impl<Range, Size> sized_impl_type;
		public:
			sized_range() = default;
			sized_range(sized_range const&) = default;
			explicit SPROUT_CONSTEXPR sized_range(range_type& range)
				: base_type(
					sprout::begin(range),
					sized_impl_type::static_size < static_cast<typename sprout::container_traits<Range>::size_type>(sprout::size(range))
						? sprout::next(sprout::begin(range), sized_impl_type::static_size)
						: sprout::end(range)
					)
			{}
		};

		//
		// size_holder
		//
		template<std::size_t Size>
		class size_holder
			: public std::integral_constant<std::size_t, Size>
		{};

		//
		// sized
		//
		template<std::size_t Size>
		inline SPROUT_CONSTEXPR sprout::adaptors::size_holder<Size> sized() {
			return sprout::adaptors::size_holder<Size>();
		}

		//
		// operator|
		//
		template<typename Range, std::size_t Size>
		inline SPROUT_CONSTEXPR sprout::adaptors::sized_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			Size
		>
		operator|(Range&& lhs, sprout::adaptors::size_holder<Size> const& rhs) {
			return sprout::adaptors::sized_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
				Size
			>(
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range, typename sprout::container_traits<Range>::size_type Size>
	struct container_construct_traits<sprout::adaptors::sized_range<Range, Size> > {
	private:
		typedef typename sprout::container_construct_traits<Range>::copied_type range_copied_type;
	public:
		typedef typename sprout::containers::weak_rebind_size<
			range_copied_type,
			sprout::adaptors::sized_range<Range, Size>::static_size
		>::type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return sprout::range::fixed::copy(sprout::forward<Cont>(cont), sprout::pit<copied_type>());
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::make<copied_type>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::adaptors::sized_range<Range, Size> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_SIZED_HPP
