#ifndef DRAW_HPP_INCLUDED
#define DRAW_HPP_INCLUDED

#include<windows.h>
#include <ctime>
#include <graphics.h>
#include <iostream>
#include <fstream>

#include <string.h>
#include "Logics.hpp"
#include "inGameHolder.hpp"
#include <string.h>

#define latura 100
#define margine 150
#define margine2 20

bool language;

struct structura
{
    char cuvant[35];
}cuvinte[20];

//int width = latura*6+500, height = latura*6;
void Draw_Select_Menu();
void gameOver(int playerNumber);
void mainMenuHolder();
void openWindow();
void color(int i,int j,int culoare);
void makeClickUndoActive(bool active);
int mainMenu(int width,int height);
void SkipAI_Select(bool option);
void coverTime();
void changePlayer();
void WitchTurn();
void apelGameOver();
int checkButtonsLanguage();

bool checkUndoIfPressed();

bool restart=false;
bool cover=false;
int timeIn;
int timeDiff;
char cuvant[1];
//bool checkUndoButton(int points[], int x, int y);

int pointsSkipButton[]=
    {
        latura*6+margine2+30,height-margine2-latura ,
        width-margine2-latura*2-20,height-margine2-latura,
        width-margine2-latura*2-20,height-margine2,
        latura*6+margine2+30,height-margine2,
        latura*6+margine2+30,height-margine2-latura
    };

   int pointsUndo[]={
        latura*6+margine2+30,latura*4-margine2,
        latura*6+500-margine2,latura*4-margine2,
        latura*6+500-margine2,latura*5-margine2*2,
        latura*6+margine2+30,latura*5-margine2*2,
        latura*6+margine2+30,latura*4-margine2
    };

bool checkButt(int points[], int x, int y);


void checkLastGame()
{
//    if(checkLastGamePressed(pointsUndo,x,y))
}

void draw_timer()
{
    int timerPosition[]=
    {
        width-latura*2.5f, height-latura*4,
        width-latura,height-latura*4,
        width-latura,height-latura*3.5f,
        width-latura*2.5f,height-latura*3.5f,
        width-latura*2.5f, height-latura*4
    };
    int present=(clock()/1000)+1;
    int dif=timeIn-present;
    if(dif<10 && cover==false)
    {
        cover=true;
        coverTime();
    }
    if(dif==-1 && restart==false)
    {
        restart=true;
        apelGameOver();
    }
    itoa(dif,cuvant,10);
    if(restart==false)
        outtextxy(width-latura*2.5f,height-latura*4,cuvant);
}

void coverTime()
{
      int timerPosition[]=
    {
        width-latura*2.5f, height-latura*4,
        width-latura,height-latura*4,
        width-latura,height-latura*3.5f,
        width-latura*2.5f,height-latura*3.5f,
        width-latura*2.5f, height-latura*4
    };
    setfillstyle(SOLID_FILL,BLACK);
    fillpoly(5,timerPosition);
   for(int i=0;i<10;i+=2)
   {
       floodfill(timerPosition[i],timerPosition[i+1],0);
   }
}

void resetTime()
{
    restart=false;
    cover=false;
    coverTime();
    timeIn=((clock()/1000)+1)+20;
}

void Draw_Select_Menu(int pointsAI_Easy[], int pointsAI_Hard[], int pointsHuman[])
{
    drawpoly(5,pointsAI_Easy);
    outtextxy(width/2-textwidth(cuvinte[4].cuvant)/2,pointsAI_Easy[1]+margine2+textheight(cuvinte[4].cuvant)/2,cuvinte[4].cuvant);
    drawpoly(5,pointsAI_Hard);
    outtextxy(width/2-textwidth(cuvinte[5].cuvant)/2,pointsAI_Hard[1]+margine2+textheight(cuvinte[5].cuvant)/2,cuvinte[5].cuvant);
    drawpoly(5,pointsHuman);
    outtextxy(width/2-textwidth(cuvinte[6].cuvant)/2,pointsHuman[1]+margine2+textheight(cuvinte[6].cuvant)/2,cuvinte[6].cuvant);
    drawBackButton();
}

void Draw_Undo_Button()
{
    outtextxy((pointsUndo[4]+pointsUndo[6])/2-textwidth(cuvinte[10].cuvant)/2,(pointsUndo[1]+pointsUndo[5])/2-textheight(cuvinte[10].cuvant)/2,cuvinte[10].cuvant);
    drawpoly(5,pointsUndo);
    makeClickUndoActive(true);
}

