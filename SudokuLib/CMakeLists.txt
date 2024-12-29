project(SudokuLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h
        SudokuView.cpp
        SudokuView.h
        Sudoku.cpp
        Sudoku.h
        Item.cpp
        Item.h
        SpartyHead.cpp
        SpartyHead.h
        Digits.h
        Digits.cpp
        Givens.h
        Givens.cpp
        Level.cpp
        Level.h
        Scoreboard.h
        Scoreboard.cpp
        DigitsDec.cpp
        DigitsDec.h
        Background.cpp
        Background.h
        Declarations.cpp
        Declarations.h
        BackgroundDec.cpp
        BackgroundDec.h
        SpartyHeadDec.cpp
        SpartyHeadDec.h
        GivensDec.cpp
        GivensDec.h
        Xray.cpp
        Xray.h
        XrayDec.cpp
        XrayDec.h
        Container.cpp
        Container.h
        ItemVisitor.cpp
        ItemVisitor.h
        DigitEater.cpp
        DigitEater.h
        ContainerDec.h
        ContainerDec.cpp
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})