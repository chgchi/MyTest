AUX_SOURCE_DIRECTORY(. TESTWANGLE_SRC)

INCLUDE_DIRECTORIES(BEFORE /usr/local/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/utils)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/libout/utils)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
message(STATUS "in testWangle CXXFLAG :" ${CMAKE_CXX_FLAGS})

ADD_EXECUTABLE(testWangle ${TESTWANGLE_SRC})
TARGET_LINK_LIBRARIES(testWangle libgtest.a libgmock.a libutils.a)
TARGET_LINK_LIBRARIES(testWangle wangle folly z ssl crypto cap event glog gflags pthread double-conversion boost_system boost_thread boost_filesystem)

INSTALL(TARGETS testWangle RUNTIME DESTINATION bin)

