/**
 * @file Background.h
 * @author Noor M.
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_BACKGROUND_H
#define PROJECT1_SUDOKULIB_BACKGROUND_H
#include "Item.h"

/**
 * class for the background that derives from item
 */
class Background : public Item
{
private:
    /// Digit filename
    std::wstring mBackgroundImageFile;

    ///Background bitmap
    wxGraphicsBitmap mBackgroundBitmap;

    ///Pointer for the background image
    std::shared_ptr<wxImage> mBackgroundImage;

public:
    /**
     * Constructor
     * @param sudoku
     */
    Background(Sudoku *sudoku);

    void SetImage(const std::wstring& file) override;

    /**
     * Getter for background image file
     * @return background image
     */
    std::wstring GetImageFile() { return mBackgroundImageFile; }


    wxXmlNode* XmlSave(wxXmlNode* node) override;


    void XmlLoad(wxXmlNode* node) override;

    /// Assignment operator
    void operator=(const Background &) = delete;

};

#endif //PROJECT1_SUDOKULIB_BACKGROUND_H
