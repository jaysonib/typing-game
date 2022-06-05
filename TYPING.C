#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <graphics.h>

#define TESTMODE '1'
#define TRAINMODE '2'
#define QUIT '3'
#define ESC '\x1b'
#define Y 'y'
#define N 'n'

void MainInitial () ;
void Body () ;
void MainProcess () ;
void TestMode () ;
void TestInitial (int * , int * , FILE * , char *) ;
void TestProcess (int * , int * , int * , int * , char * , int * ) ;
void UserInput (int * , int * , int * , int * , char *) ;
void EndTestMode () ;
void OutputLetter (int * , int * , char , int *) ;
void CheckCursorPosition (int * , int * , int * , char * , int *) ;
void NewFile (int * , int * , FILE *) ;
void NewPage (int * , int * , char * , int *) ;
void NewLine (int * , int *) ;
void CheckIfTyped(int * , int *) ;
void Report (int * , int *) ;
void TrainMode () ;
void TrainInitial () ;
void TrainLetter () ;
void TrainWord () ;
void TrainProcess (int * , int *) ;
void SelectLetter (char , int * , int *) ;
void PrintLetter () ;
void TrainUserInput (char , int * , int *) ;
void EndTrainMode () ;
void TrainOutputLetter (int , int * , int *) ;
void SelectWord (int * , int *) ;
void PrintWord (char *) ;
void TrainUserInputWord (char * , int * , int *) ;
void EndTrainWordMode () ;
void TrainOutputWord (int * , int *) ;
void TrainCheckIfTyped (int * , int *) ;
void TrainReport (int * , int *) ;
void QuitConfirm () ;
void EndBody () ;
void EndProgram () ;

enum Boolean { FALSE , TRUE } ;
enum Boolean 	ExitProgram , ExitTestProcess , ExitTrainProcess , ExitTrainUserInput
	      ,	MiddleRow , UpperRow , LowerRow , NumberRow
	      , TrainSelect , ChoiceLetter , ExitTrainUserInputWord
	      , EndOfWord ;

int FileLength ;
char RequiredLetter ;
float TimeUsed ;

char MiddleRowLetters [9] = {'a','s','d','f','g','h','j','k','l'} ;
char UpperRowLetters [10] = {'q','w','e','r','t','y','u','i','o','p'} ;
char LowerRowLetters [7]  = {'z','x','c','v','b','n','m'} ;
char NumberRowLetters [10]= {'0','1','2','3','4','5','6','7','8','9'} ;

clock_t TimeStart , TimeStop ;

void main()
{
	randomize () ;   //to make the random number generated more randomly

	MainInitial () ;

	Body () ;

	EndProgram () ;
}

void MainInitial ()
{
	ExitProgram = FALSE ;
}

void Body ()
{
	do
	{
	       MainProcess () ;

	} while (ExitProgram == FALSE) ;  //Once ExitProgram is True,
}					  //it will exit MainProcess ()

void MainProcess ()
{
	int Count ;
	char MenuChoice ;

	textcolor(WHITE);	//change the text and background colour
	textbackground(BLUE);
	clrscr () ;
	gotoxy (30 , 9) ;	//display the frame
	printf ("\xc9") ;
		for (Count = 1 ; Count <= 25 ; Count++ )
		{
			printf ("\xcd") ;
		}
	gotoxy (56 , 9) ;
		for (Count = 1 ; Count <= 6 ; Count++ )
		{
			gotoxy (30 , 9 + Count) ;
			printf ("\xba") ;
		}
	gotoxy (56 , 9) ;
	printf ("\xbb") ;
	gotoxy (30 , 15) ;
	printf ("\xc8") ;
		for (Count = 1 ; Count <= 26 ; Count++ )
		{
			printf ("\xcd") ;
		}
	gotoxy (56 , 15) ;
	printf ("\xbc") ;
		for (Count = 1 ; Count <= 5 ; Count++ )
		{
			gotoxy (56 , 9 + Count) ;
			printf ("\xba") ;
		}



	gotoxy (35 , 10) ;
	printf ("1. Test Mode") ;       //Display the menu
	gotoxy (35 , 11) ;
	printf ("2. Training Mode") ;
	gotoxy (35 , 12) ;
	printf ("3. Quit Now") ;
	gotoxy (35 , 14) ;
	printf ("What Choice? : \n") ;
	gotoxy (30 , 25) ;
	printf ("Press ESC to quit.") ;
	gotoxy (52 , 14) ;

	MenuChoice = getch () ;           //Accept a key value from the user

	switch (MenuChoice)
	{
		case TESTMODE :		 //if the user press 1

			TestMode () ;
			break ;

		case TRAINMODE :	 //if the user press 2

			TrainMode () ;
			break ;

		case QUIT :	case ESC :	//if the user press ESC or 3

			QuitConfirm () ;	//Call QuitConfirm ()
	}					//function to confirm if the
}						//user want to quit or
					//selected it by mistake




