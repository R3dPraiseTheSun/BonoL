#ifndef MOVEPIECE_HPP_INCLUDED
#define MOVEPIECE_HPP_INCLUDED

#include "Draw.hpp"
#include "Logics.hpp"
#include "inGameHolder.hpp"

#define latura 100

bool validPos(int a[6][6],int i,int j,int nr);
bool checkMatrixes();


void fillspace(int i,int j);
void changePlayer();
void Update();
void initiereCopiazaMatricea(bool tableToAux);
void cleanPlayer(int playerNumber);
void CheckBackButtonPress();
void moveCoin2(int getClick);
void moveCoin(int coinM);
void draw_timer();

void FirstTimeOp(bool option);

void Draw_Undo_Button();
void Hide_Undo_Button();

void drawSkipButton();
void hideSkipButton();

bool checkUndoIfPressed();

bool checkSkipButtonPress();

void getAIPosition(int NormalTable[6][6],int AI_difficulty);
void giveAI_LastPosition(int NormalTable[6][6],int TablaCuPiesa[6][6]);

int startPosx=-1, startPosy=-1;

void resetTime();
bool timeReset=true;
bool firstStart=true;


void movePiece(int playerNumber,int Table[6][6],int matriceSecundara[6][6],int PlayerMoved,int k,int AI_difficulty)
{
    if(firstStart==true)
    {
        resetTime();
        firstStart=false;
    }
    //if(checkLastGame()) FirstTimeOp(false);
redoFunc:
    if(playerNumber==1) setfillstyle(SOLID_FILL,BLUE);
    else setfillstyle(SOLID_FILL,RED);
    while(!PlayerMoved)
    {
        if(timeReset==true)
        {
            timeReset=false;
            resetTime();
        }
        draw_timer();
        CheckBackButtonPress();
        if(checkUndoIfPressed()) goto out;
        if(!AI_difficulty)
        {
        human:
            checkUndoIfPressed();
            int x=mousex(), y=mousey();
            //std::cout<<"MOVE PIECE!"<<std::endl;
            if(ismouseclick(WM_LBUTTONDBLCLK))
            {
                if(x<latura*6 && y<latura*6 && y>latura && x>latura)
                {
                    if(Table[y/latura][x/latura]==0)
                    {

                        if(startPosx==-1 && startPosy==-1) startPosx=x/latura,startPosy=y/latura;
                        Table[y/latura][x/latura]=playerNumber;
                        //std::cout<<k<<std::endl;
                        k++;
                        PlaySound("BoopEffect.wav",0,SND_ASYNC);
                        if(playerNumber==1)
                            setfillstyle(SOLID_FILL,BLUE);
                        else
                            setfillstyle(SOLID_FILL,RED);
                        fillspace(y/latura,x/latura);
                        if(k==4)
                        {
                            if(validPos(Table,startPosy,startPosx,playerNumber) && !checkMatrixes())
                            {
                                Hide_Undo_Button();
                                PlayerMoved=1;
                                Update();
                                startPosx=-1, startPosy=-1;
                            }
                            else
                            {
                                initiereCopiazaMatricea(false);
                                Update();
                                k=0;
                                PlaySound("InvalidMove.wav",0,SND_ASYNC);
                                //std::cout<<"Invalid move"<<std::endl;
                                clearmouseclick(WM_LBUTTONDBLCLK);
                                goto redoFuncStep;
                            }
                            //clearmouseclick(WM_LBUTTONDBLCLK);
                            Update();
                            drawSkipButton();
                            //Draw_Undo_Button();
                        }
                    }
                }
            }
        }
        else
        {
            if(playerNumber==1)
                goto human;
            Update();
            giveAI_LastPosition(Table,matriceSecundara);
            getAIPosition(Table,AI_difficulty);
            PlayerMoved=1;
            changePlayer();
            Update();
        }
    }
    goto out;
redoFuncStep:
    initiereCopiazaMatricea(true);
    startPosx=-1; startPosy=-1;
    cleanPlayer(playerNumber);
    goto redoFunc;
out:;
}

void moveCoin2(bool getClick,int Table[6][6])
{
    //std::cout<<"DROP COIN!"<<std::endl;
    int x,y;
    while(!getClick)
    {
        draw_timer();
        CheckBackButtonPress();
        //Update();
        clearmouseclick(WM_LBUTTONDOWN);
        getmouseclick(WM_LBUTTONDBLCLK,x,y);
        if(x>=latura&&x<=latura*5 && y>=latura && y<=latura*5)
        {
            if(Table[y/latura][x/latura]==0)
            {
                PlaySound("BoopEffect.wav",0,SND_ASYNC);
                Table[y/latura][x/latura]=-1;
                Draw_Undo_Button();
                resetTime();
                timeReset=true;
                getClick=true;
                changePlayer();
                Update();
            }
        }
       // CheckBackButtonPress();
    }
}

void moveCoin(bool coinM,bool getClick,int Table[6][6],int AI_difficulty,int playerNumber)
{
    //std::cout<<"GET COIN!"<<std::endl;
    int x,y;
    while(!coinM)
    {
        CheckBackButtonPress();
        draw_timer();
        if(checkSkipButtonPress()) {hideSkipButton(); changePlayer(); goto out;}
        if(!AI_difficulty)
        {
            human:
                getmouseclick(WM_LBUTTONDBLCLK,x,y);
                if(Table[y/latura][x/latura]==-1)
                {
                    PlaySound("BoopEffect.wav",0,SND_ASYNC);
                    Table[y/latura][x/latura]=0;
                    hideSkipButton();
                    Update();
                    coinM=true;
                    moveCoin2(getClick,Table);
                }
        }
        else
        {
            if(playerNumber==1) goto human;
            if(AI_difficulty==2) goto out;
            coinM=true;
            int iF,jF,Coin[4]; Coin[1]=-1;
            while(Table[iF][jF]!=0)
            {
                iF=rand()%4+1;
                jF=rand()%4+1;
            }
            Table[iF][jF]=-1;

            for(int i=1;i<5;i++)
            {

                for(int j=1;j<5;j++)
                {
                    if(Table[i][j]==-1)
                    {
                        if(Coin[1]==-1)
                            Coin[0]=i,Coin[1]=j;
                        else
                            Coin[2]=i,Coin[3]=j;
                    }
                }
            }
            if(rand()%2==1)
                Table[Coin[0]][Coin[1]]=0;
            else
                Table[Coin[2]][Coin[3]]=0;
            //Update();
        }
    }
out:;
}


#endif // MOVEPIECE_HPP_INCLUDED
