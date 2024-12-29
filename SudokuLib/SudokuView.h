/**
 * @file SudokuView.h
 * @author Pavel Shevchenko
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_SUDOKUVIEW_H
#define PROJECT1_SUDOKULIB_SUDOKUVIEW_H

#include "Sudoku.h"
#include "Level.h"
#include <vector>

/**
 * View class for our sudoku game
 */
class SudokuView : public wxWindow
{
private:
    /**
     * function to paint
     * @param event
     */
    void OnPaint(wxPaintEvent& event);
    /**
     * on left mouse down function
     */
    void OnLeftDown(wxMouseEvent &event);
    /**
     * On timer event
     * @param event
     */
    void OnTimer(wxTimerEvent& event);
    /**
     * On key down
     * @param event
     */
    void OnKeyDown(wxKeyEvent& event);

    ///Sudoku game object
    Sudoku mSudoku;

    /**
     * level class variable
     */
    Level mLevel;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;



public:
    /**
     * Initialize view
     * @param parent
     */
    void Initialize(wxFrame* parent);

    /**
     * Save file
     */
    void OnFileSaveAs(wxCommandEvent &event);

    /**
     * Load level 1
     */
    void OnLevel1(wxCommandEvent &event);

    /**
     * Load level 2
     */
    void OnLevel2(wxCommandEvent &event);

    /**
     * Load level 3
     */
    void OnLevel3(wxCommandEvent &event);

    /**
     * Solve
     * @param event
     */
    void OnSolve(wxCommandEvent &event);

    /**
     * get os name
     * @return
     */
    std::string getOsName();





};

#endif //PROJECT1_SUDOKULIB_SUDOKUVIEW_H
