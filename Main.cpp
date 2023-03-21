#include <iostream>
#include <sstream>
#include <string>
#include "robot.h"
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

void printfile(ostream& out, vector<robot>& vs) {
	//print robots with ranged based loop
	for (const auto& r : vs) 
	{
		printout(r);
	}
}

void del(robot &rob, vector<robot> &vs){
	//iterate through robot locations in vector
	for (int i = 0; i < vs.size(); i++) {
		//store robot to be deleted
		auto& r = vs[i];
		if (r.robID() == rob.robID()) {
			//delete robot from system
			vs.erase(vs.begin() + i);
		}
	}
}

void moverobot(vector<robot>& vs, int id) {
	//identify chosen moving robot through robot ID
	for (auto& r : vs) 
	{
		if (r.robID() == id)
		{//ROBOT DIRECTION CASES
			//CASE ONE(NORTH[^])===============================================================================================================================
			if (r.direction() == 1)
			{//detect robot at end position
				for (auto& er : vs) 
				{//detect if robot is enemy
					if (er.xAXIS() == r.xAXIS() && er.yAXIS() == r.yAXIS() + 1 && er.robTeamID() != r.robTeamID()) 
					{	//delete enemy robot, step forward and update moving robot's step count
						r.setyAXIS(r.yAXIS() + 1);
						r.setsteps();
						del(er, vs);
						return;
					}
					//detect if robot is friendly
					else if (er.xAXIS() == r.xAXIS() && er.yAXIS() == r.yAXIS() + 1 && er.robTeamID() == r.robTeamID()){/*move forward is aborted*/ return;}
				}
				//no robots ahead, move forward
				r.setyAXIS(r.yAXIS() + 1);
				r.setsteps();
			}
			//CASE TWO(EAST[>])===============================================================================================================================
			if (r.direction() == 2)
			{//detect robot at end position
				for (auto& er : vs)
				{//detect if robot is enemy
					if (er.xAXIS() == r.xAXIS() + 1 && er.yAXIS() == r.yAXIS() && er.robTeamID() != r.robTeamID())
					{//delete enemy robot, step forward and update moving robot's step count
						r.setxAXIS(r.xAXIS() + 1);
						r.setsteps();
						del(er, vs);
						return;
					}
					//detect if robot is friendly
					else if (er.xAXIS() == r.xAXIS() + 1 && er.yAXIS() == r.yAXIS() && er.robTeamID() == r.robTeamID()) {/*move forward is aborted*/ return; }
				}
				//no robots ahead, move forward
				r.setxAXIS(r.xAXIS() + 1);
				r.setsteps();
			}
			//CASE THREE(SOUTH[v])===============================================================================================================================
			if (r.direction() == 3)
			{//detect robot at end position
				for (auto& er : vs)
				{//detect if robot is enemy
					if (er.xAXIS() == r.xAXIS() && er.yAXIS() == r.yAXIS() - 1 && er.robTeamID() != r.robTeamID())
					{//delete enemy robot, step forward and update moving robot's step count
						r.setyAXIS(r.yAXIS() - 1);
						r.setsteps();
						del(er, vs);
						return;
					}
					//detect if robot is friendly
					else if (er.xAXIS() == r.xAXIS() && er.yAXIS() == r.yAXIS() - 1 && er.robTeamID() == r.robTeamID()) {/*move forward is aborted*/ return; }
				}
				//no robots ahead, move forward
				r.setyAXIS(r.yAXIS() - 1);
				r.setsteps();
			}
			//CASE FOUR(WEST[<])===============================================================================================================================
			if (r.direction() == 4)
			{//detect robot at end position
				for (auto& er : vs)
				{//detect if robot is enemy
					if (er.xAXIS() == r.xAXIS() - 1 && er.yAXIS() == r.yAXIS() && er.robTeamID() != r.robTeamID())
					{//delete enemy robot, step forward and update moving robot's step count
						r.setxAXIS(r.xAXIS() - 1);
						r.setsteps();
						del(er, vs);
						return;
					}
					//detect if robot is friendly
					else if (er.xAXIS() == r.xAXIS() - 1 && er.yAXIS() == r.yAXIS() && er.robTeamID() == r.robTeamID()) {/*move forward is aborted*/ return; }
				}
				//no robots ahead, move forward
				r.setxAXIS(r.xAXIS() - 1);
				r.setsteps();
			}
		}
		//END OF DIRECTION CASES
	}
}

