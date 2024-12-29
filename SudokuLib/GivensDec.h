/**
 * @file GivensDec.h
 * @author Pavel Shevchenko
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_GIVENSDEC_H
#define PROJECT1_SUDOKULIB_GIVENSDEC_H

#include "Declarations.h"
/**
 * Givens declaration class from base declaration class
 */

class GivensDec : public Declarations
{
private:
    ///value of given digit
    int mValue;

public:

    /**
     * Constructor
     * @param sudoku
     */
    GivensDec(Sudoku *sudoku);

    /**
     * setting digit value
     * @param val
     */
    void SetValue(int val) { mValue = val; }
};

#endif //PROJECT1_SUDOKULIB_GIVENSDEC_H
