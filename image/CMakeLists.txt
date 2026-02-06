#
# 주의 사항
# MSVC 2022 에서 구성시 'Visual Studio Build Tools 2022 Release - x86_amd64' 를 선택해야 합니다.
# 'Visual Studio Build Tools 2022 Release - amd64_x86' 을 선택시 link 오류가 발생합니다.
#


cmake_minimum_required(VERSION 3.20)
project(AppMain LANGUAGES CXX)

set(TARGET AppMain)

set(CMAKE_CXX_STANDARD 17)

# 소스 파일 (src 폴더 및 하위 폴더의 모든 .cpp 파일 자동 포함)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS 
    "${CMAKE_SOURCE_DIR}/src/*.cpp" 
    "${CMAKE_SOURCE_DIR}/res/*.cpp"
)

# 실행 파일 출력 경로 설정 (예: gcprojecttemplate/Debug 또는 gcprojecttemplate/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

# 중간 생성 디렉토리 미리 생성
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Release)

# 헤더 파일 포함 경로
include_directories("${CMAKE_SOURCE_DIR}/../../include")


# 타겟 정의
add_executable(${TARGET} ${SRC_FILES})
# 링커 설정
target_link_libraries(${TARGET} PRIVATE grapi-base gcruntime grapi-assist grapi-io)
if(QNX)
  target_link_libraries(${TARGET} PRIVATE c++fs)
endif()

# Debug/Release 전처리기 및 컴파일 옵션
target_compile_definitions(${TARGET} PRIVATE
    $<$<CONFIG:Debug>:_CRT_SECURE_NO_DEPRECATE>
    $<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=0>
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    D_CONSOLE DWIN32 _USE_MATH_DEFINES=1
    UNICODE _UNICODE
)

target_compile_options(${TARGET} PRIVATE
    /utf-8 /MP /std:c++latest /W0 /Zc:__cplusplus 
    $<$<CONFIG:Release>:/O2> 
    $<$<CONFIG:Debug>:/MDd> 
    $<$<CONFIG:Release>:/MD>
)


# 라이브러리 경로 변수 정의 (절대 경로 사용)
get_filename_component(RUNTIME_LIB_DIR_COMMON "${CMAKE_SOURCE_DIR}/../../lib/windows/x86_64" ABSOLUTE)
get_filename_component(RUNTIME_LIB_DIR_DEBUG "${RUNTIME_LIB_DIR_COMMON}/debug" ABSOLUTE)
get_filename_component(RUNTIME_LIB_DIR_RELEASE "${RUNTIME_LIB_DIR_COMMON}/release" ABSOLUTE)

# 라이브러리 검색 경로 (타겟별 설정 및 구성별 경로)
target_link_directories(${TARGET} PRIVATE
    $<$<CONFIG:Debug>:${RUNTIME_LIB_DIR_DEBUG}>
    $<$<CONFIG:Release>:${RUNTIME_LIB_DIR_RELEASE}>
)

# ${RUNTIME_LIB_DIR_DEBUG} 경로 출력
message(STATUS "RUNTIME_LIB_DIR_DEBUG: ${RUNTIME_LIB_DIR_DEBUG}")
message(STATUS "RUNTIME_LIB_DIR_RELEASE: ${RUNTIME_LIB_DIR_RELEASE}")

# # 리소스 파일 컴파일
# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/LearnGraphics.res
#     COMMAND rc.exe
#         /I "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared"
#         /I "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um"
#         ${CMAKE_SOURCE_DIR}/LearnGraphics/LearnGraphics.rc
#     DEPENDS ${CMAKE_SOURCE_DIR}/LearnGraphics/LearnGraphics.rc
#     COMMENT "컴파일 .rc 파일"
# )