void Hide_Undo_Button()
{
    int pointsUndoCopy[]={
        latura*6+margine2-40,latura*4-margine2-10,
        latura*6+500-margine2+10,latura*4-margine2-10,
        latura*6+500-margine2+10,latura*5-margine2*2+10,
        latura*6+margine2-40,latura*5-margine2*2+10,
        latura*6+margine2-40,latura*4-margine2-10
    };

    setfillstyle(SOLID_FILL,BLACK);
    fillpoly(5,pointsUndoCopy);
    makeClickUndoActive(false);
   for(int i=0;i<10;i+=2)
   {
       floodfill(pointsUndoCopy[i],pointsUndoCopy[i+1],0);
   }

}

int drawButtonsLanguage()
{
    int widthText=textwidth(cuvinte[11].cuvant);
    int pointsRomana[]=
        {
            width/2-latura,height/2+latura/2-margine,
            width/2+latura,height/2+latura/2-margine,
            width/2+latura,height/2-latura/3-margine,
            width/2-latura,height/2-latura/3-margine,
            width/2-latura,height/2+latura/2-margine
        };
    outtextxy(pointsRomana[0]+latura-widthText/2,pointsRomana[1]-latura/2,cuvinte[11].cuvant);
    drawpoly(5,pointsRomana);

    int pointsEngleza[]=
        {
            width/2-latura,height/2+latura/2,
            width/2+latura,height/2+latura/2,
            width/2+latura,height/2-latura/3,
            width/2-latura,height/2-latura/3,
            width/2-latura,height/2+latura/2
        };
    outtextxy(pointsEngleza[0]+latura-textwidth(cuvinte[12].cuvant)/2,pointsEngleza[1]-latura/2,cuvinte[12].cuvant);
    drawpoly(5,pointsEngleza);

    outtextxy(pointsMenu[0]+latura-textwidth(cuvinte[3].cuvant)/2,pointsMenu[1]+latura/2-textheight(cuvinte[3].cuvant)/2,cuvinte[3].cuvant);
    drawpoly(5,pointsMenu);

    return checkButtonsLanguage(pointsRomana,pointsEngleza,pointsMenu);
}

void gameOver(int playerNumber)
{
    int x,y;
    char playerCh[10];
    if(playerNumber==2)
        strcpy(playerCh,cuvinte[14].cuvant);
    else if(playerNumber==1)
        strcpy(playerCh,cuvinte[15].cuvant);
    outtextxy(latura*3-textwidth(playerCh)/2,latura/2,playerCh);
    drawpoly(5,pointsSkipButton);
    outtextxy((pointsSkipButton[4]+pointsSkipButton[6])/2-textwidth(cuvinte[13].cuvant)/2,(pointsSkipButton[1]+pointsSkipButton[5])/2-textheight(cuvinte[13].cuvant)/2,cuvinte[13].cuvant);
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN,x,y);
        if(checkButtDoi(pointsSkipButton,x,y))
        {
            SkipAI_Select(true);
            startGame();
        }
    }
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,x,y);
        if(checkButtDoi(pointsSkipButton,x,y))
        {
            resetTime();
            SkipAI_Select(true);
            startGame();
        }
        if(checkButtDoi(pointsMenu,x,y))
        {
            checkBackButton(pointsMenu,x,y);
        }
    }
}

void drawColorPlayerTurn(bool playerTurn)
{
    int pointsColorPlayer[]=
    {
        width-latura*3.5f, height-latura*5,
        width-latura,height-latura*5,
        width-latura,height-latura*4.5f,
        width-latura*3.5f,height-latura*4.5f,
        width-latura*3.5f, height-latura*5
    };
    drawpoly(5,pointsColorPlayer);
    if(playerTurn==true)
    {
        outtextxy(width-latura*2.25f-textwidth(cuvinte[7].cuvant)/2,height-latura*5.5f,cuvinte[7].cuvant);
        setfillstyle(SOLID_FILL,BLUE);
        fillpoly(5,pointsColorPlayer);
    }
    else
    {
        outtextxy(width-latura*2.25f-textwidth(cuvinte[8].cuvant)/2,height-latura*5.5f,cuvinte[8].cuvant);
        setfillstyle(SOLID_FILL,RED);
        fillpoly(5,pointsColorPlayer);
    }
  //  outtextxy(width-latura*2-textwidth("Player 1")/2,height-latura*5.5f,"Player 1");
}

