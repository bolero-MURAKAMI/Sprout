/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LOGIC_TRIBOOL_IO_HPP
#define SPROUT_LOGIC_TRIBOOL_IO_HPP

#include <locale>
#include <string>
#include <istream>
#include <ostream>
#include <sprout/config.hpp>
#include <sprout/utility/noncopyable.hpp>
#include <sprout/logic/tribool/tribool.hpp>
#include <sprout/detail/literal_def.hpp>

namespace sprout {
	namespace logic {
		namespace detail {
			SPROUT_LITERAL_STRING_DEF(default_indeterminate_name, "indeterminate", 13);
		}	// namespace detail
		//
		// get_default_indeterminate_name
		//
		template<typename Elem>
		inline SPROUT_NON_CONSTEXPR std::basic_string<Elem>
		get_default_indeterminate_name() {
			return sprout::logic::detail::default_indeterminate_name<Elem>::value.c_str();
		}

		//
		// indeterminate_name
		//
		template<typename Elem>
		class indeterminate_name
			: public std::locale::facet
			, private sprout::noncopyable
		{
		public:
			typedef Elem char_type;
			typedef std::basic_string<char_type> string_type;
		public:
			static std::locale::id id;
		private:
			string_type name_;
		public:
			SPROUT_NON_CONSTEXPR indeterminate_name()
				: name_(sprout::logic::get_default_indeterminate_name<char_type>())
			{}
			explicit SPROUT_NON_CONSTEXPR indeterminate_name(string_type const& initial_name)
				: name_(initial_name)
			{}
			SPROUT_NON_CONSTEXPR string_type name() const {
				return name_;
			}
		};
		template<typename Elem>
		std::locale::id sprout::logic::indeterminate_name<Elem>::id;

		//
		// operator<<
		//
		template<typename Elem, typename Traits>
		inline SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>&
		operator<<(std::basic_ostream<Elem, Traits>& lhs, sprout::logic::tribool rhs) {
			if (!sprout::logic::indeterminate(rhs)) {
				lhs << static_cast<bool>(rhs);
			} else {
				typename std::basic_ostream<Elem, Traits>::sentry cerberus(lhs);
				if (cerberus) {
					if (lhs.flags() & std::ios_base::boolalpha) {
						if (std::has_facet<sprout::logic::indeterminate_name<Elem> >(lhs.getloc())) {
							indeterminate_name<Elem> const& facet
								= std::use_facet<sprout::logic::indeterminate_name<Elem> >(lhs.getloc())
								;
							lhs << facet.name();
						} else {
							lhs << sprout::logic::get_default_indeterminate_name<Elem>();
						}
					} else {
						lhs << 2;
					}
				}
			}
			return lhs;
		}
		template<typename Elem, typename Traits>
		inline SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>&
		operator<<(std::basic_ostream<Elem, Traits>& lhs, sprout::logic::indeterminate_keyword_t) {
			return lhs << sprout::logic::tribool(indeterminate);
		}

		//
		// operator>>
		//
		template<typename Elem, typename Traits>
		inline SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>&
		operator>>(std::basic_istream<Elem, Traits>& lhs, sprout::logic::tribool& rhs) {
			if (lhs.flags() & std::ios_base::boolalpha) {
				typename std::basic_istream<Elem, Traits>::sentry cerberus(lhs);
				if (cerberus) {
					typedef std::basic_string<Elem> string_type;
					const std::numpunct<Elem>& numpunct_facet =
						std::use_facet<std::numpunct<Elem> >(lhs.getloc())
						;
					string_type falsename = numpunct_facet.falsename();
					string_type truename = numpunct_facet.truename();
					string_type othername = std::has_facet<sprout::logic::indeterminate_name<Elem> >(lhs.getloc())
						? std::use_facet<indeterminate_name<Elem> >(lhs.getloc()).name()
						: sprout::logic::get_default_indeterminate_name<Elem>()
						;
					typename string_type::size_type pos = 0;
					bool falsename_ok = true;
					bool truename_ok = true;
					bool othername_ok = true;
					while (falsename_ok && pos < falsename.size()
						|| truename_ok && pos < truename.size()
						|| othername_ok && pos < othername.size()
						)
					{
						typename Traits::int_type c = lhs.get();
						if (c == Traits::eof()) {
							return lhs;
						}
						bool matched = false;
						if (falsename_ok && pos < falsename.size()) {
							if (Traits::eq(Traits::to_char_type(c), falsename[pos])) {
								matched = true;
							} else {
								falsename_ok = false;
							}
						}
						if (truename_ok && pos < truename.size()) {
							if (Traits::eq(Traits::to_char_type(c), truename[pos])) {
								matched = true;
							} else {
								truename_ok = false;
							}
						}
						if (othername_ok && pos < othername.size()) {
							if (Traits::eq(Traits::to_char_type(c), othername[pos])) {
								matched = true;
							} else {
								othername_ok = false;
							}
						}
						if (matched) {
							++pos;
						}
						if (pos > falsename.size()) {
							falsename_ok = false;
						}
						if (pos > truename.size()) {
							truename_ok = false;
						}
						if (pos > othername.size()) {
							othername_ok = false;
						}
					}
					if (pos == 0) {
						lhs.setstate(std::ios_base::failbit);
					} else {
						if (falsename_ok) {
							rhs = false;
						} else if (truename_ok)	{
							rhs = true;
						} else if (othername_ok) {
							rhs = indeterminate;
						} else {
							lhs.setstate(std::ios_base::failbit);
						}
					}
				}
			} else {
				long value;
				if (lhs >> value) {
					switch (value) {
					case 0:
						rhs = false;
						break;
					case 1:
						rhs = true;
						break;
					case 2:
						rhs = indeterminate;
						break;
					default:
						lhs.setstate(std::ios_base::failbit);
					}
				}
			}
			return lhs;
		}
	}	// namespace logic
}	// namespace sprout

#endif	// #ifndef SPROUT_LOGIC_TRIBOOL_IO_HPP
