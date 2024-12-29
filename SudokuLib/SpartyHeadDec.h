/**
 * @file SpartyHeadDec.h
 * @author Thomas Toaz
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_SPARTYHEADDEC_H
#define PROJECT1_SUDOKULIB_SPARTYHEADDEC_H
#include "Declarations.h"

/**
 * derived class from declarations for Sparty
 */

class SpartyHeadDec : public Declarations
{
    private:

        /// sparty head filename
        std::wstring mSpartyHeadImageFile;

        /// facing indicator for sparty head
        int mFront;

        /// sparty mouth filename
        std::wstring mSpartyMouthImageFile;

        /// Head pivot angle
        double mHeadPivotAngle;

        /// X-direction of head pivot amount
        int mHeadPivotX;

        /// Y-direction of head pivot amount
        int mHeadPivotY;

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

    public:
    /**
     * Constructor
     * @param sudoku
     */
        SpartyHeadDec(Sudoku *sudoku);

        /**
         * get spartyhead filename
         * @return image file
         */
        std::wstring GetHeadImage() const {return mSpartyHeadImageFile;}

        /**
         * Get facing indicator for sparty
         * @return return direction
         */
        int GetFront() const {return mFront;}

        /**
         * Get Sparty mouth filename
         * @return
         */
        std::wstring GetMouthImage() const {return mSpartyMouthImageFile;}

        /**
         * Get head pivot angle
         * @return head pivot angle
         */
        double GetHeadPivot() const {return mHeadPivotAngle;}

        /**
         * Get x direction of head pivot
         * @return x direction
         */
        int GetHeadPivotX() const {return mHeadPivotX;}

        /**
         * Get y direction of head pivot
         * @return y direction
         */
        int GetHeadPivotY() const {return mHeadPivotY;}

        /**
         * Get angle that sparty mouth pivots
         * @return mouth pivot angle
         */
        double GetMouthPivot() const {return mMouthPivotAngle;}

        /**
         * Get x direction of mouth pivot
         * @return x direction
         */
        int GetMouthPivotX() const {return mMouthPivotX;}

        /**
         * Get y direction of mouth pivot
         * @return y direction
         */
        int GetMouthPivotY() const {return mMouthPivotY;}

        /**
         * Get x offset for moving sparty
         * @return x offset
         */
        double GetTargetX() const {return mTargetX;}

        /**
         * Get y offset for moving sparty
         * @return y offset
         */
        double GetTargetY() const {return mTargetY;}



        /**
         * set spartyhead filename
         * @param headImage
         */
        void SetHeadImage(std::wstring headImage) {mSpartyHeadImageFile = headImage;}

        /**
         * Set facing indicator for sparty
         * @param front
         */
        void SetFront(int front) {mFront = front;}

        /**
         * Set Sparty mouth filename
         * @param mouthImage
         */
        void SetMouthImage(std::wstring mouthImage) {mSpartyMouthImageFile = mouthImage;}

        /**
         * Set head pivot angle
         * @param headPivotAngle
         */
        void SetHeadPivot(double headPivotAngle) {mHeadPivotAngle = headPivotAngle;}

        /**
         * Set x direction of head pivot
         * @param headPivotX
         */
        void SetHeadPivotX(int headPivotX) {mHeadPivotX = headPivotX;}

        /**
         * Set y direction of head pivot
         * @param headPivotY
         */
        void SetHeadPivotY(int headPivotY) {mHeadPivotY = headPivotY;}

        /**
         * Set angle that sparty mouth pivots
         * @param mouthPivotAngle
         */
        void SetMouthPivot(double mouthPivotAngle) {mMouthPivotAngle = mouthPivotAngle;}

        /**
         * Set x direction of mouth pivot
         * @param mouthPivotX
         */
        void SetMouthPivotX(int mouthPivotX) {mMouthPivotX = mouthPivotX;}

        /**
         * Set y direction of mouth pivot
         * @param mouthPivotY
         */
        void SetMouthPivotY(int mouthPivotY) {mMouthPivotY = mouthPivotY;}

        /**
         * Set x offset for moving sparty
         * @param x
         */
        void SetTargetX(double x){mTargetX = x;}

        /**
         * Set y offset for moving sparty
         * @param y
         */
        void SetTargetY(double y){mTargetY = y;}

};

#endif //PROJECT1_SUDOKULIB_SPARTYHEADDEC_H
