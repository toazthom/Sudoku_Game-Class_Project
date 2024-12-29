/**
 * @file Item.cpp
 * @author Pavel Shevchenko, Pranav Shukla
 */


#include "pch.h"
#include "Item.h"
#include "Sudoku.h"

/// Scaling constant for shrinking items into xray
const double XrayScale = 0.6;

/**
 * Destructor
 */
Item::~Item()
{

}


Item::Item(Sudoku *sudoku) : mSudoku(sudoku)
{
}

/**
 * saves level for sudoku game
 * @param node
 * @return node
 */
wxXmlNode *Item::XmlSave(wxXmlNode *node) {
    return node;
}

/**
 * Loads in items for sudoku game
 * @param node
 */
void Item::XmlLoad(wxXmlNode *node) {

}



void Item::SetImage(const std::wstring &file) {
    if (!file.empty())
    {
        mItemImage = std::make_unique<wxImage>(file, wxBITMAP_TYPE_ANY);
    }
    else
    {
        mItemImage.release();
    }

    mFile = file;
}



bool Item::HitTest(int x, int y)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX();// - wid / 2;
    double testY = y - GetY();// - hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return true;
}


void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mItemBitmap.IsNull())
    {
        mItemBitmap = graphics->CreateBitmapFromImage(*mItemImage);
    }

    int digitWidth = mItemImage->GetWidth();
    int digitHeight = mItemImage->GetHeight();

    auto xray = GetSudoku()->GetXray();


    graphics->PushState();
    if (mItemIsEaten && !mRandomPositionSet)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        auto xray = GetSudoku()->GetXray();


        std::uniform_real_distribution<double> distX(0, xray->GetWidth() - digitWidth * XrayScale);
        std::uniform_real_distribution<double> distY(0, xray->GetHeight() - digitHeight * XrayScale);

        mRandomX = distX(gen);
        mRandomY = distY(gen);
        mRandomPositionSet = true; // Ensure we don't generate the position again
    }


    //shrink item and put it in xray if it was eaten
    if(mItemIsEaten)
    {
        //auto xray = GetSudoku()->GetXray();
        graphics->Translate(xray->GetX() + mRandomX, xray->GetY() + mRandomY);
        /// graphics->DrawBitmap(mItemBitmap, int(GetX() * 48), int(GetY() + 1) * 48 - digitHeight, digitWidth -1 , digitHeight);
        graphics->DrawBitmap(mItemBitmap, 0, 0, digitWidth * XrayScale, digitHeight * XrayScale);
    }
    else
    {
        if(!GetInitialize())
        {
            if(!mDigit)
            {
                graphics->Translate(GetCol()*(GetSudoku()->GetTileWidth()), (GetRow()+1)*(GetSudoku()->GetTileHeight()) - digitHeight);
                SetLocation(GetCol()*(GetSudoku()->GetTileWidth()),(GetRow()+1)*(GetSudoku()->GetTileHeight()) - digitHeight);
            }
            else
            {
                graphics->Translate(GetX()*(GetSudoku()->GetTileWidth()), (GetY()+1)*(GetSudoku()->GetTileHeight()) - digitHeight);
            }

            Initialize();
        }
        else
        {
            graphics->Translate(GetX(), GetY());
        }

        /// graphics->DrawBitmap(mItemBitmap, int(GetX() * 48), int(GetY() + 1) * 48 - digitHeight, digitWidth -1 , digitHeight);
        graphics->DrawBitmap(mItemBitmap, 0, 0, digitWidth, digitHeight);
    }

    graphics->PopState();



}


