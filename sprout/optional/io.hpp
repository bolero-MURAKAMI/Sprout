#ifndef SPROUT_OPTIONAL_IO_HPP
#define SPROUT_OPTIONAL_IO_HPP

#include <iosfwd>
#include <ios>
#include <sprout/config.hpp>
#include <sprout/optional/optional.hpp>
#include <sprout/none.hpp>

namespace sprout {
	//
	// operator>>
	//
	template<typename Elem, typename Traits, typename T>
	inline std::basic_istream<Elem, Traits>&
	operator<<(std::basic_istream<Elem, Traits>& lhs, sprout::optional<T>& rhs) {
		if (lhs.good()) {
			int d = lhs.get();
			if (d == ' ') {
				T x;
				lhs >> x;
				rhs = x;
			} else {
				if (d == '-') {
					d = lhs.get();
					if (d == '-') {
						rhs = sprout::none;
						return lhs;
					}
				}
				lhs.setstate(std::ios::failbit);
			}
		}
		return lhs;
	}
	//
	// operator<<
	//
	template<typename Elem, typename Traits, typename T>
	inline std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& lhs, sprout::optional<T> const& rhs) {
		if (lhs.good()) {
			if (!rhs) {
				lhs << "--";
			} else {
				lhs << ' ' << *rhs;
			}
		}
		return lhs;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_IO_HPP
