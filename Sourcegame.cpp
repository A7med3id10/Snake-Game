#include<iostream>
#include<windows.h>
#include<conio.h>
#include<chrono>
#include<ctime>

int height = 25;                                             //height of window

int width = 100;                                            //width of window

int gameover = 0, counter, gameover2 = 0, choice, counter2;
int lflag = 0, rflag = 0, uflag = 0, dflag = 0;
int lflag2 = 0, rflag2 = 0, uflag2 = 0, dflag2 = 0;
short fcount;

using namespace std;

long fibonacci(unsigned n)
{
	if (n < 2) return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}


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



	void textcolour(int k)                                    //this function controls the color of the text
	{
		// is color code according to your need.

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);      //To get the value of handle, call a predefined function �GetStdHandle(STD_OUTPUT_HANDLE)�
		SetConsoleTextAttribute(hConsole, k);

	}

public:

	void window()
	{
		if (choice == 1)
			textcolour(4);
		else
			textcolour(1);
		for (int i = 0; i <= width; i++)
		{
			gotoxy(i, 0);
			cout << "�";
			gotoxy(i, height);
			cout << "�";
		}

		for (int i = 0; i <= height; i++)
		{
			gotoxy(0, i);
			cout << "�";
			gotoxy(width, i);
			cout << "�";
		}
	}


	void setup()
	{
		counter = 0;
		gameover = 0;
		window();
		resetflag();
		nameandscore();
		head = new node;                 //creating an new node
		head->nx = width / 2;
		head->ny = height / 2;
		head->next = NULL;
		head->back = NULL;
		x = width / 2;                     //initial X position of the snake
		y = height / 2;                    //initial Y position of the snake

		fx = rand() % width;
		while (fx == 0 || fx == width)
		{
			fx = rand() % width;
		}

		//give random values does not exceed the value of width


		fy = rand() % height;
		while (fy == 0 || fy == height)
		{
			fy = rand() % height;
		}

		//give random values does not exceed the value of height

	}

	void setup2()
	{
		resetflag2();
		gameover2 = 0;
		counter2 = 0;
		fcount = 10;
		head2 = new node;
		head2->nx = width / 2 + 5;
		head2->ny = height / 2 + 5;
		head2->next = NULL;
		head2->back = NULL;
		x2 = width / 2 + 5;
		y2 = height / 2 + 5;

	}

	void drawlist(struct node* h, int k)
	{
		textcolour(k);
		struct node* ptr;
		ptr = h;
		while (ptr != NULL)
		{
			gotoxy(ptr->nx, ptr->ny);
			cout << "�";
			ptr = ptr->next;
		}
	}


	void destroylist(struct node* h)
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



	void draw()
	{

		drawlist(head, 2);
		drawlist(head2, 5);
		gotoxy(fx, fy);
		textcolour(4);
		cout << "@";
		Sleep(40);
		destroylist(head);
		destroylist(head2);
	}

	void resetflag()
	{
		uflag = 0;
		dflag = 0;
		lflag = 0;
		rflag = 0;
	}

	void resetflag2()
	{
		uflag2 = 0;
		dflag2 = 0;
		lflag2 = 0;
		rflag2 = 0;
	}

	void play()
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
			case 72:if (dflag != 1) { resetflag(); uflag = 1; }
				   break;
			case 80:if (uflag != 1) { resetflag(); dflag = 1; }
				   break;
			case 75:if (rflag != 1) { resetflag(); lflag = 1; }
				   break;
			case 77:if (lflag != 1) { resetflag(); rflag = 1; }
				   break;

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

	void box(int m1, int n1, int m2, int n2)
	{
		for (int i = m1; i <= m2; i++)
		{
			gotoxy(i, n1);
			cout << "//";
			gotoxy(i, n2);
			cout << "//";
		}

		for (int i = n1; i <= n2; i++)
		{
			gotoxy(m1, i);
			cout << "//";
			gotoxy(m2, i);
			cout << "//";
		}
	}
	char welcomegame()
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
		gotoxy(width / 2 - 16, height / 2 - 1);
		cout << "b.quit\n";
		gotoxy(width / 2 - 16, height / 2);
		cin >> k;
		//choose the no. of players
		system("cls");
		return k;

	}
	void welcome()
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
		cin >> choice;                               //choose the no. of players
		system("cls");
	}



	void welcome1()
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(6);
		gotoxy(width / 2 - 18, height / 2 - 3);
		cout << "WELCOME TO SNAKE GAME SINGLE PLAYER MODE ";
		textcolour(8);
		gotoxy(width / 2 - 13, height / 2);
		cout << "Enter Your Name : ";
		cin >> playername;
		system("cls");
		//system() : It is used to execute a system command by passing the command as argument to this function.
		// Use �cls� in place of �clear� in system() call.

	}

	void welcome2()
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
		cin >> playername;
		gotoxy(width / 2 + 7, height / 2 + 2);
		cin >> playername2;
		system("cls");
	}




	char end()
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
				cout << playername << " has lost !";// << endl << playername2 << "has won";
			}
			else
			{
				gotoxy(width / 2 - 15, height / 2 + 1);
				cout << playername2 << " has lost !";// << endl << playername << "has won";
			}
			if (fcount == 0)
			{
				textcolour(4);
				gotoxy(width / 2 - 15, height / 2 + 1);
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
		cout << "(Y / N)" << endl;
		gotoxy(width / 2 - 15, height / 2 + 3);
		cout << "Press Y if you Want To Play Again  : " << endl;
		gotoxy(width / 2 - 15, height / 2 + 4);
		cout << "Press N To Return To Start Page : " << endl;
		gotoxy(width / 2 - 15, height / 2 + 5);
		cin >> c;
		system("cls");
		return c;

	}



	void run()    //directions of snake's motion
	{
		if (uflag == 1)
			y--;
		else if (dflag == 1)
			y++;
		else if (lflag == 1)
			x--;
		else if (rflag == 1)
			x++;


		if (uflag2 == 1)
			y2--;
		else if (dflag2 == 1)
			y2++;
		else if (lflag2 == 1)
			x2--;
		else if (rflag2 == 1)
			x2++;

	}

	void dolist(struct node* h, int pp, int qq)
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




	void drawagain()
	{
		if (x == width)
		{
			x = 1;
		}
		if (x == 0)
		{
			x = width - 1;
		}
		if (y == 0)
		{
			y = height - 1;
		}
		if (y == height)
		{
			y = 1;
		}
	}


	void drawagain2()
	{
		if (x2 == width)
		{
			x2 = 1;
		}
		if (x2 == 0)
		{
			x2 = width - 1;
		}
		if (y2 == 0)
		{
			y2 = height - 1;
		}
		if (y2 == height)
		{
			y2 = 1;
		}
	}

	void generatefruit()
	{
		//label1:
		fx = rand() % width;
		while (fx == 0 || fx == width)
		{
			fx = rand() % width;

		}
		fy = rand() % height;
		while (fy == 0 || fy == height)
		{
			fy = rand() % height;
		}

	}

	void checkfcount()
	{
		if (fcount == 0)
		{
			gameover = 1;
			gameover2 = 1;
		}
	}

	void checkup()
	{
		if (choice == 1)
		{
			if (x == width || x == 0)
				gameover = 1;
			if (y == height || y == 0)
				gameover = 1;
		}
		if (choice == 2)
		{
			if (x == width || x == 0 || x2 == width || x2 == 0)
				gameover = 1;
			if (y == height || y == 0 || y2 == height || y2 == 0)
				gameover = 1;
		}
		drawagain();

		struct node* h;
		h = head->next;
		while (h != NULL)
		{
			if (x == h->nx && y == h->ny)
			{
				gameover = 1;
				break;
			}
			h = h->next;
		}

		if (x == fx && y == fy)
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


	void checkup2()
	{
		drawagain2();
		struct node* h;
		h = head2->next;
		while (h != NULL)
		{
			if (x2 == h->nx && y2 == h->ny)
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
	void again()
	{
		welcome();
		if (choice == 1)
		{
			
			game1();
		}

		if (choice == 2)
		{
			game2();
		}

	}

	int game1()
	{
		char ch;
		
		welcome1();
		
		do {
			setup();
			window();
			

			while (!gameover)
			{
				draw();
				play();
				run();
				checkup();

			}
			ch = end();

		} while (ch == 'y' || ch == 'Y');
		if (welcomegame() == 'a') {
			again();
		}
		
		return 0;
	}

	int game2()
	{
		char ch, k;
		welcome2();
		do {

			setup2();
			setup();
			window();

			while (gameover != 1 && gameover2 != 1)
			{
				draw();
				play();
				run();
				checkup();
				checkup2();

			}ch = end();
			

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
	auto start = chrono::steady_clock::now();

	// do some stuff here
   //sf:: sleep(sf::int);3;*/
	Snake s;
	if (s.welcomegame() == 'b')                        //choose the no. of players

		return 0;

	s.welcome();
	if (choice == 1)
	{
		s.game1();
	}
	if (choice == 2)
	{
		s.game2();
	}
	system("exit");
	auto end = chrono::steady_clock::now();

	cout << "Elapsed time in nanoseconds: "
		<< chrono::duration_cast<chrono::nanoseconds>(end - start).count()
		<< " ns" << endl;

	cout << "Elapsed time in microseconds: "
		<< chrono::duration_cast<chrono::microseconds>(end - start).count()
		<< " �s" << endl;

	cout << "Elapsed time in milliseconds: "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;

	cout << "Elapsed time in seconds: "
		<< chrono::duration_cast<chrono::seconds>(end - start).count()
		<< " sec" << endl;



	/*chrono::time_point<chrono::system_clock> start, end;

   start = chrono::system_clock::now();
   cout << "f(42) = " << fibonacci(42) << '\n';
   end = chrono::system_clock::now();

   chrono::duration<double> elapsed_seconds = end - start;
   time_t end_time = chrono::system_clock::to_time_t(end);

   cout << "finished computation at " << ctime(&end_time)<< "elapsed time: " << elapsed_seconds.count() << "s\n";*/
}