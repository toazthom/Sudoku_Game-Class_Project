/**
 * @file Level.cpp
 * @author Pavel Shevchenko
 */

#include "pch.h"
#include "Level.h"
#include "Sudoku.h"
#include "Givens.h"
#include "GivensDec.h"
#include "Digits.h"
#include "DigitsDec.h"
#include "SpartyHead.h"
#include "SpartyHeadDec.h"
#include "Xray.h"
#include "XrayDec.h"
#include "Background.h"
#include "BackgroundDec.h"
#include "Container.h"
#include "ContainerDec.h"
#include <sstream>
using namespace std;


/**
 * Level constructor
 */
Level::Level()
{

}


void Level::Load(const wxString &filename, Sudoku *sudoku)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Sudoku file");
        return;
    }

    int check = 0;

    auto root = xmlDoc.GetRoot();

    auto wid = root->GetAttribute(L"width");
    auto heit = root->GetAttribute(L"height");
    long width, height;
    wid.ToLong(&width);
    heit.ToLong(&height);
    sudoku->SetBounds(width, height);

    wid = root->GetAttribute(L"tilewidth");
    heit = root->GetAttribute(L"tileheight");
    wid.ToLong(&width);
    heit.ToLong(&height);
    sudoku->SetTiles(width, height);

    auto child = root->GetChildren();

    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"declarations")
        {
            DecLoop(child, sudoku);
        }
        else if (name == L"items")
        {
            ItemLoop(child, sudoku);
        }
        else if (name == L"game")
        {
            GameLoop(child, sudoku);
        }
    }
}



void Level::XmlDeclaration(wxXmlNode* node, Sudoku *sudoku)
{
    std::shared_ptr<Declarations> dec;

    auto value = node->GetName();

    if (value == L"given")
    {
        std::shared_ptr<GivensDec> item;
        dec = std::make_shared<GivensDec>(sudoku);

        value = node->GetAttribute(L"id");
        dec->SetId(value.ToStdWstring());

        value = node->GetAttribute(L"width");
        dec->SetWidth(wxAtoi(value));

        value = node->GetAttribute(L"height");
        dec->SetHeight(wxAtoi(value));

        value = node->GetAttribute(L"value");
        dec->SetValue(wxAtoi(value));

        value = node->GetAttribute(L"image");
        dec->SetImage(value.ToStdWstring());

    }
    else if (value == L"digit")
    {
        std::shared_ptr<DigitsDec> item;
        dec = std::make_shared<DigitsDec>(sudoku);

        value = node->GetAttribute(L"id");
        dec->SetId(value.ToStdWstring());

        value = node->GetAttribute(L"width");
        dec->SetWidth(wxAtoi(value));

        value = node->GetAttribute(L"height");
        dec->SetHeight(wxAtoi(value));

        value = node->GetAttribute(L"value");
        dec->SetValue(wxAtoi(value));

        value = node->GetAttribute(L"image");
        dec->SetImage(value.ToStdWstring());
    }
    else if (value == L"sparty")
    {
        std::shared_ptr<DigitsDec> item;
        auto sparty = std::make_shared<SpartyHeadDec>(sudoku);

        value = node->GetAttribute(L"id");
        sparty->SetId(value.ToStdWstring());

        value = node->GetAttribute(L"width");
        sparty->SetWidth(wxAtoi(value));

        value = node->GetAttribute(L"height");
        sparty->SetHeight(wxAtoi(value));

        value = node->GetAttribute(L"image1");
        sparty->SetHeadImage(value.ToStdWstring());

        value = node->GetAttribute(L"target-x");
        sparty->SetTargetX(wxAtoi(value));

        value = node->GetAttribute(L"target-y");
        sparty->SetTargetY(wxAtoi(value));

        value = node->GetAttribute(L"front");
        sparty->SetFront(wxAtoi(value));

        value = node->GetAttribute(L"image2");
        sparty->SetMouthImage(value.ToStdWstring());

        value = node->GetAttribute(L"head-pivot-angle");
        sparty->SetHeadPivot(std::stod(value.ToStdWstring()));

        value = node->GetAttribute(L"head-pivot-x");
        sparty->SetHeadPivotX(wxAtoi(value));

        value = node->GetAttribute(L"head-pivot-y");
        sparty->SetHeadPivotY(wxAtoi(value));

        value = node->GetAttribute(L"mouth-pivot-angle");
        sparty->SetMouthPivot(std::stod(value.ToStdWstring()));

        value = node->GetAttribute(L"mouth-pivot-x");
        sparty->SetMouthPivotX(wxAtoi(value));

        value = node->GetAttribute(L"mouth-pivot-y");
        sparty->SetMouthPivotY(wxAtoi(value));

        //Add the sparty head declaration to its own member variable for extra memeber variables
        mSpartyDeclaration = sparty;
        dec = nullptr;
    }
    else if (value == L"background")
    {

        dec = std::make_shared<BackgroundDec>(sudoku);

        value = node->GetAttribute(L"id");
        dec->SetId(value.ToStdWstring());

        value = node->GetAttribute(L"width");
        dec->SetWidth(wxAtoi(value));

        value = node->GetAttribute(L"height");
        dec->SetHeight(wxAtoi(value));

        value = node->GetAttribute(L"image");
        dec->SetImage(value.ToStdWstring());
    }
    else if (value == L"xray")
    {
        dec = std::make_shared<XrayDec>(sudoku);

        value = node->GetAttribute(L"id");
        dec->SetId(value.ToStdWstring());

        value = node->GetAttribute(L"width");
        dec->SetWidth(wxAtoi(value));

        value = node->GetAttribute(L"height");
        dec->SetHeight(wxAtoi(value));

        value = node->GetAttribute(L"image");
        dec->SetImage(value.ToStdWstring());

        // value = node->GetAttribute(L"capacity");
        // dec->SetCapacity(wxAtoi(value));
    }
    else if (value == "container")
    {
        std::shared_ptr<ContainerDec> item;
        dec = std::make_shared<ContainerDec>(sudoku);

        value = node->GetAttribute(L"id");
        dec->SetId(value.ToStdWstring());

        value = node->GetAttribute(L"width");
        dec->SetWidth(wxAtoi(value));

        value = node->GetAttribute(L"height");
        dec->SetHeight(wxAtoi(value));

        value = node->GetAttribute(L"image");
        dec->SetImage(value.ToStdWstring());

        value = node->GetAttribute(L"front");
        dec->SetFrontImage(value.ToStdWstring());
    }

    if (dec != nullptr)
    {
        Add(dec->GetId(), dec);
    }
}


