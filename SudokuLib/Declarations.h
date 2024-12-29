/**
 * @file Declarations.h
 * @author Pavel Shevchenko
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATIONS_H
#define PROJECT1_SUDOKULIB_DECLARATIONS_H

#include "Sudoku.h"

/**
 * base class for the declarations
 */

class Declarations
{
private:
    ///id from xml file
    std::wstring mId;

    ///image member variable
    std::wstring mImage;

    ///width member variable
    int mWidth;

    ///height member variable
    int mHeight;

    ///member variable for digit value
    int mValue;

    ///front image for items that have a front image
    std::wstring mFrontImage;

public:
    /**
     * constructor
     */
    Declarations();

    /**
     * getting id member variable
     * @return id
     */
    std::wstring GetId() { return mId; }

    /**
     * getter for image
     * @return image string
     */
    std::wstring GetImage() { return mImage; }

    /**
     * getter for width
     * @return
     */
    int GetWidth() { return mWidth; }

    /**
     * Getter for height
     * @return
     */
    int GetHeight() { return mHeight; }

    /**
     * setting id member variable
     * @param id
     */
    void SetId(std::wstring id) { mId = id; }

    /**
     * seting width member variable
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

    /**
      * setting image member variable
      * @param image
      */
    void SetFrontImage(std::wstring image) { mFrontImage = image; }

    /**
     * setting digit value
     * @param val
     */
    void SetValue(int val) { mValue = val; }

    /**
     * Value getter
     * @return
     */
    int GetValue() { return mValue; }

    /// Assignment operator
    void operator=(const Item &) = delete;



};

#endif //PROJECT1_SUDOKULIB_DECLARATIONS_H
