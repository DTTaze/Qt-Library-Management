cmake_minimum_required(VERSION 3.16)

project(librarymanage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6  REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

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
        themDocGia_dialog.h themDocGia_dialog.cpp themDocGia_dialog.ui
        themdausach.h themdausach.cpp themdausach.ui
        queue.h


        thanh_ly.h thanh_ly.cpp thanh_ly.ui
        Ma_The.txt
        danhmucsach.h danhmucsach.cpp danhmucsach.ui
        xoa_dau_sach.h xoa_dau_sach.cpp xoa_dau_sach.ui
        hieuChinhDocGia_dialog.h hieuChinhDocGia_dialog.cpp hieuChinhDocGia_dialog.ui
        edit_sach.h edit_sach.cpp edit_sach.ui
        xoaDocGia_dialog.h xoaDocGia_dialog.cpp xoaDocGia_dialog.ui
        nhap_dausach.h nhap_dausach.cpp nhap_dausach.ui




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

target_link_libraries(librarymanage PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

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
