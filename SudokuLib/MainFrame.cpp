/**
 * @file MainFrame.cpp
 * @author Pavel Shevchenko
 */

#include "pch.h"
#include "MainFrame.h"
#include "SudokuView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Action Sudoku",
           wxDefaultPosition,  wxSize( 960,720 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto sudokuView = new SudokuView();
    sudokuView->Initialize(this);

    // Add it to the sizer
    sizer->Add(sudokuView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu;

    auto helpMenu = new wxMenu;

    auto levelMenu = new wxMenu;

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level" );
    menuBar->Append(helpMenu, L"&Help" );



    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    fileMenu->Append(IDM_SOLVE, "Solve", "Solve Action Sudoku");
    levelMenu->Append(IDM_LEVEL1, L"&Level 1", L"Go to Level 1");
    levelMenu->Append(IDM_LEVEL2, L"&Level 2", L"Go to Level 2");
    levelMenu->Append(IDM_LEVEL3, L"&Level 3", L"Go to Level 3");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    SetMenuBar( menuBar );
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::ExitMsg, this, wxID_ABOUT);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Makes the Message box for the Action Sudoku info
 * @param event
 */
void MainFrame::ExitMsg(wxCommandEvent& event)
{
    wxMessageBox(L"Action Sudoku",
                 L"Action Sudoku by Iapetus",
                 wxOK,
                 this);
}
