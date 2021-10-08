//#include <iostream>
//#include <math.h>
//#include <unistd.h>
//#include <windows.h>
//#include <conio.h>
//#include <iostream>

//using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <time.h.>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

//RADIUS can be changed at will.
#define RADIUS  5

    ///
/// /// /// /// /// /// /// /// /// /// ///
    ///                                 ///
    /// PROJECT: Kangaroo v2.0          ///
    /// CODER: Álvaro Navarro Quijada.  ///
    /// DATE: 04/10/2021. 02:25 am.     ///
    /// SIGNATURE: RSG                  ///
    ///                                 ///
    /// /// /// /// /// /// /// /// /// //////
                                        ///

//This project is for flexing purposes only, no copyright allowed nor changing code.

//struct used for Food.
typedef struct{
    int X, Y;
    char pfp;
}DISH;

//struct used for Kangaroo. dir is the direction input (WASD), pfp is the char displayed as profile picture
//NewX and NewY are used as a 'ghost', once you move, if the ghost lands in a legit tile, the rest
//of the body will follow (X = NewX and Y = NewY), otherwise, the ghost will return to the body (NewX = X and NewY = Y).
typedef struct{
    int X, Y;
    int NewX, NewY;
    char dir;
    char pfp;
    int jumps;
}ANIMAL;

//Printing map function. Inputs are used to print each entity inside the map.
void printMap(ANIMAL Animal, DISH Food);

//Used to set up "DISH" type structures data.
void dishSetUp(DISH* Food);

//Used to set up "ANIMAL" type structures data.
void animalSetUp(ANIMAL* Animal);

//Receive an Animal, it will change it's position according to an established criteria.
void movement(ANIMAL* Animal);

//Updates inputed animal coordinates in a relative position to the Radius
void updateMap(ANIMAL Animal);

//Goes to the X Y position of the screen. Used along with printf("");
void gotoxy(int x,int y);

//Hides cursor so that it looks nicer.
void hidecursor();

//Final game screen. Pretty Shabby.
void endGame(int cont);

int main()
{
    //Kangaroo is created and set up.
    ANIMAL Kangaroo;
    animalSetUp(&Kangaroo);

    //Food is created and set up.
    DISH Food;
    dishSetUp(&Food);

    //Prints map once.
    printMap(Kangaroo, Food);

    while( ( Kangaroo.X != Food.X) || ( Kangaroo.Y != Food.Y ) ){
        //Movement of kangaroo is managed here, as well as updating location.
        movement(&Kangaroo);
    }
    usleep(300000);
    //Prints how many jumps it took to the Kangaroo to reach food.
    endGame(Kangaroo.jumps);

    return 0;
}

void printMap(ANIMAL Animal, DISH Dish){
    hidecursor();
    system("cls");
    //Don't even try to understand what's going on here, go to the next comment.
    //But just in case you want to know, it doubles the radius (diameter), and prints it
    //as a map, placing each Animal and Dish in it's correct place.
    for(int i = 0 - RADIUS ; i <= RADIUS ; i++){
        for(int j = 0 - RADIUS ; j <= RADIUS ; j++){
            if( (i*i + j*j) < RADIUS*RADIUS){ // If it's within radius
                if(Animal.X == j && Animal.Y == i){ // If it's within radius and it's an Animal...
                    printf("%c", Animal.pfp);
                }else if(Dish.X == j && Dish.Y == i){ //If it's within radius and it's a Dish...
                    printf("%c", Dish.pfp);
                }
                else
                    printf(" "); //If it's in radius but it's nothing else, print an space.
            }
            else
                printf("%c", 219); //If it's not in radius, print this char -> █ .

        }
        printf("\n");
    }
}

void dishSetUp(DISH *Dish){

    do{
        printf("Set x,y Coordinates for Dish: ");
        scanf("%d,%d", &Dish->X, &Dish->Y);
        system("cls");
    }while( (Dish->X * Dish->X) + (Dish->Y * Dish->Y) > RADIUS * RADIUS);

    Dish->pfp = 'x'; // This char -> x .
}

void animalSetUp(ANIMAL* Animal){
    srand( (unsigned)time( NULL ) );
    do{
        Animal->X = rand() % (RADIUS*2) - RADIUS;
        Animal->Y = rand() % (RADIUS*2) - RADIUS;
    }while( (Animal->X * Animal->X) + (Animal->Y * Animal->Y) > RADIUS * RADIUS);

    Animal->NewX = Animal->X;
    Animal->NewY = Animal->Y;

    Animal->pfp = (char)1; // This char -> ☺ .
    Animal->jumps = 0; // Set number of jumps to 0.

}
void movement(ANIMAL* Animal){
        Animal->dir = getch();
        switch(Animal->dir){
        case 'w':
        case 'W':
            Animal->NewY--;
            break;
        case 'a':
        case 'A':
            Animal->NewX--;
            break;
        case 's':
        case 'S':
            Animal->NewY++;
            break;
        case 'd':
        case 'D':
            Animal->NewX++;
            break;
        default:
            //This is used so that its considered and invalid movement.
            Animal->NewX = RADIUS;
            Animal->NewY = RADIUS;
            break;
        }
        // If the 'Ghost' is in a legit tile, move body to the 'Ghost'
        if((Animal->NewX * Animal->NewX) + (Animal->NewY * Animal->NewY) < RADIUS * RADIUS){
            updateMap(*Animal);
            Animal->X = Animal->NewX;
            Animal->Y = Animal->NewY;
            Animal->jumps++;
        // Otherwise, 'Ghost' returns to the body
        }else{
            gotoxy(1, RADIUS * 2 + 3); //If it's not a legit tile, do Grr :3
            printf("Grr...");

            usleep(300000);

            gotoxy(1, RADIUS * 2 + 3);
            printf("      ");

            Animal->NewX = Animal->X;
            Animal->NewY = Animal->Y;
        }


}

void endGame(int cont){
    system("cls");
    printf("\n This is some serious gourmet shit.\n\n");
    printf("It took you %d jumps.\n\n", cont);

    usleep(1000000);
}

void updateMap(ANIMAL Animal){

    gotoxy(RADIUS*2 + 3, 2);
    printf("Jumps: %d", Animal.jumps);

    gotoxy(Animal.NewX + RADIUS, Animal.NewY + RADIUS);
    printf("%c", Animal.pfp);

    gotoxy(Animal.X + RADIUS, Animal.Y + RADIUS);
    printf(" ");
}

void gotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
