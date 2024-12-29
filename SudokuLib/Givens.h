/**
 * @file Givens.h
 * @author Thomas Toaz
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_GIVENS_H
#define PROJECT1_SUDOKULIB_GIVENS_H

#include "Item.h"
#include <wx/graphics.h>

/**
 * class for given integer values on sudoku levels
 */
class Givens : public Item
{
private:
    /// Given filename
    std::wstring mGivenImageFile = L"images/1b.png";

public:

    Givens(Sudoku *sudoku);


    void SetImage(const std::wstring& file) override;

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void XmlLoad(wxXmlNode* node) override;

    /// Assignment operator
    void operator=(const Givens &) = delete;

//    /**
//     * Accept a visitor
//     * @param visitor The visitor we accept
//     */
//    void Accept(ItemVisitor* visitor) override {}

};

#endif //PROJECT1_SUDOKULIB_GIVENS_H