//for paragraph typing
void TestMode ()
{
	//pointers must be initialised
	int x = 0 , y = 0 , InputCount = 0 , CorrectInputCount = 0 ,
	    Page = 0 ;

	FILE *FilePointer ;	//initial the pointer of the file

	char str[50000] ;	 //declare a buffer to hold the passage

	clrscr () ;                //clear the screen

	TestInitial (&x , &y , FilePointer , str) ;

	do                         //Once the user pressed ESC, it will exit
	{			   //TestProcess
		TestProcess (    &x , &y , &InputCount ,
			&CorrectInputCount , str , &Page ) ;

	} while (ExitTestProcess == FALSE) ;

	//if the user have not typed any letter, no report will be printed
	CheckIfTyped (&InputCount , &CorrectInputCount) ;

	fclose (FilePointer) ;	//close the file
}

void TestInitial (int *x , int *y , FILE *FilePointer , char *str)
{
	int Row , Column , Count , Size , RandomFile ;
	RandomFile = random (10) + 1 ;		//generate a random number
						//in the range from 1 to 10
	switch (RandomFile)    //select a random file
	{
		case 1 :
			FilePointer = fopen ("passage1.txt" , "r") ;
			break ;
		case 2 :
			FilePointer = fopen ("passage2.txt" , "r") ;
			break ;
		case 3 :
			FilePointer = fopen ("passage3.txt" , "r") ;
			break ;
		case 4 :
			FilePointer = fopen ("passage4.txt" , "r") ;
			break ;
		case 5 :
			FilePointer = fopen ("passage5.txt" , "r") ;
			break ;
		case 6 :
			FilePointer = fopen ("passage6.txt" , "r") ;
			break ;
		case 7 :
			FilePointer = fopen ("passage7.txt" , "r") ;
			break ;
		case 8 :
			FilePointer = fopen ("passage8.txt" , "r") ;
			break ;
		case 9 :
			FilePointer = fopen ("passage9.txt" , "r") ;
			break ;
		case 10 :
			FilePointer = fopen ("passage0.txt" , "r") ;
			break ;
	}
	if ( FilePointer == NULL )		//if cannot open the file
	{
		printf ("\nCannot open the file.") ;
		ExitTestProcess = TRUE ;
	}
	else					//if can open the file
	{
		clrscr () ;
		//The letters of the external file are checked if they are
		//newlines or tabs. If they are , they will be changed into
		//spaces to avoid any error.
		for ( Count = 0 ;  !feof(FilePointer)  ; Count++ )
		{
			if (   (str[Count] = fgetc(FilePointer))  ==  '\t'
				||   str[Count] == '\n'	)
			{
				str[Count] = ' ' ;
			}
		}
		//Print out the passage to the screen and add empty lines
		//between every lines
		for (Row = 0 ; Row < 6 ; Row++)
		{
			for (Column = 1 ; Column <= 80 ; Column++)
			{
				if (str[80 * Row + Column - 1] == EOF)
				{
					goto ExitFor ;
				}
				printf ("%c" , str[80 * Row + Column - 1] ) ;
			}
			printf ("\n\n")  ;
		}
	}

ExitFor :

	ExitTestProcess = FALSE ;

	*x = 1 ;	//tell the computer that the starting cursor position
	*y = 2 ;	//is (1 , 2) .

	gotoxy (1 , 25) ;
	printf ("Press any key to start!") ;
	getch () ;	//wait for the user to press any key

	delline () ;	//delete all the content of the current line

	gotoxy (30 , 25) ;
	printf ("Press ESC to quit.") ;

	TimeUsed = 0 ;
	TimeStart = clock () ;	//record the current time into TimeStart

	gotoxy (1 , 2) ;
}

