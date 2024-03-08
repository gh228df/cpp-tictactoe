#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

unsigned char winarr[19683] = {0};

unsigned short pr[19683][9];

const unsigned short power3[9] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561};

const bool EXTRACOCKY = 0;

bool checkWin(char board[9], char sw) {
    bitset<9> pl;
    for (short i = 0; i < 9; ++i)
    	pl.set(i, board[i] == sw);
    const bitset<9> win[] = {0b111000000,0b000111000,0b000000111,0b100100100,0b010010010,0b001001001,0b100010001,0b001010100};
    for (const auto& combination : win)
		if ((pl & combination) == combination) return true;
    return false;
}

void display(short compcurpos)
{
	for (short j = 9; j > 0; --j){
		if (j % 3 == 0 && j != 9) cout << "---+---+---" << endl;
		for (short u = 0; u < 9; ++u){
			if ((compcurpos / power3[(((j + 2) / 3) * 3 - u / 3 - 1)]) % 3 == (8 - u % 3 + (j - 1) % 3) % 2 + 1)
				if ((compcurpos / power3[(((j + 2) / 3) * 3 - u / 3 - 1)]) % 3 == 1) cout << "\033[1;31m#\033[0m";
				else cout << "\033[1;33m#\033[0m";
			else if (j % 3 == 2 && u % 3 == 1 && (compcurpos / power3[(((j + 2) / 3) * 3 - u / 3 - 1)]) % 3 == 0) cout << ((j + 2) / 3) * 3 - u / 3;
			else cout << " ";
			if (u % 3 == 2 && u < 8) cout << "|";
		}
		cout << endl;
	}
}

void input(short *compcurpos, bool mul)
{
	short p;
	cout << "enter your legit move: ";
	cin >> p;
	if (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        input(compcurpos, mul);
    }else
		if ((*compcurpos / power3[p - 1]) % 3 == 0 && p > 0 && p < 10)
			*compcurpos += (power3[p - 1] << mul);
		else
			input(compcurpos, mul);
}

void draw(bool sw)
{
	cout << endl << "\033[1;32m##  ###  #  # # #" << endl << "# # # # # # # # #" << endl << "# # ##  ### # # #" << endl << "# # # # # # # # #" << endl << "##  # # # #  # #\033[0m" << endl << endl;
	const char* dc[] = {"Impressive, you've achieved the impossible: a draw. I almost broke a sweat.", "A tie? Well, I suppose even a broken clock is right twice a day.", "You've found the perfect recipe for mediocrity - a draw with me!", "A draw? That's almost as rare as me making a mistake.", "I must admit, you've got some skills to pull off a draw against me.", "You've reached the pinnacle of Tic-Tac-Toe - a stalemate with the unbeatable!", "A tie game? You're like a worthy adversary... almost.", "A draw? It's almost like you're pretending to be a challenge.", "Congratulations, you've earned the title of 'Almost a Winner' in this game.", "A tie? You must be a true master of drawing games. Bravo."};
	if(EXTRACOCKY == 1){
		if(sw == 0) cout << "\033[35mBot: \033[31m" << dc[rand () % 10] << "\033[0m" << endl << endl;
		else cout << "\033[35mBot: \033[33m" << dc[rand () % 10] << "\033[0m" << endl << endl;
	}
}

void lose(short compcurpos, bool sw)
{
	const char* wcf[] = {"Your move. Oh wait, it doesn't matter. I've already secured victory with: ", "You thought you had a shot? Adorable. The game was over when I placed: ", "You're ten moves behind, and I've just sealed the deal with: ", "You're trying so hard, but I've already won with: ", "It's almost cute how you keep playing, even though I've dominated with: ", "You see, the moment I moved, it was all over. You just didn't realize it yet.", "You're like a mariner lost at sea, and I'm the lighthouse guiding you to your inevitable loss with: ", "They say practice makes perfect, but it seems like you've got a long way to go. My move sealed the deal: ", "You're playing Tic-Tac-Toe, and I'm playing 4D chess. My winning move was: ", "You can keep trying, but the outcome is crystal clear with: "};
	cout << endl << "\033[1;32m# #  #  # #  #    #  ### ###" << endl << "# # # # # #  #   # # #   #" << endl << "# # # # # #  #   # # ### ###" << endl << " #  # # # #  #   # #   # #" << endl << " #   #   #   ###  #  ### ###\033[0m" << endl << endl;
	if(EXTRACOCKY == 1){
		if(sw == 0) cout << "\033[35mBot: \033[31m" << wcf[rand () % 10] << "\033[0m" << endl << endl;
		else cout << "\033[35mBot: \033[33m" << wcf[rand () % 10] << "\033[0m" << endl << endl;
	}
	else cout << "the losing position is: " << endl;
	display(compcurpos);
	const char* wcf1[] = {"Well, that was cute. Almost like a real challenge!","You're playing Tic-Tac-Toe, right? I thought it was supposed to be a game, not a cakewalk.","It's like watching a master at work, and by master, I mean me.","Do you even know the rules? I mean, you're trying so hard.","You're making this game feel like a warm-up for me. Keep trying!","I hate to break it to you, but you might want to find a new hobby.","Close, but not quite. Maybe one day you'll get the hang of it.","It's almost admirable how consistently you lose.","I heard you're a Tic-Tac-Toe legend... in a parallel universe.","You're the best at losing I've ever seen. Keep up the good work!"};
	if(sw == 0) cout << "\033[35mBot: \033[31m" << wcf1[rand () % 10] << "\033[0m" << endl << endl;
	else cout << "\033[35mBot: \033[33m" << wcf1[rand () % 10] << "\033[0m" << endl << endl;
}

