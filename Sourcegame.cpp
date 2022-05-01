#include<iostream>
#include<windows.h>
#include<ctime>
#include <time.h>
#include <conio.h> //for time analysis

int height = 25;                                             //height of window

int width = 100;                                             //width of window
//variables of time analysis
time_t t1;
time_t t2;
time_t t3;
time_t t4;
time_t t5;
time_t t6;
time_t t7;
time_t t8;

int gameover = 0;
int counter;
int gameover2 = 0;
int counter2;
int choice;
char choice1;
int lflag = 0, rflag = 0, uflag = 0, dflag = 0;
int lflag2 = 0, rflag2 = 0, uflag2 = 0, dflag2 = 0;
short fcount;

using namespace std;

class Snake

{

	int x, y, fx, fy, x2, y2;
	char playername[50], playername2[50];;

	struct node
	{
		int nx, ny;
		struct node* next;
		struct node* back;
	};

	struct node* head = NULL;
	struct node* head2 = NULL;


	void gotoxy(int x, int y)                     //describes the coordinates of cursor in x and y
	{
		COORD pos = { x,y };                         //Coord: The predefined function used to get X and Y coordinates.
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	void nameandscore()                                      //describes name and score of player(s)
	{
		gotoxy(101, 0);
		textcolour(10);                                     //describes the color of the window
		cout << "MADE BY = Mo3Gza ";
		textcolour(6);
		gotoxy(101, 2);
		cout << playername << "'s SCORE = " << counter * 100;      //set the name of player
		if (choice == 2)                                      //in case of 2 players
		{
			gotoxy(101, 4);
			cout << playername2 << "'s SCORE = " << counter2 * 100;  //set the name of player 2
			gotoxy(101, 6);
			cout << "Remained Fruit :";                        //no. of remainder fruits
			gotoxy(117, 6);
			cout << "  ";
			gotoxy(117, 6);
			cout << fcount;
		}
	}



	void textcolour(int k)                                        //this function controls the color of the text
	{
		                                                         // is color code according to your need.

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);      //To get the value of handle, call a predefined function “GetStdHandle(STD_OUTPUT_HANDLE)”
		SetConsoleTextAttribute(hConsole, k);

	}

public:

	void window()                                             // to make the boarder
	{
		if (choice == 1)
			textcolour(4);
		else
			textcolour(1);
		for (int i = 0; i <= width; i++)             //draw the width of the border
		{
			gotoxy(i, 0);
			cout << "Û";                            //shape of the boarder
			gotoxy(i, height);
			cout << "Û";
		}

		for (int i = 0; i <= height; i++)        //draw the height of the border
		{
			gotoxy(0, i);
			cout << "Û";
			gotoxy(width, i);
			cout << "Û";
		}
	}


	void setup()                                        // single player mood
	{
		counter = 0;
		gameover = 0;
		window();
		resetflag();
		nameandscore();
		head = new node;                 //creating an new node
		head->nx = width / 7;
		head->ny = height / 7;
		head->next = NULL;
		head->back = NULL;
		x = width / 7;                     //initial X position of the snake
		y = height / 7;                    //initial Y position of the snake

		fx = rand() % width;                 //give random values does not exceed the value of width
		while (fx == 0 || fx == width)
		{
			fx = rand() % width;
		}


		fy = rand() % height;               //give random values does not exceed the value of height
		while (fy == 0 || fy == height)
		{
			fy = rand() % height;
		}
	}

	void setup2()                     // Two players mood
	{
		resetflag2();
		gameover2 = 0;
		counter2 = 0;
		fcount = 10;
		head2 = new node;                      //creating an new node
		head2->nx = width / 2;
		head2->ny = height / 2;
		head2->next = NULL;
		head2->back = NULL;
		x2 = width / 2;                //initial X2 position of the snake
		y2 = height / 2;              //initial Y2 position of the snake

	}

	void drawlist(struct node* h, int k)            //to draw Snake
	{
		textcolour(k);
		struct node* ptr;
		ptr = h;
		while (ptr != NULL)
		{
			gotoxy(ptr->nx, ptr->ny);
			cout << "Û";
			ptr = ptr->next;
		}
	}


	void destroylist(struct node* h)                  // avoid making infinity linked list of snake
	{
		struct node* ptr;
		ptr = h;
		while (ptr != NULL)
		{
			gotoxy(ptr->nx, ptr->ny);
			cout << " ";
			ptr = ptr->next;
		}
	}
	void draw()                        // draw game 1
	{
		drawlist(head, 7);                // draw snake 1
		gotoxy(fx, fy);
		textcolour(4);
		cout << "\242";                      // fruit shape
		Sleep(40);                        // To control the speed of snake
		destroylist(head);
	}


