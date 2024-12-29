/**
 * @file Xray.h
 * @author Pavel Shevchenko
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_XRAY_H
#define PROJECT1_SUDOKULIB_XRAY_H


#include "Item.h"

/**
 * Xray item class derived from Item base class
 */

class Xray : public Item
{
private:
    /// Digit filename
    ///std::wstring mDigitImageFile = L"images/xray.png";

    int mCapacity = 8;

    /// All of the items in the xray
    std::vector<std::shared_ptr<Item>> mItems;

public:
    /**
     * Constructor
     * @param sudoku
     */
    Xray(Sudoku *sudoku);

   /// void SetImage(const std::wstring& file) override;

    /// Assignment operator
    void operator=(const Sudoku &) = delete;

    bool EatDigit(std::shared_ptr<Item> item);

    /**
     * Draw this item
     * @param graphics pointer to graphic being drawn
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void MoveToSudoku(std::wstring itemFile);
};

#endif //PROJECT1_SUDOKULIB_XRAY_H
