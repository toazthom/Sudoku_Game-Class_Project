/**
 * @file DigitsDec.h
 * @author Pavel Shevchenko
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_DIGITSDEC_H
#define PROJECT1_SUDOKULIB_DIGITSDEC_H

#include "Declarations.h"

/**
 * derived class from declarations for the digits
 */

class DigitsDec : public Declarations
{
private:


public:
    /**
     * Constructor
     * @param sudoku
     */
    DigitsDec(Sudoku *sudoku);



};

#endif //PROJECT1_SUDOKULIB_DIGITSDEC_H
