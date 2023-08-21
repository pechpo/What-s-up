# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "23_wechat_autogen"
  "CMakeFiles/23_wechat_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/23_wechat_autogen.dir/ParseCache.txt"
  )
endif()
