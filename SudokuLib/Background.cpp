/**
 * @file Background.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "Background.h"



Background::Background(Sudoku *sudoku) : Item(sudoku)
{


}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void Background::SetImage(const std::wstring& file)
{
    // This save the image supplied to SetImage to
    // a member variable so we can restore save it to XML
    if(!file.empty() && mBackgroundImageFile.empty())
    {
        mBackgroundImageFile = file;
    }
    mBackgroundImage = std::make_unique<wxImage>(file, wxBITMAP_TYPE_ANY);

    Item::SetImage(file);

}



/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* Background::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"background");
    itemNode->AddAttribute(L"file", mBackgroundImageFile);

    return itemNode;
}


/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void Background::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    SetImage(node->GetAttribute(L"file").ToStdWstring());
}

//void Background::Draw(std::shared_ptr<wxGraphicsContext> graphics)
//{
//    int pixelWidth = 48*mWidth;
//    int pixelHeight = 48*mHeight;
//    if(mBackgroundBitmap.IsNull())
//    {
//        mBackgroundBitmap = graphics->CreateBitmapFromImage(*mBackgroundImage);
//    }
//
//    int width = GetWidth();
//    int height = GetHeight();
//    std::cout<<width<< "  " << height << std::endl;
//    graphics->DrawBitmap(mBackgroundBitmap, int(GetX()*48), int(GetY()+1)*48 - GetHeight(), GetWidth(), GetHeight());
//}

