/*
**************************************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
**************************************************************
*  Date of creating this file: 10.12.2018
*  Last changes: 24.12.2018
*  creator: Felix Weichselgartner
*  purpose: learning pathfinding algorithms
**************************************************************
*  This is a pathfinding algorithm 
*  based on the A* (a star) algorithm
**************************************************************
*/

//for debugging with vs_code:
//"program": "${workspaceFolder}/${fileBasenameNoExtension}.exe",  ---for debugging with vscode

//compile command for gcc:
//g++ .\a-star-pathfinding-algorithm.cpp -o .\a-star-pathfinding-algorithm.exe

#include <iostream>
using namespace std;
#include <conio.h>
#include <ctime>
#include <fstream>
#include <windows.h>

#define x 37
#define y 22
const char EMPTY = 176;

int absolute(int retval) {
	if (retval >= 0)
		return retval;
	else return -retval;
}

void delay(int milli_seconds) {
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds)
		;
}

class pathfinding {

    public: class values {
    private:

        // 176 means the square is empty
        // 'S' signals the start point
        // 'E' signals the end point
        // '#' signals a solid wall
        char content;
        
        //G is the movement cost from the start point A to the current square. 
        //So for a square adjacent to the start point A, this would be 1, 
        //but this will increase as we get farther away from the start point.
        int G; 

        //H is the estimated movement cost from the current square to the destination point 
        //(we’ll call this point B for Bone!) This is often called the heuristic 
        //because we don’t really know the cost yet – it’s just an estimate.
        int H; 

        //F = G + H
        //F is the score of the field
        int F;

        //if open == true it has already been considered to walk here
        bool open;

        //no need to consider again
        bool closed;

		//parent field to go back to when path did not work out
        int parentGcost;
        int parent_x;
        int parent_y;
        int parent_count;

        //current run on the loop for calculating 
        bool run;

    public:
        values() {content = EMPTY; G = 0; H = 0; F = 0; open = false; closed = false;}
        void setG(int g) {G = g;}
        void setH(int h) {H = h;}
        void calcF() {F = G + H;}
        void setContent(int c) {content = c;}
        void setOpen(bool b) {open = b;}
        void setClosed(bool b) {closed = b;}
        void setParent(int a, int b) {parent_x = a; parent_y = b;}
        void setParentCount(int a) {parent_count = a;}
        void setRun(int r) { run = r; }
        int getG() {return G;}
        int getH() {return H;}
        int getF() {return F;}
        int getParentG() {return parentGcost;}
        void setParentG(int a) {parentGcost = a;}
        char getContent() {return content;}
        bool getOpen() {return open;}
        bool getClosed() {return closed;}
        int getParentX() {return parent_x;}
        int getParentY() {return parent_y;}
        int getParentCount() {return parent_count;}
        bool getRun() { return run; }
    };

private:
    //the array to look through is an array of the type values
    class values arr[x][y];

    //those are the start coordinates
    int start_x, start_y;
    
    //those are the end coordinates
    int end_x, end_y;

    //this is the current position of the square calculated around
    int current_pos_x, current_pos_y;

    //counts how much runs through the loop were needed
    int count;

public:
	pathfinding() { count = 1; }

    /**
     * @brief  sets the start value for the pathfinding
     * @note   
     * @param  startx: x value of start point
     * @param  starty: y value of start point
     * @retval None
     */
    void setStartValue(int startx, int starty) {
        start_x = current_pos_x = startx; start_y = current_pos_y = starty; 
        arr[start_x][start_y].setParent(startx, starty);
        arr[start_x][start_y].setParentCount(0);
        arr[start_x][start_y].setContent('S'); 
        arr[start_x][start_y].setClosed(true);
    }

    /**
     * @brief  sets the start value for the pathfinding
     * @note   
     * @param  endx: x value of end point
     * @param  endy: y value of end point
     * @retval None
     */
    void setEndValue(int endx, int endy) { end_x = endx; end_y = endy; arr[end_x][end_y].setContent('E'); }
    void setCurrentX(int setx) { current_pos_x = setx; }
    void setCurrentY(int sety) { current_pos_y = sety; }
    void setWall(int setx, int sety) { arr[setx][sety].setContent('#'); arr[setx][sety].setClosed(true); }
    int getCurrentX() { return current_pos_x; }
    int getCurrentY() { return current_pos_y; }
    int getCount() { return count; }

	/**
	 * @brief  calculates the G cost
	 * @note   
	 * @param  newX: x value of the field to calculate g cost for
	 * @param  newY: y value of the field to calculate g cost for
	 * @retval g cost for field
	 */
	int calcG(int xx, int yy) {
        //might be a good idea to refer G cost to parent field
        int xp = xx, yp = yy;
        int amount = 1;
        do {
            xp = arr[xp][yp].getParentX(); //returns bs for 0 4 so next cant work
            yp = arr[xp][yp].getParentY(); //segmentation fault bs 4
            amount++;
        } while(xp != start_x && yp != start_y);
		return amount + 1;
	}