void TestProcess (int *x , int *y , int *InputCount ,
		  int *CorrectInputCount , char *str , int *Page )
{
	UserInput (x , y , InputCount , CorrectInputCount , str ) ;

	CheckCursorPosition (x , y , CorrectInputCount , str , Page) ;
}

void UserInput (int *x , int *y , int *InputCount , int *CorrectInputCount ,
		char *str )
{
	char InputLetter ;
	static float TimeStop ;
	gotoxy (27 , 19) ;
		printf ("Time used     :   ") ;
	gotoxy (27 , 20) ;
		printf ("Accuracy      :   ") ;
	gotoxy (27 , 21) ;
		printf ("Speed         :   ") ;
	gotoxy (27 , 22) ;
		printf ("Wrong letters :   ") ;
	gotoxy (27 , 23) ;
		printf ("Typed letters :   ") ;
	gotoxy (*x , *y) ;
while ( !kbhit() )
{
	if ( *InputCount > 0 )
	{
	double Speed ;
	//Calculate the accuracy
	float Accuracy = (float) *CorrectInputCount * 100 / *InputCount ;
	//Calculate the number of letters typed wrongly
	int WrongInput = *InputCount - *CorrectInputCount ;
	//Calculate wpm
	TimeStop = clock () ;
	TimeUsed = TimeUsed + (TimeStop - TimeStart) / CLK_TCK ;
	Speed = *CorrectInputCount / 5 / (TimeUsed / 60) ;
	TimeStart = clock () ;
	gotoxy (45 , 19) ;
		printf ("%10.2f seconds" , TimeUsed) ;
	gotoxy (45 , 20) ;
		printf ("%10.2f %%" , Accuracy) ;
	gotoxy (45 , 21) ;
		printf ("%10.2f wpm" , Speed) ;
	gotoxy (45 , 22) ;
		printf ("%10d letters" , WrongInput) ;
	gotoxy (45 , 23) ;
		printf ("%10d letters" , *InputCount) ;
	gotoxy (*x , *y) ;
	delay (100) ;
	}
}
	InputLetter = getch () ;
	if (InputLetter == ESC)	//if the user press ESC
	{
	       TimeStop = clock () ;
	       EndTestMode () ;
	}
	else
	{
		//if the user typed correcly
		if ( InputLetter == str [ *CorrectInputCount ] )
		{
			OutputLetter (x , InputCount ,
					 InputLetter , CorrectInputCount) ;
		}
		else            //if the user typed wrongly
		{
			(*InputCount) ++ ;
		}
	}
}

void EndTestMode ()
{
	ExitTestProcess = TRUE ;
}

void OutputLetter (int *x , int *InputCount ,
			 char InputLetter , int *CorrectInputCount)
{
	(*CorrectInputCount) ++ ;	//the user typed 1 more correct
	(*InputCount) ++ ;		//the user typed 1 more letter
	putchar (InputLetter) ;		//output the key the user pressed

	(*x) ++ ;			//tell the computer that
					//the cursor should be shifted
					//to right by 1 position
}

void CheckCursorPosition (int *x , int *y ,
			int *CorrectInputCount , char *str , int *Page)
{
	if ( str[*CorrectInputCount] == EOF )
	{
		getch () ;
		TimeStop = clock () ;
		EndTestMode () ;
	}
	else	//if the cursor reach the end of any line ,
	{
		if (	wherex () == 1 && wherey () >= 17   )
		{
			clrscr () ;
			NewPage (x , y , str , Page) ;
		}
		else
		{
			if (*x == 81)
			{
				NewLine (x , y) ;
			}
		}
	}
}

