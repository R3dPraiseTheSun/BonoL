#ifndef AI_HPP_INCLUDED
#define AI_HPP_INCLUDED

#include "Pozitii.hpp"
#include "Logics.hpp"
#include "Draw.hpp"
#include "inGameHolder.hpp"

#define margine 150
#define margine2 20

int width = latura*6+500, height = latura*6;

int AI_Table[6][6];
int AI_TableAux[6][6];

void giveAI_LastPosition(int NormalTable[6][6],int TablaCuPiesa[6][6]);
void getAIPosition(int NormalTable[6][6]);
void SimpleAI(int AI_Table[6][6]);
void HardAI(int AI_Table[6][6]);
int AI_Select();

//from GameHolder
void copiazaMatricea(int M1[6][6],int M2[6][6]);
void cleanPlayer(int playerNumber);
void cleanPlayerAI();

//from Draw
void Draw_Select_Menu(int pointsAI_Easy[], int pointsAI_Hard[], int pointsHuman[]);

//from Logics
int CheckAI_Select(int pointsAI_Easy[], int pointsAI_Hard[], int pointsHuman[]);
void CheckBackButtonPress();
bool validPosAI(int a[6][6],int i,int j,int nr);
bool checkIfTheSameMatrix(int M1[6][6], int M2[6][6]);



int pointsAI_Easy[]={width/2-margine,height/2-margine/4-margine, width/2+margine,height/2-margine/4-margine, width/2+margine,height/2+margine/4-margine, width/2-margine,height/2+margine/4-margine, width/2-margine,height/2-margine/4-margine};
int pointsAI_Hard[]={width/2-margine,height/2-margine/4, width/2+margine,height/2-margine/4, width/2+margine,height/2+margine/4, width/2-margine,height/2+margine/4, width/2-margine,height/2-margine/4};
int pointsHuman[]={width/2-margine,height/2-margine/4+margine, width/2+margine,height/2-margine/4+margine, width/2+margine,height/2+margine/4+margine, width/2-margine,height/2+margine/4+margine, width/2-margine,height/2-margine/4+margine};

int AI_Select()
{
    clearviewport();
    return CheckAI_Select(pointsAI_Easy, pointsAI_Hard, pointsHuman);
}

bool gasit=false;

void cleanPlayerAI()
{
    setfillstyle(SOLID_FILL,LIGHTRED);
    for(int i=1;i<5;i++)
        for(int j=1;j<5;j++)
            if(AI_Table[i][j]==1)
                {AI_Table[i][j]=0; fillspace(i,j);}
}

void SimpleAI(int AI_Table[6][6])
{
    int M0[6][6];
    copiazaMatricea(M0,AI_Table);
    //for(int i=0;i<6;i++) {for(int j=0;j<6;j++) std::cout<<M0[i][j]<<" "; std::cout<<std::endl;} std::cout<<std::endl;
backAI:
    int i=rand()%4+1,j=rand()%4+1;
    while(!AI_Table[i][j]==0)
        i=rand()%4+1,j=rand()%4+1;

    if(!validPosAI(AI_Table,i,j,0))
        goto backAI;

    if(!checkIfTheSameMatrix(AI_TableAux,AI_Table))
        copiazaMatricea(AI_TableAux,AI_Table);
    else
    {
        copiazaMatricea(AI_Table,M0);
        goto backAI;
    }
}

