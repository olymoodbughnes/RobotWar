#include "robot.h"
#include <iostream>
using namespace std;
//print to standard output ID,TeamID,x and y coordinates

void printout(const robot &rob) {

	cout << '\n' << rob.robID() << ' ' << rob.robTeamID() << ' ' << rob.xAXIS() << ' ' << rob.yAXIS()  << ' ' << '\n';

}

//Sort robots by id, in ascending order
bool sortbyID(const robot& x, const robot& y) {

	return x.robID() < y.robID();

}


//Sort robots by steps taken/travelled distance
bool sortbyTravel(const robot& x, const robot& y) {

	return x.steps() < y.steps();

}