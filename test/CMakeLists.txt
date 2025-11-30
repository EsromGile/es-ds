add_executable(em_ds_test main.c)

target_link_libraries(em_ds_test PRIVATE em_ds)

# Optional: register with CTest
enable_testing()
add_test(NAME em_ds_test COMMAND em_ds_test)