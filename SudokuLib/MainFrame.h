/**
 * @file MainFrame.h
 * @author Pavel Shevchenko
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_MAINFRAME_H
#define PROJECT1_SUDOKULIB_MAINFRAME_H

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:

public:
    void Initialize();

    void OnExit(wxCommandEvent& event);
    void ExitMsg(wxCommandEvent& event);


};

#endif //PROJECT1_SUDOKULIB_MAINFRAME_H
