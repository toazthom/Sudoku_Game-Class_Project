/**
 * @file ContainerDec.h
 * @author Pranav Shukla
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_CONTAINERDEC_H
#define PROJECT1_SUDOKULIB_CONTAINERDEC_H

#include "Declarations.h"
#include "Digits.h"
#include "vector"
#include "memory"
#include "utility"

/**
 * Derived class from Declarations for Containers
 */
class ContainerDec : public Declarations
{
private:
    /// container filename
    std::wstring mContainerFile;

    /// container front filename
    std::wstring mFrontFile;

    /// member variable for digits inside container
    std::vector<std::unique_ptr<Digits>> mContainerDigits;
public:
    /**
     * Constructor
     * @param sudoku
     */
    ContainerDec(Sudoku *sudoku);

    /**
     * Add digit to container
     * @param digit
     */
     void AddDigit(std::unique_ptr<Digits> digit) { mContainerDigits.push_back(std::move(digit)); }

     /// Assignment Operator
     void operator=(const ContainerDec &) = delete;
};

#endif //PROJECT1_SUDOKULIB_CONTAINERDEC_H