void NewPage (int *x , int *y , char *str , int *Page)
{
	int Row , Column ;

	(*Page) ++ ;

	clrscr () ;

	for (Row = 0 ; Row < 6 ; Row++)
	{
		for ( Column = 1 ; Column <= 80 ; Column++   )
		{
			if (str[ (Row * 80  + Column - 1)
				+ (*Page * 80 * 6) ] == EOF)
			{
				goto ExitFor ;
			}
			printf ("%c" ,
			 str[ (Row * 80  + Column - 1) + (*Page * 80 * 6) ] ) ;
		}
		printf ("\n\n")  ;
	}

ExitFor:
	gotoxy (30 , 25) ;
	printf ("Press ESC to quit.") ;

	*x = 1 ;
	*y = 2 ;

	gotoxy (*x , *y) ;
}

void NewLine (int *x , int *y)
{
	*x = 1 ;
	*y += 3 ;	//tell computer to shift the cursor down two rows

	gotoxy (*x , *y) ;
}

void CheckIfTyped (int *InputCount , int *CorrectInputCount)
{
	if (*InputCount != 0)	//if the user have not typed anything
		Report (InputCount , CorrectInputCount) ;//generate report
}

void Report (int *InputCount , int *CorrectInputCount)
{
	//Calculate the accuracy
	float Accuracy = (float) *CorrectInputCount * 100 / *InputCount ;
	//Calculate the number of letters typed wrongly
	int WrongInput = *InputCount - *CorrectInputCount ;
	//Calculate wpm
	double Speed = *CorrectInputCount / 5 / (TimeUsed / 60) ;

	clrscr () ;

	gotoxy (20 , 8) ;
	printf ( "Time Used       : %10.2f seconds" , TimeUsed ) ;
	gotoxy (20 , 10) ;
	printf ( "Character Typed : %10d letters" , *InputCount ) ;
	gotoxy (20 , 12) ;
	printf ( "Wrong Input     : %10d letters" , WrongInput ) ;
	gotoxy (20 , 14) ;
	printf ( "Accuracy        : %10.2f %%" , Accuracy) ;
	gotoxy (20 , 16) ;
	printf ( "Speed           : %10.2f wpm (words per minute)" , Speed) ;
	gotoxy (26 , 25) ;
	printf ( "Press ESC key to exit") ;

	//wait until the user press ESC
	while (    tolower(getch ())  != ESC  ) {}
}






//it is for traning mode
void TrainMode ()
{
	int CorrectInputCount = 0 , InputCount = 0 ;

	TimeUsed = 0 ;

	TrainInitial () ;

	//Once the user pressed ESC , it will end TrainProcess
	while (ExitTrainProcess == FALSE)
	{
		TrainProcess ( &CorrectInputCount , &InputCount) ;
	}

	//Check if the user typed in train mode
	TrainCheckIfTyped ( &CorrectInputCount , &InputCount ) ;
}

void TrainInitial ()
{

	char ch ;
	clrscr () ;

	ExitTrainUserInputWord = FALSE ;
	ExitTrainProcess = FALSE ;

	gotoxy (28 , 12) ;
	printf ("1. I want to train single letters.") ;
	gotoxy (28 , 14) ;
	printf ("2. I want to train words.") ;
	gotoxy (28 , 16) ;
	printf ("Please press either 1 , 2 or ESC : ") ;
	while (    (ch = getch ())   !=   '1'  &&   ch   !=   '2'
			&&	ch   !=   ESC  )
	{}

	if (ch == ESC)
	{
		ExitTrainProcess = TRUE ;
	}
	else
	{
		if (ch == '1')
		{
			TrainLetter () ;
		}
		else
		{
			TrainWord () ;
		}
	}
}

