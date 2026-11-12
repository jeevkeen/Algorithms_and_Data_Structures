#pragma once

# —оздаем header-only библиотеку (INTERFACE означает, что она не требует компил€ции в .lib/.a)
add_library(StackOnMassLib INTERFACE)

# ”казываем, что любой проект, подключивший эту библиотеку, должен искать заголовочные файлы в этой папке
target_include_directories(StackOnMassLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})