cmake_minimum_required(VERSION 3.16)

project(librarymanage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        librarymanagementsystem.cpp
        librarymanagementsystem.h
        librarymanagementsystem.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(librarymanage
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        muonsach.h muonsach.cpp muonsach.ui
        trasach.h trasach.cpp trasach.ui
        timkiemmasach.h timkiemmasach.cpp timkiemmasach.ui

        Dau_sach.h
        Dau_sach.cpp
        Danh_sach_dau_sach.txt
        intheotheloai.h intheotheloai.cpp intheotheloai.ui
        Muon_tra.h
        Muon_tra.cpp
        The_doc_gia.cpp
        The_doc_gia.h

        ngay.h
        ngay.cpp
        docgia_100.txt
        themdocgia_dialog.h themdocgia_dialog.cpp themdocgia_dialog.ui
        themdausach.h themdausach.cpp themdausach.ui
        queue.h

        Ma_The.txt

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET librarymanage APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(librarymanage SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(librarymanage
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(librarymanage PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.librarymanage)
endif()
set_target_properties(librarymanage PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS librarymanage
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(librarymanage)
endif()
