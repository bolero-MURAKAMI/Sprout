/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_IO_HPP
#define SPROUT_IO_HPP

#include <iosfwd>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/detail/param_at.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/array/array.hpp>
#include <sprout/string.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/range/algorithm/lower_bound.hpp>
#include <sprout/range/numeric/partial_sum.hpp>
#include <sprout/type_traits/is_char_type.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace io {
		namespace flags {
			//
			// fmtflags
			//
			enum fmtflags {
				boolalpha = 1L << 0,
				showbase = 1L << 1,
				showpoint = 1L << 2,
				showpos = 1L << 3,
				uppercase = 1L << 4,
				skipws = 1L << 5,
				right = 1L << 6,
				left = 1L << 7,
				internal = 1L << 8,
				dec = 1L << 9,
				hex = 1L << 10,
				oct = 1L << 11,
				fixed = 1L << 12,
				scientific = 1L << 13,
				adjustfield = right | left | internal,
				basefield = dec | hex | oct,
				floatfield = fixed | scientific,
				booleanfield = boolalpha | showbase | showpoint | showpos | uppercase | skipws,
				default_flags = right | dec | fixed,
				precision_ = 1L << 14,
				width_ = 1L << 15,
				fill_ = 1L << 16,
				modified_shift_ = 17,
			};
			//
			// boolean_flag
			//
			template<sprout::io::flags::fmtflags Flag>
			struct boolean_flag
				: public sprout::integral_constant<sprout::io::flags::fmtflags, Flag>
			{
			private:
				bool flag_;
			public:
				SPROUT_CONSTEXPR boolean_flag() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				boolean_flag(boolean_flag const&) = default;
				SPROUT_CONSTEXPR boolean_flag(bool flag)
					: flag_(flag)
				{}
				SPROUT_CONSTEXPR boolean_flag operator()(bool flag) const {
					return boolean_flag(flag);
				}
				SPROUT_CONSTEXPR operator bool() const {
					return flag_;
				}
				SPROUT_CONSTEXPR bool operator!() const {
					return !flag_;
				}
			};
			//
			// field_flag
			//
			template<sprout::io::flags::fmtflags Flag, sprout::io::flags::fmtflags Mask>
			struct field_flag
				: public sprout::integral_constant<sprout::io::flags::fmtflags, Flag>
			{
			public:
				SPROUT_STATIC_CONSTEXPR sprout::io::flags::fmtflags mask = Mask;
			public:
				SPROUT_CONSTEXPR field_flag() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				field_flag(field_flag const&) = default;
			};
			template<sprout::io::flags::fmtflags Flag, sprout::io::flags::fmtflags Mask>
			SPROUT_CONSTEXPR_OR_CONST sprout::io::flags::fmtflags sprout::io::flags::field_flag<Flag, Mask>::mask;

			//
			// precision_t
			//
			struct precision_t {
			public:
				typedef std::streamsize type;
			public:
				type value;
			public:
				SPROUT_CONSTEXPR precision_t(type value)
					: value(value)
				{}
				SPROUT_CONSTEXPR operator type() const {
					return value;
				}
			};

			//
			// width_t
			//
			struct width_t {
			public:
				typedef std::streamsize type;
			public:
				type value;
			public:
				SPROUT_CONSTEXPR width_t(type value)
					: value(value)
				{}
				SPROUT_CONSTEXPR operator type() const {
					return value;
				}
			};

			//
			// fill_t
			//
			struct fill_t {
			public:
				typedef char type;
			public:
				type value;
			public:
				SPROUT_CONSTEXPR fill_t(type value)
					: value(value)
				{}
				SPROUT_CONSTEXPR operator type() const {
					return value;
				}
			};
		}	// namespace flags

		SPROUT_STATIC_CONSTEXPR sprout::io::flags::boolean_flag<sprout::io::flags::boolalpha> boolalpha = true;
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::boolean_flag<sprout::io::flags::showbase> showbase = true;
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::boolean_flag<sprout::io::flags::showpoint> showpoint = true;
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::boolean_flag<sprout::io::flags::showpos> showpos = true;
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::boolean_flag<sprout::io::flags::uppercase> uppercase = true;
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::boolean_flag<sprout::io::flags::skipws> skipws = true;
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::field_flag<sprout::io::flags::right, sprout::io::flags::adjustfield> right = {};
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::field_flag<sprout::io::flags::left, sprout::io::flags::adjustfield> left = {};
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::field_flag<sprout::io::flags::internal, sprout::io::flags::adjustfield> internal = {};
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::field_flag<sprout::io::flags::dec, sprout::io::flags::basefield> dec = {};
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::field_flag<sprout::io::flags::hex, sprout::io::flags::basefield> hex = {};
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::field_flag<sprout::io::flags::oct, sprout::io::flags::basefield> oct = {};
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::field_flag<sprout::io::flags::fixed, sprout::io::flags::floatfield> fixed = {};
		SPROUT_STATIC_CONSTEXPR sprout::io::flags::field_flag<sprout::io::flags::scientific, sprout::io::flags::floatfield> scientific = {};

		//
		// precision
		// width
		// fill
		//
		inline SPROUT_CONSTEXPR sprout::io::flags::precision_t
		precision(sprout::io::flags::precision_t::type value) {
			return sprout::io::flags::precision_t(value);
		}
		inline SPROUT_CONSTEXPR sprout::io::flags::width_t
		width(sprout::io::flags::width_t::type value) {
			return sprout::io::flags::width_t(value);
		}
		inline SPROUT_CONSTEXPR sprout::io::flags::fill_t
		fill(sprout::io::flags::fill_t::type value) {
			return sprout::io::flags::fill_t(value);
		}

		//
		// format_settings
		//
		class format_settings {
		private:
			sprout::io::flags::fmtflags flags_;
			sprout::io::flags::precision_t precision_;
			sprout::io::flags::width_t width_;
			sprout::io::flags::fill_t fill_;
		private:
			SPROUT_CONSTEXPR format_settings(format_settings const& other, sprout::io::flags::fmtflags flags)
				: flags_(flags)
				, precision_(other.precision_)
				, width_(other.width_)
				, fill_(other.fill_)
			{}
			SPROUT_CONSTEXPR format_settings(format_settings const& other, sprout::io::flags::precision_t precision)
				: flags_(static_cast<sprout::io::flags::fmtflags>(other.flags_ | sprout::io::flags::precision_))
				, precision_(precision)
				, width_(other.width_)
				, fill_(other.fill_)
			{}
			SPROUT_CONSTEXPR format_settings(format_settings const& other, sprout::io::flags::width_t width)
				: flags_(static_cast<sprout::io::flags::fmtflags>(other.flags_ | sprout::io::flags::width_))
				, precision_(other.precision_)
				, width_(width)
				, fill_(other.fill_)
			{}
			SPROUT_CONSTEXPR format_settings(format_settings const& other, sprout::io::flags::fill_t fill)
				: flags_(static_cast<sprout::io::flags::fmtflags>(other.flags_ | sprout::io::flags::fill_))
				, precision_(other.precision_)
				, width_(other.width_)
				, fill_(fill)
			{}
			SPROUT_CONSTEXPR format_settings(
				sprout::io::flags::fmtflags flags,
				sprout::io::flags::precision_t precision,
				sprout::io::flags::width_t width,
				sprout::io::flags::fill_t fill
				)
				: flags_(flags)
				, precision_(precision)
				, width_(width)
				, fill_(fill)
			{}
		public:
			SPROUT_CONSTEXPR format_settings()
				: flags_(sprout::io::flags::default_flags)
				, precision_(6)
				, width_(0)
				, fill_(' ')
			{}
			format_settings(format_settings const&) = default;
			explicit SPROUT_CONSTEXPR format_settings(sprout::io::flags::fmtflags flags)
				: flags_(flags)
				, precision_(6)
				, width_(0)
				, fill_(' ')
			{}
			explicit SPROUT_CONSTEXPR format_settings(sprout::io::flags::precision_t precision)
				: flags_(sprout::io::flags::default_flags)
				, precision_(precision)
				, width_(0)
				, fill_(' ')
			{}
			explicit SPROUT_CONSTEXPR format_settings(sprout::io::flags::width_t width)
				: flags_(sprout::io::flags::default_flags)
				, precision_(6)
				, width_(width)
				, fill_(' ')
			{}
			explicit SPROUT_CONSTEXPR format_settings(sprout::io::flags::fill_t fill)
				: flags_(sprout::io::flags::default_flags)
				, precision_(6)
				, width_(0)
				, fill_(fill)
			{}
			SPROUT_CONSTEXPR sprout::io::flags::fmtflags flags() const {
				return flags_;
			}
			template<sprout::io::flags::fmtflags Flag>
			SPROUT_CONSTEXPR format_settings flags(sprout::io::flags::boolean_flag<Flag> flag) const {
				return format_settings(
					*this,
					static_cast<sprout::io::flags::fmtflags>(
						(flag ? flags_ | Flag : flags_ & ~Flag) | (Flag << sprout::io::flags::modified_shift_)
						)
					);
			}
			template<sprout::io::flags::fmtflags Flag, sprout::io::flags::fmtflags Mask>
			SPROUT_CONSTEXPR format_settings flags(sprout::io::flags::field_flag<Flag, Mask>) const {
				return format_settings(
					*this,
					static_cast<sprout::io::flags::fmtflags>(
						(flags_ & ~Mask) | (Flag & Mask) | (Mask << sprout::io::flags::modified_shift_)
						)
					);
			}
			SPROUT_CONSTEXPR sprout::io::flags::precision_t::type precision() const {
				return precision_;
			}
			SPROUT_CONSTEXPR format_settings precision(sprout::io::flags::precision_t precision) const {
				return format_settings(*this, precision);
			}
			SPROUT_CONSTEXPR sprout::io::flags::width_t::type width() const {
				return width_;
			}
			SPROUT_CONSTEXPR format_settings width(sprout::io::flags::width_t width) const {
				return format_settings(*this, width);
			}
			SPROUT_CONSTEXPR sprout::io::flags::fill_t::type fill() const {
				return fill_;
			}
			SPROUT_CONSTEXPR format_settings fill(sprout::io::flags::fill_t fill) const {
				return format_settings(*this, fill);
			}
			SPROUT_CONSTEXPR format_settings combine(format_settings const& base) const {
				return format_settings(
					static_cast<sprout::io::flags::fmtflags>(
						(base.flags_ & ~(flags_ >> sprout::io::flags::modified_shift_)) | flags_
						),
					flags_ & sprout::io::flags::precision_ ? precision_ : base.precision_,
					flags_ & sprout::io::flags::width_ ? width_ : base.width_,
					flags_ & sprout::io::flags::fill_ ? fill_ : base.fill_
					);
			}
		};

		//
		// format_holder
		//
		template<typename T>
		class format_holder {
		private:
			sprout::value_holder<T const&> holder_;
			sprout::io::format_settings settings_;
		public:
			SPROUT_CONSTEXPR format_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			format_holder(format_holder const&) = default;
			explicit SPROUT_CONSTEXPR format_holder(T const& value)
				: holder_(value)
				, settings_()
			{}
			SPROUT_CONSTEXPR format_holder(
				T const& value,
				sprout::io::format_settings const& settings
				)
				: holder_(value)
				, settings_(settings)
			{}
			SPROUT_CONSTEXPR format_holder(
				format_holder const& holder,
				sprout::io::format_settings const& settings
				)
				: holder_(holder)
				, settings_(settings)
			{}
			SPROUT_CONSTEXPR T const& value() const {
				return holder_;
			}
			SPROUT_CONSTEXPR sprout::io::format_settings const& settings() const {
				return settings_;
			}
			SPROUT_CONSTEXPR format_holder settings(sprout::io::format_settings const& settings) const {
				return format_holder(holder_, settings);
			}
		};

		namespace flags {
			template<typename T, sprout::io::flags::fmtflags Flag>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(T const& value, sprout::io::flags::boolean_flag<Flag> flag) {
				return sprout::io::format_holder<T>(value, sprout::io::format_settings().flags(flag));
			}
			template<typename T, sprout::io::flags::fmtflags Flag, sprout::io::flags::fmtflags Mask>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(T const& value, sprout::io::flags::field_flag<Flag, Mask> flag) {
				return sprout::io::format_holder<T>(value, sprout::io::format_settings().flags(flag));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(T const& value, sprout::io::flags::precision_t precision) {
				return sprout::io::format_holder<T>(value, sprout::io::format_settings(precision));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(T const& value, sprout::io::flags::width_t width) {
				return sprout::io::format_holder<T>(value, sprout::io::format_settings(width));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(T const& value, sprout::io::flags::fill_t fill) {
				return sprout::io::format_holder<T>(value, sprout::io::format_settings(fill));
			}

			template<typename T, sprout::io::flags::fmtflags Flag>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(sprout::io::format_holder<T> const& holder, sprout::io::flags::boolean_flag<Flag> flag) {
				return holder.settings(holder.settings().flags(flag));
			}
			template<typename T, sprout::io::flags::fmtflags Flag, sprout::io::flags::fmtflags Mask>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(sprout::io::format_holder<T> const& holder, sprout::io::flags::field_flag<Flag, Mask> flag) {
				return holder.settings(holder.settings().flags(flag));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(sprout::io::format_holder<T> const& holder, sprout::io::flags::precision_t precision) {
				return holder.settings(holder.settings().precision(precision));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(sprout::io::format_holder<T> const& holder, sprout::io::flags::width_t width) {
				return holder.settings(holder.settings().width(width));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<T>
			operator|(sprout::io::format_holder<T> const& holder, sprout::io::flags::fill_t fill) {
				return holder.settings(holder.settings().fill(fill));
			}
		}	// namespace flags

		template<std::size_t N, typename Elem = char, typename Expression>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, N>
		output(Expression const& expr);

		//
		// nil_expression
		//
		class nil_expression {};
		//
		// is_nil_expression
		//
		template<typename T>
		struct is_nil_expression
			: public sprout::false_type
		{};
		template<typename T>
		struct is_nil_expression<T const>
			: public sprout::io::is_nil_expression<T>
		{};
		template<typename T>
		struct is_nil_expression<T const volatile>
			: public sprout::io::is_nil_expression<T>
		{};
		template<>
		struct is_nil_expression<sprout::io::nil_expression>
			: public sprout::true_type
		{};

		//
		// root_expression
		//
		class root_expression {
		private:
			sprout::io::format_settings settings_;
		public:
			SPROUT_CONSTEXPR root_expression()
				: settings_()
			{}
			root_expression(root_expression const&) = default;
			explicit SPROUT_CONSTEXPR root_expression(sprout::io::format_settings const& settings)
				: settings_(settings)
			{}
			SPROUT_CONSTEXPR sprout::io::format_settings const& settings() const {
				return settings_;
			}
		};
		//
		// is_root_expression
		//
		template<typename T>
		struct is_root_expression
			: public sprout::false_type
		{};
		template<typename T>
		struct is_root_expression<T const>
			: public sprout::io::is_root_expression<T>
		{};
		template<typename T>
		struct is_root_expression<T const volatile>
			: public sprout::io::is_root_expression<T>
		{};
		template<>
		struct is_root_expression<sprout::io::root_expression>
			: public sprout::true_type
		{};

		//
		// leaf_expression
		//
		template<typename T>
		class leaf_expression {
		private:
			sprout::value_holder<T const&> value_;
		public:
			SPROUT_CONSTEXPR leaf_expression()
				: value_()
			{}
			leaf_expression(leaf_expression const&) = default;
			explicit SPROUT_CONSTEXPR leaf_expression(T const& value)
				: value_(value)
			{}
			SPROUT_CONSTEXPR T const& value() const {
				return value_;
			}
		};
		//
		// is_leaf_expression
		//
		template<typename T>
		struct is_leaf_expression
			: public sprout::false_type
		{};
		template<typename T>
		struct is_leaf_expression<T const>
			: public sprout::io::is_leaf_expression<T>
		{};
		template<typename T>
		struct is_leaf_expression<T const volatile>
			: public sprout::io::is_leaf_expression<T>
		{};
		template<typename T>
		struct is_leaf_expression<sprout::io::leaf_expression<T> >
			: public sprout::true_type
		{};

		//
		// format_expression
		//
		template<typename Left, typename Right>
		class format_expression {
		private:
			typedef typename std::conditional<
				sprout::io::is_root_expression<Left>::value,
				Left,
				Left const&
			>::type left_held_type;
			typedef typename std::conditional<
				sprout::io::is_nil_expression<Right>::value || sprout::io::is_leaf_expression<Right>::value,
				Right,
				Right const&
			>::type right_held_type;
			typedef sprout::value_holder<left_held_type> left_holder_type;
			typedef sprout::value_holder<right_held_type> right_holder_type;
		private:
			left_holder_type left_;
			right_holder_type right_;
		public:
			SPROUT_CONSTEXPR format_expression()
				: left_(), right_()
			{}
			format_expression(format_expression const&) = default;
			explicit SPROUT_CONSTEXPR format_expression(Left const& left)
				: left_(left), right_()
			{}
			explicit SPROUT_CONSTEXPR format_expression(left_holder_type left)
				: left_(left), right_()
			{}
			SPROUT_CONSTEXPR format_expression(Left const& left, Right const& right)
				: left_(left) , right_(right)
			{}
			SPROUT_CONSTEXPR format_expression(left_holder_type left, right_holder_type right)
				: left_(left), right_(right)
			{}
			SPROUT_CONSTEXPR Left const& left() const {
				return left_;
			}
			SPROUT_CONSTEXPR Right const& right() const {
				return right_;
			}
			SPROUT_CONSTEXPR sprout::io::format_settings const& settings() const {
				return left().settings();
			}
			template<std::size_t N, typename Elem = char>
			SPROUT_CONSTEXPR sprout::basic_string<Elem, N> output() const {
				return sprout::io::output<N, Elem>(*this);
			}
			template<std::size_t N, typename Elem = char>
			SPROUT_CONSTEXPR operator sprout::basic_string<Elem, N>() const {
				return sprout::io::output<N, Elem>(*this);
			}
		};
		//
		// is_format_expression
		//
		template<typename T>
		struct is_format_expression
			: public sprout::false_type
		{};
		template<typename T>
		struct is_format_expression<T const>
			: public sprout::io::is_format_expression<T>
		{};
		template<typename T>
		struct is_format_expression<T const volatile>
			: public sprout::io::is_format_expression<T>
		{};
		template<typename Left, typename Right>
		struct is_format_expression<sprout::io::format_expression<Left, Right> >
			: public sprout::true_type
		{};

		//
		// root_t
		//
		typedef sprout::io::format_expression<
			sprout::io::root_expression,
			sprout::io::nil_expression
		> root_t;

		//
		// root
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::io::root_t root = {};
		}	// anonymous-namespace

		template<typename Left, typename Right, typename T>
		inline SPROUT_CONSTEXPR auto
		operator<<(sprout::io::format_expression<Left, Right> const& lhs, sprout::io::format_holder<T> const& rhs)
		-> sprout::io::format_expression<
			sprout::io::format_expression<Left, Right>,
			decltype(std::declval<sprout::io::root_t>() << rhs.value())
		>
		{
			typedef decltype(sprout::io::root << rhs.value()) type;
			return sprout::io::format_expression<sprout::io::format_expression<Left, Right>, type>(
				lhs,
				sprout::io::root_t(sprout::io::root_expression(rhs.settings().combine(lhs.settings()))) << rhs.value()
				);
		}
		template<typename Left, typename Right, typename T>
		inline SPROUT_CONSTEXPR sprout::io::format_expression<
			sprout::io::format_expression<Left, Right>,
			sprout::io::leaf_expression<T>
		>
		operator<<(sprout::io::format_expression<Left, Right> const& lhs, T const& rhs) {
			return sprout::io::format_expression<
				sprout::io::format_expression<Left, Right>,
				sprout::io::leaf_expression<T>
			>(lhs, sprout::io::leaf_expression<T>(rhs));
		}

		//
		// leaf_count
		//
		namespace detail {
			template<typename Expression>
			struct leaf_count;
			template<>
			struct leaf_count<sprout::io::root_t>
				: public sprout::integral_constant<std::size_t, 0>
			{};
			template<typename T>
			struct leaf_count<sprout::io::leaf_expression<T> >
				: public sprout::integral_constant<std::size_t, 1>
			{};
			template<typename Left, typename Right>
			struct leaf_count<sprout::io::format_expression<Left, Right> >
				: public sprout::integral_constant<
					std::size_t,
					sprout::io::detail::leaf_count<Left>::value + sprout::io::detail::leaf_count<Right>::value
				>
			{};
		}	// namespace detail
		template<typename Expression>
		struct leaf_count
			: public sprout::io::detail::leaf_count<Expression>
		{};
		template<typename Expression>
		struct leaf_count<Expression const>
			: public sprout::io::leaf_count<Expression>
		{};
		template<typename Expression>
		struct leaf_count<Expression const volatile>
			: public sprout::io::leaf_count<Expression>
		{};

		//
		// leaf_at
		//
		namespace detail {
			template<std::size_t I, typename Expression>
			struct leaf_at;
			template<std::size_t I, typename T>
			struct leaf_at<I, sprout::io::leaf_expression<T> > {
			public:
				typedef T type;
			};
			template<std::size_t I, typename Left, typename Right>
			struct leaf_at<I, sprout::io::format_expression<Left, Right> >
				: public std::conditional<
					I < sprout::io::leaf_count<Left>::value,
					sprout::io::detail::leaf_at<I, Left>,
					sprout::io::detail::leaf_at<I - sprout::io::leaf_count<Left>::value, Right>
				>::type
			{};
		}	// namespace detail
		template<std::size_t I, typename Expression>
		struct leaf_at
			: public sprout::io::detail::leaf_at<I, Expression>
		{};
		template<std::size_t I, typename Expression>
		struct leaf_at<I, Expression const>
			: public sprout::io::leaf_at<I, Expression>
		{};
		template<std::size_t I, typename Expression>
		struct leaf_at<I, Expression const volatile>
			: public sprout::io::leaf_at<I, Expression>
		{};

		//
		// get_leaf
		//
		namespace detail {
			template<
				std::size_t I, typename Left, typename Right,
				typename sprout::enabler_if<(I >= sprout::io::leaf_count<Left>::value)>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<
				typename sprout::io::leaf_at<I, sprout::io::format_expression<Left, Right> >::type
			>
			get_leaf(sprout::io::format_expression<Left, Right> const& expr);

			template<
				std::size_t I, typename Left, typename T,
				typename sprout::enabler_if<(I == sprout::io::leaf_count<Left>::value)>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<
				typename sprout::io::leaf_at<I, sprout::io::format_expression<Left, sprout::io::leaf_expression<T> > >::type
			>
			get_leaf(sprout::io::format_expression<Left, sprout::io::leaf_expression<T> > const& expr) {
				return sprout::io::format_holder<
					typename sprout::io::leaf_at<I, sprout::io::format_expression<Left, sprout::io::leaf_expression<T> > >::type
				>(expr.right().value(), expr.settings());
			}

			template<
				std::size_t I, typename Left, typename Right,
				typename sprout::enabler_if<(I < sprout::io::leaf_count<Left>::value)>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<
				typename sprout::io::leaf_at<I, sprout::io::format_expression<Left, Right> >::type
			>
			get_leaf(sprout::io::format_expression<Left, Right> const& expr) {
				return sprout::io::detail::get_leaf<I>(expr.left());
			}
			template<
				std::size_t I, typename Left, typename Right,
				typename sprout::enabler_if<(I >= sprout::io::leaf_count<Left>::value)>::type
			>
			inline SPROUT_CONSTEXPR sprout::io::format_holder<
				typename sprout::io::leaf_at<I, sprout::io::format_expression<Left, Right> >::type
			>
			get_leaf(sprout::io::format_expression<Left, Right> const& expr) {
				return sprout::io::detail::get_leaf<I - sprout::io::leaf_count<Left>::value>(expr.right());
			}
		}	// namespace detail
		template<std::size_t I, typename Expression>
		inline SPROUT_CONSTEXPR sprout::io::format_holder<typename sprout::io::leaf_at<I, Expression>::type>
		get_leaf(Expression const& expr) {
			return sprout::io::detail::get_leaf<I>(expr);
		}

		//
		// eval
		//
		template<
			typename Elem, std::size_t N, typename T,
			typename sprout::enabler_if<
				std::is_integral<T>::value
					&& !sprout::is_char_type<T>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		eval(sprout::io::format_holder<T> const& holder)
		-> decltype(sprout::int_to_string<Elem>(holder.value()))
		{
			return sprout::int_to_string<Elem>(holder.value());
		}
		template<
			typename Elem, std::size_t N, typename T,
			typename sprout::enabler_if<std::is_floating_point<T>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		eval(sprout::io::format_holder<T> const& holder)
		-> decltype(sprout::float_to_string<Elem>(holder.value()))
		{
			return sprout::float_to_string<Elem>(holder.value());
		}
		template<
			typename Elem, std::size_t N, typename T,
			typename sprout::enabler_if<sprout::is_char_type<T>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		eval(sprout::io::format_holder<T> const& holder)
		-> decltype(sprout::detail::string_construct_access<Elem, 1>::raw_construct(1, static_cast<Elem>(holder.value())))
		{
			return sprout::detail::string_construct_access<Elem, 1>::raw_construct(1, static_cast<Elem>(holder.value()));
		}
		template<
			typename Elem, std::size_t N, typename T,
			typename sprout::enabler_if<std::is_array<T>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		eval(sprout::io::format_holder<T> const& holder)
		-> decltype(sprout::to_string(holder.value()))
		{
			return sprout::to_string(holder.value());
		}
		template<
			typename Elem, std::size_t N, typename T,
			typename sprout::enabler_if<sprout::is_string<T>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR auto
		eval(sprout::io::format_holder<T> const& holder)
		-> decltype(holder.value())
		{
			return holder.value();
		}

		namespace detail {
			template<typename Elem, typename RandomAccessIterator, std::size_t K, typename... Args>
			inline SPROUT_CONSTEXPR Elem
			get_param(RandomAccessIterator found, sprout::array<std::size_t, K> const& sizes, std::size_t idx, Args const&... args) {
				return found == sizes.end() ? static_cast<Elem>('\0')
					: sprout::detail::param_seq_at<Elem>(
						found - sizes.begin(),
						idx - (found != sizes.begin() ? found[-1] : 0),
						args...
						)
					;
			}
		}	// namespace detail

		namespace detail {
			template<typename Elem, std::size_t N, sprout::index_t... Indexes, std::size_t K, typename... Args>
			inline SPROUT_CONSTEXPR sprout::basic_string<Elem, N>
			output_impl_1(sprout::index_tuple<Indexes...>, sprout::array<std::size_t, K> const& sizes, Args const&... args) {
				typedef sprout::detail::string_construct_access<Elem, N> access_type;
				return access_type::raw_construct(
					NS_SSCRISK_CEL_OR_SPROUT::min(sizes.back(), N),
					sprout::io::detail::get_param<Elem>(
						sprout::range::lower_bound(sizes, static_cast<std::size_t>(Indexes + 1)),
						sizes,
						Indexes,
						args...
						)...
					);
			}
			template<typename Elem, std::size_t N, typename... Args>
			inline SPROUT_CONSTEXPR sprout::basic_string<Elem, N>
			output_impl(Args const&... args) {
				return sprout::io::detail::output_impl_1<Elem, N>(
					sprout::make_index_tuple<N>::make(),
					sprout::range::partial_sum(
						sprout::array<std::size_t, sizeof...(Args)>{{args.size()...}},
						sprout::pit<sprout::array<std::size_t, sizeof...(Args)> >()
						),
					args...
					);
			}
			template<typename Elem, std::size_t N, typename Expression, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR sprout::basic_string<Elem, N>
			output(Expression const& expr, sprout::index_tuple<Indexes...>) {
				return sprout::io::detail::output_impl<Elem, N>(
					sprout::io::eval<Elem, N>(sprout::io::get_leaf<Indexes>(expr))...
					);
			}
		}	// namespace detail
		//
		// output
		//
		template<std::size_t N, typename Elem, typename Expression>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, N>
		output(Expression const& expr) {
			return sprout::io::detail::output<Elem, N>(
				expr,
				sprout::make_index_tuple<sprout::io::leaf_count<Expression>::value>::make()
				);
		}
	}	// namespace io
}	// namespace sprout

#endif	// #ifndef SPROUT_IO_HPP
