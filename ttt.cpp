#include <iostream>
#include <fstream>
#include <bitset>
#include <chrono>
#include <thread>
#include <string>

using namespace std;
using namespace chrono;

int8_t posopti[19561][11], winarr[19561] = {0};
short pr[18913], power3[9] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561}, power3double[9] = {2, 6, 18, 54, 162, 486, 1458, 4374, 13122};

bool EXTRACOCKY = 1;

int8_t consel(short num, int dig){
	for (short i = 8;; i--)
		if (num >= power3double[i]){
			if(i == dig)
				return 2;
            num -= power3double[i];
		}	
		else if (num >= power3[i]){
			if(i == dig)
				return 1;
            num -= power3[i];
		}else
			if(i == dig)
				return 0;
}

void display(short compcurpos)
{
	const int8_t gr[9] = {1, 2, 1, 2, 1, 2, 1, 2, 1};
	for (int j = 9; j > 0; j--){
		if (j % 3 == 0 && j != 9)
			cout << "---+---+---" << endl;
		for (int u = 0; u < 9; ++u){
			if (consel(compcurpos,(((j + 2) / 3) * 3 - u / 3) - 1) == gr[8 - u % 3 - (9 - j) % 3])
				if (consel(compcurpos,(((j + 2) / 3) * 3 - u / 3) - 1) == 1)
					cout << "\033[1;31m#\033[0m";
				else
					cout << "\033[1;33m#\033[0m";
			else if (j % 3 == 2 && u % 3 == 1 && consel(compcurpos,(((j + 2) / 3) * 3 - u / 3) - 1) == 0)
				cout << ((j + 2) / 3) * 3 - u / 3;
			else
				cout << " ";
			if (u % 3 == 2 && u < 8)
				cout << "|";
		}
		cout << endl;
	}
}

void input(short *compcurpos, int8_t mul)
{
	short p;
	cout << "enter your legit move: ";
	cin >> p;
	if (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        input(compcurpos, mul);
    }else
		if (consel(*compcurpos, p - 1) == 0 && p > 0 && p < 10){
			if(mul == 1)
				*compcurpos += power3[p - 1];
			else
				*compcurpos += power3double[p - 1];
		}
		else
			input(compcurpos, mul);
}

short turn(short num, short *compcurpos, int8_t mul)
{
	int8_t sw = posopti[num][9];
	if(sw == 1)
		sw = posopti[num][0];
	else
		sw = posopti[num][rand() % sw];
	if(mul == 1)
		*compcurpos += power3[sw];
	else
		*compcurpos += power3double[sw];
	return sw;
}

void draw(int8_t sw)
{
	cout << endl << "\033[1;32m##  ###  #  # # #\033[0m" << endl << "\033[1;32m# # # # # # # # #\033[0m" << endl << "\033[1;32m# # ##  ### # # #\033[0m" << endl << "\033[1;32m# # # # # # # # #\033[0m" << endl << "\033[1;32m##  # # # #  # #\033[0m" << endl << endl;
	const char* dc[] = {"Impressive, you've achieved the impossible: a draw. I almost broke a sweat.", "A tie? Well, I suppose even a broken clock is right twice a day.", "You've found the perfect recipe for mediocrity - a draw with me!", "A draw? That's almost as rare as me making a mistake.", "I must admit, you've got some skills to pull off a draw against me.", "You've reached the pinnacle of Tic-Tac-Toe - a stalemate with the unbeatable!", "A tie game? You're like a worthy adversary... almost.", "A draw? It's almost like you're pretending to be a challenge.", "Congratulations, you've earned the title of 'Almost a Winner' in this game.", "A tie? You must be a true master of drawing games. Bravo."};
	if(EXTRACOCKY == 1)
		if(sw == 1)
			cout << "\033[35mBot: \033[31m" << dc[rand () % 10] << "\033[0m" << endl << endl;
		else
			cout << "\033[35mBot: \033[33m" << dc[rand () % 10] << "\033[0m" << endl << endl;
}

