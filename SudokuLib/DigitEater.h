/**
 * @file DigitEater.h
 * @author Thomas Toaz
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_DIGITEATER_H
#define PROJECT1_SUDOKULIB_DIGITEATER_H


#include "ItemVisitor.h"
#include "Item.h"

/**
 * Digit visitor concrete class to collect distance of digit and Sparty
 */
class DigitEater : public ItemVisitor
{
private:
    ///Closets distance to sparty
    double mClosestDistance = 2000;

    ///Pointer to Closets digit within range of sparty
    std::shared_ptr<Item>  mClosestDigit = nullptr;

public:
    /**
     * Returns pointer to closets digit in range of sparty
     * @return closest digit to sparty
     */

    std::shared_ptr<Item>  GetClosestDigit() { return mClosestDigit; }

    void VisitDigit(Digits* ) override;

};
#endif //PROJECT1_SUDOKULIB_DIGITEATER_H
