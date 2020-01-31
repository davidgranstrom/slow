set(source_files
  main.c
  utils.c
  )

add_executable(slow ${source_files})
install(
  TARGETS slow
  RUNTIME DESTINATION bin
  )