void TrainLetter ()
{
	char ch ;
	int temp ;

	ChoiceLetter = TRUE ;

	ExitTrainProcess = FALSE ;

	MiddleRow = FALSE ;
	UpperRow  = FALSE ;
	LowerRow  = FALSE ;
	NumberRow = FALSE ;

	clrscr () ;

	gotoxy (30 , 8) ;
	printf ("Do you want to train :") ;
//=======================================================================
	gotoxy (30 , wherey () + 2) ;
	printf ("Middle row? : ") ;
	while (  tolower(ch = getch () ) != Y  &&  tolower(ch) != N  )
	{
		gotoxy (30 , wherey () + 10) ;
		printf ("please input y or n only!") ;
		gotoxy (30 , wherey () - 10) ;
		printf ("Middle row? : ") ;
	}
	if (tolower (ch) == Y)                                //ask the user if
		MiddleRow = TRUE ;		    //he wants
	printf ("%c" , ch) ;                        //to train Middle row.

	gotoxy (30 , 20) ;
	delline () ;
	gotoxy (30 , wherey () - 10) ;
//=======================================================================
	gotoxy (30 , wherey() + 2) ;
	printf ("Upper row?  : ") ;
	while (  tolower(ch = getch () ) != Y  &&  tolower(ch) != N  )
	{
		gotoxy (30 , wherey () + 8) ;
		printf ("please input y or n only!") ;
		gotoxy (30 , wherey () - 8) ;
		printf ("Upper row?  : ") ;
	}
	if (tolower(ch) == Y)
		UpperRow = TRUE ;                     //upper row.
	printf ("%c" , ch) ;

	gotoxy (30 , 20) ;
	delline () ;
	gotoxy (30 , wherey () - 8) ;
//=======================================================================
	gotoxy (30 , wherey () + 2) ;
	printf ("Lower row?  : ") ;
	while (  tolower(ch = getch () ) != Y  &&  tolower(ch) != N  )
	{
		gotoxy (30 , wherey () + 6) ;
		printf ("please input y or n only!") ;
		gotoxy (30 , wherey () - 6) ;
		printf ("Lower row?  : ") ;
	}
	if (tolower(ch) == Y)                                      //lower row.
		LowerRow = TRUE ;
	printf ("%c" , ch) ;

	gotoxy (30 , 20) ;
	delline () ;
	gotoxy (30 , wherey () - 6) ;

//=======================================================================
	gotoxy (30 , wherey () + 2) ;
	printf ("Number row? : ") ;
	while (  tolower(ch = getch () ) != Y  &&  tolower(ch) != N  )
	{
		gotoxy (30 , wherey () + 4) ;
		printf ("please input y or n only!") ;
		gotoxy (30 , wherey () - 4) ;
		printf ("Number row? : ") ;
	}
	if (tolower(ch) == Y)                                       //number row.
		NumberRow = TRUE ;
	printf ("%c" , ch) ;

	gotoxy (30 , 20) ;
	delline () ;
	gotoxy (30 , wherey () - 4) ;
//======================================================================
	if ( MiddleRow + UpperRow + LowerRow + NumberRow == 0 )
	{
		ExitTrainProcess = TRUE ;	 //if the user has not
		ExitTrainUserInput = TRUE ;	 //chosen any row to practise,
	}					 //it will exit Trainmode.

	gotoxy (1 , 25) ;
	printf ("Press any key when ready.") ;	//wait for the user to press
	getch() ;				//any key.
}

void TrainWord ()
{
	ChoiceLetter = FALSE ;
}

void TrainProcess (int *CorrectInputCount , int *InputCount)
{
	char InputLetter ;

	if (ChoiceLetter == TRUE)
	{
		SelectLetter (InputLetter , CorrectInputCount , InputCount) ;
	}
	else
	{
		SelectWord (CorrectInputCount , InputCount) ;
	}
}

void SelectLetter (char InputLetter , int *CorrectInputCount , int *InputCount)
{
	ExitTrainUserInput = FALSE ;

	PrintLetter () ;

	do	//Once the user press ESC key , it will exit Train mode
	{
		TrainUserInput ( InputLetter , CorrectInputCount , InputCount ) ;

	} while ( ExitTrainUserInput == FALSE ) ;
}

