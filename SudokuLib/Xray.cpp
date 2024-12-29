/**
 * @file Xray.cpp
 * @author Pavel Shevchenko
 */

#include "pch.h"
#include "Xray.h"
#include "SpartyHead.h"

/// Tile number within grid
const int TileNumber = 9;

Xray::Xray(Sudoku *sudoku) : Item(sudoku)
{

}

/**adds an item to the xray item list if capacity is not full
 *
 * @param item the item being eaten by sparty
 * @return boolean of if eating was successfull/not full
 */
bool Xray::EatDigit(std::shared_ptr<Item> item)
{
    int currenctCapacity = mItems.size();
    if(currenctCapacity <= mCapacity)
    {
        item->SetIsEaten(true);
        mItems.push_back(item);
        return true;
    }
    return false;

}

void Xray::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}

/**
 * Move an item from xray items to sudoku items.
 * @param itemFile
 */
void Xray::MoveToSudoku(std::wstring itemFile)
{
    for(auto item : mItems)
    {
        if(item->GetImage() == itemFile)
        {
            auto loc = find(std::begin(mItems), std::end(mItems), item);

            if (loc != std::end(mItems))
            {
                //get sudoku and sparty pointers
                auto tempSudoku = GetSudoku();
                auto tempSparty = tempSudoku->GetSparty();

                //Animate sparty mouth for vomitting
                tempSparty->VomitDigit();
                tempSparty->EatDigit();

                //Get new spat out coordinates for item
                double newX = tempSparty->GetX()+(tempSparty->GetTargetX() - 15);
                double newY = tempSparty->GetY()+2*tempSparty->GetTargetY();

                int tempTileWidth = tempSudoku->GetTileWidth();
                int tempTileHeight = tempSudoku->GetTileHeight();

                //get tile location of those coordinates
                int colX = newX/(tempTileWidth);
                int rowY = (newY/(tempTileHeight)) - 1;

                auto x = tempSudoku->HitTest(colX*tempTileWidth, (rowY+1)*tempTileHeight);

                if(x->GetImage() == L"images/background.png" || x->GetImage() == L"images/sudoku.png"||x->GetImage() == L"images/background3.png")
                {
                    if(colX >= tempSudoku->GetSolutionCol() && colX < tempSudoku->GetSolutionCol() + TileNumber)
                    {
                        if(rowY >= tempSudoku->GetSolutionRow()-1 && rowY < tempSudoku->GetSolutionRow() + TileNumber-1)
                        {
                            newX = colX*tempTileWidth;
                            newY = (rowY+1)*tempTileHeight;
                        }
                    }
                }


                //Set Item location to new position
                item->SetLocation(newX,newY);

                //Move item from xray list to sudoku list
                tempSudoku->Add(item);
                item->SetIsEaten(false);
                mItems.erase(loc);

                //put sparty back in front of items
                tempSudoku->MoveSpartyFront(tempSparty);
                return;
            }
        }
    }

}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
//void Xray::SetImage(const std::wstring& file)
//{
//    // This save the image supplied to SetImage to
//    // a member variable so we can restore save it to XML
//    if(!file.empty() && mDigitImageFile.empty())
//    {
//        mDigitImageFile = file;
//    }
//
//    Item::SetImage(file);
//
//}