void drawSkipButton()
{

    outtextxy((pointsSkipButton[4]+pointsSkipButton[6])/2-textwidth(cuvinte[9].cuvant)/2,(pointsSkipButton[1]+pointsSkipButton[5])/2-textheight(cuvinte[9].cuvant)/2,cuvinte[9].cuvant);
    drawpoly(5,pointsSkipButton);
}

void hideSkipButton()
{
    int pointsSkipButtonI[]=
    {
        width-margine2-latura*4-20,height-margine2-latura-10 ,
        width-margine2-latura*2+20,height-margine2-latura-10,
        width-margine2-latura*2+20,height-margine2+10,
        width-margine2-latura*4-20,height-margine2+10,
        width-margine2-latura*4-20,height-margine2-latura-10
    };

    setfillstyle(SOLID_FILL,BLACK);
    fillpoly(5,pointsSkipButtonI);
   for(int i=0;i<10;i+=2)
   {
       floodfill(pointsSkipButtonI[i],pointsSkipButtonI[i+1],0);
   }


}
//UNDO AICI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void hideUndo()
{
    int pointsUndoI[]=
    {
        width-margine2-latura*4-20,height-margine2-latura-10 ,
        width-margine2-latura*2+20,height-margine2-latura-10,
        width-margine2-latura*2+20,height-margine2+10,
        width-margine2-latura*4-20,height-margine2+10,
        width-margine2-latura*4-20,height-margine2-latura-10
    };

    setfillstyle(SOLID_FILL,BLACK);
    fillpoly(5,pointsUndoI);
   for(int i=0;i<10;i+=2)
   {
       floodfill(pointsUndoI[i],pointsUndoI[i+1],0);
   }


}

void drawLines()
{
    clearviewport();
    for(int i=1;i<5;i++)
    {
        for(int j=1;j<5;j++)
        {
            line(latura*i,latura*j,latura*i,(latura*j)+latura);
            line(latura*i,latura*j,(latura*i)+latura,latura*j);
        }
    }
    line(latura,latura*5,latura*5,latura*5);
    line(latura*5,latura,latura*5,latura*5);
    for(int i=0;i<30;i++)
        line(latura*6+i,0, latura*6+i,latura*6);

}

void drawBackButton()
{
        outtextxy(pointsMenu[0]+latura-textwidth(cuvinte[3].cuvant)/2,pointsMenu[1]+latura/2-textheight(cuvinte[3].cuvant)/2,cuvinte[3].cuvant);
        drawpoly(5,pointsMenu);
}

bool checkUndoIfPressed()
{
    int x,y;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN,x,y);
        PlaySound("ButtonPress.wav",NULL,SND_ASYNC);
    }
    checkUndoButton(pointsUndo,x,y);
}


void CheckBackButtonPress()
{
    int x,y;
    if(ismouseclick(WM_LBUTTONDOWN))
        getmouseclick(WM_LBUTTONDOWN,x,y);
    checkBackButton(pointsMenu,x,y);
}

bool checkSkipButtonPress()
{
    int x,y;
    if(ismouseclick(WM_LBUTTONDOWN))
        getmouseclick(WM_LBUTTONDOWN,x,y);
    return checkSkipButton(pointsSkipButton,x,y);
}


void openWindow()
{
    initwindow(width,height);
    PlaySound("BackgroundMusic.wav",NULL,SND_ASYNC);
    mainMenuHolder();

}

void fillspace(int i,int j)
{
    int points[]={latura*j,latura*i, latura*j+latura,latura*i, latura*j+latura,latura*i+latura, latura*j,latura*i+latura, latura*j,latura*i};
    fillpoly(5,points);
}

void color(int i,int j,int culoare)
{
    setfillstyle(SOLID_FILL,culoare);
    fillspace(i,j);
}

void importRomana()
{
    language=false;
    std::ifstream RO("Romana.txt");
    int i=0;
    while(!RO.eof())
    {
        RO.get(cuvinte[i].cuvant,35);
        i++;
        RO.get();
    }

    RO.close();
}

void importEngleza()
{
    language=true;
    std:: ifstream EN("Engleza.txt");
      int i=0;
    while(!EN.eof())
    {
        EN.get(cuvinte[i].cuvant,35);
        i++;
        EN.get();
    }
  EN.close();

}

