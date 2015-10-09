#ifndef GAME_HEADER_H
#define GAME_HEADER_H

#include "stdafx.h"

using namespace std;
using std::string;

enum board{width=3,height=3};
enum piece_name{cross,circle};

class game_piece{
	friend ostream &operator<< (ostream &o,const game_piece &p);
	string pieces[3][3];
	bool whoseTurn;
	unsigned int x_,y_;
	int round;
	string valid_x,valid_o;
public:game_piece(){
		for(int i =0;i!=3;++i){
			for(int j=0;j!=3;++j){
				pieces[i][j]=" ";
			}
		}
		whoseTurn=true;
		round=0;
		valid_x="Player X: ";
		valid_o="Player O: ";
	}
	   int prompt(unsigned int &x,unsigned int &y);
	   int turn();
	   bool done();
	   bool draw();
	   int play();
};

//string game_piece::pieces[3][3]={" "};
ostream &operator<< (ostream &o,const game_piece &p);
#endif
