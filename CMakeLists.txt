# dsa-cpp - An implementation of some data structures and algorithms in C++.
# Copyright (C)  2026  Emir Baha YILDIRIM <jayshozie@gmail.com>
# Copyright (C)  2026  terra2o <terra2o@protonmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# required for c++ modules
cmake_minimum_required(VERSION 3.31)

# --------------------------------- project ---------------------------------- #
# definition
project(
    dsa-cpp
    VERSION 1.0.0
    DESCRIPTION "An implementation of some data structures and algorithms in C++."
    HOMEPAGE_URL "https://github.com/jayshozie/dsa-cpp"
    LANGUAGES CXX
)
# source file discovery
file(GLOB_RECURSE DSA_MODULE_SOURCES CONFIGURE_DEPENDS "src/*.cppm")
# library definition
add_library(dsa-cpp)
target_sources(dsa-cpp
    PUBLIC
    FILE_SET CXX_MODULES TYPE CXX_MODULES
    BASE_DIRS src
    FILES ${DSA_MODULE_SOURCES} # automated list injection
)
target_compile_features(dsa-cpp PUBLIC cxx_std_23)

# ---------------------------------- tests ----------------------------------- #
# built only internally
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    # source file discovery
    file(GLOB_RECURSE DSA_TEST_SRCS CONFIGURE_DEPENDS "tests/*.cpp")
	if(DSA_TEST_SRCS)
		# building
		foreach(DSA_TEST IN LISTS DSA_TEST_SRCS)
			# get the test's relative path relative to ./tests/
			file(RELATIVE_PATH TEST "${CMAKE_CURRENT_SOURCE_DIR}/tests" "${DSA_TEST}")
			string(REPLACE "/" "-" TEST "${TEST}")
			string(REPLACE ".cpp" "" TEST "${TEST}")

			add_executable(${TEST} ${DSA_TEST})
			target_link_libraries(${TEST} PRIVATE dsa-cpp)
			add_test(NAME ${TEST} COMMAND ${TEST})
		endforeach()
	endif()
endif()
