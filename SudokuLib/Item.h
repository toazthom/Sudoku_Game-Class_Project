/**
 * @file Item.h
 * @author Pavel Shevchenko, Pranav Shukla
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_ITEM_H
#define PROJECT1_SUDOKULIB_ITEM_H

#include <wx/xml/xml.h>
#include <wx/graphics.h>
#include <memory>
#include "ItemVisitor.h"
#include <random>
class Sudoku;

/**
 * Class describing items in our sudoku game
 */
class Item
{
private:
    /**
     * Pointer to the Sudoku game the item is in
     */
    Sudoku *mSudoku;

    /**
     * The underlying item image
     */
    std::unique_ptr<wxImage> mItemImage;

    /**
     * The bitmap we can display for this item
     */
    wxGraphicsBitmap mItemBitmap;

    /**
     * member variable for id from xml
     */
    std::wstring mId;

    /**
     * Item filename
     */
    std::wstring mFile;

    /**
     * member variable for digit/given value
     */
    int mValue = -1;

    /**
     * width member variable
     */
    int mWidth;
    /**
     * height member variable
     */
    int mHeight;

    /**
     * item row member variable
     */
    double mRow;

    /**
     * item column member variable
     */
    double mColumn;

    /**
     * Boolean to tell if digit is currently eaten
     */
    bool mItemIsEaten = false;

    /**
     * boolean to tell when item has been initialized
     */
    bool mInitialized = false;

    /**
     * boolean to check if item has been put in solved
     */
    bool mSolved = false;

    /**
     * bool to check digit
     */
    bool mDigit = false;

    /// Item location in the game
    double  mX;     ///< X location for the center of the item
    double  mY;     ///< Y location for the center of the item


    /**
     * Random number generator
     */
    std::mt19937 mRandom;

    /**
     * random location variable x
     */
    double mRandomX;

    /**
     * random location variable y
     */
    double mRandomY;
    /**
     * Boolean to check if item needs to be randomly located in xray
     *
     */
    bool mRandomPositionSet = false;

protected:
    /**
     * constructor
     * @param sudoku
     */
    Item(Sudoku *sudoku);

public:
    /**
     * Default constructor (disabled)
     */
    Item() = delete;

    /**
     * Copy constructor (disabled)
     */
    Item(const Item &) = delete;

    /**
     * Assignment operator
     */
    void operator=(const Item &) = delete;

    /**
     * Destructor
     */
    virtual ~Item();

    /**
     * Get sudoku game item is in
     * @return
     */
    Sudoku *GetSudoku() {return mSudoku;}

    /**
     * Set variable for checking item is solved
     */
    void SetSolved() { mSolved = true; }

    /**
     * Getter for solved check
     * @return
     */
    bool GetSolved() { return mSolved; }

    /**
     * set x location
     * @param x
     */
    void SetX(double x){mX = x;}
    /**
     * set y location
     * @param y
     */
    void SetY(double y){mY = y;}
    /**
     * set digit check
     */
    void SetDigit(){mDigit = true;}
    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Setter for item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * setting digit value
     * @param val
     */
    void SetValue(int val) { mValue = val; }

    /**
     * Get digit value
     * @return
     */
    int GetValue() { return mValue; }

    /**
     * Setter for column member variable
     * @param col
     */
    void SetCol(double col) { mColumn = col; }

    /**
     * Setter for row member variable
     * @param row
     */
    void SetRow(double row) { mRow = row; }

    /**
     * Column member variable getter
     * @return
     */
    int GetCol() { return mColumn; }

    /**
     * Row member variable getter
     * @return
     */
    int GetRow(){ return mRow; }

    /**
     * Image file getter
     * @return
     */
    std::wstring GetImage() { return mFile; }


    /**
     * Set whether item is eaten or is not eaten
     * @param isEaten
     */
    void SetIsEaten(bool isEaten) {mItemIsEaten = isEaten;}

    /**
     * width member variable getter
     * @return
     */
    int GetWidth() { return mWidth; }

    /**
     * height member variable getter
     * @return
     */
    int GetHeight() { return mHeight; }

    /**
     * Draw this item
     * @param graphics pointer to graphic being drawn
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Image setter
     * @param file
     */
    virtual void SetImage(const std::wstring &file);

    /**
     * Width setter
     * @param width
     */
    void SetWidth(int width) { mWidth = width; }

    /**
     * Height setter
     * @param height
     */
    void SetHeight(int height) { mHeight = height; }

    /**
     * setting id from xml file
     * @param id
     */
    void SetId(std::wstring id) { mId = id; }

    /**
     * getting id from xml file
     * @return id for items correct use
     */
    std::wstring GetId() { return mId; }

    virtual wxXmlNode *XmlSave(wxXmlNode *node);
    virtual void XmlLoad(wxXmlNode *node);

    /**
     * Handle updates for animation
     * @param elapsed time since last update
     */
    virtual void Update(double elapsed) {}

    /**  Test this item to see if it has been clicked on
    * @param x X location on the game to test
    * @param y Y location on the game to test
    * @return true if clicked on */
    virtual bool HitTest(int x, int y);

    /**
     * Accept a visitor
      * @param visitor The visitor we accept
      */
    virtual void Accept(ItemVisitor* visitor) {};

    /**
     * check if board is initialized
     */
    void Initialize() {mInitialized = true;}

    /**
     * Get boolean to true to tell when item has been initialized
     * @return
     */
    bool GetInitialize() const {return mInitialized;}

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() {return mRandom;}

};

#endif //PROJECT1_SUDOKULIB_ITEM_H