    /**
     * @brief  this function calculates the Manhattan Distance of two points
     * @note   https://en.wikipedia.org/wiki/Taxicab_geometry
     * @param  newX: x value of field to calculate manhattan distance for
     * @param  newY: y value of field to calculate manhattan distance for
     * @retval manhattan distance for field
     */
    int ManhattanDistance(int newX, int newY) {
        int deltaX = absolute(end_x - newX);
        int deltaY = absolute(end_y - newY);
        return deltaX + deltaY;
    }

    /**
     * @brief  calculates the H cost
     * @note   
     * @param  newX: x value of the field to calculate h cost for
     * @param  newY: y value of the field to calculate h cost for
     * @retval h cost for the field
     */
    int calcH(int newX, int newY) {
        return ManhattanDistance(newX, newY);
    }

    /**
     * @brief  give the order to calculate G, H and F
     * @note   F = G + H
     * @param  newX: x value of the field to calculate cost for
     * @param  newY: y value of the field to calculate cost for
     * @retval returns the cost of F
     */
    int calc(int newX, int newY) {
        arr[newX][newY].setG(calcG(newX, newY));
        arr[newX][newY].setH(calcH(newX, newY));
        arr[newX][newY].calcF();
        return arr[newX][newY].getF();
    }

    /**
	 * @brief  adding parent information to a field
	 * @note   
	 * @param  xx: x of current field
	 * @param  yy: y of current field
	 * @param  px: x of parent field
	 * @param  py: y of parent field
	 * @retval None
	 */
	void Parent(int newX, int newY, int px, int py) {
		arr[newX][newY].setParent(px, py); //changed px and xx && py and yy
	}

    /**
     * @brief  checks whether the fields around are possible to move at
     * @note   
     * @param  newX: x value to check if moving there is possible
     * @param  newY: y value to check if moving there is possible
     * @retval 2 = End; 1 = possible; 0 = not possible
     */
    int possible(int xx, int yy, int newX, int newY) {
        if (arr[newX][newY].getClosed() == false && arr[newX][newY].getContent() != '#' && (newX <= x && newX >= 0 && newY <= y && newY >= 0)) { //out of map
            if (arr[newX][newY].getContent() == 'E') {
                Parent(newX, newY, xx, yy);
                return 2;
            }
            arr[newX][newY].setOpen(true);
            Parent(newX, newY, xx, yy);
            return 1;
        } else {
            return 0;
        }
    }

