#ifndef SPROUT_LOGIC_TRIBOOL_IO_HPP
#define SPROUT_LOGIC_TRIBOOL_IO_HPP

#include <locale>
#include <string>
#include <iosfwd>
#include <ios>
#include <sprout/config.hpp>
#include <sprout/utility/noncopyable.hpp>
#include <sprout/logic/tribool/tribool.hpp>

namespace sprout {
	namespace logic {
		//
		// get_default_indeterminate_name
		//
		template<typename Char>
		inline std::basic_string<Char>
		get_default_indeterminate_name();
		template<>
		inline std::basic_string<char>
		get_default_indeterminate_name<char>() {
			return "indeterminate";
		}
		template<>
		inline std::basic_string<wchar_t>
		get_default_indeterminate_name<wchar_t>() {
			return L"indeterminate";
		}
#if SPROUT_USE_UNICODE_LITERALS
		template<>
		inline std::basic_string<char16_t>
		get_default_indeterminate_name<char16_t>() {
			return u"indeterminate";
		}
		template<>
		inline std::basic_string<char32_t>
		get_default_indeterminate_name<char32_t>() {
			return U"indeterminate";
		}
#endif

		//
		// indeterminate_name
		//
		template<typename Char>
		class indeterminate_name
			: public std::locale::facet
			, private sprout::noncopyable
		{
		public:
			typedef Char char_type;
			typedef std::basic_string<char_type> string_type;
		public:
			static std::locale::id id;
		private:
			string_type name_;
		public:
			indeterminate_name()
				: name_(sprout::logic::get_default_indeterminate_name<char_type>())
			{}
			explicit indeterminate_name(string_type const& initial_name)
				: name_(initial_name)
			{}
			string_type name() const {
				return name_;
			}
		};
		template<typename Char>
		std::locale::id sprout::logic::indeterminate_name<Char>::id;

		//
		// operator<<
		//
		template<typename Char, typename Traits>
		inline std::basic_ostream<Char, Traits>&
		operator<<(std::basic_ostream<Char, Traits>& lhs, sprout::logic::tribool rhs) {
			if (!sprout::logic::indeterminate(rhs)) {
				lhs << static_cast<bool>(rhs);
			} else {
				typename std::basic_ostream<Char, Traits>::sentry cerberus(lhs);
				if (cerberus) {
					if (lhs.flags() & std::ios_base::boolalpha) {
						if (std::has_facet<sprout::logic::indeterminate_name<Char> >(lhs.getloc())) {
							indeterminate_name<Char> const& facet
								= std::use_facet<sprout::logic::indeterminate_name<Char> >(lhs.getloc())
								;
							lhs << facet.name();
						} else {
							lhs << sprout::logic::get_default_indeterminate_name<Char>();
						}
					} else {
						lhs << 2;
					}
				}
			}
			return lhs;
		}
		template<typename Char, typename Traits>
		inline std::basic_ostream<Char, Traits>&
		operator<<(std::basic_ostream<Char, Traits>& lhs, sprout::logic::indeterminate_keyword_t) {
			return lhs << sprout::logic::tribool(indeterminate);
		}

		//
		// operator>>
		//
		template<typename Char, typename Traits>
		inline std::basic_istream<Char, Traits>&
		operator>>(std::basic_istream<Char, Traits>& lhs, sprout::logic::tribool& rhs) {
			if (lhs.flags() & std::ios_base::boolalpha) {
				typename std::basic_istream<Char, Traits>::sentry cerberus(lhs);
				if (cerberus) {
					typedef std::basic_string<Char> string_type;
					const std::numpunct<Char>& numpunct_facet =
						std::use_facet<std::numpunct<Char> >(lhs.getloc())
						;
					string_type falsename = numpunct_facet.falsename();
					string_type truename = numpunct_facet.truename();
					string_type othername = std::has_facet<sprout::logic::indeterminate_name<Char> >(lhs.getloc())
						? std::use_facet<indeterminate_name<Char> >(lhs.getloc()).name()
						: sprout::logic::get_default_indeterminate_name<Char>()
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
