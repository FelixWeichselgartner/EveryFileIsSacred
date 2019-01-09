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
//g++ .\a-star-pathfinding-algorithm.cpp .\fweichsel_header\fweichsel.c -o .\a-star-pathfinding-algorithm.exe

#include <iostream>
using namespace std;
#include <conio.h>
#include <ctime>
#include <windows.h>
#include "fweichsel_header/fweichsel.h"

#define x 13
#define y 9
const char EMPTY = 176;

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
    };

private:
    //the array to look through is an array of the type values
    class values arr[x][y];

    //those are the start coordinates
    int start_x, start_y;
    
    //those are the end coordinates
    int end_x, end_y;

    //this is the current position of the square calculated around
    int current_pos_x; int current_pos_y;

    //counts how much runs through the loop were needed
    int count;

	//how much steps to the end
	int steps;

public:
	pathfinding() { count = 1; steps = 1; }

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
    void setEndValue(int endx, int endy) {end_x = endx; end_y = endy; arr[end_x][end_y].setContent('E');}
    void setCurrentX(int setx) {current_pos_x = setx;}
    void setCurrentY(int sety) {current_pos_y = sety;}
    void setWall(int setx, int sety) {arr[setx][sety].setContent('#'); arr[setx][sety].setClosed(true);}
    int getCurrentX() {return current_pos_x;}
    int getCurrentY() {return current_pos_y;}
    int getCount() {return count;}
	int getSteps() { return steps; }

    //
	/**
	 * @brief  calculates the G cost
	 * @note   
	 * @param  newX: x value of the field to calculate g cost for
	 * @param  newY: y value of the field to calculate g cost for
	 * @retval g cost for field
	 */
	int calcG(int newX, int newY) {
        //might be a good idea to refer G cost to parent field
		return steps;
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
     * @brief  checks whether the fields around are possible to move at
     * @note   
     * @param  newX: x value to check if moving there is possible
     * @param  newY: y value to check if moving there is possible
     * @retval 2 = End; 1 = possible; 0 = not possible
     */
    int possible(int newX, int newY) {
        if (arr[newX][newY].getClosed() == false && arr[newX][newY].getContent() != '#' && (newX <= x && newX >= 0 && newY <= y && newY >= 0)) { //out of map
            if (arr[newX][newY].getContent() == 'E') {
                return 2;
                arr[newX][newY].setClosed(true);
            }
            arr[newX][newY].setOpen(true);
            arr[newX][newY].setParent(current_pos_x, current_pos_y);
            arr[newX][newY].setParentCount(steps);
            
            return 1;
        } else {
            return 0;
        }
    }

    /**
     * @brief  returns the smallest value of the surrounding fields
     * @note   
     * @param  n1: f cost of right field
     * @param  n2: f cost of left field
     * @param  n3: f cost of up field
     * @param  n4: f cost of down field
     * @retval the smallest the 4 values
     */
    int smallest_value(int n1, int n2, int n3, int n4) {
		int a[4] = {n1, n2, n3, n4};
		bubblesort_down(a, 4);
		if (a[3] == -1) {
			if (a[2] == -1) {
				if (a[1] == -1) {
					return a[0];
				}
				else {
					return a[1];
				}
			}
			else {
				return a[2];
			}
		}
		else {
			return a[3];
		}
    }

    /**
     * @brief  searches for an open field
     * @note   to add: with the lowest F cost
     * @param  *a: pointer to a value to write x value of open field to
     * @param  *b: pointer to a value to write y value of open field to
     * @retval None
     */
    void searchOpen(int *a, int *b) {
        for (int i = 0; i < x; i++) {
            for (int k = 0; k < y; k++) {
                if (arr[i][k].getOpen() && arr[i][k].getClosed() == false) {
                    *a = i;
                    *b = k;
                }
            }
        }
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
	void Parent(int xx, int yy, int px, int py) {
		arr[xx][yy].setParent(px, py);
		arr[xx][yy].setParentCount(steps);
	}

    /**
     * @brief  checks the surrounding fields
     * @note   
     * @param  newX: x value of the field to check
     * @param  newY: y value of the field to check
     * @retval true = end was found; false = end wasn't found
     */
    bool surrounding(int newX, int newY) {
        if (arr[current_pos_x][current_pos_y].getContent() == 'E')
            return true;
        bool right = false, left = false, up = false, down = false;
        bool flag = false;
        int vsmall;
        int r = -1, l = -1, u = -1, d = -1;
        int px, py;

        right = possible(newX + 1, newY);
        left = possible(newX - 1, newY);
        up = possible(newX, newY + 1);
        down = possible(newX, newY - 1);

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
        if (right == false && left == false && up == false && down == false) {
            searchOpen(&px, &py);
            current_pos_x = arr[px][py].getParentX();
            current_pos_y = arr[px][py].getParentY();
            steps = arr[px][py].getParentCount();
        }

        if ((r < l || left == false) && (r < u || up == false) && (r < d || down == false) && right) {
            //the field right to the original field has the smallest F value
            current_pos_x++;
            Parent(current_pos_x - 1, current_pos_y, current_pos_x, current_pos_y);
            arr[current_pos_x][current_pos_y].setClosed(true);
            flag = true;
        }
        if ((l < r || right == false) && (l < u || up == false) && (l < d || down == false) && left) {
            //the field left to the original field has the smallest F value
            current_pos_x--;
            Parent(current_pos_x + 1, current_pos_y, current_pos_x, current_pos_y);
            arr[current_pos_x][current_pos_y].setClosed(true);
            flag = true;
        }
        if ((u < d || down == false) && (u < r || right == false) && (u < l || left == false) && up) {
            //the field over to the original field has the smallest F value
            current_pos_y++;
            Parent(current_pos_x, current_pos_y - 1, current_pos_x, current_pos_y);
            arr[current_pos_x][current_pos_y].setClosed(true);
            flag = true;
        }
        if ((d < u || up == false) && (d < r || right == false) && (d < l || left == false) && down) {
            //the field under to the original field has the smallest F value
            current_pos_y--;
            Parent(current_pos_x, current_pos_y + 1, current_pos_x, current_pos_y);
            arr[current_pos_x][current_pos_y].setClosed(true);
            flag = true;
        }

        //if the values of two fields are equal
        if (flag == false) {
            vsmall = smallest_value(r, l, u, d);
			if (vsmall == -1) {
				//cout << "error";
				return false;
			}
            if (r == vsmall && right) {
                current_pos_x++;
                Parent(current_pos_x - 1, current_pos_y, current_pos_x, current_pos_y);
                arr[current_pos_x][current_pos_y].setClosed(true);
            } else if (l == vsmall && left) {
                current_pos_x--;
                Parent(current_pos_x + 1, current_pos_y, current_pos_x, current_pos_y);
                arr[current_pos_x][current_pos_y].setClosed(true);
            } else if (u == vsmall && up) {
                current_pos_y++;
                Parent(current_pos_x, current_pos_y - 1, current_pos_x, current_pos_y);
                arr[current_pos_x][current_pos_y].setClosed(true);
            } else if (d == vsmall && down) {
                current_pos_y--;
                Parent(current_pos_x, current_pos_y + 1, current_pos_x, current_pos_y);
                arr[current_pos_x][current_pos_y].setClosed(true);
            }
        }

        if (count == 8) {
            cout << "wow awesome" << endl;
        }

		steps++;
        count++;
		//cout << count << endl;

        if (r == 2 || l == 2 || u == 2 || d == 2) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief  this starts the search loop
     * @note   
     * @retval true = path was found; false = no path was found
     */
    bool find() {
        bool finished = false;
        do {
            finished = surrounding(current_pos_x, current_pos_y);

            //optional:
            //just if you want to look what the algorithm is doing
            //system("cls");
            print();
            delay(100);
            //end of optional

        } while (!finished && count < 10000);
        if (count >= 1000)
            return false;
        return true;
    }

    /**
     * @brief  prints the array to the console
     * @note   
     * @retval None
     */
    void print() {
        for (int i = 0; i < y; i++) {
            for (int k = 0; k < x; k++) {
                if (arr[k][i].getClosed() == true && arr[k][i].getContent() != '#') {
                    cout << "P";
                } else {
                    cout << arr[k][i].getContent();
                    //cout << arr[k][i].getContent() << "." << arr[k][i].getG() << "." << arr[k][i].getH() << "." << arr[k][i].getF() << "." << arr[k][i].getOpen() << "." << arr[k][i].getClosed() << " ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
	time_t start = time(0);
    class pathfinding path;
    path.setStartValue(0, 3);
    path.setEndValue(7, 7);
    for (int i = 0; i < 8; i++) {
        path.setWall(i + 1, 4);
    }
    path.print();
    if (!path.find()) {
        system("cls");
        cout << "pathfinding was not succesfull!" << endl;
    }
    system("cls");
    cout << "pathfinding was succesfull" << endl;
    path.print();
    cout << "The amount of iterations needed: " << path.getCount() << endl;
	cout << "The amount of steps needed: " << path.getSteps() << endl;
	cout << "The time needed: " << (double)difftime(time(0), start) << " seconds" << endl;

    //program stays open
    cout << endl << "press any button to close the program" << endl;
    getch();
    return 0;
}