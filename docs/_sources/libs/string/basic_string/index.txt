.. _sprout-string-basic_string:
###############################################################################
basic_string
###############################################################################

.. toctree::
    :hidden:

    constructor-
    operator-assign
    begin
    end
    rbegin
    rend
    cbegin
    cend
    crbegin
    crend
    size
    length
    max_size
    resize
    clear
    empty
    operator-subscript
    at
    front
    back
    assign
    swap
    data
    c_array
    data
    find
    rfind
    find_first_of
    find_last_of
    find_first_not_of
    find_last_not_of
    substr
    compare
    operator-std-basic_string
    operator-assign-iterator
    assign-iterator
    find-iterator
    rfind-iterator
    find_first_of-iterator
    find_last_of-iterator
    find_first_not_of-iterator
    find_last_not_of-iterator
    compare-iterator

Interface
========================================
.. sourcecode:: c++

  template <typename T, std::size_t N, typename Traits = sprout::char_traits<T> >
  class basic_string;

Description
========================================

Member types
----------------------------------------

======================================== =============================================================================== =======================================
type                                     definition                                                                      note
======================================== =============================================================================== =======================================
traits_type                              Traits
value_type                               Traits::char_type
size_type                                std::size_t
difference_type                          std::ptrdiff_t
reference                                value_type&
const_reference                          value_type const&
pointer                                  value_type*
const_pointer                            value_type const*
iterator                                 **ConstexprRandomAccessIterator**                                               convertible to const_iterator,
                                                                                                                         convertible to pointer
const_iterator                           **ConstexprRandomAccessIterator**                                               convertible to const_pointer
reverse_iterator                         sprout::reverse_iterator<iterator>,
                                         **ConstexprRandomAccessIterator**
const_reverse_iterator                   sprout::reverse_iterator<const_iterator>,
                                         **ConstexprRandomAccessIterator**
======================================== =============================================================================== =======================================

Member functions
----------------------------------------

construct/copy/destroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`(constructor) <./constructor->`
:doc:`operator= <./operator-assign>`
======================================== ===============================================================================

iterators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`begin <./begin>`
:doc:`end <./end>`
:doc:`rbegin <./rbegin>`
:doc:`rend <./rend>`
:doc:`cbegin <./cbegin>`
:doc:`cend <./cend>`
:doc:`crbegin <./crbegin>`
:doc:`crend <./crend>`
======================================== ===============================================================================

capacity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`size <./size>`
:doc:`length <./length>`
:doc:`max_size <./max_size>`
:doc:`resize <./resize>`
:doc:`clear <./clear>`
:doc:`empty <./empty>`
======================================== ===============================================================================

element access
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`operator[] <./operator-subscript>`
:doc:`at <./at>`
:doc:`front <./front>`
:doc:`back <./back>`
======================================== ===============================================================================

modifiers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`assign <./assign>`
:doc:`swap <./swap>`
======================================== ===============================================================================

string operations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

============================================================ ===============================================================================
function
============================================================ ===============================================================================
:doc:`data <./data>`
:doc:`c_array <./c_array>`
:doc:`find <./find>`
:doc:`rfind <./rfind>`
:doc:`find_first_of <./find_first_of>`
:doc:`find_last_of <./find_last_of>`
:doc:`find_first_not_of <./find_first_not_of>`
:doc:`find_last_not_of <./find_last_not_of>`
:doc:`substr <./substr>`
:doc:`compare <./compare>`
============================================================ ===============================================================================
    
conversions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

================================================================================ ===============================================================================
function
================================================================================ ===============================================================================
:doc:`operator std::basic_string <./operator-std-basic_string>`
================================================================================ ===============================================================================

construct/copy/destroy (for string iterator)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

============================================================ ===============================================================================
function
============================================================ ===============================================================================
:doc:`operator= <./operator-assign-iterator>`
============================================================ ===============================================================================

modifiers (for string iterator)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`assign <./assign-iterator>`
======================================== ===============================================================================

string operations (for string iterator)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

============================================================ ===============================================================================
function
============================================================ ===============================================================================
:doc:`find <./find-iterator>`
:doc:`rfind <./rfind-iterator>`
:doc:`find_first_of <./find_first_of-iterator>`
:doc:`find_last_of <./find_last_of-iterator>`
:doc:`find_first_not_of <./find_first_not_of-iterator>`
:doc:`find_last_not_of <./find_last_not_of-iterator>`
:doc:`compare <./compare-iterator>`
============================================================ ===============================================================================

Header
========================================

``sprout/string/string.hpp``

Convenience header: ``sprout/string.hpp``

