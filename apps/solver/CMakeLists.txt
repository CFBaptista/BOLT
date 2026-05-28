add_executable(bolt
    main.cpp
)

target_compile_features(bolt PRIVATE cxx_std_23)

target_link_libraries(bolt PRIVATE
    tomlplusplus::tomlplusplus
)
