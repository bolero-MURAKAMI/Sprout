/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_IO_IOS_STATE_HPP
#define SPROUT_DETAIL_IO_IOS_STATE_HPP

#include <string>
#include <ios>
#include <ostream>
#include <streambuf>
#include <locale>
#include <sprout/config.hpp>
#include <sprout/detail/io_fwd.hpp>

namespace sprout {
	namespace detail {
		namespace io {
			class ios_flags_saver {
			public:
				typedef std::ios_base state_type;
				typedef std::ios_base::fmtflags aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
			private:
				ios_flags_saver& operator=(ios_flags_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR ios_flags_saver(state_type& s)
					: s_save_(s)
					, a_save_(s.flags())
				{}
				SPROUT_NON_CONSTEXPR ios_flags_saver(state_type& s, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.flags(a))
				{}
				SPROUT_NON_CONSTEXPR ~ios_flags_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.flags(a_save_);
				}
			};

			class ios_precision_saver {
			public:
				typedef std::ios_base state_type;
				typedef std::streamsize aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
			private:
				ios_precision_saver& operator=(ios_precision_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR ios_precision_saver(state_type& s)
					: s_save_(s)
					, a_save_(s.precision())
				{}
				SPROUT_NON_CONSTEXPR ios_precision_saver(state_type& s, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.precision(a))
				{}
				SPROUT_NON_CONSTEXPR ~ios_precision_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.precision(a_save_);
				}
			};

			class ios_width_saver {
			public:
				typedef std::ios_base state_type;
				typedef std::streamsize aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
			private:
				ios_width_saver& operator=(ios_width_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR ios_width_saver(state_type& s)
					: s_save_(s)
					, a_save_(s.width())
				{}
				SPROUT_NON_CONSTEXPR ios_width_saver(state_type& s, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.width(a))
				{}
				SPROUT_NON_CONSTEXPR ~ios_width_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.width(a_save_);
				}
			};

			template<typename Elem, typename Traits>
			class basic_ios_iostate_saver {
			public:
				typedef std::basic_ios<Elem, Traits> state_type;
				typedef std::ios_base::iostate aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
			private:
				basic_ios_iostate_saver& operator=(basic_ios_iostate_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR basic_ios_iostate_saver(state_type& s)
					: s_save_(s)
					, a_save_(s.rdstate())
				{}
				SPROUT_NON_CONSTEXPR basic_ios_iostate_saver(state_type& s, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.rdstate())
				{
					s.clear(a);
				}
				SPROUT_NON_CONSTEXPR ~basic_ios_iostate_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.clear(a_save_);
				}
			};

			template<typename Elem, typename Traits>
			class basic_ios_exception_saver {
			public:
				typedef std::basic_ios<Elem, Traits> state_type;
				typedef std::ios_base::iostate aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
			private:
				basic_ios_exception_saver& operator=(basic_ios_exception_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR basic_ios_exception_saver(state_type& s)
					: s_save_(s)
					, a_save_(s.exceptions())
				{}
				SPROUT_NON_CONSTEXPR basic_ios_exception_saver(state_type& s, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.exceptions())
				{
					s.exceptions(a);
				}
				SPROUT_NON_CONSTEXPR ~basic_ios_exception_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.exceptions(a_save_);
				}
			};

			template<typename Elem, typename Traits>
			class basic_ios_tie_saver {
			public:
				typedef std::basic_ios<Elem, Traits> state_type;
				typedef std::basic_ostream<Elem, Traits>* aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
			private:
				basic_ios_tie_saver& operator=(basic_ios_tie_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR basic_ios_tie_saver(state_type& s)
					: s_save_(s)
					, a_save_(s.tie())
				{}
				SPROUT_NON_CONSTEXPR basic_ios_tie_saver(state_type& s, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.tie(a))
				{}
				SPROUT_NON_CONSTEXPR ~basic_ios_tie_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.tie(a_save_);
				}
			};

			template<typename Elem, typename Traits>
			class basic_ios_rdbuf_saver {
			public:
				typedef std::basic_ios<Elem, Traits> state_type;
				typedef std::basic_streambuf<Elem, Traits>* aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
			private:
				basic_ios_rdbuf_saver& operator=(basic_ios_rdbuf_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR basic_ios_rdbuf_saver(state_type& s)
					: s_save_(s)
					, a_save_(s.rdbuf())
				{}
				SPROUT_NON_CONSTEXPR basic_ios_rdbuf_saver(state_type& s, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.rdbuf(a))
				{}
				SPROUT_NON_CONSTEXPR ~basic_ios_rdbuf_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.rdbuf(a_save_);
				}
			};

			template<typename Elem, typename Traits>
			class basic_ios_fill_saver {
			public:
				typedef std::basic_ios<Elem, Traits> state_type;
				typedef typename state_type::char_type aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
			private:
				basic_ios_fill_saver& operator=(basic_ios_fill_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR basic_ios_fill_saver(state_type& s)
					: s_save_(s)
					, a_save_(s.fill())
				{}
				SPROUT_NON_CONSTEXPR basic_ios_fill_saver(state_type& s, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.fill(a))
				{}
				SPROUT_NON_CONSTEXPR ~basic_ios_fill_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.fill(a_save_);
				}
			};

