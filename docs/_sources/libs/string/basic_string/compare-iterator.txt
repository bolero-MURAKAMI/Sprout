.. _sprout-string-basic_string-compare-iterator:

###############################################################################
compare
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename StringConstIterator>
  SPROUT_CONSTEXPR int compare(StringConstIterator s) const;

Requires
========================================

| ``std::is_same<StringConstIterator, const_iterator>::value || std::is_same<StringConstIterator, iterator>::value``.

Returns
========================================

| ``compare(basic_string(s))``.

----

Interface
========================================
.. sourcecode:: c++

  template<typename StringConstIterator>
  SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, StringConstIterator s) const;

Requires
========================================

| ``std::is_same<StringConstIterator, const_iterator>::value || std::is_same<StringConstIterator, iterator>::value``.

Returns
========================================

| ``basic_string(*this, pos, n1).compare(basic_string(s))``.

----

Interface
========================================
.. sourcecode:: c++

  template<typename StringConstIterator>
  SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, StringConstIterator s, size_type n2) const;

Requires
========================================

| ``std::is_same<StringConstIterator, const_iterator>::value || std::is_same<StringConstIterator, iterator>::value``.

Returns
========================================

| ``basic_string(*this, pos, n1).compare(basic_string(s, n2))``.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

