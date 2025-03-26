cmake_minimum_required(VERSION 3.19)
project(project-dialogue LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

add_subdirectory(external/nodeeditor)

qt_standard_project_setup()


set(CALC_SOURCE_FILES
  src/MathOperationDataModel.cpp
  src/NumberDisplayDataModel.cpp
  src/NumberSourceDataModel.cpp
)

set(CALC_HEADER_FILES
  include/AdditionModel.hpp
  include/DivisionModel.hpp
  include/DecimalData.hpp
  include/MathOperationDataModel.hpp
  include/NumberDisplayDataModel.hpp
  include/NumberSourceDataModel.hpp
  include/SubtractionModel.hpp
)

qt_add_executable(project-dialogue
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    ${CALC_SOURCE_FILES}
    ${CALC_HEADER_FILES}
)

target_link_libraries(project-dialogue
    PRIVATE
        Qt::Core
        Qt::Widgets
        QtNodes
)

target_include_directories(project-dialogue
    PRIVATE
        include
        external/nodeeditor/include
)

target_compile_definitions(project-dialogue
    PRIVATE
        -DNODE_EDITOR_STATIC)

include(GNUInstallDirs)

install(TARGETS project-dialogue
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET project-dialogue
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
