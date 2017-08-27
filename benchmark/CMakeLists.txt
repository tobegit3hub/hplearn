# Copyright 2017 The Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.7)
project(hplearn)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES ../src/op.h ../src/op.cpp ../src/graph.h ../src/graph.cpp ../src/session.h ../src/session.cpp ../src/optimizer.h ../src/optimizer.cpp)

add_executable(benchmark_liner_regression benchmark_liner_regression.cpp ${SOURCE_FILES})

add_executable(benchmark_add_operation benchmark_add_operation.cpp ${SOURCE_FILES})

add_executable(benchmark_multiple_operation benchmark_multiple_operation.cpp ${SOURCE_FILES})
