/**
* @file Sudoku.h
* @author Noor M.
*
*
*/


#ifndef PROJECT1_SUDOKULIB_SUDOKU_H
#define PROJECT1_SUDOKULIB_SUDOKU_H


#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <random>
#include <wx/graphics.h>
#include "Item.h"
#include "Container.h"
#include "Xray.h"

class Level;
class SpartyHead;
class Xray;

/**
 * Sudoku game for program
 */
class Sudoku
{
private:
    /**
     * Pointer the sparty head in the sudoku game
     */
    std::shared_ptr<SpartyHead> mSparty;

    /**
     * Pointer to the x-ray item
     */
    std::shared_ptr<Xray> mXray;

    /**
     * graphic bitmap of background
     */
    wxGraphicsBitmap mBackgroundBitmap;

    /**
     * All of the items to populate our sudoku game
     */
    std::vector<std::shared_ptr<Item>> mItems;

    /**
     * pointer to background image
     */
    std::shared_ptr<wxImage> mBackgroundImage;

//    std::shared_ptr<Level> mLevel;
    /**
     * width to change to pixels
     */
    int mWidth = 20;
    /**
     * height to change to pixels
     */
    int mHeight = 15;

    /**
     * width of tiles
     */
    int mTileWidth;

    /**
     * height of tiles
     */
    int mTileHeight;

    /**
     * virtual pixel scale
     */
    double mScale;
    /**
     * virtual pixel width offset
     */
    double mXOffset;
    /**
     * virtual pixel height offset
     */
    double mYOffset;

    /**
     * current time member variable
     */
    double mTimeCurrent;

    /**
     * Game solution
     */
    std::vector<int> mSolution;

    /**
     * solution start column
     */
    int mSolutionCol;

    /**
     * solution start row
     */
    int mSolutionRow;

    /**
     * Level pointer
     */
    std::shared_ptr<Level> mLevel;

    /**
     * boolean to show initial pop up
     */
    bool mCheckDialoguePopUp = true;

    /**
     * checking current level number
     */
    int mCurrentLevel = 1;

    /**
     * popup message time offset
     */
    double mCheckTime = 3.0;
public:
    /**
     * Constructor
     */
    Sudoku();

    /**
     * set level number member variable
     * @param lev
     */
    void SetCurrentLevel(int lev){mCurrentLevel = lev;}


    /**
     * Function to draw sudoku
     * @param graphics
     * @param width
     * @param height
     */
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * add item to sudoku
     * @param item
     */
    void Add(std::shared_ptr<Item> item);

    /**
     * Sudoku load game file
     * @param filename
     */
    void Load(const wxString &filename);

    /**
     * Set image background member variable
     * @param image
     */
    void SetBackgroundImage(std::shared_ptr<wxImage> image) { mBackgroundImage = image; }

    /**
     * Setting boundary
     * @param width
     * @param height
     */
    void SetBounds(int width, int height) { mWidth = width; mHeight = height; }

    /**
     * Set tile widths for virtual pixels
     * @param width
     * @param height
     */
    void SetTiles(int width, int height) { mTileWidth = width; mTileHeight = height; }

    /**
     * Get the tile width of the sudoku game
     * @return
     */
    int GetTileWidth() const {return mTileWidth;}

    /**
     * Get the tile width of the sudoku game
     * @return
     */
    int GetTileHeight() const {return mTileHeight;}


    /**
     * Clear sudoku
     */
    void Clear();

    /**
     * getting Sparty
     * @return sparty
     */
    std::shared_ptr<SpartyHead> GetSparty(){return mSparty;}

    /**
     * Set sparty member variable pointer
     * @param sparty
     */
    void SetSparty(std::shared_ptr<SpartyHead> sparty){mSparty = sparty;}

    /**
     * Set Xray member variable pointer
     * @param xray
     */
    void SetXray(std::shared_ptr<Xray> xray){mXray = xray;}

    /**
     * Get xray pointer
     * @return
     */
    std::shared_ptr<Xray> GetXray(){return mXray;}

    /**
     * update sudoku
     * @param elapsed
     */
    void Update(double elapsed);

    /**
     * move sparty to front of sudoku items
     */
    void MoveSpartyFront(std::shared_ptr<SpartyHead> sparty);

    /**
     * item hit test
     * @param x
     * @param y
     * @return
     */
    std::shared_ptr<Item> HitTest(int x, int y);

    /**
     * saving
     * @param filename
     */
    void Save(const wxString &filename);

    /**
     * virtual pixel scale
     * @return scale
     */
    double GetScale()const {return mScale;}
    /**
     * virtual pixel width offset
     * @return x axis offset
     */
    double GetXOffset() const {return mXOffset;}
    /**
     * virtual pixel height offset
     * @return y axis offset
     */
    double GetYOffset() const {return mYOffset;}

    /**
     * Get solution vector
     * @return
     */
    std::vector<int> GetSolution() { return mSolution; }

    /**
     * Add int to solution vector
     * @param i
     */
    void AddToSolution(int i);

    /**
     * Set solution start column
     * @param col
     */
    void SetSolutionColumn(int col) { mSolutionCol = col; }

    /**
     * Set solution start row
     * @param row
     */
    void SetSolutionRow(int row) { mSolutionRow = row; }

    void SolveBoard();

    /**
     * Sparty headbutt function
     * @param item
     */
    void HeadButt(Item *item);


    /**
     * Dialogue pop-up for level 1
     * @param graphics
     */
    void LevelDialoguePopUp(std::shared_ptr<wxGraphicsContext> graphics, std::wstring message);

    /**
     * Dialogue pop-up check setter
     * @param check
     */
    void SetDialoguePopUp(bool check){mCheckDialoguePopUp = check;}

    /**
     * Dialogue pop-up time setter
     * @param time
     */
    void SetPopUpTime(double time){ mCheckTime = time;}

    /**
     * Visitor accept function
     * @param visitor
     */
    void Accept(ItemVisitor* visitor);

    /**
     * Move item to x-ray
     * @param item
     */
    void MoveToXray(std::shared_ptr<Item> item);

    /**
     * Get poin
     * @param pointer
     * @return
     */
    std::shared_ptr<Item> GetDigitPointer(Digits* pointer);

    /**
     * Get solution start column
     * @return
     */
    int GetSolutionCol() const{return mSolutionCol;}

    /**
     * Get solution start row
     * @return
     */
    int GetSolutionRow() const {return mSolutionRow;}



};



#endif //PROJECT1_SUDOKULIB_SUDOKU_H