add_executable( tools_compost_wavconv wavconv.cpp )
set_target_properties( tools_compost_wavconv PROPERTIES OUTPUT_NAME "wavconv" )
install( TARGETS tools_compost_wavconv
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)
