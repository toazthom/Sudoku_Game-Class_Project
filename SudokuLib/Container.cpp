/**
 * @file Container.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "Container.h"

using namespace std;


/**
 * Constructor
 * @param sudoku The soduku game this is a member of
*/
Container::Container(Sudoku *sudoku) : Item(sudoku)
{
    /// Get information from declarations
}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void Container::SetImage(const std::wstring& file)
{
    // This save the image supplied to SetImage to
    // a member variable so we can restore save it to XML
    if(!file.empty() && mContainerFile.empty())
    {
        mContainerFile = file;
    }

    Item::SetImage(file);
}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void Container::SetFrontImage(const std::wstring &file)
{
    // This save the image supplied to SetFrontImage to
    // a member variable so we can restore save it to XML
    if(!file.empty() && mFrontFile.empty())
    {
        mFrontFile = file;
    }

    if(!file.empty())
    {
        mFrontImage = std::make_unique<wxImage>(file, wxBITMAP_TYPE_ANY);
    }
    else
    {
        mFrontImage.release();
    }
    mFrontFile = file;
}


/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* Container::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"Container");
    itemNode->AddAttribute(L"file", mContainerFile);
    itemNode->AddAttribute(L"front", mFrontFile);

    return itemNode;
}


/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void Container::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    SetImage(node->GetAttribute(L"file").ToStdWstring());
}

/**
* Distributes
*/