.. _sprout-string-basic_string-substr:

###############################################################################
substr
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR basic_string substr(size_type pos = 0, size_type n = npos) const;

Requires
========================================

| ``pos <= size()``.

Returns
========================================

| ``basic_string(data() + pos, rlen)`` where rlen is the smaller of n and ``size() - pos``.

Throws
========================================

| std::out_of_range if ``pos > size()``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = x.substr(4, 4);
  SPROUT_ASSERT_MASG(y == "homu", "y is substring of x.");

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

