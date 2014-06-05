add_executable( tools_files_filegraph filegraph.cpp )
set_target_properties( tools_files_filegraph PROPERTIES OUTPUT_NAME "filegraph" )
install( TARGETS tools_files_filegraph
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)
