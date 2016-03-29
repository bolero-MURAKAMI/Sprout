add_executable( libs_utility_string_view_test_string_view string_view.cpp )
set_target_properties( libs_utility_string_view_test_string_view PROPERTIES OUTPUT_NAME "string_view" )
add_test( libs_utility_string_view_test_string_view string_view )
