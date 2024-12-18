# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "003notePad_autogen"
  "CMakeFiles/003notePad_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/003notePad_autogen.dir/ParseCache.txt"
  )
endif()
