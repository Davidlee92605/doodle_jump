#include "function.h"
#include <string>
#include <iostream>
using namespace std;
class Player {
protected:
    int power;
    string name;

public:
	Player(int basic, string name) {
		this->power = basic;
		this->name = name;
	}

    int get_base_power() const {
    	return power;
    }

    virtual int get_total_power() const = 0;

    string get_name() const {
    	return name;
    }

    virtual ~Player() {}
};

class NTDWarrior: public Player {
private:
	int dad_money;

public:
	NTDWarrior(string name, int basic, int money): Player(basic, name) {
		this->dad_money = money;
	}

	virtual ~NTDWarrior() {}

	virtual int get_total_power() const;
};

class PoorPlayer: public Player {
private:
	int kidney;

public:
	PoorPlayer(string name, int basic, int kidney): Player(basic, name) {
		this->kidney = kidney;
	}

	virtual ~PoorPlayer() {}

	virtual int get_total_power() const;
};

class Game {
protected:
	int difficulty;

public:
	Game(int diff) {
		this->difficulty = diff;
	}

	virtual void play(const Player& p1, const Player& p2) = 0;

	void print_result(int result_code, string winner) {
		if (result_code == 1) cout << winner << " wins!\n";
		else if (result_code == 2) cout << "Draw!\n";
		else if (result_code == 3) cout << "Failed!\n";
		else cout << "[ERROR] Unknown result_code!\n";
	}

	virtual ~Game() {}
};

class FreeGame: public Game {
public:
	FreeGame(int diff): Game(diff) {}
	virtual ~FreeGame() {};

	virtual void play(const Player& p1, const Player& p2);
};

class GTCGame: public Game {
public:
	GTCGame(int diff): Game(diff) {}
	virtual ~GTCGame() {}
	virtual void play(const Player& p1, const Player& p2);
};

int NTDWarrior::get_total_power() const{
    return power + 100 *dad_money;
}
int PoorPlayer::get_total_power() const{
    return power + 100000 * kidney;
}

void FreeGame::play(const Player& p1,const Player& p2){
    int A = p1.get_base_power();
    int B = p2.get_base_power();
    int result = 0;
    string win;
    if ( A < difficulty && B < difficulty)
        result = 3;
    else if (A == B)
        result = 2;
    else {
        result = 1;
        if (A > B)
            win = p1.get_name();
        else
            win = p2.get_name();
        int l = win.length();
        for(int i=0;i<l;i++){
            if(win[i] == '_')
                win[i] = ' ';
        }
    }
    this->print_result(result,win);
}
void GTCGame::play(const Player& p1,const Player& p2){
    int A = p1.get_total_power();
    int B = p2.get_total_power();
    int result = 0;
    string win;
    if( A < difficulty && B < difficulty)
        result = 3;
    else if (A == B)
        result = 2;
    else{
        result = 1;
        if(A > B) win = p1.get_name();
        else win = p2.get_name();
        int l = win.length();
        for(int i=0;i<l;i++){
            if(win[i] == '_')
                win[i] = ' ';
        }
    }
    this->print_result(result,win);
}

int main() {
	int N;
	cin >> N;
	for (int n = 1; n <= N; n++) {
		// Read player info
		string name[2];
		int power[2], extra[2], p_type[2];
		/*
			p_type == 0 -> PoorPlayer
			p_type == 1 -> NTDWarrior
		*/
		for (int i = 0; i < 2; i++)
			cin >> name[i] >> p_type[i] >> power[i] >> extra[i];
		// Create player
		Player *p[2];
		for (int i = 0; i < 2; i++) {
			if (p_type[i] == 0) p[i] = new PoorPlayer(name[i], power[i], extra[i]);
			else p[i] = new NTDWarrior(name[i], power[i], extra[i]);
		}

		// Read game info
		int difficulty, g_type;
		/*
			g_type == 0 -> FreeGame
			g_type == 1 -> GTCGame
		*/
		cin >> difficulty >> g_type;
		// Create game
		Game *game;
		if (g_type == 0) game = new FreeGame(difficulty);
		else game = new GTCGame(difficulty);

		// Play game
		cout << "Game #" << n << ": ";
		game->play(*p[0], *p[1]);

		delete p[0];
		delete p[1];
		delete game;
	}
	return 0;
}
