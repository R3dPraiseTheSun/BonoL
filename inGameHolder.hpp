#ifndef INGAMEHOLDER_HPP_INCLUDED
#define INGAMEHOLDER_HPP_INCLUDED

#include<windows.h>

#include <iostream>
#include <graphics.h>
#include <string.h>
#include "Draw.hpp"
#include "Logics.hpp"
#include "Pozitii.hpp"
#include "MovePiece.hpp"
#include "AI.hpp"

#define latura 100

int Table[6][6];
int TableForUndoButton[6][6];
int TableForUndoButton2[6][6];
int TableLastGame[6][6];


int matriceSecundara[6][6];
int playerMoved=0;
int playerNumber;
//int k=0;
bool getClick=false, coinM=false;

bool checkIfTheSameMatrix(int M1[6][6], int M2[6][6]);

void setMatrixBorder();
void color(int i, int j, int culoare);
void initializarePozitiiPiese();
void WitchTurn();
void CheckBackButtonPress();
void movePiece();
void gameOver(int playerNumber);
void drawColorPlayerTurn(bool playerTurn);
void drawBackButton();
void drawLines();
void SkipAI_Select(bool option);

void Draw_Undo_Button();

bool checkSkipButtonPress();
bool checkMatrixes();


//bool moveCoin(bool coinM, bool getClick, int Table[6][6]);

//playerOneTurn e rosu
bool playerOneTurn=true;

bool checkMatrixes()
{
    return checkIfTheSameMatrix(Table,matriceSecundara);
}

void changePlayer()
{
    std::cout<<"CHANGED PLAYER!"<<std::endl;
    playerOneTurn=!playerOneTurn;
}

void Update()
{
    //std::cout<<"Update";
    for(int i=1;i<5;i++)
    {
        for(int j=1;j<5;j++)
        {
            if(Table[i][j]==-1)
                color(i,j,2);
            else if(Table[i][j]==1)
                    color(i,j,1);
            else if(Table[i][j]==2)
                    color(i,j,4);
            else
                color(i,j,0);
        }
    }
    drawColorPlayerTurn(playerOneTurn);
    //CheckBackButtonPress();
    //checkSkipButtonPress();
    drawBackButton();
}

void cleanPlayer(int playerNumber)
{
    //std::cout<<"CLEANING FOR NEXT MOVE.. "<<std::endl;
    if(playerNumber==1) setfillstyle(SOLID_FILL,LIGHTBLUE);
        else setfillstyle(SOLID_FILL,LIGHTRED);
    for(int i=1;i<5;i++)
        for(int j=1;j<5;j++)
            if(Table[i][j]==playerNumber)
                {Table[i][j]=0; fillspace(i,j);}

}



void copiazaMatricea(int matriceContainer[6][6],int matriceInitiala[6][6])
{
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
            matriceContainer[i][j]=matriceInitiala[i][j];
}

void initiereCopiazaMatricea(bool tableToAux)
{
    if(tableToAux)
        copiazaMatricea(matriceSecundara,Table);
    else
        copiazaMatricea(Table,matriceSecundara);
}


bool FreezeGame=false;

int AI_difficulty;
bool AI_selection=true;
bool didUndo=false;
bool FirstTime=true;

void startGame()
{
      //AI Select
    if(!AI_selection)
        switch(AI_Select())
        {
        case 1:
            //std::cout<<"EASY!"<<std::endl;
            AI_difficulty=1;
            break;
        case 2:
            //std::cout<<"HARD!"<<std::endl;
            AI_difficulty=2;
            break;
        default:
            //std::cout<<"HUMAN!"<<std::endl;
            AI_difficulty=0;
            break;
        }

    drawLines();
    drawBackButton();

    // marginea neagra din fereastra
    setMatrixBorder();
startAgain:
    if(FirstTime)
        initializarePozitiiPiese();
    else
        copiazaMatricea(Table,TableLastGame);
    Update();


    FreezeGame=false;


    while(1)
    {

        if(!FreezeGame)
        {
            copiazaMatricea(TableForUndoButton,matriceSecundara);
            WitchTurn();
            copiazaMatricea(TableForUndoButton2,TableForUndoButton);
        }
        else
        {
            gameOver(playerNumber);
            CheckBackButtonPress();
        }
    }

}

void apelGameOver()

{
    gameOver(playerNumber);
}

void WitchTurn()
{
    //Draw_Undo_Button();
undo:
    if (playerOneTurn==true)
        playerNumber=1;
    else
        playerNumber=2;

    didUndo=false;
    copiazaMatricea(matriceSecundara,Table);
    //for(int i=0;i<6;i++) {for(int j=0;j<6;j++) std::cout<<matriceSecundara[i][j]<<" "; std::cout<<std::endl;} std::cout<<std::endl;
    cleanPlayer(playerNumber);

    //std::cout<<FindL(0,Table)<<" POZITII RAMASE PENTRU PLAYER "<<playerNumber<<std::endl;
    if(FindL(0,Table)<1)
    {

        copiazaMatricea(Table,matriceSecundara);
        Update();
        gameOver(playerNumber);
        FreezeGame=true;
    }
    else
    {

        getClick=false, coinM=false;
        movePiece(playerNumber,Table,matriceSecundara,playerMoved,0,AI_difficulty);
        if(didUndo) goto undo;
        moveCoin(coinM,getClick,Table,AI_difficulty,playerNumber);
        //Draw_Undo_Button();

        Update();
    }
}

void  initializarePozitiiPiese()
{
    playerOneTurn=true;
    FirstTime=true;
    for(int i=1;i<5;i++)
        for(int j=1;j<5;j++)
            Table[i][j]=0;
    //piese verzi
    Table[1][1]=-1;
    Table[4][4]=-1;
    //player1
    Table[2][2]=1;
    Table[3][2]=1;
    Table[4][2]=1;
    Table[4][3]=1;
    //player2
    Table[1][2]=2;
    Table[1][3]=2;
    Table[2][3]=2;
    Table[3][3]=2;

}
void setMatrixBorder()
{
    for(int i=0;i<=5;i++)
    {
        for(int j=0;j<=5;j++)
        {
            if(i==0 || i==5) Table[i][j]=-2;
            if(j==0 || j==5) Table[i][j]=-2;
        }
    }
}

void SkipAI_Select(bool option)
{
    AI_selection=option;
}

void Undo()
{
    if(!AI_difficulty)
    {
        copiazaMatricea(Table,TableForUndoButton);
        changePlayer();
    }
    else
        copiazaMatricea(Table,TableForUndoButton2);



    Update();

    didUndo=true;
}


void FirstTimeOp(bool option)
{
    copiazaMatricea(TableLastGame,matriceSecundara);
    FirstTime=option;
   // goto startAgain;
}

#endif // INGAMEHOLDER_HPP_INCLUDED
