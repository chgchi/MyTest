AUX_SOURCE_DIRECTORY(. TESTOTHER_SRC)

INCLUDE_DIRECTORIES(BEFORE /usr/local/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/utils)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/libout/utils)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
message(STATUS "in testOther CXXFLAG :" ${CMAKE_CXX_FLAGS})

ADD_EXECUTABLE(testOther ${TESTOTHER_SRC})
TARGET_LINK_LIBRARIES(testOther libgtest.a libgmock.a libutils.a)
TARGET_LINK_LIBRARIES(testOther z ssl crypto  pthread boost_system boost_thread boost_filesystem boost_regex boost_program_options dl m)

INSTALL(TARGETS testOther RUNTIME DESTINATION bin)
