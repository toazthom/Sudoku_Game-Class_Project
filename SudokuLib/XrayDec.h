/**
 * @file XrayDec.h
 * @author Pavel Shevchenko
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_XRAYDEC_H
#define PROJECT1_SUDOKULIB_XRAYDEC_H

#include "Declarations.h"
#include "Sudoku.h"

/**
 * Xray declarations class derived from base declarations class
 */

class XrayDec : public Declarations
{
private:
    /// background Id
    std::wstring mId;
    ///image variable
    std::wstring mImage;
    ///width variable
    int mWidth;
    ///height variable
    int mHeight;
    /// capacity variable
    int mCapacity;

public:
    /**
     * Constructor
     * @param sudoku
     */
    XrayDec(Sudoku *sudoku);
    /**
     * Getter for capacity
     * @param cap
     */
    void SetCapacity(int cap) { mCapacity = cap; }

    /**
     * Getting id member variable
     * @return id
     */
    std::wstring GetId() { return mId; }

    /**
     * setting id member variable
     * @param id
     */
    void SetId(std::wstring id) { mId = id; }

    /**
     * setting width member variable
     * @param width
     */
    void SetWidth(int width) { mWidth = width; }

    /**
     * setting height member variable
     * @param height
     */
    void SetHeight(int height) { mHeight = height; }

    /**
     * setting image member variable
     * @param image
     */
    void SetImage(std::wstring image) { mImage = image; }

    /// Assignment overload
    void operator=(const XrayDec &) = delete;


};

#endif //PROJECT1_SUDOKULIB_XRAYDEC_H
