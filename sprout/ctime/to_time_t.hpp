/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CTIME_TO_TIME_T_HPP
#define SPROUT_CTIME_TO_TIME_T_HPP

#include <ctime>
#include <sprout/config.hpp>
#include <sprout/ctype/ascii.hpp>
#include <sprout/algorithm/equal.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/detail/char_conversion.hpp>

namespace sprout {
	namespace detail {
		inline SPROUT_CONSTEXPR std::time_t
		to_time_t_impl(int year, int mon, int day, int hour, int min, int sec) {
			return (((
							std::time_t(year / 4 - year / 100 + year / 400 + 367 * mon / 12 + day) + year * 365 - 719499
						) * 24 + hour
					) * 60 + min
				) * 60 + sec
				;
		}
	}	// namespace detail
	//
	// to_time_t
	//
	inline SPROUT_CONSTEXPR std::time_t
	to_time_t(int year, int mon, int day, int hour, int min, int sec) {
		return mon <= 2
			? sprout::detail::to_time_t_impl(year - 1, mon + 10, day, hour, min, sec)
			: sprout::detail::to_time_t_impl(year, mon - 2, day, hour, min, sec)
			;
	}
	inline SPROUT_CONSTEXPR std::time_t
	to_time_t(std::tm const& t) {
		return sprout::to_time_t(t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	}

	namespace detail {
		template<typename Elem>
		inline SPROUT_CONSTEXPR int
		get_num(Elem c) {
			return !sprout::isdigit(c) ? 0
				: sprout::detail::char_to_int(c)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR int
		get_month(InputIterator const& date) {
			return sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Jan")) ? 1
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Feb")) ? 2
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Mar")) ? 3
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Apr")) ? 4
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("May")) ? 5
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Jun")) ? 6
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Jul")) ? 7
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Aug")) ? 8
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Sep")) ? 9
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Oct")) ? 10
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Nov")) ? 11
				: sprout::equal(sprout::ptr_index(date), sprout::ptr_index(date, 3), sprout::ptr_index("Dec")) ? 12
				: 0
				;
		}
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR int
		get_day(RandomAccessIterator const& date) {
			return sprout::detail::get_num(date[0]) * 10
				+ sprout::detail::get_num(date[1])
				;
		}
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR int
		get_year(RandomAccessIterator const& date) {
			return sprout::detail::get_num(date[0]) * 1000
				+ sprout::detail::get_num(date[1]) * 100
				+ sprout::detail::get_num(date[2]) * 10
				+ sprout::detail::get_num(date[3])
				;
		}
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR int
		get_time(RandomAccessIterator const& time) {
			return sprout::detail::get_num(time[0]) * 10
				+ sprout::detail::get_num(time[1])
				;
		}
	}	// namespace detail
	//
	// to_time_t
	//
	template<typename RandomAccessIterator1, typename RandomAccessIterator2>
	inline SPROUT_CONSTEXPR std::time_t
	to_time_t(RandomAccessIterator1 const& date, RandomAccessIterator2 const& time) {
		return sprout::to_time_t(
			sprout::detail::get_year(date + 7),
			sprout::detail::get_month(date + 0),
			sprout::detail::get_day(date + 4),
			sprout::detail::get_time(time + 0),
			sprout::detail::get_time(time + 3),
			sprout::detail::get_time(time + 6)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CTIME_TO_TIME_T_HPP
