/**
 * @file DigitEater.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "DigitEater.h"
#include "Sudoku.h"
#include "Item.h"
#include "Digits.h"
#include "SpartyHead.h"

/// Minimum distance from sparty for sparty to eat a digit
const double MaxDistance = 80;

/// Minimum distance from sparty for sparty to eat a digit
const double MinDistance = 20;

/**
 * Visit a Digits object
 * @param digit Digit we are visiting
 */
void DigitEater::VisitDigit(Digits*  digit)
{
    auto sparty = digit->GetSudoku()->GetSparty();
    double bottomleftX = sparty->GetX() -  sparty->GetHeight() + sparty->GetWidth();
    double bottomleftY = sparty->GetY() + sparty->GetWidth() - sparty->GetHeight();

    double distance = sqrt(pow(digit->GetX() - bottomleftX,2) + pow(digit->GetY() - bottomleftY, 2));

    // Set a pointer here if in range of sparty and closets distance
    if(distance<mClosestDistance && distance<MaxDistance && distance>MinDistance)
    {
        if((digit->GetX()>sparty->GetX())&&(digit->GetY()>(sparty->GetY()+sparty->GetHeight()/4)))
        {
            mClosestDigit = digit->GetSudoku()->GetDigitPointer(digit);
            mClosestDistance = distance;
        }
    }


    //Variation of closet digit based on hit test

//    auto coorX = sparty->GetX() + sparty->GetTargetX();
//    auto coorY = sparty->GetX() +3*sparty->GetTargetY();
//    auto digitIsHit = digit->HitTest(coorX,coorY);
//    if(digitIsHit )
//    {
//        mClosestDigit = digit->GetSudoku()->GetDigitPointer(digit);
//        mClosestDistance = distance;
//    }


}


