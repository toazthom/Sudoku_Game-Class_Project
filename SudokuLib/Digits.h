/**
 * @file Digits.h
 * @author Pavel Shevchenko
 *
 *
 */
 
#ifndef PROJECT1_SUDOKULIB_DIGITS_H
#define PROJECT1_SUDOKULIB_DIGITS_H

#include "Item.h"
#include "ItemVisitor.h"
#include <wx/graphics.h>

/**
 * Class describing our digits
 */
class Digits : public Item
{
private:
    /// Digit filename
    std::wstring mDigitImageFile;

public:
    Digits(Sudoku *sudoku);

    void SetImage(const std::wstring& file) override;

    wxXmlNode* XmlSave(wxXmlNode* node) override;


    void XmlLoad(wxXmlNode* node) override;

    /// Assignment operator
    void operator=(const Digits &) = delete;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitDigit(this); }
};



#endif //PROJECT1_SUDOKULIB_DIGITS_H
