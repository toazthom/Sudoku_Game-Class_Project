/**
 * @file DigitsTest.cpp
 * @author Pavel Shevchenko
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <Sudoku.h>
#include <Digits.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

TEST(DigitsTest, Construct) {
    Sudoku sudoku;
    Digits digit(&sudoku);
}
