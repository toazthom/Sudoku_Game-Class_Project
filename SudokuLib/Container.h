/**
 * @file Container.h
 * @author Thomas Toaz
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_CONTAINER_H
#define PROJECT1_SUDOKULIB_CONTAINER_H

#include "Item.h"
#include <wx/graphics.h>

/**
 * Container class for digits to be stored in
 */
class Container : public Item
{
private:
    /// container filename
    std::wstring mContainerFile;

    /// Front filename
    std::wstring mFrontFile;

    /// Frontal item image
    std::unique_ptr<wxImage> mFrontImage;

    /// Boolean for determining if front file should appear or not
    bool mFrontVisible = true;

    /// All of the items in the container
    std::vector<std::shared_ptr<Item>> mItems;

public:

    Container(Sudoku *sudoku);

    void SetImage(const std::wstring& file) override;

    void SetFrontImage(const std::wstring& file);


    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void XmlLoad(wxXmlNode* node) override;

    void operator=(const Container &) = delete;

    /**
     * Check for headbutting
     */
    void Headbutted();
};

#endif //PROJECT1_SUDOKULIB_CONTAINER_H