void lose(short compcurpos, int8_t sw)
{
	const char* wcf[] = {"Your move. Oh wait, it doesn't matter. I've already secured victory with: ", "You thought you had a shot? Adorable. The game was over when I placed: ", "You're ten moves behind, and I've just sealed the deal with: ", "You're trying so hard, but I've already won with: ", "It's almost cute how you keep playing, even though I've dominated with: ", "You see, the moment I moved, it was all over. You just didn't realize it yet.", "You're like a mariner lost at sea, and I'm the lighthouse guiding you to your inevitable loss with: ", "They say practice makes perfect, but it seems like you've got a long way to go. My move sealed the deal: ", "You're playing Tic-Tac-Toe, and I'm playing 4D chess. My winning move was: ", "You can keep trying, but the outcome is crystal clear with: "};
	cout << endl << "\033[1;32m# #  #  # #  #    #  ### ###\033[0m" << endl << "\033[1;32m# # # # # #  #   # # #   #\033[0m" << endl << "\033[1;32m# # # # # #  #   # # ### ###\033[0m" << endl << "\033[1;32m #  # # # #  #   # #   # #\033[0m" << endl << "\033[1;32m #   #   #   ###  #  ### ###\033[0m" << endl << endl;
	if(EXTRACOCKY == 1){
		if(sw == 1)
			cout << "\033[35mBot: \033[31m" << wcf[rand () % 10] << "\033[0m" << endl << endl;
		else
			cout << "\033[35mBot: \033[33m" << wcf[rand () % 10] << "\033[0m" << endl << endl;
	}
	else
		cout << "the losing position is: " << endl;
	display(compcurpos);
	const char* wcf1[] = {"Well, that was cute. Almost like a real challenge!","You're playing Tic-Tac-Toe, right? I thought it was supposed to be a game, not a cakewalk.","It's like watching a master at work, and by master, I mean me.","Do you even know the rules? I mean, you're trying so hard.","You're making this game feel like a warm-up for me. Keep trying!","I hate to break it to you, but you might want to find a new hobby.","Close, but not quite. Maybe one day you'll get the hang of it.","It's almost admirable how consistently you lose.","I heard you're a Tic-Tac-Toe legend... in a parallel universe.","You're the best at losing I've ever seen. Keep up the good work!"};
	if(sw == 1)
		cout << "\033[35mBot: \033[31m" << wcf1[rand () % 10] << "\033[0m" << endl << endl;
	else
		cout << "\033[35mBot: \033[33m" << wcf1[rand () % 10] << "\033[0m" << endl << endl;
}

bool checkWin(int8_t board[9], char sw) {
    bitset<9> pl;
    for (short i = 0; i < 9; ++i)
        if(board[i] == sw)
            pl.set(i);
    bitset<9> win[] = {0b111000000,0b000111000,0b000000111,0b100100100,0b010010010,0b001001001,0b100010001,0b001010100};
    for (const auto& combination : win)
        if((pl & combination) == combination)
            return true;
    return false;
}

void calcfir(int8_t *addtwo, short *optirand){
	for (int i = 0; i < 200000; ++i)
	{
		short prev, last, compcurpos = 0, prevprev, lastlast;
		for (short it = 0;; ++it)
		{
			if (pr[compcurpos] == 0){
				pr[prev] -= power3[last];
				break;
			}
			prevprev = prev;
			prev = compcurpos;
			last = turn(pr[compcurpos], &compcurpos, 1);
			if (winarr[compcurpos] == 1){
				if (posopti[pr[prev]][10] == 1)
					pr[prev] += power3[last];
				if (posopti[pr[prevprev]][10] == 1)
					addtwo[prevprev] = lastlast;
				break;
			}
			if (it == 4)
				break;
			turn(optirand[compcurpos], &compcurpos, 2);
			if (winarr[compcurpos] == 2){
				pr[prev] -= power3[last];
				break;
			}
			lastlast = last;
		}
	}
}

