cmake_minimum_required(VERSION 3.16)

project(GPA_Calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Sql )
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Sql REQUIRED)

enable_testing()





add_executable(GPA_Calculator
    #MANUAL_FINALIZATION
    #${PROJECT_SOURCES}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    person.h Person.cpp
    student.h student.cpp
    

    gpa.qrc
    gpa.qrc
    gpa.qrc
    registration_dialog.h 
    registration_dialog.cpp 
    registration_dialog.ui

    registration.qrc
    signin_dialog.h signin_dialog.cpp signin_dialog.ui
    student_profile_dialog.h student_profile_dialog.cpp student_profile_dialog.ui
    subject.h
    icons.qrc

    administration.h administration.cpp
    mainwindow.h mainwindow.cpp mainwindow.ui
    mysqlite_db.h mysqlite_db.cpp
    Gpa.qrc

)


#target_link_libraries(GPA_Calculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(GPA_Calculator PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
        Qt6::Core
        Qt6::Sql
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GPA_Calculator)
endif()
set_target_properties(GPA_Calculator PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GPA_Calculator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GPA_Calculator)
endif()
