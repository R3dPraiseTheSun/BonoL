#ifndef LOGICS_HPP_INCLUDED
#define LOGICS_HPP_INCLUDED

#include "inGameHolder.hpp"
#include "Draw.hpp"

bool checkButt(int points[], int x, int y);
bool checkButtDoi(int points[], int x, int y);
bool canClickUndo;

//bool checkUndoButton(int points[],int x,int y);
bool checkUndoIfPressed();
void Hide_Undo_Button();
//for AI
int CheckAI_Select(int pointsAI_Easy[], int pointsAI_Hard[], int pointsHuman[]);

//from Draw
void Draw_Select_Menu(int pointsAI_Easy[], int pointsAI_Hard[], int pointsHuman[]);


void mainMenuHolder();
void resetTime();

int pointsMenu[]={width-margine2-latura*2,height-margine2-latura ,width-margine2,height-margine2-latura, width-margine2,height-margine2, width-margine2-latura*2,height-margine2, width-margine2-latura*2,height-margine2-latura};

void makeClickUndoActive(bool active)
{
    if(active==true)
        canClickUndo=true;
    else
        canClickUndo=false;
}

void checkUndoButton(int points[],int x,int y)
{
    if(canClickUndo==true)
    {
        if(checkButtDoi(points,x,y)==true)
        {
            PlaySound("UndoEffect.wav",NULL,SND_ASYNC);
            //std::cout<<"Undo!"<<std::endl;
            Undo();
            Hide_Undo_Button();
        }
    }
}

bool checkSkipButton(int points[],int x,int y)
{
    if(checkButtDoi(points,x,y)==true)
    {
        PlaySound("ButtonPress.wav",NULL,SND_ASYNC);
        resetTime();
        return true;
    }
    return false;
}

void checkBackButton(int points[],int x,int y)
{
    if(checkButtDoi(points,x,y)==true)
    {
        PlaySound("ButtonPress.wav",NULL,SND_ASYNC);
        //std::cout<<"Done!";
        mainMenuHolder();
    }
}


int CheckAI_Select(int pointsAI_Easy[], int pointsAI_Hard[], int pointsHuman[])
{
    while(1)
    {
        Draw_Select_Menu(pointsAI_Easy, pointsAI_Hard, pointsHuman);
        int x,y;

        if(ismouseclick(WM_LBUTTONDOWN))
            getmouseclick(WM_LBUTTONDOWN,x,y);
        checkBackButton(pointsMenu,x,y);
        if(checkButtDoi(pointsAI_Easy,x,y))
        {
            resetTime();
            return 1;
        }
        if(checkButtDoi(pointsAI_Hard,x,y))
        {
            resetTime();
            return 2;
        }
        if(checkButtDoi(pointsHuman,x,y))
        {
            resetTime();
            return 0;
        }
    }
}

bool checkIfTheSameMatrix(int M1[6][6],int M2[6][6])
{
    for(int i=1;i<5;i++)
        for(int j=1;j<5;j++)
            if(M1[i][j]!=M2[i][j])
                return false;
    return true;
}

int checkClickButtonMainMenu(int pointsPlay[],int pointsExit[],int pointsLanguage[],int pointsHelp[])
{
    int x,y;
    getmouseclick(WM_LBUTTONDOWN,x,y);
    if(checkButt(pointsPlay,x,y)|| checkButtDoi(pointsPlay,x,y))
            return 1;
    else if(checkButt(pointsExit,x,y) || checkButtDoi(pointsExit,x,y))
            return -1;
    else if(checkButt(pointsLanguage,x,y) || checkButtDoi(pointsLanguage,x,y))
            return 2;
    else if(checkButt(pointsHelp,x,y)||checkButtDoi(pointsHelp,x,y))
    {
            //std::cout<<"1";
            return 3;
    }

    return 0;
}

int checkButtonsLanguage(int pointsRomana[],int pointsEngleza[],int pointsMenu[])
{
    int x,y;
    getmouseclick(WM_LBUTTONDOWN,x,y);
    if(checkButt(pointsRomana,x,y))
        return 1;
    if(checkButt(pointsEngleza,x,y))
        return 2;
    if(checkButtDoi(pointsMenu,x,y))
        return 3;
    return 0;

}

bool checkButt(int points[], int x, int y)
{
    if(x>points[0] && x<points[2] && y<points[1] && y>points[5])
    {
        PlaySound("ButtonPress.wav",NULL,SND_ASYNC);
        //std::cout<<"Button 1 fct"<<std::endl;
        return true;
    }
    return false;
}
bool checkButtDoi(int points[], int x, int y)
{
    if(x>points[0] && x<points[2] && y>points[1] && y<points[5])
       {
        PlaySound("ButtonPress.wav",NULL,SND_ASYNC);
        //std::cout<<"Button 2 fct"<<std::endl;
        return true;
        }
    return false;
}

