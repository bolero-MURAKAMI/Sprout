.. _sprout-algorithm-clamp:
###############################################################################
clamp
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T>
  inline SPROUT_CONSTEXPR T const&
  clamp(T const& value, typename sprout::identity<T>::type const& low, typename sprout::identity<T>::type const& high);
  
  template<typename T, typename Compare>
  inline SPROUT_CONSTEXPR T const&
  clamp(T const& value, typename sprout::identity<T>::type const& low, typename sprout::identity<T>::type const& high, Compare comp);

Requires
========================================

| Type T is LessThanComparable.

Returns
========================================

| low if the following corresponding conditions hold: ``value < low``, ``comp(value, low)``.
| high if the following corresponding conditions hold: ``high < value``, ``comp(high, value)``.
| Otherwise, returns value.

Remarks
========================================

| Using clamp with floating point numbers may give unexpected results if one of the values is NaN.

Complexity
========================================

| Exactly one or two comparisons.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/clamp.hpp>
  #include <sprout/array.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{0, 10}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::clamp(20, input[0], input[1]);
  static_assert(result == 10, "clamped value is 10.");

Header
========================================

| ``sprout/algorithm/clamp.hpp``
| Convenience header: ``sprout/algorithm.hpp``