	void draw2()                            // draw game 2
	{

		drawlist(head, 12);                // draw snake 1
		drawlist(head2, 9);               // draw snake 2
		gotoxy(fx, fy);
		textcolour(4);
		cout << "\242";                      // fruit shape
		Sleep(40);                        // To control the speed of snake
		destroylist(head);
		destroylist(head2);
	}

	void resetflag()                      // reset first snake flags
	{
		uflag = 0;
		dflag = 0;
		lflag = 0;
		rflag = 0;
	}

	void resetflag2()                    // reset second snake flags
	{
		uflag2 = 0;
		dflag2 = 0;
		lflag2 = 0;
		rflag2 = 0;
	}

	void play()              // the process of the game
	{
		int h;
		char ch;
		if (_kbhit())        //kbhit() is used to determine if a key has been pressed or not.
		{

			ch = _getch();
			//getch() also reads a single character from the keyboard.
			//But it does not use any buffer, so the entered character is immediately returned without waiting for the enter key.
			//the return value is ascii value of the key pressed
			h = ch;
			switch (h)
			{   //this cases is the values of ascii code of the pressed key
				// this ascii code for keys to control of direction of snake 1
			case 72:if (dflag != 1) { resetflag(); uflag = 1; }
				   break;
			case 80:if (uflag != 1) { resetflag(); dflag = 1; }
				   break;
			case 75:if (rflag != 1) { resetflag(); lflag = 1; }
				   break;
			case 77:if (lflag != 1) { resetflag(); rflag = 1; }
				   break;

				   // this ascii code for keys to control of direction of snake 2

			case 119:if (dflag2 != 1) { resetflag2(); uflag2 = 1; }
					break;
			case 115:if (uflag2 != 1) { resetflag2(); dflag2 = 1; }
					break;
			case 97:if (rflag2 != 1) { resetflag2(); lflag2 = 1; }
				   break;
			case 100:if (lflag2 != 1) { resetflag2(); rflag2 = 1; }
					break;

			default:break;
			}
		}
	}

