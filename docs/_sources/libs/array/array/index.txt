.. _sprout-array-array:

###############################################################################
array
###############################################################################

.. toctree::
    :hidden:

    initializer-
    operator-assign
    fill
    assign
    swap
    begin
    end
    rbegin
    rend
    cbegin
    cend
    crbegin
    crend
    size
    max_size
    empty
    operator-subscript
    at
    front
    back
    data
    c_array

Interface
========================================
.. sourcecode:: c++

  template <typename T, std::size_t N>
  class array;

Description
========================================

Member types
----------------------------------------

.. csv-table::
    :header: type, definition, note
    :widths: 4, 4, 4

    reference,              T&,                                           ""
    const_reference,        T const&,                                     ""
    iterator,               **ConstexprRandomAccessIterator**,            "| convertible to const_iterator
                                                                             convertible to pointer"
    const_iterator,         **ConstexprRandomAccessIterator**,            convertible to const_pointer
    size_type,              std::size_t,                                  ""
    difference_type,        std::ptrdiff_t,                               ""
    value_type,             T,                                            ""
    pointer,                T*,                                           ""
    const_pointer,          T const*,                                     ""
    reverse_iterator,       "| sprout::reverse_iterator<iterator>
                               **ConstexprRandomAccessIterator**",        ""
    const_reverse_iterator, "| sprout::reverse_iterator<const_iterator>
                               **ConstexprRandomAccessIterator**",        ""

Member functions
----------------------------------------

(initializer)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`(initializer) <./initializer->`, ""

construct/copy/destroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`operator= <./operator-assign>`, ""

modifiers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`fill <./fill>`, ""
    :doc:`assign <./assign>`, ""
    :doc:`swap <./swap>`, ""

iterators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`begin <./begin>`, ""
    :doc:`end <./end>`, ""
    :doc:`rbegin <./rbegin>`, ""
    :doc:`rend <./rend>`, ""
    :doc:`cbegin <./cbegin>`, ""
    :doc:`cend <./cend>`, ""
    :doc:`crbegin <./crbegin>`, ""
    :doc:`crend <./crend>`, ""

capacity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`size <./size>`, ""
    :doc:`max_size <./max_size>`, ""
    :doc:`empty <./empty>`, ""

element access
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. csv-table::
    :header: function
    :widths: 4, 8

    :doc:`operator[] <./operator-subscript>`, ""
    :doc:`at <./at>`, ""
    :doc:`front <./front>`, ""
    :doc:`back <./back>`, ""
    :doc:`data <./data>`, ""
    :doc:`c_array <./c_array>`, ""

Header
========================================

``sprout/array/array.hpp``

Convenience header: ``sprout/array.hpp``

Interface of all
========================================
.. sourcecode:: c++

  template <typename T, std::size_t N>
  class array {
    // types:
    typedef T& reference;
    typedef T const& const_reference;
    typedef /*implementation-defined*/ iterator;
    typedef /*implementation-defined*/ const_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T const* const_pointer;
    typedef sprout::reverse_iterator<iterator> reverse_iterator;
    typedef sprout::reverse_iterator<const_iterator> const_reverse_iterator;
  
    // constants:
    SPROUT_STATIC_CONSTEXPR size_type static_size = N;
  
    T elems[N ? N : 1]; // exposition only
  
    // construct/copy/destroy:
    template<typename T2>
    SPROUT_CXX14_CONSTEXPR array& operator=(array<T2, N> const& rhs);
    template<typename T2>
    SPROUT_CXX14_CONSTEXPR array& operator=(array<T2, N>&& rhs);
  
    // modifiers:
    SPROUT_CXX14_CONSTEXPR void fill(const_reference value);
    SPROUT_CONSTEXPR array fill(const_reference value) const;
    SPROUT_CXX14_CONSTEXPR void assign(const_reference value);
    SPROUT_CONSTEXPR array assign(const_reference value) const;
    SPROUT_CXX14_CONSTEXPR void swap(array&) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>())));
  
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
    SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT;
  
    // element access:
    SPROUT_CXX14_CONSTEXPR reference operator[](size_type n);
    SPROUT_CONSTEXPR const_reference operator[](size_type n) const;
    SPROUT_CXX14_CONSTEXPR reference at(size_type n);
    SPROUT_CONSTEXPR const_reference at(size_type n) const;
    SPROUT_CXX14_CONSTEXPR reference front();
    SPROUT_CONSTEXPR const_reference front() const;
    SPROUT_CXX14_CONSTEXPR reference back();
    SPROUT_CONSTEXPR const_reference back() const;
    SPROUT_CXX14_CONSTEXPR pointer data() SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT;
    SPROUT_CXX14_CONSTEXPR pointer c_array() SPROUT_NOEXCEPT;
    SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT;
  };
