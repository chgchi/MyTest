AUX_SOURCE_DIRECTORY(. TESTBOOST_SRC)

INCLUDE_DIRECTORIES(BEFORE /usr/local/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/utils)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/libout/utils)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
message(STATUS "in testBoost CXXFLAG :" ${CMAKE_CXX_FLAGS})

ADD_EXECUTABLE(testBoost ${TESTBOOST_SRC})
TARGET_LINK_LIBRARIES(testBoost libgtest.a libgmock.a libutils.a)
TARGET_LINK_LIBRARIES(testBoost boost_system boost_thread boost_filesystem boost_regex boost_program_options pthread dl m)

INSTALL(TARGETS testBoost RUNTIME DESTINATION bin)