void calcsec(int8_t *addtwo, short *optirand){
	for (int i = 0; i < 200000; ++i)
	{
		short prev, last, compcurpos = 0, prevprev, lastlast;
		for (short it = 0;; ++it)
		{
			turn(optirand[compcurpos], &compcurpos, 1);
			if (winarr[compcurpos] == 1){
				pr[prev] -= power3[last];
				break;
			}
			lastlast = last;
			if (it == 4)
				break;
			if (pr[compcurpos] == 0){
				pr[prev] -= power3[last];
				break;
			}
			prevprev = prev;
			prev = compcurpos;
			last = turn(pr[compcurpos], &compcurpos, 2);
			if (winarr[compcurpos] == 2){
				if (posopti[pr[prev]][10] == 1)
					pr[prev] += power3[last];
				if (posopti[pr[prevprev]][10] == 1)
					addtwo[prevprev] = lastlast;
				break;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	auto start = high_resolution_clock::now();
	string operation;
	if(argc > 1)
		operation = argv[1];
	srand(time(NULL));
    int8_t optipos[9] = {0};
	int checksum = 0, temp;
	for (short h = 0; h < 19561; ++h, ++optipos[0])
	{	
		for (short i = 0; i < 8; ++i)
			if (optipos[i] == 3)
			{
				++optipos[i + 1];
				optipos[i] = 0;
			}
		posopti[h][9] = 0;
		posopti[h][10] = 1;
		for(short i = 0; i < 9; ++i)
			if(optipos[i] == 2)
			{
				posopti[h][0] = i;
				++posopti[h][10];
				++posopti[h][9];
				break;
			}
		if(posopti[h][10] == 1)
			for(short i = 0; i < 9; ++i)
				if(optipos[i] == 1)
				{
					posopti[h][posopti[h][9]] = i;
					++posopti[h][9];
				}
		if(checkWin(optipos, 1) == 1)
			winarr[h] = 1;
		else if(checkWin(optipos, 2) == 1)
			winarr[h] = 2;
	}
	bool fail = 0, deb = 0;
	if(operation == "rebuild" and argc > 1)
		fail = 1;
	else if(operation == "check" and argc > 1)
		deb = 1;
	else if(operation == "both" and argc > 1){
		deb = 1;
		fail = 1;
	}
	fstream load;
	load.open("memory.glx", ios::in);
	load >> std::hex >> temp;
	if(!load or temp != 16)
		fail = 1;
	else{
		for(short i = 0; i < 18913; ++i){
			load >> pr[i];
			checksum += pr[i];
		}
		load >> temp;
		load.close();
		if(temp != checksum)
			fail = 1;
	}
	if(fail == 1){
		load.close();
		remove("memory.glx"); 
		load.open("memory.glx", ios::out);
		load << std::hex << 16 << " ";
		int8_t addtwo[18913];
		for(int i = 0; i < 18913; i++)
			addtwo[i] = -1;
		fill_n(pr, 18913, 0);
		int8_t optiarr[9] = {0};
		for(int h = 0; h < 18913; h++, ++optiarr[0]){
			for (short i = 0; i < 8; ++i)
				if (optiarr[i] == 3)
				{
					++optiarr[i + 1];
					optiarr[i] = 0;
				}
			for (short i = 0; i < 9; ++i)
				if (optiarr[i] == 0)
					pr[h] += power3[i];
		}
		short optirand[18913];
		for(int i = 0; i < 18913; i++)
			optirand[i] = pr[i]; 
		thread th1(calcfir, addtwo, optirand);
		thread th2(calcsec, addtwo, optirand);
		th1.join();
		th2.join();
		for(short i = 0; i < 18913; ++i)
			if(addtwo[i] > -1 and consel(pr[i], addtwo[i]) == 1 and posopti[pr[i]][10] == 1)
				pr[i] += power3[addtwo[i]];
		int gen = 0;
		for(short i = 0; i < 18913; ++i){
			load << pr[i] << " ";
			gen += pr[i];
		}
		load << gen;
		load.close();
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "Duration in microseconds: " << duration.count() << endl;
		if(deb){ //DEBUG
			int winrate = 0, winrate1 = 0;
			for (int n = 0; n < 1000000; ++n)
			{
				short compcurpos = 0;
				for (short it = 0;; ++it){
					turn(pr[compcurpos], &compcurpos, 1);
					if (winarr[compcurpos] == 1){
						++winrate;
						break;
					}
					if (it == 4)
						break;
					turn(optirand[compcurpos], &compcurpos, 2);
					if (winarr[compcurpos] == 2){
						cout << "cache is broken..." << endl;
						break;
					}
				}
			}
			for (int n = 0; n < 1000000; ++n)
			{
				short compcurpos = 0;
				for (short it = 0;; ++it){
					turn(optirand[compcurpos], &compcurpos, 1);
					if (winarr[compcurpos] == 1){
						cout << "cache is broken..." << endl;
						break;
					}
					if (it == 4)
						break;
					turn(pr[compcurpos], &compcurpos, 2);
					if (winarr[compcurpos] == 2){
						++winrate1;
						break;
					}
				}
			}
			cout << double(winrate) / double(10000) << "%" << endl;
			cout << double(winrate1) / double(10000) << "%" << endl;
		}
	}
	system("CLS");
	for (;;)
	{
		short compcurpos = 0;
		if (rand() % 2)
		{
			cout << "Bot starts first" << endl;
			for (short it = 0;; ++it){
				turn(pr[compcurpos], &compcurpos, 1);
				if (winarr[compcurpos] == 1){
					lose(compcurpos, 1);
					break;
				}
				display(compcurpos);
				if (it == 4){
					draw(1);
					break;
				}
				input(&compcurpos, 2);
			}
		}
		else
		{
			cout << "You start first" << endl;
			for (short it = 0;; ++it)
			{
				display(compcurpos);
				input(&compcurpos, 1);
				if (it == 4){
					draw(2);
					break;
				}
				turn(pr[compcurpos], &compcurpos, 2);
				if (winarr[compcurpos] == 2){
					lose(compcurpos, 2);
					break;
				}
			}
		}
	}
}