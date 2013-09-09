.. _sprout-string-basic_string-constructor-:
###############################################################################
basic_string
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR basic_string() = default;

Effects
========================================

| Constructs an empty object of class basic_string.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>();

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR basic_string(basic_string const&) = default;
  
  template<std::size_t N2, typename Enable = typename std::enable_if<(N2 < N)>::type>
  SPROUT_CONSTEXPR basic_string(basic_string<T, N2, Traits> const& str);

Effects
========================================

| Constructs an object of class basic_string.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>(x);

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR basic_string(basic_string const& str, size_type pos, size_type n = npos);
  
  template<std::size_t N2, typename Enable = typename std::enable_if<(N2 < N)>::type>
  SPROUT_CONSTEXPR basic_string(basic_string<T, N2, Traits> const& str, size_type pos, size_type n = npos);

Requires
========================================

| ``pos <= str.size()``.

Effects
========================================

| Constructs an object of class basic_string and determines the effective length rlen of the initial string value as the smaller of n and ``str.size() - pos``.

Throws
========================================

| std::out_of_range if ``pos > str.size()``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>(x, 4, 4);

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

----

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N2, typename Enable = typename std::enable_if<(N2 - 1 <= N)>::type>
  SPROUT_CONSTEXPR basic_string(T const(& arr)[N2]);
  
  template<std::size_t N2, typename Enable = typename std::enable_if<(N2 - 1 <= N)>::type>
  SPROUT_CONSTEXPR basic_string(T const(& arr)[N2], size_type n);

Requires
========================================

| ``min(n, rlen) <= N`` where rlen is length of arr.

Effects
========================================

| Constructs an object of class basic_string.

Throws
========================================

| std::out_of_range if ``min(n, rlen) > N`` where rlen is length of arr.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

----

Interface
========================================
.. sourcecode:: c++

  explicit SPROUT_CONSTEXPR basic_string(value_type const* s);

Requires
========================================

| s points to an array of at least ``traits_type::length(s) + 1`` elements of value_type.
| ``traits_type::length(s) <= N``.

Effects
========================================

| Constructs an object of class basic_string and determines its initial string value from the array of value_type of length ``traits_type::length(s)`` whose first element is designated by s.

Throws
========================================

| std::out_of_range if ``traits_type::length(s) > N``.

Remarks
========================================

| Uses ``traits_type::length()``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR char const* input = "homuhomu";
  SPROUT_STATIC_CONSTEXPR auto x = string<8>(input);

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR basic_string(value_type const* s, size_type n);

Requires
========================================

| s points to an array of at least n elements of value_type.
| ``min(n, traits_type::length(s)) <= N``.

Effects
========================================

| Constructs an object of class basic_string and determines its initial string value from the array of value_type of length n whose first element is designated by s.

Throws
========================================

| std::out_of_range if ``min(n, traits_type::length(s)) > N``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR char const* input = "homuhomu";
  SPROUT_STATIC_CONSTEXPR auto x = string<8>(input, 4);

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR basic_string(size_type n, value_type c);

Requires
========================================

| ``n < N``.

Effects
========================================

| Constructs an object of class basic_string and determines its initial string value by repeating the char-like object c for all n elements.

Throws
========================================

| std::out_of_range if ``n > N``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>(8, 'H');

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

----

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator>
  SPROUT_CONSTEXPR basic_string(InputIterator first, InputIterator last);

Requires
========================================

| ``distance(first, last) <= N``.

Effects
========================================

| If InputIterator is an integral type, equivalent to ``basic_string(static_cast<size_type>(first), static_cast<value_type>(last))``.
| Otherwise constructs a string from the values in the range [begin,end).

Throws
========================================

| std::out_of_range if ``distance(first, last) > N``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>(x.begin(), x.end());

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth if InputIterator meets ConstexprRandomAccessIterator requirements or an integral type, and *O(logN)* (logarithmic) depth otherwise.

----

Interface
========================================
.. sourcecode:: c++

  basic_string(std::initializer_list<value_type> il);

Requires
========================================

| ``il.size() <= N``.

Effects
========================================

| Same as ``basic_string(il.begin(), il.end())``.

Throws
========================================

| std::out_of_range if ``il.size() > N``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>({'h', 'o', 'm', 'u', 'h', 'o', 'm', 'u'});

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