void PrintLetter ()
{
	//Convert the four choices into binary number to analyst
	int RowChoice = 1000*MiddleRow + 100*UpperRow
				 + 10*LowerRow + NumberRow ;

	//make a random number to choose a random row.
	int RandomRow = random (MiddleRow + UpperRow
				 + LowerRow + NumberRow) + 1 ;

	int RandomUpperLetter    ,    RandomMiddleLetter ,
	    RandomNumberLetter	 ,    RandomLowerLetter ;

	RandomNumberLetter = random (10) ;	//from 0 to 9

	RandomUpperLetter = random (10) ;	//generate a random
						//from 0 to 9

	RandomMiddleLetter = random (9) ;	// from 0 to 8

	RandomLowerLetter = random (7) ;	//from 0 to 6

	switch (RowChoice)
	{
/*number only*/	case    1 :
			RequiredLetter=NumberRowLetters[RandomNumberLetter]; //from 0 to 9
			break ;
/*lower only*/	case   10 :
			RequiredLetter=LowerRowLetters[RandomLowerLetter];
			break ;
		case   11 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=LowerRowLetters[RandomLowerLetter];
					break ;
				case 2 :
					RequiredLetter=NumberRowLetters[RandomNumberLetter];
					break ;
			}
			break ;
/*upper only*/	case  100 :
			RequiredLetter=UpperRowLetters[RandomUpperLetter];
			break ;
		case  101 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=UpperRowLetters[RandomUpperLetter];
					break ;
				case 2 :
					RequiredLetter=NumberRowLetters[RandomNumberLetter];
					break ;
			}
			break ;
		case  110 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=UpperRowLetters[RandomUpperLetter];
					break ;
				case 2 :
					RequiredLetter=LowerRowLetters[RandomLowerLetter];
					break ;
			}
			break ;
		case  111 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=UpperRowLetters[RandomUpperLetter];
					break ;
				case 2 :
					RequiredLetter=LowerRowLetters[RandomLowerLetter];
					break ;
				case 3 :
					RequiredLetter=NumberRowLetters[RandomNumberLetter];
					break ;
			}
			break ;
/*middle only*/	case 1000 :
			RequiredLetter=MiddleRowLetters[RandomMiddleLetter];
			break ;
		case 1001 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=MiddleRowLetters[RandomMiddleLetter];
					break ;
				case 2 :
					RequiredLetter=NumberRowLetters[RandomNumberLetter];
					break ;
			}
			break ;
		case 1010 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=MiddleRowLetters[RandomMiddleLetter];
					break ;
				case 2 :
					RequiredLetter=LowerRowLetters[RandomLowerLetter];
					break ;
			}
			break ;
		case 1011 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=MiddleRowLetters[RandomMiddleLetter];
					break ;
				case 2 :
					RequiredLetter=LowerRowLetters[RandomLowerLetter];
					break ;
				case 3 :
					RequiredLetter=NumberRowLetters[RandomNumberLetter];
					break ;
			}
			break ;
		case 1100 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=MiddleRowLetters[RandomMiddleLetter];
					break ;
				case 2 :
					RequiredLetter=UpperRowLetters[RandomUpperLetter];
					break ;
			}
			break ;
		case 1101 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=MiddleRowLetters[RandomMiddleLetter];
					break ;
				case 2 :
					RequiredLetter=UpperRowLetters[RandomUpperLetter];
					break ;
				case 3 :
					RequiredLetter=NumberRowLetters[RandomNumberLetter];
					break ;
			}
			break ;
		case 1110 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=MiddleRowLetters[RandomMiddleLetter];
					break ;
				case 2 :
					RequiredLetter=UpperRowLetters[RandomUpperLetter];
					break ;
				case 3 :
					RequiredLetter=LowerRowLetters[RandomLowerLetter];
					break ;
			}
			break ;
/*All the rows*/
		case 1111 :
			switch (RandomRow)
			{
				case 1 :
					RequiredLetter=MiddleRowLetters[RandomMiddleLetter];
					break ;
				case 2 :
					RequiredLetter=UpperRowLetters[RandomUpperLetter];
					break ;
				case 3 :
					RequiredLetter=LowerRowLetters[RandomLowerLetter];
					break ;
				case 4 :
					RequiredLetter=NumberRowLetters[RandomNumberLetter];
					break ;
			}
			break ;
		default :
			printf("\nYou are at the default position") ;
	}

	clrscr () ;

	gotoxy (1 , 19) ;
	//Show all the choices the user has chosen
	printf ("You are praticing :") ;
	if (MiddleRow)
		printf ("\nMiddle row.") ;
	if (UpperRow)
		printf ("\nUpper row.") ;
	if (LowerRow)
		printf ("\nLower row.") ;
	if (NumberRow)
		printf ("\nNumber row.") ;
	gotoxy (30 , 25) ;
	printf ("Press ESC to quit.") ;

	gotoxy (40 , 12) ;
	printf ("%c" , RequiredLetter) ;
	TimeStart = clock () ;	//record the current time as start time
}

