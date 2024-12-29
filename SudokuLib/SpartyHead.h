/**
 * @file SpartyHead.h
 * @author Thomas Toaz
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_SPARTYHEAD_H
#define PROJECT1_SUDOKULIB_SPARTYHEAD_H

#include "Item.h"
#include "Xray.h"
#include <string>
#include <memory>
#include <wx/graphics.h>

#include "SpartyHeadDec.h"

/**
 * Class describing the spary head in the sudoku game
 */
class SpartyHead : public Item
{
private:
    ///pointer from declaration of sparty
    std::shared_ptr<SpartyHeadDec> mdec;
    /// The underlying sparty mouth image
    std::unique_ptr<wxImage> mSpartyHeadImage = nullptr;

    /// The bitmap we can display for this sparty mouth
    wxGraphicsBitmap mSpartyHeadBitmap;

    /// sparty head filename
    std::wstring mSpartyHeadImageFile;

    /// The underlying sparty mouth image
    std::unique_ptr<wxImage> mSpartyMouthImage = nullptr;

    /// The bitmap we can display for this sparty mouth
    wxGraphicsBitmap mSpartyMouthBitmap;

    /// facing indicator for sparty head
    int mFront;

    /// sparty mouth filename
    std::wstring mSpartyMouthImageFile;

    /// Head pivot angle
    double mHeadPivotAngle;

    ///boolean to tell if sparty is eating or not
    bool mIsEating = false;

    ///boolean to tell if sparty is headbutting or not
    bool mIsHeadbutting = false;

    ///boolean to tell if sparty is vomiting up digit or not
    bool mIsVomiting = false;

    /// X-direction of head pivot amount
    int mHeadPivotX;

    /// Y-direction of head pivot amount
    int mHeadPivotY;

    /// Headbutting time
    double mHeadButtCurrent;

    /// angle at which sparty mouth pivots
    double mMouthPivotAngle;

    /// x-direction of mouth pivot amount
    int mMouthPivotX;

    /// y-direction of mouth pivot amount
    int mMouthPivotY;

    /// X-offset of location sparty is trying to eat
    int mTargetX;

    /// Y-offset of location sparty is trying to eat
    int mTargetY;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /// Assignment operator
    void operator=(const SpartyHead &) = delete;

    /// Current position of the sparty in motion
    /// as a T value from 0 to 1.
    double mT = 0;

    /// x position of where sparty is moving to
    double mMoveToX = -10000;

    /// y position of where sparty is moving to
    double mMoveToY = 0;

    /// position incrementation vector for sparty motion
    wxRealPoint mPosition = wxRealPoint(0, 0);

    ///boolean to tell when sparty has been initialized
    bool mInitialized = false;

    /// Character speed
    const double mMaxSpeed = 12.0;

    ///Minimum distance to cause sparty to move
    const double mMinMagnitude = 8.00;

    /// The time for an eating cycles in seconds
    const double mEatingTime = 0.5;

    /// The time for a headbutt cycle in seconds
    const double mHeadbuttTime = 0.5;

    ///Pointer to the closest digit if sparty is eating
    std::shared_ptr<Digits> mDigitForEating;


public:
    SpartyHead(Sudoku *sudoku);

    void SetImage(const std::wstring& file) override;

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void XmlLoad(wxXmlNode* node) override;




    /**
     * Getting x offset of moving sparty
     * @return offset x
     */
    double GetTargetX() const {return mTargetX;}

    /**
     * getting y offset of moving sparty
     * @return offset y
     */
    double GetTargetY() const {return mTargetY;}

   /**
    * get x location of where sparty moves
    * @return x location
    */
    double GetMoveX() const {return mMoveToX;}

    /**
     * get y location for where sparty moves
     * @return y location
     */
    double GetMoveY() const {return mMoveToY;}

    /**
     * sets the x-coordinate sparty is moving to
     * @param x x-coordinate of mouse click
     */
    void SetMoveX(double x) {mMoveToX = x;}

    /**
     * sets the y-coordinate sparty is moving to
     * @param y y-coordinate of mouse click
     */
    void SetMoveY(double y) {mMoveToY = y;}

    /**
     * Handle updates for animation
     * @param elapsed time since last update
     */
    void Update(double elapsed) override;

    /**
     * Animate sparty mouth and allow him to eat a digit
     */
    void EatDigit();

    ///Set sparty variable for vomiting to true
    void VomitDigit() {mIsVomiting = true;}

    void HeadButtMovement();

    /**
     * Hit Test overidden
     * @param x
     * @param y
     * @return
     */
    bool HitTest(int x, int y) override {return false;}

    /**
     * Set Y-offset of location sparty is trying to eat
     * @param targetY
     */
    void SetTargetY(int targetY) {mTargetY = targetY;}

    /**
     * Set X-offset of location sparty is trying to eat
     * @param targetX
     */
    void SetTargetX(int targetX) {mTargetX = targetX;}

    /**
     * Set y-direction of mouth pivot amount
     * @param pivotY
     */
    void SetMouthPivotY(int pivotY) {mMouthPivotY = pivotY;}

    /**
     * Set x-direction of mouth pivot amount
     * @param pivotX
     */
    void SetMouthPivotX(int pivotX) {mMouthPivotX = pivotX;}

    /**
     * Set mouth pivot angle for sparty
     * @param mouthAngle
     */
    void SetMouthAngle(double mouthAngle) {mMouthPivotAngle = mouthAngle;}

    /**
     * Set Y-direction of head pivot amount
     * @param pivotY
     */
    void SetHeadPivotY(int pivotY) {mHeadPivotY = pivotY;}

    /**
     * Set X-direction of head pivot amount
     * @param pivotX
     */
    void SetHeadPivotX(int pivotX) {mHeadPivotX = pivotX;}

    /**
     * Set Head pivot angle
     * @param headAngle
     */
    void SetHeadPivotAngle(double headAngle) {mHeadPivotAngle = headAngle;}



};

#endif //PROJECT1_SUDOKULIB_SPARTYHEAD_H
