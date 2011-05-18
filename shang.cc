#include <iostream>
#define ROWS 40
#define COLS 20
    
char g_mainSetting[ROWS][COLS+1] = // the row setting so far
    {
        "                   *",
        "                  **",
        "       *     *  *   ",
        "           *   ***  ",
        "*   *          *  * ",
        "           **    * *",
        "  * **  *     *     ",
        "            *****   ",
        "   **    *   * *    ",
        "          * *   *** ",
        " * *   *   *  *     ",
        "      **    * *  *  ",
        "  *  *  *     * *   ",
        "          *  *  ** *",
        " ***   *         *  ",
        " *  * * *   * *     ",
        "   **  * *    * *   ",
        "  *****           * ",
        "  *  *   * **  *    ",
        "    *  *  * * * *   ",
        "         * ***   ** ",
        "     ** *  *   * *  ",
        "        *** * *   * ",
        "  ***   *  *  *     ",
        "       *  ** * *  * ",
        "   ** * * *  * *    ",
        "    *  *  * *** *   ",
        "*****         *    *",
        "   **    * * ***    ",
        "*  * * ***    *     ",
        "         ***  ** * *",
        "     ** *   ** * *  ",
        "***   * *      ***  ",
        "      **   ** *** * ",
        " * * **  *** *      ",
        "* *** ***   **      ",
        "        *** * ** ***",
        " **** **       ***  ",
        "**   *** *   **  ** ",
        "*   * * *****  **  *",
    };
class Game
{
public:
    char rg[ROWS][COLS+1]; // the row setting so far
    int  rowIndexes[20];
    int afAvailableRows[40];
    bool SolveGame(int index);
    bool CheckConstraint(int NextRow);
};
bool Game::SolveGame(int NextRow)
{
   if (NextRow == 20)
    {
      int i;
        std::cout<<"Solved"<<std::endl;
        // solved the game!! Print it out and exit
        for (i=0; i<20; i++)
            std::cout<<g_mainSetting[rowIndexes[i]]<<std::endl;
        std::cout<<"Rows"<<std::endl;
        for(i=0; i<20; i++)
            std::cout<<rowIndexes[i]<<std::endl;
        return true;
    }
    
    // try to locate the first available row
    for (int i = 0; i < 40; i++)
    {
        if(afAvailableRows[i]) 
        {
            Game    newGame(*this);
            newGame.rowIndexes[NextRow] = i;
            newGame.afAvailableRows[i] = false;
            strcpy(newGame.rg[NextRow], g_mainSetting[i]);
            // Do constraint check
            if (!newGame.CheckConstraint(NextRow))
                continue;
            
            // constraint check succeeded
            if( newGame.SolveGame(NextRow + 1))
            {
                return true;
            }
        }
    }
    return false;
}
bool Game::CheckConstraint(int NextRow)
{
    // make sure that there is a viable set of columns from the remaining rows
    // in the main set 
    // sweep across all 20 columns and convert them into rows
    char rowsToCols[20][20];
    int i, j;
    for(i = 0; i< 20; i++)
    {
        for(j =0; j <20; j++)
        {
            rowsToCols[i][j] = rg[j][i];
        }
    }
    int temp_afAvailableRows[40];
    ::memcpy(temp_afAvailableRows, afAvailableRows, sizeof(int) *40);
         
    // go through all rows, and make sure that there is an available row that
    // matches the first NextRow characters
    for(i = 0; i<20; i++)
    {
        for(j = 0; j<40; j++)
        {
            if(!temp_afAvailableRows[j])
                continue;
            if(strncmp(g_mainSetting[j], rowsToCols[i], NextRow + 1) == 0) // match
            {
                temp_afAvailableRows[j] = false;
                break;
            }
        }
        if(j>=40) // weren't able to fulfill constraints
            return false;
    }
    return true;
}
int main()
{
    Game game;
    
    for (int i = 0; i < 40; i++)
    {
        game.afAvailableRows[i] = true;
    }
    int    f = game.SolveGame(0);
    std::cout << "Exit value: " << f << std::endl;
    return f;
}
