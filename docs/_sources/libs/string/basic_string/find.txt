.. _sprout-string-basic_string-find:
###############################################################################
find
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N2>
  SPROUT_CONSTEXPR size_type find(basic_string<T, N2, Traits> const& str, size_type pos = 0) const SPROUT_NOEXCEPT;

Effects
========================================

| Determines the lowest position xpos, if possible, such that both of the following conditions obtain:

* ``pos <= xpos and xpos + str.size() <= size();``
* ``traits_type::eq(at(xpos + I), str.at(I))`` for all elements I of the string controlled by str.

Returns
========================================

| xpos if the function can determine such a value for xpos. Otherwise, returns npos.

Remarks
========================================

| Uses ``traits_type::eq()``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("madocchi");
  SPROUT_STATIC_CONSTEXPR auto result = input.find("cchi");
  static_assert(result == 4, "a found position is 4.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

.. note::
  The current implementation is incomplete. *O(N)* (linear) depth.

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR size_type find(value_type const* s, size_type pos, size_type n) const;

Returns
========================================

| 

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR size_type find(value_type const* s, size_type pos = 0) const;

Returns
========================================

| 

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR size_type find(value_type c, size_type pos = 0) const;

Returns
========================================

| 

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

