#pragma once
#ifndef ROBOT_H
#define ROBOT_H
#include <string>
#include <array>

class robot {
//Private Data
private:
	int _robID;
	int _robTeamID;
	int _xAXIS;
	int _yAXIS;
	// 1 is north, 4 is west
	int _direction;
	int _steps;

public: 
	//robot constructor
	robot(int id, int Tid, int dx, int dy) : _robID(id), _robTeamID(Tid), _xAXIS(dx), _yAXIS(dy), _direction(1), _steps(0) {};
	//robot unique id
	int robID() const		{ return _robID; }
	//robot team id
	int robTeamID() const	{ return _robTeamID; }
	
	//x coordinate retrieve/modify
	int xAXIS() const		{ return _xAXIS; }
	int setxAXIS(int a)			{ return _xAXIS = a; }
	
	//y coordinate retrieve/modify
	int yAXIS() const		{ return _yAXIS; }
	int setyAXIS(int b)			{ return _yAXIS = b; }
	
	//direction retrieve/modify
	int direction() const   { return _direction; }
	int setdirection(int ndirection)		{ return _direction = ndirection; }

	//steps retrieve/increase
	int steps()	const		{ return _steps; }
	int setsteps()			{ return _steps++; }

	virtual ~robot() {}
};
//print robots still in system
void printout(const robot& rob);

//sort robots by order of id
bool sortbyID(const robot& x, const robot& y);

//sort robots by order of steps taken/travelled distance
bool sortbyTravel(const robot& x, const robot& y);


#endif
