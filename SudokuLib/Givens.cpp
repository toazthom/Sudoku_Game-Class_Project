/**
 * @file Givens.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "Givens.h"

using namespace std;

/**
 * Constructor
 * @param sudoku The soduku game this is a member of
*/
Givens::Givens(Sudoku *sudoku) : Item(sudoku)
{
    //automatically set as solved so givens do not move on solve
    SetSolved();
}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void Givens::SetImage(const std::wstring& file)
{
    // This save the image supplied to SetImage to
    // a member variable so we can restore save it to XML
    if(!file.empty() && mGivenImageFile.empty())
    {
        mGivenImageFile = file;
    }

    Item::SetImage(file);
}

/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* Givens::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"given");
    itemNode->AddAttribute(L"file", mGivenImageFile);

    return itemNode;
}


/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void Givens::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    SetImage(node->GetAttribute(L"file").ToStdWstring());
}


