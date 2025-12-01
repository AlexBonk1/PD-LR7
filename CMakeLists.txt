cmake_minimum_required(VERSION 3.16)

project(LR_7 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


# set(ASM_SOURCE_BLUR "${CMAKE_CURRENT_SOURCE_DIR}/blur.asm")
# set(ASM_OBJECT_BLUR "${CMAKE_CURRENT_BINARY_DIR}/blur.o")

# # 3. Создаем кастомную команду для компиляции
# # Мы сами пишем флаги: -f elf64 (для Linux x64)
# add_custom_command(
#     OUTPUT ${ASM_OBJECT_BLUR}
#     COMMAND /usr/bin/nasm -f elf64 ${ASM_SOURCE_BLUR} -o ${ASM_OBJECT_BLUR}
#     DEPENDS ${ASM_SOURCE_BLUR}
#     COMMENT "Compiling NASM assembly: ${ASM_SOURCE_BLUR}"
# )


set(ASM_COLORS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/colorOperations.asm")
set(ASM_COLORS_OBJECT "${CMAKE_CURRENT_SOURCE_DIR}/colorOperations.o")


add_custom_command(
    OUTPUT ${ASM_COLORS_OBJECT}
    COMMAND /usr/bin/nasm -f elf64 ${ASM_COLORS_SOURCE} -o ${ASM_COLORS_OBJECT}
    DEPENDS ${ASM_COLORS_SOURCE}
    COMMENT "Compiling NASM assembly: ${ASM_COLORS_SOURCE}"
)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        scrollerswidget.h
        scrollerswidget.cpp
        menubar.h
        menubar.cpp
        iactionmanager.h
        iactionmanager.cpp
        contentwidget.h
        contentwidget.cpp

        actionmanager.h
        actionmanager.cpp
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    add_executable(LR_7 ${PROJECT_SOURCES} ${ASM_COLORS_OBJECT}
        sliderbox.h sliderbox.cpp
        imageeffectscontroller.h imageeffectscontroller.cpp
        stacklist.h stacklist.cpp
        Effects/abstracteffect.h

        Effects/EffectsBuilder.h
        fileinfo.h fileinfo.cpp

        )
else()
    if(ANDROID)
        add_library(LR_7 SHARED ${PROJECT_SOURCES} ${ASM_COLORS_OBJECT} )
    else()
        add_executable(LR_7 ${PROJECT_SOURCES} ${ASM_COLORS_OBJECT} )
    endif()
endif()

target_link_libraries(LR_7 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