void Level::XmlItem(wxXmlNode* node, Sudoku *sudoku)
{

    std::shared_ptr<Item> item;


    auto value = node->GetName();

    if (value == L"given")
    {
        item = std::make_shared<Givens>(sudoku);

        value = node->GetAttribute(L"id");
        item->SetId(value.ToStdWstring());

        auto id = item->GetId();
        auto dec = mDeclarations.at(id);

        item->SetValue(dec->GetValue());

        double x, y;
        node->GetAttribute(L"col", L"0").ToDouble(&x);
        item->SetCol(x);

        node->GetAttribute(L"row", L"0").ToDouble(&y);
        item->SetRow(y);

//        item->SetLocation(x*48,y*48);

        item->SetImage(L"images/"+ dec->GetImage());
        item->SetWidth(dec->GetWidth());
        item->SetHeight(dec->GetHeight());
        sudoku->Add(item);
        return;

    }
    else if (value == L"digit")
    {
        item = std::make_shared<Digits>(sudoku);

        value = node->GetAttribute(L"id");
        item->SetId(value.ToStdWstring());

        auto id = item->GetId();
        auto dec = mDeclarations.at(id);

        item->SetValue(dec->GetValue());

        double x, y;
        node->GetAttribute(L"col", L"0").ToDouble(&x);
        item->SetCol(x);

        node->GetAttribute(L"row", L"0").ToDouble(&y);
        item->SetRow(y);
        item->SetLocation(x*48,y*48);


        item->SetImage(L"images/"+ dec->GetImage());
        item->SetWidth(dec->GetWidth());
        item->SetHeight(dec->GetHeight());
        sudoku->Add(item);
        return;

    }
    else if (value == L"background")
    {
        item = std::make_shared<Background>(sudoku);
    }
    else if (value == L"xray")
    {
        auto xrayItem = std::make_shared<Xray>(sudoku);

        mXray = xrayItem;

        item = xrayItem;

    }
    else if (value == L"sparty")
    {
        std::shared_ptr<SpartyHead> spartyItem = std::make_shared<SpartyHead>(sudoku);

        auto thing =  mSpartyDeclaration;

        spartyItem->SetImage(L"images/"+ thing->GetHeadImage());
        spartyItem->SetImage(L"images/"+ thing->GetMouthImage());

        value = node->GetAttribute(L"id");
        spartyItem->SetId(value.ToStdWstring());

        double x, y;
        node->GetAttribute(L"col", L"0").ToDouble(&x);
        spartyItem->SetCol(x);

        node->GetAttribute(L"row", L"0").ToDouble(&y);
        spartyItem->SetRow(y);

        spartyItem->SetLocation(x,y);

        spartyItem->SetWidth(thing->GetWidth());
        spartyItem->SetHeight(thing->GetHeight());

        spartyItem->SetTargetY(thing->GetTargetY());
        spartyItem->SetTargetX(thing->GetTargetX());

        spartyItem->SetMouthPivotX(thing->GetMouthPivotX());
        spartyItem->SetMouthPivotY(thing->GetMouthPivotY());

        spartyItem->SetMouthAngle(thing->GetMouthPivot());

        spartyItem->SetHeadPivotY(thing->GetHeadPivotY());
        spartyItem->SetHeadPivotX(thing->GetHeadPivotX());
        spartyItem->SetHeadPivotAngle(thing->GetHeadPivot());

        sudoku->SetXray(mXray);

        sudoku->Add(spartyItem);
        sudoku->SetSparty(spartyItem);
        return;
    }
    else if (value == L"container")
    {
        item = std::make_shared<Container>(sudoku);

    }


    value = node->GetAttribute(L"id");
    item->SetId(value.ToStdWstring());

    double x, y;
    node->GetAttribute(L"col", L"0").ToDouble(&x);
    item->SetCol(x);

    node->GetAttribute(L"row", L"0").ToDouble(&y);
    item->SetRow(y);

    item->SetLocation(x,y);


    auto id = item->GetId();
    auto dec = mDeclarations.at(id);


    item->SetImage(L"images/"+ dec->GetImage());
    item->SetWidth(dec->GetWidth());
    item->SetHeight(dec->GetHeight());


    if (item != nullptr)
    {
        sudoku->Add(item);
    }
}



