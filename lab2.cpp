// lab2.cpp : Defines the entry point for the console application.
//


//include header
#include "stdafx.h"
#include "lab2.h"
#include "game_header.h"

//include precompiler


using namespace std;
using std::string;


int main(int argc, char * argv[])
{
	if(argc!=input_length){
		usage(argv[program_name_index]);
		return bad_command_line;
	}
	game_piece game;
	cout<<game;
	int result=game.play();
	while(result==carry_on){
		cout<<game;
		result=game.play();
		if(result==quit)
			return result;
		if(result==game_failed)
			return result;
		if(result==game_finish){
			cout<<game;
			return result;
		}
	}
	
	return result;
}

void usage(char * program_name){
	cout<<"How to run this program correctly:"<<endl;
	cout<<"Input: "<<program_name<<endl;
	cout<<"Have fun:)"<<endl;
}

void lower_str(string &str){
	string new_str="";
	for(auto c:str){
		c=tolower(c);
		new_str+=c;
	}
	str=new_str;
}

ostream &operator<< (ostream &o,const game_piece &p){
	o<<"4"<<endl;
	o<<"3"<<"  "<<p.pieces[0][0]<<" "<<p.pieces[0][1]<<" "<<p.pieces[0][2]<<endl;
	o<<"2"<<"  "<<p.pieces[1][0]<<" "<<p.pieces[1][1]<<" "<<p.pieces[1][2]<<endl;
	o<<"1"<<"  "<<p.pieces[2][0]<<" "<<p.pieces[2][1]<<" "<<p.pieces[2][2]<<endl;
	o<<"0"<<endl;
	o<<" "<<"0 "<<"1 "<<"2 "<<"3 "<<"4 "<<endl;
	o<<p.valid_x<<endl;
	o<<p.valid_o<<endl;
	return o;
}

int game_piece::prompt(unsigned int &x,unsigned int &y){
	string line;
	string new_line("");
	bool check(false);

	while(!check){
		cout<<"Input your move by inputing (x,x) or type 'quit' to exit."<<endl;
		cin>>line;
		remove_if(line.begin(),line.end(),isspace);
		if(line=="quit")
			return quit;
		new_line="";
		for(auto c:line){
			if(c==','){
				c=' ';
				check=true;
			}
			new_line+=c;
		}
		if(!check)
			cout<<"Bad input form, please try again."<<endl;
	}

	istringstream iss(new_line);
	iss>>x>>y;
	if(whoseTurn){
		valid_x+=line;
		valid_x+=";";
	}
	else{
		valid_o+=line;
		valid_o+=";";
	}
	return success;
}

int game_piece::turn(){
	string piece;
	bool check(false);

	if(whoseTurn)
		piece="x";
	else
		piece="o";

	while(!check){
		int result=prompt(x_,y_);
		if(result==quit)
			return result;
		x_=3-x_;
		y_=y_-1;
		if((x_>2||x_<0)||(y_>2||y_<0)||(pieces[x_][y_]!=" ")){
			cout<<"The coordinate you input is invalide, please try again."<<endl;
			continue;
		}
		else
			check=true;
	}
	pieces[x_][y_]=piece;
	whoseTurn=!whoseTurn;
	return success;
}

bool game_piece::draw(){
	string temp_pieces[3][3];
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			temp_pieces[i][j]=pieces[i][j];

	for(int i=0;i<3;i++) //testify by filling blanks with 'x'
		for(int j=0;j<3;j++)
			if(pieces[i][j]==" ")
				pieces[i][j]="x";

	if(done()){
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				pieces[i][j]=temp_pieces[i][j];
		return false;
	}

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			pieces[i][j]=temp_pieces[i][j];

	for(int i=0;i<3;i++) //testify by filling blanks with 'o'
		for(int j=0;j<3;j++)
			if(pieces[i][j]==" ")
				pieces[i][j]="o";

	if(done()){
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				pieces[i][j]=temp_pieces[i][j];
		return false;
	}

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			pieces[i][j]=temp_pieces[i][j];

	return true;
}

bool game_piece::done(){
	for(int i=0;i<3;i++)
		if(pieces[i][0]!=" "&&pieces[i][0]==pieces[i][1]&&pieces[i][1]==pieces[i][2])
			return true;
	for(int i=0;i<3;i++)
		if(pieces[0][i]!=" "&&pieces[0][i]==pieces[1][i]&&pieces[1][i]==pieces[2][i])
			return true;
	if(pieces[0][0]!=" "&&pieces[0][0]==pieces[1][1]&&pieces[1][1]==pieces[2][2])
		return true;
	if(pieces[2][0]!=" "&&pieces[2][0]==pieces[1][1]&&pieces[1][1]==pieces[0][2])
		return true;

	return false;
}

int game_piece::play(){
	if(turn()==quit)
		return quit;
	round++;
	string piece;
	if(whoseTurn)
		piece="o";
	else
		piece="x";
	if(done()){
		cout<<"The winner is: "<<piece<<endl;
		return game_finish;
	}
	if(draw()){
		cout<<"Game draw, the total turns is: "<<round<<endl;
		return game_failed;
	}

	return carry_on;
}
