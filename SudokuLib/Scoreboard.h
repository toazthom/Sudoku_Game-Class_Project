/**
 * @file Scoreboard.h
 * @author Pranav Shukla
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_SCOREBOARD_H
#define PROJECT1_SUDOKULIB_SCOREBOARD_H

#include "Item.h"
#include <wx/graphics.h>

/**
  * Class to create scoreboard
  */
class Scoreboard : public Item
{
private:
/// The underlying scoreboard image
    std::unique_ptr<wxImage> mScoreboardImage;

    /// The bitmap we can display for this scoreboard
    wxGraphicsBitmap mBitmap;

    /// Scoreboard filename
    std::wstring mScoreboardImageFile = L"images/1r.png";

public:
    /**
     * Constructor
     * @param scoreboard
     */
    Scoreboard(Scoreboard *scoreboard);

//    /// Draw scoreboard on board
//    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /// Assignment operator
    void operator=(const Scoreboard &) = delete;

};

#endif //PROJECT1_SUDOKULIB_SCOREBOARD_H