    /**
     * @brief  checks the surrounding fields
     * @note   
     * @param  newX: x value of the field to check
     * @param  newY: y value of the field to check
     * @retval true = end was found; false = end wasn't found
     */
    bool surrounding(int newX, int newY) {
        //variable definitions:
        //bool right left up down -- right if possible, false if not
        //int r l u p -- F cost of the richt left up or down field
        int right = false, left = false, up = false, down = false;
        bool flag = false;
        int vsmall;
        int r = -1, l = -1, u = -1, d = -1;
        int px, py;

        //checking for possible options
        right = possible(newX, newY, newX + 1, newY);
        left = possible(newX, newY, newX - 1, newY);
        up = possible(newX, newY, newX, newY + 1);
        down = possible(newX, newY, newX, newY - 1);

        //calculating the F cost for every possible direction
        if (right) {
            r = calc(newX + 1, newY);
        }
        if (left) {
            l = calc(newX - 1, newY);
        }
        if (up) {
            u = calc(newX, newY + 1);
        }
        if (down) {
            d = calc(newX, newY - 1);
        }

        if (right == 2 || left == 2 || up == 2 || down == 2) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief  searches field with lowest f cost
     * @note   
     * @param  *xx: x value of field with lowest f cost
     * @param  *yy: y value of field with lowest f cost
     * @retval true = end found; false = end not found
     */
    bool lowestFcost() {
        int temp, fcost;
        bool flag = false, retval = false;

        //get lowest f cost value
        for (int i = 0; i < y; i++) {
            for (int k = 0; k < x; k++) {
                if (arr[k][i].getOpen() && arr[k][i].getClosed() == false) {
                    temp = arr[k][i].getF();
                    arr[k][i].setRun(true);
                    if (temp  < fcost) {
                        fcost = temp;
                    }
                }
            }
        }

        //new field are opened with lower f cost than temp
        //does more than one iteration then
        //calculate surrounding of all open fields with lowest f cost
        for (int i = 0; i < y; i++) {
            for (int k = 0; k < x; k++) {
                if (arr[k][i].getOpen() && arr[k][i].getClosed() == false && arr[k][i].getRun()) {
                    arr[k][i].setRun(false);
                    if (arr[k][i].getF() == fcost) {
                        arr[k][i].setClosed(true);
                        retval = surrounding(k, i);
                        if (retval) {
                            return true;
                        }
                    }
                }
            }
        }

        count++;
        
        return false;
    }

    /**
     * @brief  this starts the search loop
     * @note   
     * @retval true = path was found; false = no path was found
     */
    bool find() {
        bool finished = false;

        //surrounding of start position
        if (count == 1) {
            finished = surrounding(start_x, start_y);
            arr[start_x][start_y].setClosed(true);
            print();
            if (finished) {
                return true;
            }
        }

        do {
            //surrounding of open field with lowest f cost
            finished = lowestFcost();

            //optional:
            //just if you want to look what the algorithm is doing
            //system("cls");
            print();
            cout << endl;
            //delay(100);
            //end of optional

        } while (!finished);
        print();
        return true;
    }

    /**
     * @brief  prints the array to the console
     * @note   
     * @retval None
     */
    void print() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);
        for (int i = 0; i < y; i++) {
            for (int k = 0; k < x; k++) {
                if (arr[k][i].getContent() == 'P') {
                    SetConsoleTextAttribute(hConsole, 9);
                    cout << "P";
                    SetConsoleTextAttribute(hConsole, 7);
                } else if (arr[k][i].getContent() == 'S') {
                    SetConsoleTextAttribute(hConsole, 6);
                    cout << "S";
                    SetConsoleTextAttribute(hConsole, 7);
                } else if (arr[k][i].getContent() == 'E') {
                    SetConsoleTextAttribute(hConsole, 6);
                    cout << "E";
                    SetConsoleTextAttribute(hConsole, 7);
                } else if (arr[k][i].getContent() == '#') {
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << "#";
                } else if (arr[k][i].getOpen() && arr[k][i].getClosed() == false) {
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << "O";
                    SetConsoleTextAttribute(hConsole, 7);
                } else if (arr[k][i].getClosed() && arr[k][i].getContent() != '#') {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "C";
                    SetConsoleTextAttribute(hConsole, 7);
                } else if (arr[k][i].getContent() == EMPTY) {
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << arr[k][i].getContent();
                }
            }
            cout << endl;
        }
        SetConsoleTextAttribute(hConsole, 7);
    }

    /**
     * @brief  writes the path to the end in the matrix
     * @note   calles function print to print the array
     * @retval None
     */
    void printPathToEnd() {
        int xp = end_x, yp = end_y;
        int tempx = end_x, tempy = end_y;
        do {
            tempx = arr[xp][yp].getParentX();
            tempy = arr[xp][yp].getParentY();
            xp = tempx; yp = tempy;
            arr[xp][yp].setContent('P');
        } while(xp != start_x && yp != start_y);
        //arr[arr[xp][yp].getParentX()][arr[xp][yp].getParentY()].setContent('P');
		print();
    }

    /**
     * @brief  reads a maze from a text file
     * @note   you might want to change the characters that represent the elements in your maze
     * @retval None
     */
    void readMazeFromFile() {
        fstream file;
        char c;
        int xindex = 0, yindex = 0;

        file.open("asciiMaze.txt", fstream::in);
        while(file.get(c)) {
            if (c == 'S') {
                setStartValue(xindex, yindex);
            } else if (c == 'E') {
                setEndValue(xindex, yindex);
            } else if (c == ' ') {
                arr[xindex][yindex].setContent(EMPTY);
            } else if (c == '+' || c == '-' || c == '|') {
                setWall(xindex, yindex);
            }
            xindex++;
            if (c == '\n') {
                xindex = 0;
                yindex++;
            }
        }

        file.close();
        //print();
        return;
    }
};

int main() {
	time_t start = time(0);
    class pathfinding path;
    path.readMazeFromFile();

    /*
    path.setStartValue(0, 3);
    path.setEndValue(7, 7);
    for (int i = 0; i < 8; i++) {
        path.setWall(i + 1, 4);
    }
    */
   
    if (!path.find()) {
        system("cls");
        cout << "pathfinding was not succesfull!" << endl;
    }
    path.printPathToEnd();
    
    
    //system("cls");
    cout << "pathfinding was succesfull" << endl;
    path.print();
    cout << "The amount of iterations needed: " << path.getCount() << endl;
	cout << "The time needed: " << (double)difftime(time(0), start) << " seconds" << endl;

    //program stays open
    cout << endl << "press any button to close the program" << endl;
    getch();
    return 0;
}