bool validPos(int a[6][6],int i,int j,int nr)
{
    //if(samePos()) return false;
    //L din cap
    if(a[i+2][j]==nr && a[i+1][j]==nr && (a[i+2][j+1]==nr || a[i+2][j-1]==nr)) return true;
    else if(a[i-2][j]==nr && a[i-1][j]==nr && (a[i-2][j+1]==nr || a[i-2][j-1]==nr)) return true;
    else if(a[i][j+2]==nr && a[i][j+1]==nr && (a[i-1][j+2]==nr || a[i+1][j+2]==nr)) return true;
    else if(a[i][j-2]==nr && a[i][j-1]==nr && (a[i-1][j-2]==nr || a[i+1][j-2]==nr)) return true;
    //L din coada
    if(a[i+1][j]==nr && ((a[i+1][j+1]==nr && a[i+1][j+2]==nr)||(a[i+1][j-1]==nr && a[i+1][j-2]==nr))) return true;
    else if(a[i-1][j]==nr && ((a[i-1][j+1]==nr && a[i-1][j+2]==nr)||(a[i-1][j-1]==nr && a[i-1][j-2]==nr))) return true;
    else if(a[i][j+1]==nr && ((a[i+1][j+1]==nr && a[i+2][j+1]==nr)||(a[i-1][j+1]==nr && a[i-2][j+1]==nr))) return true;
    else if(a[i][j-1]==nr && ((a[i+1][j-1]==nr && a[i+2][j-1]==nr)||(a[i-1][j-1]==nr && a[i-2][j-1]==nr))) return true;

    return false;
}

bool validPosAI(int a[6][6],int i,int j,int nr)
{
    if(a[i][j]==nr)
    {
        //L din cap
        if(a[i+2][j]==nr && a[i+1][j]==nr && (a[i+2][j+1]==nr || a[i+2][j-1]==nr))
        {
            a[i][j]=2,a[i+2][j]=2,a[i+1][j]=2;

            if(a[i+2][j+1]==nr)
                a[i+2][j+1]=2;
            else if(a[i+2][j-1]==nr)
                a[i+2][j-1]=2;

            return true;
        }
        else if(a[i-2][j]==nr && a[i-1][j]==nr && (a[i-2][j+1]==nr || a[i-2][j-1]==nr))
        {
            a[i-2][j]=2,a[i-1][j]=2,a[i][j]=2;

            if(a[i-2][j+1]==nr)
                a[i-2][j+1]=2;
            else if(a[i-2][j-1]==nr)
                a[i-2][j-1]=2;

            return true;
        }
        else if(a[i][j+2]==nr && a[i][j+1]==nr && (a[i-1][j+2]==nr || a[i+1][j+2]==nr))
        {
            a[i][j]=2,a[i][j+1]=2,a[i][j+2]=2;
            if(a[i-1][j+2]==nr)
                a[i-1][j+2]=2;
            else if(a[i+1][j+2]==nr)
                a[i+1][j+2]=2;

            return true;
        }
        else if(a[i][j-2]==nr && a[i][j-1]==nr && (a[i-1][j-2]==nr || a[i+1][j-2]==nr))
        {
            a[i][j]=2,a[i][j-1]=2,a[i][j-2]=2;
            if(a[i-1][j-2]==nr)
                a[i-1][j-2]=2;
            else if(a[i+1][j-2]==nr)
                a[i+1][j-2]=2;

            return true;
        }

        //L din coada
        else if(a[i+1][j]==nr && ((a[i+1][j+1]==nr && a[i+1][j+2]==nr)||(a[i+1][j-1]==nr && a[i+1][j-2]==nr)))
        {
            a[i][j]=2,a[i+1][j]=2;
            if(a[i+1][j+1]==nr && a[i+1][j+2]==nr)
                a[i+1][j+1]=2,a[i+1][j+2]=2;
            else if(a[i+1][j-1]==nr && a[i+1][j-2]==nr)
                a[i+1][j-1]=2,a[i+1][j-2]=2;

            return true;
        }
        else if(a[i-1][j]==nr && ((a[i-1][j+1]==nr && a[i-1][j+2]==nr)||(a[i-1][j-1]==nr && a[i-1][j-2]==nr)))
        {
            a[i][j]=2,a[i-1][j]=2;
            if(a[i-1][j+1]==nr && a[i-1][j+2]==nr)
                a[i-1][j+1]=2,a[i-1][j+2]=2;
            else if(a[i-1][j-1]==nr && a[i-1][j-2]==nr)
                a[i-1][j-1]=2,a[i-1][j-2]=2;

            return true;
        }
        else if(a[i][j+1]==nr && ((a[i+1][j+1]==nr && a[i+2][j+1]==nr)||(a[i-1][j+1]==nr && a[i-2][j+1]==nr)))
        {
            a[i][j]=2,a[i][j+1]=2;
            if(a[i+1][j+1]==nr && a[i+2][j+1]==nr)
                a[i+1][j+1]=2,a[i+2][j+1]=2;
            else if(a[i-1][j+1]==nr && a[i-2][j+1]==nr)
                a[i-1][j+1]=2,a[i-2][j+1]=2;

            return true;
        }
        else if(a[i][j-1]==nr && ((a[i+1][j-1]==nr && a[i+2][j-1]==nr)||(a[i-1][j-1]==nr && a[i-2][j-1]==nr)))
        {
            a[i][j]=2,a[i][j-1]=2;
            if(a[i+1][j-1]==nr && a[i+2][j-1]==nr)
                a[i+1][j-1]=2,a[i+2][j-1]=2;
            else if(a[i-1][j-1]==nr && a[i-2][j-1]==nr)
                a[i-1][j-1]=2,a[i-2][j-1]=2;

            return true;
        }
    }

    return false;
}

#endif // LOGICS_HPP_INCLUDED
