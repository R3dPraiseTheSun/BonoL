#ifndef POZITII_HPP_INCLUDED
#define POZITII_HPP_INCLUDED

#include <iostream>

int FindL(int k,int Table[6][6]);
void FindLBot(int i,int j,int k,int Table[6][6]);
void FindLTop(int i,int j,int k,int Table[6][6]);
void FindLLef(int i,int j,int k,int Table[6][6]);
void FindLRig(int i,int j,int k,int Table[6][6]);

int nr_pos;

int FindL(int k,int Table[6][6])
{
    nr_pos=-1;
    int i,j;
    for(i=1;i<5;i++)
    {
        for(j=1;j<5;j++)
        {
                FindLBot(i,j,k,Table);
                FindLTop(i,j,k,Table);
                FindLLef(i,j,k,Table);
                FindLRig(i,j,k,Table);
        }
    }
    return nr_pos;
}

void FindLBot(int i,int j,int k,int Table[6][6])
{
    if(Table[i][j]==0)
        if(k<2 && i+1<5)FindLBot(i+1,j,k+1,Table);
    if(k==2 && Table[i][j]==0)
    {
        if(j+1<5 && Table[i][j+1]==0) nr_pos++;
        if(j-1>0 && Table[i][j-1]==0) nr_pos++;
    }

}

void FindLTop(int i,int j,int k,int Table[6][6])
{
    if(Table[i][j]==0)
        if(k<2 && i-1>0 ) FindLTop(i-1,j,k+1,Table);
    if(k==2 && Table[i][j]==0)
    {
        if(j+1<5 && Table[i][j+1]==0) nr_pos++;
        if(j-1>0 && Table[i][j-1]==0) nr_pos++;
    }
}

void FindLLef(int i,int j,int k,int Table[6][6])
{
    if(Table[i][j]==0)
        if(k<2 && j-1>0) FindLLef(i,j-1,k+1,Table);
    if(k==2 && Table[i][j]==0)
    {
        if(i-1>0 && Table[i-1][j]==0) nr_pos++;
        if(i+1<5 && Table[i+1][j]==0) nr_pos++;
    }
}

void FindLRig(int i,int j,int k,int Table[6][6])
{
    if(Table[i][j]==0)
        if(k<2 && j+1<5) FindLRig(i,j+1,k+1,Table);
    if(k==2 && Table[i][j]==0)
    {
        if(i-1>0 && Table[i-1][j]==0) nr_pos++;
        if(i+1<5 && Table[i+1][j]==0) nr_pos++;
    }
}
#endif // POZITII_HPP_INCLUDED
