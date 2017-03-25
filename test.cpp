#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <stdlib.h>

using namespace std;

const int width=15;
const int length=30;

struct Point {
	int x;
	int y;
};

bool reachBorder(int x, int y) {
	if (x == width || y == length) return true;
	return false;
}

bool validInput(char input, string HeadDirection) {
	string headDirectionList_1[] = { "up", "down", "left", "right" };
	string headDirectionList_2[] = { "down", "up", "right", "left" };
	char inputList[]= { 'w', 's', 'a', 'd' };
	for (int i = 0; i <= 3; i++) {
		if (input == inputList[i] && ( HeadDirection == headDirectionList_1[i] || HeadDirection == headDirectionList_2[i] ) ) return false;
	}
	return true;
}
void renderSnake(const vector<vector<bool> > &snake, Point head) { //verified
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			if (i==head.x && j==head.y) cout << "O";
			else if (snake[i][j]) cout << "*";
			else cout << "-";
		}
		cout << endl;
	}
}

void getTailDirection(Point tail, 
					  const vector<vector<bool> > &snake,
					  string &TailDirection,
					  vector<string> &directions) 
{ 
	string TailDirectionList[] = { "up", "down", "left", "right" };
	int surround_x[] = { -1, 1, 0, 0 };
	int surround_y[] = { 0, 0, -1, 1 };
	for (int i = 0; i < 4; i++) {
		if (TailDirectionList[i]==TailDirection) {
			int x=tail.x + surround_x[i];
			int y=tail.y + surround_y[i];
			if (snake[x][y]==false || reachBorder(x,y)) {
				TailDirection = directions[0]; 
				directions.erase(directions.begin());
			}
			else return;
		}
	}
}

void HeadMove(Point &head, string &HeadDirection, vector<vector<bool> > &snake) {
	if (HeadDirection == "up") { head.x -= 1; }
	if (HeadDirection == "down") { head.x += 1; }
	if (HeadDirection == "left") { head.y -= 1; }
	if (HeadDirection == "right") { head.y += 1; }
	snake[head.x][head.y] = true;
}

void TailMove(Point &tail, string &TailDirection, vector<vector<bool> > &snake) {
	snake[tail.x][tail.y] = false;
	if (TailDirection == "up") { tail.x -= 1; }
	if (TailDirection == "down") { tail.x += 1; }
	if (TailDirection == "left") { tail.y -= 1; }
	if (TailDirection == "right") { tail.y += 1; }
}

void GenerateSnake(vector<vector<bool> > &snake, Point &head, Point &tail) {
	for (int i = tail.y; i <= head.y; i++) {
		snake[head.x][i] = true;
	}
}

void SnakeMove(vector<vector<bool> > &snake,
			   vector<string> &directions,
			   Point &head, Point &tail,
			   string &HeadDirection, string &TailDirection)
{
	system("cls");
	HeadMove(head, HeadDirection, snake);
	TailMove(tail, TailDirection, snake);
	getTailDirection(tail, snake, TailDirection, directions);
	renderSnake(snake, head);
	cout << tail.x << " " << tail.y << " ";
	cout << head.x << " " << head.y;
	cout << endl << HeadDirection << " " << TailDirection;
}

int main() {
	vector<vector<bool> > snake(width, vector<bool>(length, false));
	vector<string> directions; 
	Point head, tail;
	string HeadDirection = "right";
	string TailDirection = "right";
	head.x = width / 2; head.y = 6;
	tail.x = width / 2; tail.y = 0;
	GenerateSnake(snake, head, tail);
	renderSnake(snake, head);
	for (;;) {
		SnakeMove(snake, directions, head, tail, HeadDirection, TailDirection);
		for (int i=0; i < directions.size(); i++) {
			cout << directions[i] << " ";
		}
		if (kbhit()) {
			char input=getch();
			if (validInput(input, HeadDirection)) {
				switch(input) {
					case 'w': HeadDirection = "up"; break;
					case 's': HeadDirection = "down"; break;
					case 'a': HeadDirection = "left"; break;
					case 'd': HeadDirection = "right"; break;
					default: break;
				} 
				directions.push_back(HeadDirection);
			}
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	return 0;
}