	void box(int m1, int n1, int m2, int n2)           // Make the inner box  which any window of welcom is shown
	{
		for (int i = m1; i <= m2; i++)                 // draw width of yhe inner box
		{
			gotoxy(i, n1);
			cout << "//";
			gotoxy(i, n2);
			cout << "//";
		}

		for (int i = n1; i <= n2; i++)              // draw height of the inner box
		{
			gotoxy(m1, i);
			cout << "//";
			gotoxy(m2, i);
			cout << "//";
		}
	}
	char welcomegame()                       // start page
	{
		char k;
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(10);
		gotoxy(width / 2 - 20, height / 2 - 10);
		cout << " WELCOME TO SNAKE GAME ";
		textcolour(9);
		gotoxy(width / 2 - 16, height / 2 - 3);
		cout << "a.start \n";
		gotoxy(width / 2 - 16, height / 2 - 2);
		cout << "b.quit\n";
		gotoxy(width / 2 - 16, height / 2);
		cin >> k;
		while (k != 'a' && k != 'b')
            {
			cout << endl;
			cout << "please choose (a) or (b)" << endl;
			cin >> k;
		}
		system("cls");
		return k;

	}
	void welcome()     //The page that appears after the start page to choose mood game
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(10);
		gotoxy(width / 2 - 20, height / 2 - 10);
		cout << "* WELCOME TO SNAKE GAME BY Mo3Gza* ";
		textcolour(9);
		gotoxy(width / 2 - 16, height / 2 - 3);
		cout << "Press 1 For Single player \n";
		gotoxy(width / 2 - 16, height / 2 - 1);
		cout << "Press 2 For Multiplayer \n";
		gotoxy(width / 2 - 16, height / 2);
		cin >> choice1;
		while (choice1 != '1' && choice1 != '2')
            {
			cout << endl;
			cout << "please choose (1) or (2)" << endl;
			cin >> choice1;
		}
		if (choice1 == '1')
			choice = 1;
		else
			choice = 2;
		system("cls");           //system() : It is used to execute a system command by passing the command as argument to this function.
                                // Use “cls” in place of “clear” in system() call.
	}

	void welcome1()                           // for mood single player
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(6);
		gotoxy(width / 2 - 18, height / 2 - 3);
		cout << "WELCOME TO SNAKE GAME SINGLE PLAYER MODE ";
		textcolour(8);
		gotoxy(width / 2 - 13, height / 2);
		cout << "Enter Your Name : ";
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cin.getline(playername, 50);
		system("cls");
		//system() : It is used to execute a system command by passing the command as argument to this function.
		// Use “cls” in place of “clear” in system() call.

	}

	void welcome2()                           // for mood Two player
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(6);
		gotoxy(width / 2 - 18, height / 2 - 3);
		cout << "WELCOME TO SNAKE GAME MULTIPLAYER MODE ";
		textcolour(8);
		gotoxy(width / 2 - 13, height / 2);
		cout << "Enter Player1 Name : ";
		gotoxy(width / 2 - 13, height / 2 + 2);
		cout << "Enter Player2 Name : ";
		gotoxy(width / 2 + 7, height / 2);
		cin.clear();                                     // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n');                       // ignore last input
		cin.getline(playername, 50);
		gotoxy(width / 2 + 7, height / 2 + 2);
		cin.getline(playername2, 50);
		system("cls");                                  //system() : It is used to execute a system command by passing the command as argument to this function.
		                                               // Use “cls” in place of “clear” in system() call.
	}


	char end()               // This is the function on which the end window appears and determines whether you win or lose
	{
		char c;
		gotoxy(width / 2 - 5, height / 2 - 4);
		cout << "GAME OVER \n";
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);

		textcolour(1);
		gotoxy(width / 2 - 15, height / 2 - 2);
		cout << playername << " You Scored : " << counter * 100;
		if (choice == 2)
		{
			gotoxy(width / 2 - 15, height / 2);
			cout << playername2 << " You Scored : " << counter2 * 100;
			textcolour(4);
			if (gameover != 0)
			{
				gotoxy(width / 2 - 15, height / 2 + 1);
				cout << playername << " has lost !";
			}
			else
			{
				gotoxy(width / 2 - 15, height / 2 + 1);
				cout << playername2 << " has lost !";
			}
			if (fcount == 0)
			{
				textcolour(4);
				gotoxy(width / 2 - 15, height / 2 + 1);      // if player1 or player2 in mood Two player eat all the fruit
				if (counter > counter2)
				{
					cout << playername << " has WON !";
				}
				else
				{
					cout << playername2 << " has WON !";
				}
			}
		}
		textcolour(6);
		gotoxy(width / 2 - 15, height / 2 + 2);
		cout << "(y / n)" << endl;
		gotoxy(width / 2 - 15, height / 2 + 3);
		//asking the user if he wants to play again
		cout << "Press y if you Want To Play Again  : " << endl;
		gotoxy(width / 2 - 15, height / 2 + 4);
		cout << "Press n To Return To Start Page : " << endl;
		gotoxy(width / 2 - 15, height / 2 + 5);
		cin >> c;
		while (c != 'y' && c != 'n') {
			cout << endl;
			cout << "please choose (y) or (n)" << endl;
			cin >> c;
		}

		system("cls");                                         //system() : It is used to execute a system command by passing the command as argument to this function.
		                                                      // Use “cls” in place of “clear” in system() call.
		return c;

	}

	void run()    //directions of snake's motion
	{
		          // directions of snake 1 motion
		if (uflag == 1)
			y--;
		else if (dflag == 1)
			y++;
		else if (lflag == 1)
			x--;
		else if (rflag == 1)
			x++;
		              // directions of snake 2 motion

		if (uflag2 == 1)
			y2--;
		else if (dflag2 == 1)
			y2++;
		else if (lflag2 == 1)
			x2--;
		else if (rflag2 == 1)
			x2++;

	}

	void dolist(struct node* h, int pp, int qq)      //to make the snake grow when it eats
	{
		struct node* ptr, * prev;
		ptr = h;
		prev = h;

		while (ptr->next != NULL)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		while (prev != h)
		{
			ptr->nx = prev->nx;
			ptr->ny = prev->ny;
			prev = prev->back;
			ptr = ptr->back;
		}
		ptr->nx = prev->nx;
		ptr->ny = prev->ny;
		prev->nx = pp;
		prev->ny = qq;
	}

	void generatefruit()          // function to make fruit appear in random places
	{
		fx = rand() % width;    // make fruit appers in random places in width
		while (fx == 0 || fx == width)
		{
			fx = rand() % width;

		}
		fy = rand() % height;    // make fruit appers in random places in height
		while (fy == 0 || fy == height)
		{
			fy = rand() % height;
		}

	}

	void checkfcount()                  //one of the cases of ending the game in two player mode
	{
		if (fcount == 0)
		{
			gameover = 1;
			gameover2 = 1;
		}
	}

	void checkup()                               //a function that show the Scenarios of end game for first snake
	{
		if (choice == 1)                         //hit boarder in single player mode
		{
			if (x == width || x == 0)
				gameover = 1;
			if (y == height || y == 0)
				gameover = 1;
		}
		if (choice == 2)                         //hit boarder in double player mode
		{
			if (x == width || x == 0 || x2 == width || x2 == 0)
				gameover = 1;
			if (y == height || y == 0 || y2 == height || y2 == 0)
				gameover = 1;
		}

		struct node* h;
		h = head->next;                 // making the snake move
		while (h != NULL)
		{
			if (x == h->nx && y == h->ny)       // snake hits itself in one player mode
			{
				gameover = 1;
				break;
			}
			h = h->next;
		}

		if (x == fx && y == fy)                // snake hits itself in two player mode
		{
			if (choice == 2)
			{

				fcount--;
				checkfcount();
			}
			struct node* t, * ptr, * prev;
			t = new node;
			t->next = NULL;
			t->back = NULL;
			ptr = head;
			prev = head;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = t;
			t->back = ptr;
			generatefruit();
			counter++;
			nameandscore();
		}
		dolist(head, x, y);
	}

	void checkup2()                             //a function that show the Scenarios of end game for second snake
	{
		struct node* h;
		h = head2->next;                       //second snake moves
		while (h != NULL)
		{
			if (x2 == h->nx && y2 == h->ny)    //second snake hits itself
			{
				gameover2 = 1;
				break;
			}
			h = h->next;
		}


		if (x2 == fx && y2 == fy)
		{
			fcount--;
			checkfcount();
			struct node* t, * ptr, * prev;
			t = new node;
			t->next = NULL;
			t->back = NULL;
			ptr = head2;
			prev = head2;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = t;
			t->back = ptr;
			generatefruit();
			counter2++;
			nameandscore();
		}
		dolist(head2, x2, y2);
	}

	void again()              // function to make user play again
	{
		welcome();
		if (choice == 1)  // if choice 1 user will play single player
		{

			game1();
		}

		else if (choice == 2)  // if choice 2 user will play double player
		{
			game2();

		}
		else
		{
			cout << "please choose (1) or (2)" << endl;
			void again();

		}

	}

	int game1()              // single player mode
	{
		char ch;
		t1=clock();         // start of the time of analysis + user game
		welcome1();
		do {
			setup();
			window();
            t3=clock();    // start of the time of user game
			while (!gameover)
			{

				draw();
				play();
				run();
				checkup();
			}
			t4=clock();         //end of the time of user game
			ch = end();
			t2=clock();         //end of the time of analysis + user game
		} while (ch == 'y' || ch == 'Y');
		if (welcomegame() == 'a') {
			again();
		}
		return 0;
		}

	int game2()                // double player mode
	{
		char ch, k;
		t5=clock();            // start of the time of analysis + user game
		welcome2();
		do {

			setup2();
			setup();
			window();

			t7=clock();        // start of the time of user game
			while (gameover != 1 && gameover2 != 1)
			{
				draw2();
				play();
				run();
				checkup();
				checkup2();
			}
			t8=clock();       //end of the time of user game
			ch = end();
			t6=clock();       //end of the time of analysis + user game
		} while (ch == 'y' || ch == 'Y');

		if (welcomegame() == 'a')
		{
			again();
		}
		return 0;
	}

};
int main()
{
	Snake s;
	if (s.welcomegame() == 'b')                        //choose the no. of players

		return 0;

	s.welcome();
	if (choice == 1)
	{
		s.game1();
	}
	else if (choice == 2)
	{
		s.game2();
	}
	else {
		system("exit");
	}
	system("exit");
	double cpu_time_used1 = ((double) (t2 - t1)) / CLOCKS_PER_SEC; // time of the analysis of the single game + time of the user game
	double cpu_time_used2 = ((double) (t4 - t3)) / CLOCKS_PER_SEC; // time of the user game1
	double cpu_time_used3 = ((double) (t6 - t5)) / CLOCKS_PER_SEC; // time of the analysis of the multplayer game + time of the user game
	double cpu_time_used4 = ((double) (t8 - t7)) / CLOCKS_PER_SEC; // time of the user game2
	double timeofanalysis1=cpu_time_used1-cpu_time_used2;
	double timeofanalysis2=cpu_time_used3-cpu_time_used4;
	printf("\n");
    printf("time of single game %f seconds to execute \n", timeofanalysis1);
    printf("\n");
    printf("time of multiplayer game %f seconds to execute \n", timeofanalysis2);
}
