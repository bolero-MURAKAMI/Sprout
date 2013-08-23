.. _sprout-algorithm-max:
###############################################################################
max
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T>
  inline SPROUT_CONSTEXPR T const&
  max(T const& a, T const& b);
  
  template<typename T, typename Compare>
  inline SPROUT_CONSTEXPR T const&
  max(T const& a, T const& b, Compare comp);

Requires
========================================

| Type T is LessThanComparable.

Returns
========================================

| The larger value.

Remarks
========================================

| Returns the first argument when the arguments are equivalent.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/max.hpp>
  #include <sprout/array.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{-1, 1}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::max(input[0], input[1]);
  static_assert(result == 1, "max value is 1.");

-------------------------------------------------------------------------------

Interface
========================================
.. sourcecode:: c++

  template<typename T, typename Compare>
  inline SPROUT_CONSTEXPR T
  max(std::initializer_list<T> t, Compare comp);
  
  template<typename T>
  inline SPROUT_CONSTEXPR T
  max(std::initializer_list<T> t);

Requires
========================================

| T is LessThanComparable and CopyConstructible and ``t.size() > 0``.

Returns
========================================

| The largest value in the initializer_list.

Remarks
========================================

| Returns a copy of the leftmost argument when several arguments are equivalent to the largest.
| If an implementation not support C++14 initializer_list (SPROUT_NO_CXX14_INITIALIZER_LIST defined), then this function is not specified constexpr.

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/max.hpp``
| Convenience header: ``sprout/algorithm.hpp``