int main(){
    srand(time(NULL));
    for(int i = 0; i < 19683; i++)
        for(int u = 0; u < 9; u++)
            pr[i][u] = 32768;
    char optipos[9] = {0};
	for (short h = 0; h < 19683; ++h, ++optipos[0])
	{	
		for (short i = 0; i < 8; ++i)
			optipos[i] = (optipos[i] == 3) ? (optipos[i + 1]++, 0) : optipos[i];
		if(checkWin(optipos, 1) == 1)
			winarr[h] = 1;
		else if(checkWin(optipos, 2) == 1)
			winarr[h] = 2;
	}
    vector<short> move {0, 1, 2, 3, 4, 5, 6, 7, 8};
    for(;;){
        short curpos = power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]];
        if(winarr[curpos] == 1){
            pr[0][move[0]]++;
            pr[power3[move[0]] + power3[move[1]] * 2][move[2]]++;
            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2][move[4]] += 4;

            pr[power3[move[0]]][move[1]]--;
            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]]][move[3]]--;
        }
        else
        {
            curpos += power3[move[5]] * 2;
            if(winarr[curpos] == 2){
                pr[power3[move[0]]][move[1]]++;
                pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]]][move[3]]++;
                pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]]][move[5]] += 4;

                pr[0][move[0]]--;
                pr[power3[move[0]] + power3[move[1]] * 2][move[2]]--;
                pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2][move[4]]--;
            }
            else
            {
                curpos += power3[move[6]];
                if(winarr[curpos] == 1){
                    pr[0][move[0]]++;
                    pr[power3[move[0]] + power3[move[1]] * 2][move[2]]++;
                    pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2][move[4]]++;
                    pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]] + power3[move[5]] * 2][move[6]] += 4;
                    
                    pr[power3[move[0]]][move[1]]--;
                    pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]]][move[3]]--;
                    pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]]][move[5]]--;
                }
                else
                {
                    curpos += power3[move[7]] * 2;
                    if(winarr[curpos] == 2){
                        pr[power3[move[0]]][move[1]]++;
                        pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]]][move[3]]++;
                        pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]]][move[5]]++;
                        pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]] + power3[move[5]] * 2 + power3[move[6]]][move[7]] += 4;

                        pr[0][move[0]]--;
                        pr[power3[move[0]] + power3[move[1]] * 2][move[2]]--;
                        pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2][move[4]]--;
                        pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]] + power3[move[5]] * 2][move[6]]--;
                    }
                    else{
                        curpos += power3[move[8]];
                        if(winarr[curpos] == 1){
                            pr[0][move[0]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2][move[2]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2][move[4]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]] + power3[move[5]] * 2][move[6]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]] + power3[move[5]] * 2 + power3[move[6]] + power3[move[7]] * 2][move[8]] += 4;

                            pr[power3[move[0]]][move[1]]--;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]]][move[3]]--;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]]][move[5]]--;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]] + power3[move[5]] * 2 + power3[move[6]]][move[7]]--;
                        }else{
                            pr[0][move[0]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2][move[2]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2][move[4]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]] + power3[move[5]] * 2][move[6]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]] + power3[move[5]] * 2 + power3[move[6]] + power3[move[7]] * 2][move[8]]++;

                            pr[power3[move[0]]][move[1]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]]][move[3]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]]][move[5]]++;
                            pr[power3[move[0]] + power3[move[1]] * 2 + power3[move[2]] + power3[move[3]] * 2 + power3[move[4]] + power3[move[5]] * 2 + power3[move[6]]][move[7]]++;
                        }
                    }
                }
            }
        }
        if(next_permutation(move.begin(), move.end()) == 0)
            break;
    }
    pr[6724][1] += 24;
    pr[6724][3] += 24;
    pr[6724][5] += 24;
    pr[6724][7] += 24;
    pr[900][1] += 24;
    pr[900][3] += 24;
    pr[900][5] += 24;
    pr[900][7] += 24;
    pr[13210][6] += 24; // 2
    pr[13258][2] += 24; // 4 
    pr[2034][0] += 24; // 6
    pr[5202][0] += 24; // 8
    system("CLS");
    for(;;){
        short compcurpos = 0;
        if(rand() % 2){
            cout << "Bot starts first" << endl;
            for(int m = 0;; m++){
                unsigned short moveval = 0, move = 0;
                for(int j = 0; j < 9; j++)
                    if(pr[compcurpos][j] > moveval and (compcurpos / power3[j]) % 3 == 0){
                        moveval = pr[compcurpos][j];
                        move = j;
                    }
                compcurpos += power3[move];
                if(winarr[compcurpos] == 1){
                    lose(compcurpos, 0);
                    break;
                }
                if(m == 4){
                    draw(1);
                    break;
                }
                display(compcurpos);
                input(&compcurpos, 1);
            }
        }
        else
        {
            cout << "User starts first" << endl;
            for(int m = 0;; m++){
                display(compcurpos);
                input(&compcurpos, 0);
                if(m == 4){
                    draw(0);
                    break;
                }
                unsigned short moveval = 0, move = 0;
                for(int j = 0; j < 9; j++)
                    if(pr[compcurpos][j] > moveval and (compcurpos / power3[j]) % 3 == 0){
                        moveval = pr[compcurpos][j];
                        move = j;
                    }
                compcurpos += 2 * power3[move];
                if(winarr[compcurpos] == 2){
                    lose(compcurpos, 1);
                    break;
                }
            }
        }
    }
}
