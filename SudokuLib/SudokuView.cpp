/**
 * @file SudokuView.cpp
 * @author Pavel Shevchenko
 */

#include "pch.h"
#include "SudokuView.h"
#include "SpartyHead.h"
#include "ids.h"



#include <wx/dcbuffer.h>

/// Sparty offset scalar
const double SpartyScale = 3.0;

/// Time popups should show on the screen
const double PopUpTime = 3.0;

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

///constant for level 1 file path
const wstring level1filename = L"levels/level1.xml";

///Minimum x - cooridante for movement to be allowed
const int MinX = 24;

///Minimum y - cooridante for movement to be allowed
const int MinY = 94;

///Offset value for playing area x - movement prevention
const int OffsetX = 72;

///Offset value for playing area y - movement prevention
const int OffsetY = 24;

///Begging wstring section for general digit file name
const wstring DigitFileStart = L"images/";

///Ending wstring section for general digit file name
const wstring DigitFileEnd = L"r.png";


void SudokuView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &SudokuView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &SudokuView::OnLeftDown, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevel1, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevel2, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevel3, this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnSolve, this, IDM_SOLVE);
    //Key function bindings
    Bind(wxEVT_KEY_DOWN, &SudokuView::OnKeyDown, this);




    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    Bind(wxEVT_TIMER, &SudokuView::OnTimer, this);
    mStopWatch.Start();

//    const wstring levelName = L"levels/level1.xml";
//    mSudoku.Load(levelName);
}


void SudokuView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;

    mTime = newTime;
    mSudoku.Update(elapsed);


    // Create a graphics context
    auto gc =
        shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();


    mSudoku.OnDraw(gc, rect.GetWidth(), rect.GetHeight());


}


void SudokuView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void SudokuView::OnLeftDown(wxMouseEvent &event)
{
    auto sparty = mSudoku.GetSparty();

    auto hit = mSudoku.HitTest((event.GetX() - mSudoku.GetXOffset())/(mSudoku.GetScale()),(event.GetY() - mSudoku.GetYOffset())/(mSudoku.GetScale()));
    if(hit != nullptr)
    {
        auto xMoveCoor = (event.GetX() - mSudoku.GetXOffset())/(mSudoku.GetScale())-sparty->GetTargetX();
        auto yMoveCoor = (event.GetY() - mSudoku.GetYOffset())/(mSudoku.GetScale())-SpartyScale*sparty->GetTargetY();

        if(xMoveCoor < MinX)
        {
            xMoveCoor += OffsetX;
        }
        if(yMoveCoor < MinY)
        {
            yMoveCoor += OffsetY;
        }
        sparty->SetMoveX(xMoveCoor);
        sparty->SetMoveY(yMoveCoor);

    }


    Refresh();

}

/**
 * Makes the Message box for the Sudoku info
 * @param event
 */
void SudokuView::OnFileSaveAs(wxCommandEvent &event)
{
    wxFileDialog saveFileDialog(this, L"Save Sudoku file", L"", L"",
                                L"Sudoku Files (*.sdku)|*.sdku", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    mSudoku.Save(filename);
}


void SudokuView::OnKeyDown(wxKeyEvent& event)
{
    auto sparty = mSudoku.GetSparty();
    wxChar uc = event.GetUnicodeKey();
    if(uc == L'B')
    {
        sparty->HeadButtMovement();
    }
    else if(uc == L' ')
    {
        sparty->EatDigit();
    }
    else if(uc == L'0' || uc == L'1' || uc == L'2' || uc == L'3' || uc == L'4' || uc == L'5' || uc == L'6'
        || uc == L'7' || uc == L'8')
    {
        wstring itemFile = DigitFileStart + uc + DigitFileEnd;
        mSudoku.GetXray()->MoveToSudoku(itemFile);
    }

}

/**
 * Function to load level 1 on event
 * @param event
 */
void SudokuView::OnLevel1(wxCommandEvent &event)
{

    mSudoku.Clear();
    mSudoku.SetCurrentLevel(1);
    mSudoku.Load(L"levels/level1.xml");
    mSudoku.SetDialoguePopUp(true);
    mSudoku.SetPopUpTime(PopUpTime);

    Refresh();
}

/**
 * Function to load level 2 on event
 * @param event
 */
void SudokuView::OnLevel2(wxCommandEvent &event)
{

    mSudoku.Clear();
    mSudoku.SetCurrentLevel(2);
    mSudoku.Load(L"levels/level2.xml");
    mSudoku.SetDialoguePopUp(true);
    mSudoku.SetPopUpTime(PopUpTime);
    Refresh();
}

/**
 * Function to load level 3 on event
 * @param event
 */
void SudokuView::OnLevel3(wxCommandEvent &event)
{

    if (getOsName() == "Mac OSX")
    {
        for(int i = 0; i < 10; i++)
        {
            system("open https://www.youtube.com/watch?v=uHgt8giw1LY");
        }
        system("open https://r.mtdv.me/products/Sudokuapp-for-app-of-awsomeness");
    }
    else if (getOsName() == "Windows 32-bit" || getOsName() == "Windows 64-bit")
    {
        std::string op = std::string("start ").append("https://www.youtube.com/watch?v=uHgt8giw1LY");
        for(int i = 0; i < 10; i++)
        {
            system(op.c_str());
        }

        system(op.c_str());

        std::string op2 = std::string("start ").append("https://r.mtdv.me/products/Sudokuapp-for-app-of-awsomeness");
        system(op2.c_str());
    }

    mSudoku.Clear();
    mSudoku.SetCurrentLevel(3);
    mSudoku.Load(L"levels/level3.xml");
    mSudoku.SetDialoguePopUp(true);
    mSudoku.SetPopUpTime(PopUpTime);
    Refresh();
}

void SudokuView::OnSolve(wxCommandEvent &event)
{
    mSudoku.SolveBoard();
    Refresh();
}

std::string SudokuView::getOsName()
{
    #ifdef _WIN32
        return "Windows 32-bit";
    #elif _WIN64
        return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
        return "Mac OSX";
    #endif
}