void TrainUserInput (char InputLetter , int *CorrectInputCount , int *InputCount)
{
	gotoxy (40 , 13) ;

	InputLetter = getch () ; //wait for the user to input choice

	if (InputLetter == ESC)  //Pressed ESC key
	{
		EndTrainMode () ;
	}
	else
	{
		if (InputLetter == RequiredLetter)	 //Typed correctly
		{
			TrainOutputLetter (InputLetter , CorrectInputCount , InputCount) ;
		}
		else					//Typed wrongly
		{
			(*InputCount) ++ ;
		}
	}

}

void EndTrainMode ()
{
	ExitTrainUserInput = TRUE ;
	ExitTrainProcess   = TRUE ;
}

void TrainOutputLetter (int InputLetter , int *CorrectInputCount , int *InputCount)
{
	TimeStop = clock () ;	//Record the current time as stop time

	(*CorrectInputCount) ++ ;

	(*InputCount) ++ ;

	printf ("%c" , InputLetter) ;

	ExitTrainUserInput = TRUE ;

	//Accumulate the time used of the user to type many letters
	TimeUsed = TimeUsed + (TimeStop - TimeStart) / CLK_TCK  ;

}

void SelectWord (int *CorrectInputCount , int *InputCount)
{
	char Word[20] ;
	int Count ;

	ExitTrainUserInputWord = FALSE ;

	for (Count = 0 ; Count < 20 ; Count++)
	{
		Word[Count] = 0 ;
	}

	PrintWord (Word) ;

	do
	{
		TrainUserInputWord (Word , CorrectInputCount , InputCount) ;

	} while (  (ExitTrainUserInputWord == FALSE)  &&  (EndOfWord == FALSE)   ) ;

}

void PrintWord (char *Word)
{
	FILE *FilePointer ;

	long int Random = random (20000) , Count = 0 ;

	FilePointer = fopen ("words.txt" , "r") ;

	clrscr () ;

	if (FilePointer == NULL)
	{
		printf ("Cannot open the file 'words.txt'."
			"\nPlease copy it into the directory.") ;
		ExitTrainUserInputWord = TRUE ;
		ExitTrainProcess = TRUE ;
	}
	else
	{
		fseek (FilePointer , 16 * Random , SEEK_SET) ;

		while (	  (Word[Count] = fgetc(FilePointer))  !=  ' '
			&&   (Word[Count++]   !=   '\n')	)
		{}

		gotoxy (35 , 12) ;
		for (Count = 0 ; Count < 20 ; Count++)
		{
			printf ( "%c" , Word[Count] ) ;
		}

		gotoxy (1 , 25) ;
		printf ("Press any key to start!") ;
		getch () ;	//wait for the user to press any key

		delline () ;	//delete all the content of the current line

		gotoxy (35 , 13) ;

		EndOfWord = FALSE ;

		fclose (FilePointer) ;
	}
}

