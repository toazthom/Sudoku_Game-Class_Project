/**
 * @file ItemVisitor.h
 *
 * @author Thomas Toaz
 *
 * Tile visitor base class.
 */

#ifndef SUDOKU_ITEMVISITOR_H
#define SUDOKU_ITEMVISITOR_H

// Forward references to all tile types
class Digits;
class Container;


/**
 * Tile visitor base class
 */
class ItemVisitor
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}

public:
    virtual ~ItemVisitor() {}

    /**
     * Visit a Digits object
     * @param digit digit we are visiting
     */
    virtual void VisitDigit(Digits* digit) {}

    /**
     * Visit a Container object
     * @param container Containter tile we are visiting
     */
    virtual void VisitContainer(Container* container) {}

};

#endif //SUDOKU_ITEMVISITOR_H