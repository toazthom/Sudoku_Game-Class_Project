/**
 * @file SpartyHead.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "SpartyHead.h"
#include "DigitEater.h"

using namespace std;

/// Character speed in pixels per second
const double MaxSpeed = 400.00;

///initial movement initializer amount
const double minMove = -100;

/// The time for an eating cycles in seconds
const double EatingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

/// The time for a headbutt cycle in seconds
const double spartyInitialOffset= 0.6;

/**
 * Constructor
 * @param sudoku The sudoku game this is a member of
*/
SpartyHead::SpartyHead(Sudoku *sudoku) : Item(sudoku)
{

}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void SpartyHead::SetImage(const std::wstring& file)
{
    // This save the image supplied to SetImage to
    // a member variable so we can restore save it to XML

    //fill image files
    if(!file.empty() && mSpartyHeadImageFile.empty())
    {
        mSpartyHeadImageFile = file;
    }
    else if(!file.empty() && mSpartyMouthImageFile.empty())
    {
        mSpartyMouthImageFile = file;
    }

    //fill images
    if (!file.empty() && (mSpartyHeadImage == nullptr))        //head
    {
        mSpartyHeadImage = std::make_unique<wxImage>(file, wxBITMAP_TYPE_ANY);
    }
    else if (!file.empty())  //mouth
    {
        mSpartyMouthImage = std::make_unique<wxImage>(file, wxBITMAP_TYPE_ANY);
    }
//    else
//    {
//        mSpartyMouthImage.release();
//        mSpartyHeadImage.release();
//    }
}

/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* SpartyHead::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"sparty");
    itemNode->AddAttribute(L"file", mSpartyHeadImageFile);
    itemNode->AddAttribute(L"file", mSpartyMouthImageFile);

    return itemNode;
}


/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void SpartyHead::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    SetImage(node->GetAttribute(L"image1").ToStdWstring());
    SetImage(node->GetAttribute(L"image2").ToStdWstring());
}

/**
 * Draw this sparty head
 * @param graphics grpahics context to draw on
 */
void SpartyHead::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    //rotate head for headbutt or mouth for eating before
    double tempHeadAngle = 0;
    double tempMouthAngle = 0;

    if(mHeadButtCurrent<mHeadbuttTime/2)
    {
        tempHeadAngle = (mHeadButtCurrent/(mHeadbuttTime/2)) * mHeadPivotAngle;
        tempMouthAngle = (mHeadButtCurrent/(mHeadbuttTime/2)) * mMouthPivotAngle;
    }
    else
    {
        tempHeadAngle = (mHeadbuttTime - (mHeadButtCurrent))/(mHeadbuttTime/2) * mHeadPivotAngle;
        tempMouthAngle = (mHeadbuttTime - (mHeadButtCurrent))/(mHeadbuttTime/2) * mMouthPivotAngle;
    }

    if(mSpartyHeadBitmap.IsNull())
    {
        mSpartyHeadBitmap = graphics->CreateBitmapFromImage(*mSpartyHeadImage);

    }
    if(mSpartyMouthBitmap.IsNull())
    {
        mSpartyMouthBitmap = graphics->CreateBitmapFromImage(*mSpartyMouthImage);

    }

    int headWidth = mSpartyHeadImage->GetWidth();
    int headHeight = mSpartyHeadImage->GetHeight();

    int mouthWidth = mSpartyMouthImage->GetWidth();
    int mouthHeight = mSpartyMouthImage->GetHeight();

    graphics->PushState();

    if(!GetInitialize())
    {
        graphics->Translate(GetCol()*(GetSudoku()->GetTileWidth()), (GetRow()+1)*(GetSudoku()->GetTileHeight()) -spartyInitialOffset*headHeight);
        SetLocation(GetCol()*(GetSudoku()->GetTileWidth()),(GetRow()+1)*(GetSudoku()->GetTileHeight()) -spartyInitialOffset*headHeight);
        Initialize();
    }
    else
    {
        graphics->Translate(GetX(), GetY());
    }


    //Headbutt functionality
    if(mIsHeadbutting && !mIsEating)
    {
        graphics->Translate(mHeadPivotX, mHeadPivotY);
        graphics->Rotate(tempHeadAngle);
        graphics->Translate(-mHeadPivotX, -mHeadPivotY);

        //draw head
        graphics->DrawBitmap(mSpartyHeadBitmap, 0, 0, headWidth, headHeight);

        //draw mouth
        graphics->DrawBitmap(mSpartyMouthBitmap, 0, 0, mouthWidth, mouthHeight);
    }






    //Mouth Eating functionality
    if(mIsEating && !mIsHeadbutting)
    {
        graphics->Translate(mMouthPivotX, mMouthPivotY);
        graphics->Rotate(tempMouthAngle);
        graphics->Translate(-mMouthPivotX, -mMouthPivotY);

        //draw mouth
        graphics->DrawBitmap(mSpartyMouthBitmap, 0, 0, mouthWidth, mouthHeight);

        graphics->PopState();

        graphics->PushState();
        graphics->Translate(GetX(), GetY());

        //draw head
        graphics->DrawBitmap(mSpartyHeadBitmap, 0, 0, headWidth, headHeight);
    }
    else
    {
        //draw head
        graphics->DrawBitmap(mSpartyHeadBitmap, 0, 0, headWidth, headHeight);

        //draw mouth
        graphics->DrawBitmap(mSpartyMouthBitmap, 0, 0, mouthWidth, mouthHeight);
    }



    graphics->PopState();

}



void SpartyHead::Update(double elapsed)
{
    double distanceX = GetMoveX()-GetX();
    double distanceY = GetMoveY()-GetY();
    double vecMag = sqrt((distanceX * distanceX) + (distanceY * distanceY));
    mPosition = wxRealPoint((distanceX/vecMag)*mMaxSpeed, (distanceY/vecMag)*mMaxSpeed);

    if(vecMag>mMinMagnitude && GetMoveX()>=minMove)
    {
        SetLocation(GetX()+mPosition.x,GetY()+mPosition.y);
    }

    if (mHeadButtCurrent > 0)
    {

        double newtime = mHeadButtCurrent - elapsed;
        if (mHeadButtCurrent >= mHeadbuttTime/2 && newtime < mHeadbuttTime/2)
        {
            //Handle eating functionality with visitor
            if(mIsEating && !mIsVomiting)
            {
                DigitEater visitor;
                GetSudoku()->Accept(&visitor);
                auto DigitForEating = visitor.GetClosestDigit();
                if(DigitForEating != nullptr)
                {
                    GetSudoku()->MoveToXray(DigitForEating);
                }
            }
            else if(mIsHeadbutting)
            {
                // visitor to see if headbutting the container
//            for (auto items : )
            }
        }
        if (newtime < 0)
        {
            mHeadButtCurrent = 0;
            mIsEating = false;
            mIsHeadbutting = false;
            mIsVomiting = false;
        }
        else
        {
            mHeadButtCurrent = newtime;
        }
    }
}

///Handles setting sparty to rotate for headbutt
void SpartyHead::HeadButtMovement()
{
    mHeadButtCurrent = mHeadbuttTime;
    mIsHeadbutting = true;
}



///Handles setting sparty mouth to rotate for eating digits
void SpartyHead::EatDigit()
{
    mHeadButtCurrent = mHeadbuttTime;
    mIsEating = true;
}