void HardAI(int AI_Table[6][6])
{
    int M0[6][6];
    int i,j,pozitiiMinime=300,pozitii, AI_HardTable[6][6],AI_HardTable_C1[6][6],AI_HardTable_C2[6][6];
    int AI_AuxTable[6][6],AI_AuxTablePiecePreserve[6][6];
    copiazaMatricea(M0,AI_Table);
    for(i=1;i<5;i++)
    {
        for(j=1;j<5;j++)
        {
            if(validPosAI(AI_Table,i,j,0))
            {
                if(!checkIfTheSameMatrix(AI_TableAux,AI_Table))
                {
                    copiazaMatricea(AI_AuxTable,AI_Table);
                    std::cout<<"POZITIA GASITA INAINTE DE COIN MOVEMENT......."<<std::endl;
                    for(int iN=1;iN<5;iN++) {for(int jN=1;jN<5;jN++) std::cout<<AI_AuxTable[iN][jN]<<" "; std::cout<<std::endl;} std::cout<<std::endl;
                    //gasim coins
                    int iC,jC,minimCoin1=300,minimCoin2=300;
                    int Coin[4]; Coin[1]=-1;
                    for(iC=1;iC<5;iC++)
                    {
                        for(jC=1;jC<5;jC++)
                        {
                            if(AI_Table[iC][jC]==-1)
                            {
                                if(Coin[1]==-1)
                                    Coin[0]=iC,Coin[1]=jC;
                                else
                                    Coin[2]=iC,Coin[3]=jC;
                            }
                        }
                    }

                    //mutam in cea mai buna pozitie Coin1
                    int pozitiiCoin1;
                    AI_Table[Coin[0]][Coin[1]]=0;
                    for(iC=1;iC<5;iC++)
                    {
                        for(jC=1;jC<5;jC++)
                        {
                            if(AI_Table[iC][jC]==0)
                            {
                                AI_Table[iC][jC]=-1;
                                copiazaMatricea(AI_AuxTablePiecePreserve,AI_Table);
                                cleanPlayerAI();
                                pozitiiCoin1=FindL(0,AI_Table);
                                std::cout<<pozitiiCoin1<<" GASITE IN ITERATIA "<<iC<<" "<<jC<<std::endl;
                                if(minimCoin1>pozitiiCoin1)
                                {

                                    minimCoin1=pozitiiCoin1;
                                    //std::cout<<minimCoin1<<" pozitii ramase pe Coin1"<<std::endl;
                                    copiazaMatricea(AI_HardTable_C1,AI_AuxTablePiecePreserve);
                                }
                                copiazaMatricea(AI_Table,AI_AuxTable);
                                AI_Table[Coin[0]][Coin[1]]=0;
                            }
                        }
                    }

                    copiazaMatricea(AI_Table,AI_AuxTable);

                    //mutam in cea mai buna pozitie Coin2
                    int pozitiiCoin2;

                    AI_Table[Coin[2]][Coin[3]]=0;

                    for(iC=1;iC<5;iC++)
                    {
                        for(jC=1;jC<5;jC++)
                        {
                            if(AI_Table[iC][jC]==0)
                            {
                                AI_Table[iC][jC]=-1;
                                copiazaMatricea(AI_AuxTablePiecePreserve,AI_Table);
                                cleanPlayerAI();
                                pozitiiCoin2=FindL(0,AI_Table);
                                if(minimCoin2>pozitiiCoin2)
                                {

                                    minimCoin2=pozitiiCoin2;
                                    std::cout<<minimCoin2<<" pozitii ramase pe Coin2"<<std::endl;
                                    copiazaMatricea(AI_HardTable_C2,AI_AuxTablePiecePreserve);
                                }
                                copiazaMatricea(AI_Table,AI_AuxTable);
                                AI_Table[Coin[2]][Coin[3]]=0;
                            }
                        }
                    }

                    copiazaMatricea(AI_Table,AI_AuxTable);


                    //verificam minim
                    if(minimCoin1<minimCoin2) copiazaMatricea(AI_Table,AI_HardTable_C1);
                    else copiazaMatricea(AI_Table,AI_HardTable_C2);



                    copiazaMatricea(AI_AuxTablePiecePreserve,AI_Table);
                    cleanPlayerAI();
                    pozitii = FindL(0,AI_Table);
                    copiazaMatricea(AI_Table,AI_AuxTablePiecePreserve);


                    if(pozitiiMinime>pozitii)
                    {
                        pozitiiMinime=pozitii;
                        std::cout<<pozitiiMinime<<" MINIME.................................."<<std::endl;
                        copiazaMatricea(AI_HardTable,AI_Table);
                    }
                    copiazaMatricea(AI_Table,M0);
                }
                else
                    copiazaMatricea(AI_Table,M0);
            }
        }
    }
   // std::cout<<"COIN 1 POSITION"<<std::endl;
   // for(int i=1;i<5;i++) {for(int j=1;j<5;j++) std::cout<<AI_HardTable_C1[i][j]<<" "; std::cout<<std::endl;} std::cout<<std::endl;
   // std::cout<<"COIN 2 POSITION"<<std::endl;
   // for(int i=1;i<5;i++) {for(int j=1;j<5;j++) std::cout<<AI_HardTable_C2[i][j]<<" "; std::cout<<std::endl;} std::cout<<std::endl;
   // std::cout<<"POZITIE FINALA"<<std::endl;
    //for(int i=1;i<5;i++) {for(int j=1;j<5;j++) std::cout<<AI_HardTable[i][j]<<" "; std::cout<<std::endl;} std::cout<<std::endl;
    copiazaMatricea(AI_Table,AI_HardTable);
}

void getAIPosition(int NormalTable[6][6],int AI_difficulty)
{
    if(AI_difficulty==1)
        SimpleAI(AI_Table);
    else if(AI_difficulty==2)
        HardAI(AI_Table);

    //update piece
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
            NormalTable[i][j]=AI_Table[i][j];
}

void giveAI_LastPosition(int NormalTable[6][6],int TablaCuPiesa[6][6])
{
    copiazaMatricea(AI_Table,NormalTable);
    copiazaMatricea(AI_TableAux,TablaCuPiesa);
    //for(int i=0;i<6;i++) {for(int j=0;j<6;j++) std::cout<<AI_Table[i][j]<<" "; std::cout<<std::endl;} std::cout<<std::endl;
    //for(int i=0;i<6;i++) {for(int j=0;j<6;j++) std::cout<<AI_TableAux[i][j]<<" "; std::cout<<std::endl;} std::cout<<std::endl;
}


#endif //AI_HPP_INCLUDED
