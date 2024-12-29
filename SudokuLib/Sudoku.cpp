/**
 * @file Sudoku.cpp
 * @author Noor M.
 */

#include "pch.h"
#include <iomanip>
#include <sstream>
#include "Sudoku.h"
#include "Item.h"
#include "Level.h"
#include "Givens.h"
#include "Digits.h"
#include "Xray.h"
#include "SpartyHead.h"
#include "Level.h"
#include "Container.h"

using namespace std;


/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;


/// Top left corner of the scoreboard in virtual pixels
/// @return at pos 10, 10
const wxPoint ScoreboardTopLeft(10, 10);

/**
 * Sudoku Constructor
 */
Sudoku::Sudoku()
{
    Level level0;
    wxString filename = L"levels/level1.xml";
    level0.Load(filename, this);

}


void Sudoku::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{


    int pixelWidth = mTileWidth*mWidth;
    int pixelHeight = mTileHeight*mHeight;

    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }

    if(mCheckDialoguePopUp)
    {
        wxBrush whiteBrush(*wxWHITE);
        graphics->SetBrush(whiteBrush);
        graphics->DrawRectangle(100, 200, 720, 335);
        if(mCurrentLevel == 1)
        {
            LevelDialoguePopUp(graphics, L"Level 1 Begin");
        }
         if(mCurrentLevel == 2)
        {
            LevelDialoguePopUp(graphics, L"Level 2 Begin");
        }
        else if(mCurrentLevel == 3)
        {
            LevelDialoguePopUp(graphics, L"Level 3 Begin");
        }
    }


    int minutes = (int)mTimeCurrent / 60; // Calculate minutes
    int seconds = (int)mTimeCurrent % 60;

    auto fontStyle = graphics->CreateFont(ScoreboardTextSize, "Arial", wxFONTFLAG_BOLD,*wxWHITE);

    graphics->SetFont(fontStyle);
    wstringstream time;
    time << setw(2) << setfill(L' ')<< minutes << L":" << setw(2) << setfill(L'0') << seconds << ends;
    graphics->DrawText(time.str(), ScoreboardTopLeft.x, ScoreboardTopLeft.y);
    graphics->PopState();
}

/**
 * clear out sudoku items
 */

void Sudoku::Clear()
{
    mItems.clear();
}


void Sudoku::Load(const wxString &filename)
{
    Clear();
    mSolution.clear();
    mLevel = std::make_shared<Level>();
    mLevel->Load(filename, this);
}






void Sudoku::Add(std::shared_ptr<Item> item)
{
//    item->SetLocation(item->GetWidth()*48, item->GetHeight()*48);
//    item->SetImage(item->GetImageFile());
    mItems.push_back(item);

}

/**  Move sparty to the front of the list of items.
*
* Removes sparty from the list and adds it to the end so it
* will display last.
* @param sparty The sparty to move
*/
void Sudoku::MoveSpartyFront(std::shared_ptr<SpartyHead> sparty)
{
    auto loc = find(std::begin(mItems), std::end(mItems), sparty);
    if (loc != std::end(mItems))
    {
        mItems.erase(loc);
    }

    mItems.push_back(sparty);
}


void Sudoku::Update(double elapsed)
{
    if(mCheckDialoguePopUp)
    {
        mCheckTime -= elapsed;
        if(mCheckTime <= 0)
        {
            mCheckDialoguePopUp = false;
            mTimeCurrent = 0;
        }
    }
    else
    {
        mTimeCurrent += elapsed;
        mCheckTime = false;
    }
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}


std::shared_ptr<Item> Sudoku::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}


/**
 * Save sudoku game
 * @param filename
 */
void Sudoku::Save(const wxString &filename)
{

}


void Sudoku::HeadButt(Item *item)
{
    for (auto items : mItems)
    {
        if (item != items.get() && items->HitTest(item->GetX(), item->GetY()))
        {
            auto loc = find(begin(mItems), end(mItems), items);
            if (loc != end(mItems))
            {
                // Knock out the cauldron/pumpkin and spread digits around
                
            }
        }
        break;
    }
}

/**
 * Create popup for each level start
 * @param message
 */
void Sudoku::LevelDialoguePopUp(std::shared_ptr<wxGraphicsContext> graphics, std::wstring message)
{
    graphics->PushState();
    wxFont font(wxSize(0, 80),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    wxColour colour(57, 255, 20);
    graphics->SetFont(font, colour);
    graphics->DrawText(message, 200, 215);

    wxFont instructionFont(wxSize(0,40),
                           wxFONTFAMILY_SWISS,
                           wxFONTSTYLE_NORMAL,
                           wxFONTWEIGHT_BOLD);
    wxColour instructionColour(0, 0, 0);
    graphics->SetFont(instructionFont, instructionColour);
    graphics->DrawText(L"Space: Eat", 325, 320);
    graphics->DrawText(L"0-8: Regurgitate", 310, 370);
    graphics->DrawText(L"B: Headbutt", 325, 420);

    graphics->PopState();

}


void Sudoku::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}


void Sudoku::MoveToXray(std::shared_ptr<Item> item)
{
    auto loc = find(std::begin(mItems), std::end(mItems), item);

    if (loc != std::end(mItems) && mXray->EatDigit(item))
    {
        mItems.erase(loc);
    }
}


std::shared_ptr<Item> Sudoku::GetDigitPointer(Digits* pointer)
{
    for(auto item: mItems)
    {
        if(item.get() == pointer)
        {
            return item;
        }
    }
    return nullptr;
}


void Sudoku::AddToSolution(int i)
{
    mSolution.push_back(i);
}

/**
 * Solve sudoku board
 */
void Sudoku::SolveBoard() {
    int firstCol = mSolutionCol;
    int firstRow = mSolutionRow;
    int maxCol = mSolutionCol + 9;
    int solutionIndex = 0;
    for (auto val : mSolution)
    {
        auto x = HitTest(mSolutionCol * mTileWidth, (mSolutionRow) * mTileHeight);

        if(x->GetImage() == L"images/background.png" || x->GetImage() == L"images/sudoku.png" || x->GetImage() == L"images/background3.png")
        {
            if(x->GetValue() != val)
            {

                for(auto item : mItems)
                {
                    if(item->GetValue() == val && !item->GetSolved())
                    {

                        item->SetLocation(mSolutionCol * mTileWidth,
                                          (mSolutionRow) * mTileHeight);
                        item->SetSolved();
                        break;

                    }
                }
            }
        }

        mSolutionCol++;
        if(mSolutionCol == maxCol)
        {
            mSolutionCol = firstCol;
            mSolutionRow++;
        }
    }

}