void showInfo()
{
    //std::cout<<"1";
    int masura=20;
    int paragraf=50;
    int i=0;
    char aux[3000];
    if(language==false)
    {
        std::ifstream helpRo("HelpRo.txt");
        while(!helpRo.eof())
        {
            helpRo.get(aux,1000);
            if(i==1 || i==5 || i==8 || i==11 || i==12 ||i==14)
                outtextxy(latura+paragraf,latura+masura*i,aux);
            else
                outtextxy(latura,latura+masura*i,aux);
            helpRo.get();
            i++;
        }
        helpRo.close();
    }
    else
    {
        std::ifstream helpEn("HelpEn.txt");
        while(!helpEn.eof())
        {
            helpEn.get(aux,1000);
             if(i==1 || i==5 || i==8 || i==11)
                outtextxy(latura+paragraf,latura+masura*i,aux);
            else
                outtextxy(latura,latura+masura*i,aux);
            helpEn.get();
            i++;
        }
       // outtextxy(latura,latura,aux);
        helpEn.close();
    }

}

void mainMenuHolder()
{
    clearviewport();
    while(1)
    {
        Re:
        switch(mainMenu(width,height)){
        case 1:
            PlaySound("ButtonPress.wav",NULL,SND_ASYNC);
            SkipAI_Select(false);
            startGame();
            break;
        case -1:
            exit(0);
            break;
        case 2:
            {
                clearviewport();
                while(1)
                {
                    switch(drawButtonsLanguage())
                    {
                         case 1:
                             clearviewport();
                            importRomana();

                             break;
                         case 2:
                             clearviewport();
                            importEngleza();

                            break;
                         case 3:
                             clearviewport();
                             goto Re;
                            break;
                    }
                }
                break;
            }
        case 3:
            {
                clearviewport();
                drawBackButton();
                showInfo();
                while(1)
                    {
                        CheckBackButtonPress();
                    }

            }
        }
    }
}

int mainMenu(int width, int height) // deseneaza butoanele de Play si Exit din Menu
{
    int widthText=textwidth(cuvinte[0].cuvant);
    int pointsPlay[]=
        {
            width/2-latura,latura/2,
            width/2+latura,latura/2,
            width/2+latura,latura+latura/3,
            width/2-latura,latura+latura/3,
            width/2-latura,latura/2
        };
    outtextxy((pointsPlay[0]+pointsPlay[2])/2-textwidth(cuvinte[0].cuvant)/2,(pointsPlay[3]+pointsPlay[5])/2-textheight(cuvinte[0].cuvant)/2,cuvinte[0].cuvant);
    drawpoly(5,pointsPlay);

    widthText=textwidth(cuvinte[1].cuvant);
    int pointsLanguage[]=
        {
            width/2-latura,latura+latura/2,
            width/2+latura,latura+latura/2,
            width/2+latura,latura*2+latura/3,
            width/2-latura,latura*2+latura/3,
            width/2-latura,latura+latura/2
        };
    outtextxy((pointsLanguage[0]+pointsLanguage[2])/2-textwidth(cuvinte[1].cuvant)/2,(pointsLanguage[3]+pointsLanguage[5])/2-textheight(cuvinte[1].cuvant)/2,cuvinte[1].cuvant);
    drawpoly(5,pointsLanguage);

     widthText=textwidth(cuvinte[16].cuvant);
    int pointsHelp[]=
        {
            width/2-latura,latura*2+latura/2,
            width/2+latura,latura*2+latura/2,
            width/2+latura,latura*3+latura/3,
            width/2-latura,latura*3+latura/3,
            width/2-latura,latura*2+latura/2
        };
    outtextxy((pointsHelp[0]+pointsHelp[2])/2-textwidth(cuvinte[16].cuvant)/2,(pointsHelp[3]+pointsHelp[5])/2-textheight(cuvinte[16].cuvant)/2,cuvinte[16].cuvant);
    drawpoly(5,pointsHelp);


    widthText=textwidth(cuvinte[2].cuvant);
    int pointsExit[]=
        {
            width/2-latura,height/2+latura,
            width/2+latura,height/2+latura,
            width/2+latura,height/2+latura*1.9f,
            width/2-latura,height/2+latura*1.9f,
            width/2-latura,height/2+latura
        };
    outtextxy(pointsExit[0]+latura-widthText/2,pointsExit[1]+latura/2-textheight(cuvinte[2].cuvant)/1.2f,cuvinte[2].cuvant);
    drawpoly(5,pointsExit);

    //verifica daca este apasat butonul de play sau de exit din Menu
    return checkClickButtonMainMenu(pointsPlay,pointsExit,pointsLanguage,pointsHelp);
}



#endif // DRAW_HPP_INCLUDED
