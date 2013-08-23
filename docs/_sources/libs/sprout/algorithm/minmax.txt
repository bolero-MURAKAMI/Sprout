.. _sprout-algorithm-minmax:
###############################################################################
minmax
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T>
  inline SPROUT_CONSTEXPR sprout::pair<T const&, T const&>
  minmax(T const& a, T const& b);
  
  template<typename T, typename Compare>
  inline SPROUT_CONSTEXPR sprout::pair<T const&, T const&>
  minmax(T const& a, T const& b, Compare comp);

Requires
========================================

| Type T shall be LessThanComparable.

Returns
========================================

| ``pair<T const&, T const&>(b, a)`` if b is smaller than a, and ``pair<T const&, T const&>(a, b)`` otherwise.

Remarks
========================================

| Returns ``pair<T const&, T const&>(a, b)`` when the arguments are equivalent.

Remarks
========================================

Examples
========================================
.. sourcecode:: c++

  #include <sprout/algorithm/minmax.hpp>
  #include <sprout/array.hpp>
  using namespace sprout;

  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{-1, 1}};
  SPROUT_STATIC_CONSTEXPR auto result = sprout::minmax(input[0], input[1]);
  static_assert(result.first == -1, "min value is -1.");
  static_assert(result.second == 1, "max value is 1.");

Complexity
========================================

| Exactly one comparison.

-------------------------------------------------------------------------------

Interface
========================================
.. sourcecode:: c++

  template<typename T, typename Compare>
  inline SPROUT_CONSTEXPR sprout::pair<T, T>
  minmax(std::initializer_list<T> t, Compare comp);
  
  template<typename T>
  inline SPROUT_CONSTEXPR sprout::pair<T, T>
  minmax(std::initializer_list<T> t);

Requires
========================================

| T is LessThanComparable and CopyConstructible and ``t.size() > 0``.

Returns
========================================

| ``pair<T, T>(x, y)``, where x has the smallest and y has the largest value in the initializer list.

Remarks
========================================

| x is a copy of the leftmost argument when several arguments are equivalent to the smallest.
| y is a copy of the rightmost argument when several arguments are equivalent to the largest.
| If an implementation not support C++14 initializer_list (SPROUT_NO_CXX14_INITIALIZER_LIST defined), then this function is not specified constexpr.

Complexity
========================================

| At most ``(3/2) * t.size()`` applications of the corresponding predicate.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/algorithm/minmax.hpp``
| Convenience header: ``sprout/algorithm.hpp``