void turnleft(vector<robot>& vs, int id) {
	//find correct robot through iteration
	for ( auto& r : vs) 
	{
		//identify through robot ID
		if (r.robID() == id) 
		{
			//switch case updates direction
			switch (r.direction())
			{
			case 1: 
				r.setdirection(4);
				break;
			case 2: 
				r.setdirection(1);
				break;
			case 3: 
				r.setdirection(2);
				break;
			case 4: 
				r.setdirection(3);
				break;
			}
		}
	}
}

void turnright(vector<robot>& vs, int id) {
	//find correct robot through iteration
	for ( auto& r : vs) 
	{
		//identify through robot ID
		if (r.robID() == id) 
		{
			//switch case updates direction
			switch (r.direction())
			{
			case 1:
				r.setdirection(2);
				break;
			case 2:
				r.setdirection(3);
				break;
			case 3:
				r.setdirection(4);
				break;
			case 4:
				r.setdirection(1);
				break;
			}
		}
	}
}

void within(ostream &out, vector<robot>& vs, int tocenter) {
	//number of instances
	int count = 0;
	for (auto& r : vs) 
	{
		//calculate distance from origin point
		int distance = abs(r.xAXIS()) + abs(r.yAXIS());
		//identify robots within range
		if (distance <= tocenter) 
		{
			
			++count;
		}
	}
	//output number of instances in new line
	cout << '\n' << count << '\n';
}

void travelled(ostream& out, vector<robot> vs) {
	//sort robots by travelling distance
	sort(vs.begin(), vs.end(), sortbyTravel);
	//context
	cout << "Ordered by distance travelled";
	cout << "\n";
	for (int i = 0 ; i < vs.size(); i++) 
	{
		//robot
		auto &r = vs[i];
		//next robot
		auto& rn = vs[i];
		//check if next robot has same traveling distance
		if (r.steps() == rn.steps())
		{	//check next robot's ID to sort by ID
			if (r.robID() > rn.robID())
			{	//output 'next robot'
				cout << " " << rn.robID() << " " << rn.steps() << '\n';
				//outout current robot
				cout << " " << r.robID() << " " << r.steps() << '\n';
				//check robot after 'next robot'
				i++;
			}
		}
		//output curent robot
		cout << " " << r.robID() << " " << r.steps() << '\n';
	}
}

void readfile(vector<robot> &vs, const string &filename) {
	ifstream in(filename);
	int id;
	int team;
	int xaxis;
	int yaxis;
	//while start.txt input consists of [int, int, int, int]
	while (in >> id >> team >> xaxis >> yaxis)
	{
		//add robot to collection
		vs.push_back(robot(id, team, xaxis, yaxis));
	}
	//sort by ID ascending
	sort(vs.begin(), vs.end(), sortbyID);

}

void readcommands(vector<robot>& vs, const string& filename) {
	fstream comms("commands.txt");
	string line;
	//while there are lines to read
	while (getline(comms, line))
	{
		vector<string> wordset;
		//command as string
		string word;
		//command value
		int am;
		istringstream inpstr(line);

		//detect words witout following integer value
		if (line == "show") { printfile(cout, vs); }

		if (line == "travelled") { travelled(cout, vs); }

		//store each input line as words in a temporary vector
		while (getline(inpstr, word, ' '))
		{
			wordset.push_back(word);
		}
		//detect keyword for each command
		size_t tr = line.find("turnright");
		stringstream(word) >> am;
		if (tr != std::string::npos) { turnright(vs, am); }

		size_t tl = line.find("turnleft");
		stringstream(word) >> am;
		if (tl != std::string::npos) { turnleft(vs, am); }

		size_t mo = line.find("move");
		stringstream(word) >> am;
		if (mo != std::string::npos) { moverobot(vs, am); }

		size_t area = line.find("within");
		stringstream(word) >> am;
		if (area != std::string::npos) { within(cout, vs, am); }
	}
}

int main() {

	vector<robot> start;

	readfile(start, "start.txt");
	
	readcommands(start, "commands.txt");
};