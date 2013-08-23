.. _sprout-algorithm-min:
###############################################################################
min
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T>
  inline SPROUT_CONSTEXPR T const&
  min(T const& a, T const& b);
  
  template<typename T, typename Compare>
  inline SPROUT_CONSTEXPR T const&
  min(T const& a, T const& b, Compare comp);

Requires
========================================

| Type T is LessThanComparable.

Returns
========================================

| The smaller value.

Remarks
========================================

| Returns the first argument when the arguments are equivalent.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/min.hpp>
  #include <sprout/array.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{-1, 1}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::min(input[0], input[1]);
  static_assert(result == -1, "min value is -1.");

-------------------------------------------------------------------------------

Interface
========================================
.. sourcecode:: c++

  template<typename T, typename Compare>
  inline SPROUT_CONSTEXPR T
  min(std::initializer_list<T> t, Compare comp);
  
  template<typename T>
  inline SPROUT_CONSTEXPR T
  min(std::initializer_list<T> t);

Requires
========================================

| T is LessThanComparable and CopyConstructible and ``t.size() > 0``.

Returns
========================================

| The smallest value in the initializer_list.

Remarks
========================================

| Returns a copy of the leftmost argument when several arguments are equivalent to the smallest.
| If an implementation not support C++14 initializer_list (SPROUT_NO_CXX14_INITIALIZER_LIST defined), then this function is not specified constexpr.

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/min.hpp``
| Convenience header: ``sprout/algorithm.hpp``

