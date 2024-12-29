/**
 * @file LevelLoadTest.cpp
 * @author Pranav Shukla
 */

using namespace std;

#include <pch.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include "gtest/gtest.h"
#include <wx/filename.h>
#include <Item.h>
#include <Sudoku.h>
#include <Level.h>

class LevelTest : public ::testing::Test {
protected:
    /**
     * Test to ensure a Sudoku .sdku file is empty
     */
//    void TestOutput(Level levelOut, wxString filename)
//    {
//        cout << "Loading from file: " << filename << endl;
//
//        levelOut.PrintDeclarations();
//    }
};

TEST_F(LevelTest, Load) {
    // Create a level
    Level level;
    Level level2;
    Level level3;

    //
    // First test, loading an empty level
    //
    auto file1 = L"../Tests/test.xml";
    level.Load(file1);
    ASSERT_TRUE(0 == level.DecSize());

    //
    // Now populate the sudoku board
    //
    auto file2 = L"../Tests/test2.xml";
    level2.Load(file2);
    ASSERT_TRUE(3 == level2.DecSize());

    //
    // Test all types
    //
    auto file3 = L"../Tests/test3.xml";
    level3.Load(file3);
    ASSERT_TRUE(21 == level3.DecSize());
}