			template<typename Elem, typename Traits>
			class basic_ios_locale_saver {
			public:
				typedef std::basic_ios<Elem, Traits> state_type;
				typedef std::locale aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
			private:
				basic_ios_locale_saver& operator=(basic_ios_locale_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR basic_ios_locale_saver(state_type& s)
					: s_save_(s)
					, a_save_(s.getloc())
				{}
				SPROUT_NON_CONSTEXPR basic_ios_locale_saver(state_type& s, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.imbue(a))
				{}
				SPROUT_NON_CONSTEXPR ~basic_ios_locale_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.imbue(a_save_);
				}
			};

			class ios_iword_saver {
			public:
				typedef std::ios_base state_type;
				typedef int index_type;
				typedef long aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
				index_type const i_save_;
			private:
				ios_iword_saver& operator=(ios_iword_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR ios_iword_saver(state_type& s, index_type i)
					: s_save_(s)
					, a_save_(s.iword(i))
					, i_save_(i)
				{}
				SPROUT_NON_CONSTEXPR ios_iword_saver(state_type& s, index_type i, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.iword(i))
					, i_save_(i)
				{
					s.iword(i) = a;
				}
				SPROUT_NON_CONSTEXPR ~ios_iword_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.iword(i_save_) = a_save_;
				}
			};

			class ios_pword_saver {
			public:
				typedef std::ios_base state_type;
				typedef int index_type;
				typedef void* aspect_type;
			private:
				state_type& s_save_;
				aspect_type const a_save_;
				index_type const i_save_;
			private:
				ios_pword_saver& operator=(ios_pword_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR ios_pword_saver(state_type& s, index_type i)
					: s_save_(s)
					, a_save_(s.pword(i))
					, i_save_(i)
				{}
				SPROUT_NON_CONSTEXPR ios_pword_saver(state_type& s, index_type i, aspect_type const& a)
					: s_save_(s)
					, a_save_(s.pword(i))
					, i_save_(i)
				{
					s.pword(i) = a;
				}
				SPROUT_NON_CONSTEXPR ~ios_pword_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.pword(i_save_) = a_save_;
				}
			};

			class ios_base_all_saver {
			public:
				typedef std::ios_base state_type;
			private:
				state_type& s_save_;
				state_type::fmtflags const a1_save_;
				std::streamsize const a2_save_;
				std::streamsize const a3_save_;
			private:
				ios_base_all_saver& operator=(ios_base_all_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR ios_base_all_saver(state_type& s)
					: s_save_(s)
					, a1_save_(s.flags())
					, a2_save_(s.precision())
					, a3_save_(s.width())
				{}
				SPROUT_NON_CONSTEXPR ~ios_base_all_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.width(a3_save_);
					s_save_.precision(a2_save_);
					s_save_.flags(a1_save_);
				}
			};

			template<typename Elem, typename Traits>
			class basic_ios_all_saver {
			public:
				typedef std::basic_ios<Elem, Traits> state_type;
			private:
				state_type& s_save_;
				typename state_type::fmtflags const a1_save_;
				std::streamsize const a2_save_;
				std::streamsize const a3_save_;
				typename state_type::iostate const a4_save_;
				typename state_type::iostate const a5_save_;
				std::basic_ostream<Elem, Traits>* const a6_save_;
				std::basic_streambuf<Elem, Traits>* const a7_save_;
				typename state_type::char_type const a8_save_;
				std::locale const a9_save_;
			private:
				basic_ios_all_saver& operator=(basic_ios_all_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				explicit SPROUT_NON_CONSTEXPR basic_ios_all_saver(state_type& s)
					: s_save_(s)
					, a1_save_(s.flags())
					, a2_save_(s.precision())
					, a3_save_(s.width())
					, a4_save_(s.rdstate())
					, a5_save_(s.exceptions())
					, a6_save_(s.tie())
					, a7_save_(s.rdbuf())
					, a8_save_(s.fill())
					, a9_save_(s.getloc())
				{}
				SPROUT_NON_CONSTEXPR ~basic_ios_all_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.imbue(a9_save_);
					s_save_.fill(a8_save_);
					s_save_.rdbuf(a7_save_);
					s_save_.tie(a6_save_);
					s_save_.exceptions(a5_save_);
					s_save_.clear(a4_save_);
					s_save_.width(a3_save_);
					s_save_.precision(a2_save_);
					s_save_.flags(a1_save_);
				}
			};

			class ios_all_word_saver {
			public:
				typedef std::ios_base state_type;
				typedef int index_type;
			private:
				state_type& s_save_;
				index_type const i_save_;
				long const a1_save_;
				void* const a2_save_;
			private:
				ios_all_word_saver& operator=(ios_all_word_saver const&) SPROUT_DELETED_FUNCTION_DECL
			public:
				SPROUT_NON_CONSTEXPR ios_all_word_saver(state_type& s, index_type i)
					: s_save_(s)
					, i_save_(i)
					, a1_save_(s.iword(i))
					, a2_save_(s.pword(i))
				{}
				SPROUT_NON_CONSTEXPR ~ios_all_word_saver() {
					this->restore();
				}
				SPROUT_NON_CONSTEXPR void restore() {
					s_save_.pword(i_save_) = a2_save_;
					s_save_.iword(i_save_) = a1_save_;
				}
			};
		}	// namespace io
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_IO_IOS_STATE_HPP
