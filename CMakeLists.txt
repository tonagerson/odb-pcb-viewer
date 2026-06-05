cmake_minimum_required(VERSION 3.16)

project(ODBViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Modification ici : Passage en C++17 pour la compatibilité avec ton compilateur
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# On retire le flag manuel -std=c++20 qui causait l'erreur
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Xml)

set(PROJECT_SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.ui
    src/ApplicationController.cpp
    src/ApplicationModel.cpp
    src/Viewer2D.cpp
    src/core/GraphicObject.cpp
    src/core/ViewTransform.cpp
    src/core/Axis.cpp
    src/core/Product_Model.cpp
    src/core/Surface.cpp
    src/core/Outline.cpp
    src/core/Feature.cpp
    src/core/Edge.cpp
    src/core/Matrix.cpp
    src/core/Layer_desc.cpp
    src/core/Step_desc.cpp
    src/core/PCB_parser.cpp
    src/core/Form.cpp
    src/core/Layer.cpp
    src/core/Symbol.cpp
    src/core/Type.cpp
)

set(PROJECT_HEADERS
    include/MainWindow.h
    include/ApplicationController.hpp
    include/ApplicationModel.hpp
    include/Viewer2D.hpp
    include/core/GraphicObject.hpp
    include/core/ViewTransform.hpp
    include/core/Axis.hpp
    include/core/Product_Model.hpp
    include/core/Surface.hpp
    include/core/Outline.hpp
    include/core/Feature.hpp
    include/core/Edge.hpp
    include/core/Matrix.hpp
    include/core/Layer_desc.hpp
    include/core/Step_desc.hpp
    include/core/Form.hpp
    include/core/Layer.hpp
    include/core/Symbol.hpp
    include/core/Type.hpp
)
add_executable(ODBViewer
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}

)

target_link_libraries(ODBViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Xml)

# On utilise CMAKE_CURRENT_LIST_DIR pour s'assurer que les chemins sont trouvés
target_include_directories(ODBViewer PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/include/core
)

add_compile_definitions(STYLE_FILES_PATH="${CMAKE_CURRENT_LIST_DIR}")

set_target_properties(ODBViewer PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ODBViewer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)