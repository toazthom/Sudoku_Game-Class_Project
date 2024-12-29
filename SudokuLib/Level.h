/**
 * @file Level.h
 * @author Pavel Shevchenko
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_LEVEL_H
#define PROJECT1_SUDOKULIB_LEVEL_H

#include "Sudoku.h"
#include "DigitsDec.h"
#include "SpartyHeadDec.h"
#include "Xray.h"
#include <map>

/**
 * Class to load in level xml files
 */
class Level
{
private:
    /**
     * Xml declaration item
     * @param node
     * @param sudoku
     */
    void XmlDeclaration(wxXmlNode* node, Sudoku *sudoku);

    /**
     * Xml item creation
     * @param node
     * @param sudoku
     */
    void XmlItem(wxXmlNode* node, Sudoku *sudoku);

//    bool mContainer = false;

    /**
     * loading in correct game from xml
     * @param node
     */
    void XmlGame(wxXmlNode *node);

    /**
     * map for declarations
     */
    std::map<std::wstring, std::shared_ptr<Declarations>> mDeclarations;

    /**
     * number of declarations
     */
    int mNumDeclarations = 0;

    /**
     * Sparty head declaration
     */
    std::shared_ptr<SpartyHeadDec> mSpartyDeclaration;

    /**
     * xray head declaration
     */
    std::shared_ptr<Xray> mXray;



public:
    /**
     * constructor
     */
    Level();

    /**
     * load xml file
     * @param filename
     * @param sudoku
     */
    void Load(const wxString &filename, Sudoku *sudoku);


    void Add(std::wstring, std::shared_ptr<Declarations> dec);

    /**
     * loops through declarations
     * @param node
     * @param sudoku
     */
    void DecLoop(wxXmlNode *node, Sudoku *sudoku);
    /**
     * loop through items
     * @param node
     * @param sudoku
     */
    void ItemLoop(wxXmlNode *node, Sudoku *sudoku);

    /**
     * loop through game solution
     * @param child
     * @param sudoku
     */
    void GameLoop(wxXmlNode *child, Sudoku *sudoku);

//    /**
//     * loop through container items
//     * @param node
//     * @param sudoku
//     */
//    void ContainerLoop(wxXmlNode *node, Sudoku *sudoku);

//    /// Clear level items list
//    void Clear();

    /**
     * print declarations list
     */
    void PrintDeclarations();

    /**
     * get size of declaration list
     * @return
     */
    int DecSize();



};

#endif //PROJECT1_SUDOKULIB_LEVEL_H
