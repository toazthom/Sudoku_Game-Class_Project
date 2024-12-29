/**
 * @file ItemTest.cpp
 * @author Pavel Shevchenko
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Sudoku.h>

const std::wstring DigitImageName = L"images/1r.png";


/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Sudoku *sudoku) : Item(sudoku) {}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) {}

};

TEST(ItemTest, Construct) {
    Sudoku sudoku;
    ItemMock item(&sudoku);
}

TEST(ItemTest, GettersSetters){
    Sudoku sudoku;
    ItemMock item(&sudoku);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test a second with different values
    item.SetLocation(-72, -107);
    ASSERT_NEAR(-72, item.GetX(), 0.0001);
    ASSERT_NEAR(-107, item.GetY(), 0.0001);

}