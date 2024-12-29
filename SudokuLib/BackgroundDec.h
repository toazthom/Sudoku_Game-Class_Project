/**
 * @file BackgroundDec.h
 * @author Noor M.
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_BACKGROUNDDEC_H
#define PROJECT1_SUDOKULIB_BACKGROUNDDEC_H

#include "Sudoku.h"
#include "Declarations.h"

/**
 * class for the Background declarations
 */
class BackgroundDec : public Declarations
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
public:
    /**
     * Constructor
     * @param sudoku
     */
    BackgroundDec(Sudoku *sudoku);

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

    /// Assignment operator
    void operator=(const BackgroundDec &) = delete;
};

#endif //PROJECT1_SUDOKULIB_BACKGROUNDDEC_H
