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

#define x 9
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

public:
    pathfinding() {count = 1;}
    void setStartValue(int startx, int starty) {
        start_x = current_pos_x = startx; start_y = current_pos_y = starty; 
        arr[start_x][start_y].setContent('S'); 
        arr[start_x][start_y].setClosed(true);
    }
    void setEndValue(int endx, int endy) {end_x = endx; end_y = endy; arr[end_x][end_y].setContent('E');}
    void setCurrentX(int setx) {current_pos_x = setx;}
    void setCurrentY(int sety) {current_pos_y = sety;}
    void setWall(int setx, int sety) {arr[setx][sety].setContent('#'); arr[setx][sety].setClosed(true);}
    int getCurrentX() {return current_pos_x;}
    int getCurrentY() {return current_pos_y;}
    int getCount() {return count;}

    //calculates the G cost
    int calcG(int newX, int newY) {
		return count;
		//not correct if jumping back to a parent
		//when path was wrong
    }

    //this function calculates the Manhattan Distance of two points
    //https://en.wikipedia.org/wiki/Taxicab_geometry
    int ManhattanDistance(int newX, int newY) {
        int deltaX = absolute(end_x - newX);
        int deltaY = absolute(end_y - newY);
        return deltaX + deltaY;
    }

    //calculates the H cost
    int calcH(int newX, int newY) {
        return ManhattanDistance(newX, newY);
    }

    //give the order to calculate G, H and F
    //F = G + H
    //returns the cost of F
    int calc(int newX, int newY) {
        arr[newX][newY].setG(calcG(newX, newY));
        arr[newX][newY].setH(calcH(newX, newY));
        arr[newX][newY].calcF();
        return arr[newX][newY].getF();
    }

    //checks whether the fields around are possible to move at
    int possible(int newX, int newY) {
        if (arr[newX][newY].getClosed() == false && arr[newX][newY].getContent() != '#' && (newX <= 8 && newX >= 0 && newY <= 8 && newY >= 0)) { //out of map
            if (arr[newX][newY].getContent() == 'E') {
                return 2;
                arr[newX][newY].setClosed(true);
            }
            arr[newX][newY].setOpen(true);
            
            return 1;
        } else {
            return 0;
        }
    }

    //returns the smallest value of the surrounding fields
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

    //checks the surrounding fields
    //return value tells whether the end was found or not
    bool surrounding(int newX, int newY) {
        if (arr[current_pos_x][current_pos_y].getContent() == 'E')
            return true;
        bool right = false, left = false, up = false, down = false;
        bool flag = false;
        int vsmall;
        int r = -1, l = -1, u = -1, d = -1;

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

        if ((r < l || l == false) && (r < u || up == false) && (r < d || d == false) && right) {
            //the field right to the original field has the smallest F value
            current_pos_x++;
            arr[current_pos_x][current_pos_y].setClosed(true);
            flag = true;
        }
        if ((l < r || r == false) && (l < u || u == false) && (l < d || down == false) && left) {
            //the field left to the original field has the smallest F value
            current_pos_x--;
            arr[current_pos_x][current_pos_y].setClosed(true);
            flag = true;
        }
        if ((u < d || down == false) && (u < r || right == false) && (u < l || left == false) && up) {
            //the field over to the original field has the smallest F value
            current_pos_y++;
            arr[current_pos_x][current_pos_y].setClosed(true);
            flag = true;
        }
        if ((d < u || u == false) && (d < r || right == false) && (d < l || left == false) && down) {
            //the field under to the original field has the smallest F value
            current_pos_y--;
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
                arr[current_pos_x][current_pos_y].setClosed(true);
            } else if (l == vsmall && left) {
                current_pos_x--;
                arr[current_pos_x][current_pos_y].setClosed(true);
            } else if (u == vsmall && up) {
                current_pos_y++;
                arr[current_pos_x][current_pos_y].setClosed(true);
            } else if (d == vsmall && down) {
                current_pos_y--;
                arr[current_pos_x][current_pos_y].setClosed(true);
            }
        }

        count++;
		//cout << count << endl;

        if (r == 2 || l == 2 || u == 2 || d == 2) {
            return true;
        } else {
            return false;
        }
    }

    //this starts the search loop
    bool find() {
        bool finished = false;
        do {
            finished = surrounding(current_pos_x, current_pos_y);

            //optional:
            //just if you want to look what the algorithm is doing
            system("cls");
            print();
            delay(500);
            //end of optional

        } while (!finished && count < 10000);
        if (count >= 1000)
            return false;
        return true;
    }

    //prints the array to the console
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
	cout << "The time needed: " << (double)difftime(time(0), start) << " seconds" << endl;

    //program stays open
    cout << endl << "press any button to close the program" << endl;
	getch();
    return 0;
}