/**
 * @file Digits.cpp
 * @author Pavel Shevchenko
 */

#include "pch.h"
#include "Digits.h"

using namespace std;



/**
 * Constructor
 * @param sudoku The sudoku game this is a member of
*/
Digits::Digits(Sudoku *sudoku) : Item(sudoku)
{
    Item::SetDigit();
}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void Digits::SetImage(const std::wstring& file)
{
    // This save the image supplied to SetImage to
    // a member variable so we can restore save it to XML
    if(!file.empty() && mDigitImageFile.empty())
    {
        mDigitImageFile = file;
    }

    Item::SetImage(file);

}



/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* Digits::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"digit");
    itemNode->AddAttribute(L"file", mDigitImageFile);

    return itemNode;
}


/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void Digits::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    SetImage(node->GetAttribute(L"file").ToStdWstring());
}