# DLL 복사 작업
set(GRAPI_BASE_DLL "grapi-base.dll")
set(GRAPI_ASSIST_DLL "grapi-assist.dll")
set(GRAPI_IO_DLL "grapi-io.dll")
add_custom_target(CopyEngineDLL
    COMMAND ${CMAKE_COMMAND} -E echo "Copying runtime DLLs ($<CONFIG>) to $<TARGET_FILE_DIR:${TARGET}>..."
    # grapi-base.dll 복사
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:${RUNTIME_LIB_DIR_DEBUG}/${GRAPI_BASE_DLL}>$<$<CONFIG:Release>:${RUNTIME_LIB_DIR_RELEASE}/${GRAPI_BASE_DLL}>
        "$<TARGET_FILE_DIR:${TARGET}>/${GRAPI_BASE_DLL}"
    # grapi-base.lib 복사
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:${RUNTIME_LIB_DIR_DEBUG}/${GRAPI_ASSIST_DLL}>$<$<CONFIG:Release>:${RUNTIME_LIB_DIR_RELEASE}/${GRAPI_ASSIST_DLL}>
        "$<TARGET_FILE_DIR:${TARGET}>/${GRAPI_ASSIST_DLL}"
    # grapi-io.dll 복사
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:${RUNTIME_LIB_DIR_DEBUG}/${GRAPI_IO_DLL}>$<$<CONFIG:Release>:${RUNTIME_LIB_DIR_RELEASE}/${GRAPI_IO_DLL}>
        "$<TARGET_FILE_DIR:${TARGET}>/${GRAPI_IO_DLL}"

    COMMENT "Copying runtime DLLs for $<CONFIG> to executable directory"
    VERBATIM # 제너레이터 표현식이 올바르게 처리되도록 보장
)
add_dependencies(${TARGET} CopyEngineDLL)


# clean 확장 (원한다면)
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/Debug ${CMAKE_BINARY_DIR}/Release
    COMMAND ${CMAKE_SOURCE_DIR}/clear.bat
    COMMENT "Cleaning build artifacts and running clear.bat"
)

# ==================================================================================================
# Debug: Print compile / link options (configure-time)
# Usage: Just configure/generate to see flags in output. Toggle with VERBOSE_FLAGS.
# ==================================================================================================
# option(VERBOSE_FLAGS "Print detailed compile/link flags for this target" ON)
# if(VERBOSE_FLAGS)
#   message(STATUS "==== Compile / Link Flags Report (${TARGET}) ====")
#   message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
#   message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
#   message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")
#   message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
#   foreach(cfg DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
#     string(TOUPPER ${cfg} CFGU)
#     if(DEFINED CMAKE_CXX_FLAGS_${CFGU})
#       message(STATUS "CMAKE_CXX_FLAGS_${CFGU}: ${CMAKE_CXX_FLAGS_${CFGU}}")
#     endif()
#   endforeach()
#   get_target_property(_t_opts ${TARGET} COMPILE_OPTIONS)
#   if(_t_opts)
#     message(STATUS "${TARGET} COMPILE_OPTIONS: ${_t_opts}")
#   else()
#     message(STATUS "${TARGET} COMPILE_OPTIONS: (none explicit)")
#   endif()
#   get_target_property(_t_inc_dirs ${TARGET} INCLUDE_DIRECTORIES)
#   if(_t_inc_dirs)
#     message(STATUS "${TARGET} INCLUDE_DIRECTORIES:\n  ${_t_inc_dirs}")
#   endif()
#   get_target_property(_t_link_libs ${TARGET} LINK_LIBRARIES)
#   if(_t_link_libs)
#     message(STATUS "${TARGET} LINK_LIBRARIES: ${_t_link_libs}")
#   endif()
#   if(MSVC)
#     message(STATUS "MSVC runtime library: ${CMAKE_MSVC_RUNTIME_LIBRARY}")
#   endif()
#   if(CMAKE_EXPORT_COMPILE_COMMANDS)
#     message(STATUS "compile_commands.json generation: ENABLED")
#   else()
#     message(STATUS "Hint: set(CMAKE_EXPORT_COMPILE_COMMANDS ON) to generate compile_commands.json")
#   endif()
#   message(STATUS "==== End Flags Report (${TARGET}) ====")
# endif()