void TrainUserInputWord (char *Word , int *CorrectInputCount
				    , int *InputCount)
{
	char InputLetter ;

	static Count = 0 ;

	int x = wherex () , y = wherey () ;

	gotoxy (27 , 19) ;
		printf ("Time used     :   ") ;
	gotoxy (27 , 20) ;
		printf ("Accuracy      :   ") ;
	gotoxy (27 , 21) ;
		printf ("Speed         :   ") ;
	gotoxy (27 , 22) ;
		printf ("Wrong letters :   ") ;
	gotoxy (27 , 23) ;
		printf ("Typed letters :   ") ;
	gotoxy (x , y) ;

while ( !kbhit() )
{
	if ( *InputCount > 0 )
	{
		double Speed ;

		float Accuracy = (float) *CorrectInputCount * 100 / *InputCount ;

		int WrongInput = *InputCount - *CorrectInputCount ;

		TimeStop = clock () ;
		TimeUsed = TimeUsed + (TimeStop - TimeStart) / CLK_TCK ;
		Speed = *CorrectInputCount / 5 / (TimeUsed / 60) ;
		TimeStart = clock () ;
		gotoxy (45 , 19) ;
			printf ("%10.2f seconds" , TimeUsed) ;
		gotoxy (45 , 20) ;
			printf ("%10.2f %%" , Accuracy) ;
		gotoxy (45 , 21) ;
			printf ("%10.2f wpm" , Speed) ;
		gotoxy (45 , 22) ;
			printf ("%10d letters" , WrongInput) ;
		gotoxy (45 , 23) ;
			printf ("%10d letters" , *InputCount) ;
		gotoxy (x , y) ;
		delay (100) ;
	}
}
	InputLetter = getch () ;

	if (InputLetter == ESC)
	{
		EndTrainWordMode() ;
		Count = 0 ;
	}
	else
	{
		if (Word[Count + 1] == 0)
		{
			EndOfWord = TRUE ;
			Count = 0 ;
		}
		else
		{
			if (InputLetter == Word[Count] )
			{
				TrainOutputWord (CorrectInputCount , InputCount);
				gotoxy (x , y) ;
				printf ("%c" , InputLetter) ;
				Count++ ;
			}
			else
			{
				(*InputCount) ++ ;
			}
		}
	}
}

void EndTrainWordMode ()
{
	ExitTrainUserInputWord = TRUE ;
	ExitTrainProcess = TRUE ;
}

void TrainOutputWord (int *CorrectInputCount , int *InputCount)
{
	(*CorrectInputCount) ++ ;
	(*InputCount) ++ ;
}

void TrainCheckIfTyped (int *CorrectInputCount , int *InputCount)
{
	if (*InputCount)	//if the user has typed some letters
	{
		TrainReport (CorrectInputCount , InputCount) ;
	}
}

void TrainReport (int *CorrectInputCount , int *InputCount)
{
	double Accuracy = *CorrectInputCount * 100 / *InputCount ;

	double Speed = *CorrectInputCount / 5 / (TimeUsed / 60) ;

	int WrongInput = *InputCount - *CorrectInputCount ;

	clrscr () ;

	//Display the report
	gotoxy ( 20 , 8 ) ;
	printf ( "Time used       : %10.2f seconds per letter." ,
			 (float) TimeUsed / *CorrectInputCount) ;

	gotoxy ( 20 , 10 ) ;
	printf ( "Character Typed : %10d letters" , *InputCount) ;
	gotoxy ( 20 , 12 ) ;
	printf ( "WrongInput      : %10d letters" , WrongInput) ;
	gotoxy ( 20 , 14 ) ;
	printf ( "Accuracy        : %10.2f %%" , Accuracy) ;
	gotoxy ( 20 , 16 ) ;
	printf ( "Speed           : %10.2f wpm (words per minute)" , Speed) ;

	gotoxy ( 20 , 25 ) ;

	printf ( "Press any key (except ESC) to exit") ; //wait for the user to press

	while ( getch () == ESC ) {}		//any key to exit
}



//It is for Quite confirmation
void QuitConfirm ()
{
	char QuitChoice ;
	clrscr () ;
	gotoxy (30 , 12) ;
	printf ("Really want to quit? (y/n) : ") ;
	//wait for the user to press y or n
	if ((QuitChoice = getch ()) != ESC)
	{
		while ((tolower(QuitChoice)    !=   Y )
				&&   ( tolower(QuitChoice) != N)    )
		{
			clrscr () ;
			gotoxy (25 , 12) ;
			printf ("Please press 'y' or 'n' only!") ;
			gotoxy (25 , 14) ;
			printf ("Really want to quit? (y/n) : ") ;
			QuitChoice = getch () ;
		}
	}

	printf ("%c" , QuitChoice) ;

	if (tolower(QuitChoice) == Y)      //if the user pressed y ,
	{				   //then exit the program
		EndBody () ;
	}
}

void EndBody()
{
	ExitProgram = TRUE ;
}

void EndProgram ()
{

}