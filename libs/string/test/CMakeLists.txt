add_executable( libs_string_test_string string.cpp )
set_target_properties( libs_string_test_string PROPERTIES OUTPUT_NAME "string" )
add_test( libs_string_test_string string )
