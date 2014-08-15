.. _sprout-string-basic_string-wstring:

###############################################################################
wstring
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N>
  using wstring = sprout::basic_string<wchar_t, N>;

Examples
========================================
.. sourcecode:: c++

  #include <type_traits>
  #include <sprout/string.hpp>
  using namespace sprout;
  
  using type = wstring<8>;
  static_assert(std::is_same<type::value_type, wchar_t>::value, "element type of wstring is charwchar_t

Header
========================================

| ``sprout/string/alias.hpp``
| Convenience header: ``sprout/string.hpp``

