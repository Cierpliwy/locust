find_path(Locust_INCLUDE_DIRS Locust/Locust.hpp ${CMAKE_SOURCE_DIR}/lib/include)
find_library(Locust_LIBRARIES locust ${CMAKE_BINARY_DIR}/lib)

set(Locust_FOUND TRUE)

if (NOT Locust_INCLUDE_DIRS)
    set(Locust_FOUND FALSE)
endif (NOT Locust_INCLUDE_DIRS)

if (NOT Locust_LIBRARIES)
    set(Locust_LIBRARIES ${CMAKE_BINARY_DIR}/lib)
endif (NOT Locust_LIBRARIES)