Interface of all
========================================
.. sourcecode:: c++

  template <typename T, std::size_t N, typename Traits = sprout::char_traits<T> >
  class basic_string {
    // types:
    typedef Traits traits_type;
    typedef typename Traits::char_type value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef /*implementation-defined*/ iterator;
    typedef /*implementation-defined*/ const_iterator;
    typedef sprout::reverse_iterator<iterator> reverse_iterator;
    typedef sprout::reverse_iterator<const_iterator> const_reverse_iterator;
  
    // constants:
    SPROUT_STATIC_CONSTEXPR size_type npos = -1;
    SPROUT_STATIC_CONSTEXPR size_type static_size = N;
  
    // construct/copy/destroy:
    SPROUT_CONSTEXPR basic_string() = default;
    SPROUT_CONSTEXPR basic_string(basic_string const&) = default;
    template<std::size_t N2, typename Enable = typename std::enable_if<(N2 < N)>::type>
    SPROUT_CONSTEXPR basic_string(basic_string<T, N2, Traits> const& str);
    SPROUT_CONSTEXPR basic_string(basic_string const& str, size_type pos, size_type n = npos);
    template<std::size_t N2, typename Enable = typename std::enable_if<(N2 < N)>::type>
    SPROUT_CONSTEXPR basic_string(basic_string<T, N2, Traits> const& str, size_type pos, size_type n = npos);
    template<std::size_t N2, typename Enable = typename std::enable_if<(N2 - 1 <= N)>::type>
    SPROUT_CONSTEXPR basic_string(T const(& arr)[N2]);
    template<std::size_t N2, typename Enable = typename std::enable_if<(N2 - 1 <= N)>::type>
    SPROUT_CONSTEXPR basic_string(T const(& arr)[N2], size_type n);
    explicit SPROUT_CONSTEXPR basic_string(value_type const* s);
    SPROUT_CONSTEXPR basic_string(value_type const* s, size_type n);
    SPROUT_CONSTEXPR basic_string(size_type n, value_type c);
    template<typename InputIterator>
    SPROUT_CONSTEXPR basic_string(InputIterator first, InputIterator last);
    SPROUT_INITIALIZER_LIST_CONSTEXPR basic_string(std::initializer_list<value_type> il);
    SPROUT_CXX14_CONSTEXPR basic_string& operator=(basic_string const& rhs);
    template<std::size_t N2, typename Enable = typename std::enable_if<(N2 != N)>::type>
    SPROUT_CXX14_CONSTEXPR basic_string& operator=(basic_string<T, N2, Traits> const& rhs);
    SPROUT_CXX14_CONSTEXPR basic_string& operator=(value_type const* rhs);
    SPROUT_CXX14_CONSTEXPR basic_string& operator=(value_type rhs);
  
    // iterators:
    SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT;
    SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT;
    SPROUT_CXX14_CONSTEXPR reverse_iterator rbegin() SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT;
    SPROUT_CXX14_CONSTEXPR reverse_iterator rend() SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT;
  
    // capacity:
    SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR size_type length() const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT;
    SPROUT_CXX14_CONSTEXPR void resize(size_type n, value_type c);
    SPROUT_CXX14_CONSTEXPR void resize(size_type n);
    SPROUT_CXX14_CONSTEXPR void clear() SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT;
  
    // element access:
    SPROUT_CXX14_CONSTEXPR reference operator[](size_type i);
    SPROUT_CONSTEXPR const_reference operator[](size_type i) const;
    SPROUT_CXX14_CONSTEXPR reference at(size_type i);
    SPROUT_CONSTEXPR const_reference at(size_type i) const;
    SPROUT_CXX14_CONSTEXPR reference front();
    SPROUT_CONSTEXPR const_reference front() const;
    SPROUT_CXX14_CONSTEXPR reference back();
    SPROUT_CONSTEXPR const_reference back() const;
  
    // modifiers:
    template<std::size_t N2>
    SPROUT_CXX14_CONSTEXPR basic_string& assign(basic_string<T, N2, Traits> const& str);
    template<std::size_t N2>
    SPROUT_CXX14_CONSTEXPR basic_string& assign(basic_string<T, N2, Traits> const& str, size_type pos, size_type n);
    SPROUT_CXX14_CONSTEXPR basic_string& assign(value_type const* s, size_type n);
    SPROUT_CXX14_CONSTEXPR basic_string& assign(value_type const* s);
    SPROUT_CXX14_CONSTEXPR basic_string& assign(size_type n, value_type c);
    template<typename InputIterator>
    SPROUT_CXX14_CONSTEXPR basic_string& assign(InputIterator first, InputIterator last);
    SPROUT_CXX14_CONSTEXPR void swap(basic_string& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>())));
  
    // string operations:
    SPROUT_CONSTEXPR const_pointer c_str() const SPROUT_NOEXCEPT;
    SPROUT_CXX14_CONSTEXPR pointer data() SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT;
    SPROUT_CXX14_CONSTEXPR pointer c_array() SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT;
    template<std::size_t N2>
    SPROUT_CONSTEXPR size_type find(basic_string<T, N2, Traits> const& str, size_type pos = 0) const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR size_type find(value_type const* s, size_type pos, size_type n) const;
    SPROUT_CONSTEXPR size_type find(value_type const* s, size_type pos = 0) const;
    SPROUT_CONSTEXPR size_type find(value_type c, size_type pos = 0) const;
    template<std::size_t N2>
    SPROUT_CONSTEXPR size_type rfind(basic_string<T, N2, Traits> const& str, size_type pos = npos) const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR size_type rfind(value_type const* s, size_type pos, size_type n) const;
    SPROUT_CONSTEXPR size_type rfind(value_type const* s, size_type pos = npos) const;
    SPROUT_CONSTEXPR size_type rfind(value_type c, size_type pos = npos) const;
    template<std::size_t N2>
    SPROUT_CONSTEXPR size_type find_first_of(basic_string<T, N2, Traits> const& str, size_type pos = 0) const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR size_type find_first_of(value_type const* s, size_type pos, size_type n) const;
    SPROUT_CONSTEXPR size_type find_first_of(value_type const* s, size_type pos = 0) const;
    SPROUT_CONSTEXPR size_type find_first_of(value_type c, size_type pos = 0) const;
    template<std::size_t N2>
    SPROUT_CONSTEXPR size_type find_last_of(basic_string<T, N2, Traits> const& str, size_type pos = npos) const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR size_type find_last_of(value_type const* s, size_type pos, size_type n) const;
    SPROUT_CONSTEXPR size_type find_last_of(value_type const* s, size_type pos = npos) const;
    SPROUT_CONSTEXPR size_type find_last_of(value_type c, size_type pos = npos) const;
    template<std::size_t N2>
    SPROUT_CONSTEXPR size_type find_first_not_of(basic_string<T, N2, Traits> const& str, size_type pos = 0) const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR size_type find_first_not_of(value_type const* s, size_type pos, size_type n) const;
    SPROUT_CONSTEXPR size_type find_first_not_of(value_type const* s, size_type pos = 0) const;
    SPROUT_CONSTEXPR size_type find_first_not_of(value_type c, size_type pos = 0) const;
    template<std::size_t N2>
    SPROUT_CONSTEXPR size_type find_last_not_of(basic_string<T, N2, Traits> const& str, size_type pos = npos) const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR size_type find_last_not_of(value_type const* s, size_type pos, size_type n) const;
    SPROUT_CONSTEXPR size_type find_last_not_of(value_type const* s, size_type pos = npos) const;
    SPROUT_CONSTEXPR size_type find_last_not_of(value_type c, size_type pos = npos) const;
    SPROUT_CONSTEXPR basic_string substr(size_type pos = 0, size_type n = npos) const;
    template<std::size_t N2>
    SPROUT_CONSTEXPR int compare(basic_string<T, N2, Traits> const& str) const;
    SPROUT_CONSTEXPR int compare(value_type const* s) const;
    template<std::size_t N2>
    SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str) const;
    SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, value_type const* s) const;
    template<std::size_t N2>
    SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str, size_type pos2, size_type n2) const;
    SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, value_type const* s, size_type n2) const;
  
    // conversions:
    template<typename Allocator>
    SPROUT_EXPLICIT_CONVERSION SPROUT_NON_CONSTEXPR operator std::basic_string<T, Traits, Allocator>() const;

    // construct/copy/destroy (for string iterator):
    template<typename StringConstIterator>
    SPROUT_CXX14_CONSTEXPR basic_string& operator=(StringConstIterator rhs);

    // modifiers (for string iterator):
    template<typename StringConstIterator>
    SPROUT_CXX14_CONSTEXPR basic_string& assign(StringConstIterator s, size_type n);
    template<typename StringConstIterator>
    SPROUT_CXX14_CONSTEXPR basic_string& assign(StringConstIterator s);

    // string operations (for string iterator):
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find(StringConstIterator s, size_type pos, size_type n) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find(StringConstIterator s, size_type pos = 0) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type rfind(StringConstIterator s, size_type pos, size_type n) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type rfind(StringConstIterator s, size_type pos = npos) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find_first_of(StringConstIterator s, size_type pos, size_type n) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find_first_of(StringConstIterator s, size_type pos = 0) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find_last_of(StringConstIterator s, size_type pos, size_type n) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find_last_of(StringConstIterator s, size_type pos = 0) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find_first_not_of(StringConstIterator s, size_type pos, size_type n) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find_first_not_of(StringConstIterator s, size_type pos = 0) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find_last_not_of(StringConstIterator s, size_type pos, size_type n) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR size_type find_last_not_of(StringConstIterator s, size_type pos = npos) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR int compare(StringConstIterator s) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, StringConstIterator s) const;
    template<typename StringConstIterator>
    SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, StringConstIterator s, size_type n2) const;
  };