void Level::DecLoop(wxXmlNode *node, Sudoku *sudoku)
{
    auto child = node->GetChildren();

    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();

        if((name == L"given") || (name == L"digit") || (name == L"sparty") || (name == "xray")
            || (name == L"background") || (name == L"container"))
        {
            XmlDeclaration(child, sudoku);
        }
    }
}

/**
 * Loop to go through children of item
 */
void Level::ItemLoop(wxXmlNode *node, Sudoku *sudoku)
{
    auto child = node->GetChildren();

    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();

        if((name == L"given") || (name == L"digit") || (name == L"sparty") || (name == "xray")
            || (name == L"background") || (name == L"container"))
        {
            XmlItem(child, sudoku);
        }
    }
}

//void Level::ContainerLoop(wxXmlNode *node, Sudoku *sudoku)
//{
//    auto child = node->GetChildren();
//
//    for( ; child; child=child->GetNext())
//    {
//        auto name = child->GetName();
//
//        if (name == L"digit")
//        {
//            mContainer = true;
//            XmlItem(child, sudoku);
//        }
//    }
//
//}


void Level::GameLoop(wxXmlNode *child, Sudoku *sudoku)
{
    auto column = wxAtoi(child->GetAttribute(L"col"));
    auto row = wxAtoi(child->GetAttribute(L"row"));
    sudoku->SetSolutionColumn(column);
    sudoku->SetSolutionRow(row);

    child = child->GetChildren();
    for ( ; child; child=child->GetNext())
    {
        std::string digit;

        auto string = child->GetContent();

        std::string s( string.begin(), string.end());

        std::stringstream ss(s);
        while (std::getline(ss, digit, ' '))
        {
            sudoku->AddToSolution(stoi(digit));
        }
    }
}

/**
 * Add an item to the sudoku board
 * @param id id corresponding to declaration
 * @param dec New declaration to add
 */
void Level::Add(std::wstring id, std::shared_ptr<Declarations> dec)
{
    mDeclarations[id] = dec;
}

/**
  * Prints levels declarations and count
  */
void Level::PrintDeclarations()
{
    for(const auto & mDeclaration : mDeclarations)
    {
        std::cout << mDeclaration.first << "\n";
    }
}

/**
  * Returns size of mDeclarations
  * @return number of declarations
  */
int Level::DecSize()
{
    return mNumDeclarations;
}