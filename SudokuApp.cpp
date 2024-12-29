/**
 * @file SudokuApp.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "SudokuApp.h"
#include "Sudoku.h"
#include <MainFrame.h>


/**
 * Initialize the application.
 * @return
 */
bool SudokuApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}

