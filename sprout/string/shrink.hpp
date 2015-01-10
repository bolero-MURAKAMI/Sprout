/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_SHRINK_HPP
#define SPROUT_STRING_SHRINK_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/string/string.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// shrink_string
	//
	template<typename T, std::size_t N, typename Traits = sprout::char_traits<T> >
	class shrink_string {
	public:
		typedef sprout::basic_string<T, N, Traits> string_type;
	private:
		typedef sprout::value_holder<string_type const&> holder_type;
	private:
		template<sprout::index_t... Indexes>
		static SPROUT_CONSTEXPR sprout::basic_string<T, sizeof...(Indexes), Traits>
		implicit_conversion_impl(
			string_type const& str, std::size_t len,
			sprout::index_tuple<Indexes...>
			)
		{
			typedef sprout::detail::string_construct_access<T, sizeof...(Indexes), Traits> access_type;
			return access_type::raw_construct(len, (Indexes < N ? str[Indexes] : T())...);
		}
	private:
		holder_type holder_;
	public:
		shrink_string(shrink_string const&) = default;
		shrink_string(shrink_string&&) = default;
		SPROUT_CONSTEXPR shrink_string(string_type const& s)
			: holder_(s)
		{}
		SPROUT_CONSTEXPR operator string_type const&() const {
			return holder_.get();
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR operator sprout::basic_string<T, N2, Traits>() const {
			return implicit_conversion_impl(
				holder_.get(),
				NS_SSCRISK_CEL_OR_SPROUT::min(N2, holder_.get().size()),
				sprout::make_index_tuple<(N < N2 ? N : N2)>::make()
				);
		}
	};

	//
	// shrink
	//
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::shrink_string<T, N, Traits>
	shrink(sprout::basic_string<T, N, Traits> const& s) {
		return sprout::shrink_string<T, N, Traits>(s);
	}
	template<std::size_t To, typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, To, Traits>
	shrink(sprout::basic_string<T, N, Traits> const& s) {
		return sprout::shrink(s);
	}

	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::shrink_string<T, N>
	shrink(T const(& arr)[N]) {
		return sprout::shrink(sprout::to_string(arr));
	}
	template<std::size_t To, typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, To>
	shrink(T const(& arr)[N]) {
		return sprout::shrink<To>(sprout::to_string(arr));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_SHRINK_HPP
