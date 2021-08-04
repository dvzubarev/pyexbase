
add_library(pyexbase SHARED
  exbase_bindings.cpp
  )

target_link_libraries(pyexbase PUBLIC
  pybind11::pybind11
  Boost::boost
  Boost::locale
  )
