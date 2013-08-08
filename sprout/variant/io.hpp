/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_IO_HPP
#define SPROUT_VARIANT_IO_HPP

#include <sprout/config.hpp>
#include <sprout/variant/variant.hpp>
#include <sprout/variant/static_visitor.hpp>

namespace sprout {
	namespace detail {
		template<typename OStream>
		class variant_output_visitor
			: public sprout::static_visitor<>
		{
		public:
			typedef OStream ostream_type;
		private:
			ostream_type& out_;
		public:
			explicit variant_output_visitor(ostream_type& out)
				: out_(out)
			{}
			template<typename T>
			void operator()(T const& operand) const {
				out_ << operand;
			}
		};
	}	// namespace detail
	//
	// operator<<
	//
	template<typename Elem, typename Traits, typename... Types>
	inline std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& lhs, sprout::variant<Types...> const& rhs) {
		sprout::detail::variant_output_visitor<std::basic_ostream<Elem, Traits> > visitor(lhs);
		rhs.apply_visitor(visitor);
		return lhs;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_IO_HPP
