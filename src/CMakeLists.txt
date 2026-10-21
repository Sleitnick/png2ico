add_executable(${EXECUTABLE_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_VERSION="${PROJECT_VERSION}")

target_sources(${EXECUTABLE_NAME} PRIVATE
	buffer.c
	err.c
	ico.c
	main.c
	png.c
)

target_compile_features(${EXECUTABLE_NAME} PUBLIC c_std_99)

target_compile_options(${EXECUTABLE_NAME} PRIVATE ${BUILD_OPTIONS})
