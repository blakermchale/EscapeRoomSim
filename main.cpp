#include <fstream>
#include <iostream>
#include <list>
#define MAX_POINT 5
#define MAX_PEOPLE 8
#include<stdio.h>
#include <vector>
#include <time.h>
#include <iomanip>
#include <cstring>
using namespace std;

int CurrentGroup[MAX_PEOPLE][3]; //Sets array to keep track of specific details for each patron
const int MAXDays = 30; //Max days for simulation room
int SumGroup[6] = {0,0,0,0,0,0}; //[Skill, Total Money, Money Avg Person, Money Puzzler, Money Conn]
int ProfitMonth[3][3][MAXDays] ={0}; //Profit for month: room, patron type, day
int RecordProfitMonth[3][3][MAXDays] = {0};
//int SkillMonth
double BestTotal[3] = {0,0,0}; //Keeps track of total profit
int BestDiff[3] = {0,0,0}; //Keeps track of best difficulty
int AvgSkill[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
int BestAvgSkill[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
int TotAvgSkill[3] = {0,0,0};
int TotPatProf[3] = {0,0,0};
double TotalPeeps[3] = {0,0,0};
double BestSuccess[3] = {0,0,0};    //Keeps track of best success rate
vector<int> BestCombo[3];   //Vector that keeps track of three best combos
vector<int> Room[3] = {{5,2,1},{2,1,5},{5,1,2}}; //Sets rooms to check {5,1,2},{3,4,1},{5,2,1}
double wins = 0; //Keeps track of wins
double successPerc = 0; //Sets success percentage

int SetGroup(vector<int> Group, int diff, int day, int room)
{
    SumGroup[0] = 0;    //Resets group skill for run
    int i;  //stepper for going through people in room
    for (i = 0; i < Group.at(0)&& Group.at(0);i++)
    {
        CurrentGroup[i][0]=rand()%3+3;  //Skill Avg Person
        AvgSkill[room][0] += CurrentGroup[i][0];
    }
    for (i; i < Group.at(1) + Group.at(0)&& Group.at(1);i++)
    {
        CurrentGroup[i][0]=rand()%3+6;  //Skill Puzzlers
        AvgSkill[room][1] += CurrentGroup[i][0];
    }
    for (i; i < Group.at(2) + Group.at(1) + Group.at(0)&& Group.at(2);i++)
    {
        CurrentGroup[i][0]=rand()%6+10; //Skill Conn
        AvgSkill[room][2] += CurrentGroup[i][0];
    }

    for(int j = 0; j < MAX_PEOPLE;j++)
    {
        SumGroup[0] += CurrentGroup[j][0]; //Total skill for group
    }

    if (SumGroup[0] > diff) {
        wins++; //Adds one to number of wins
        if (SumGroup[0] >= diff + 5) {
            for (int y = 0; y < Group.at(0)&& Group.at(0); y++) {
                SumGroup[2] += 5;   //Adds money to total
                ProfitMonth[room][0][day] += 5; //Adds money to day earning Avg
            }
        }
        for (int y = 0; y < Group.at(0) && Group.at(0); y++) {
            CurrentGroup[y][2]=rand()%11+10;    //Win Money avg person
            SumGroup[2]+= CurrentGroup[y][2];   //Adds money to total
            ProfitMonth[room][0][day] += CurrentGroup[y][2]; //Add money to Avg Person for that day
        }
        if (SumGroup[0] > (diff + 10)) {
            for (int y = Group.at(0); y < (Group.at(1) + Group.at(0))&& Group.at(1); y++) {
                SumGroup[2] += 10;  //Adds money to total
                ProfitMonth[room][1][day] += 10; //Add money to puzzler for that day
            }
        }
        else
        {
            for (int y = Group.at(0); y < (Group.at(1) + Group.at(0))&& Group.at(1); y++) {
                CurrentGroup[y][2]=rand()%6+20; //Win Money Puzzler
                SumGroup[2]+= CurrentGroup[y][2];   //Adds money to total
                ProfitMonth[room][1][day]+=CurrentGroup[y][2]; //Add money to puzzler day profit
            }
            for (int y = Group.at(0)+Group.at(1); y < (Group.at(2)+Group.at(1)+Group.at(0))&& Group.at(2); y++)
            {
                CurrentGroup[y][2]=rand()%11+30;//Finds rand Win Money Conn
                SumGroup[2]+= CurrentGroup[y][2];   //Adds money to total
                ProfitMonth[room][2][day]+=CurrentGroup[y][2]; //Add money to connoisseur
            }

        }

    }
    else
    {
        for (int y = 0; y < Group.at(0)&& Group.at(0);y++)
        {
            CurrentGroup[y][2]=rand()%6+5;  //Finds Rand Loss Money Avg
            SumGroup[2]+= CurrentGroup[y][2];   //Adds money to total
            ProfitMonth[room][0][day] += CurrentGroup[y][2];    //Adds money for day earning
        }
        for (int y = Group.at(0); y < (Group.at(1) + Group.at(0))&& Group.at(1); y++) {
            CurrentGroup[y][2]=rand()%6+10; //Finds Rand Loss Money Puzz
            SumGroup[2]+= CurrentGroup[y][2];   //Adds money to total
            ProfitMonth[room][1][day]+=CurrentGroup[y][2];  //Adds money for day earning
        }
        for (int y = Group.at(0)+Group.at(1); y < (Group.at(2)+Group.at(1)+Group.at(0))&& Group.at(2); y++)
        {
            CurrentGroup[y][2]=rand()%6+15; //Finds Rand loss money Conn
            SumGroup[2]+= CurrentGroup[y][2];   //Adds money to total
            ProfitMonth[room][2][day]+=CurrentGroup[y][2];  //Adds money for day earning
        }
    }
};
vector<int> GetSkill(vector<int> Group)
{
    int AvgSkill[2] = {0,0};    //Array for min and max Avg skill
    int PuzzSkill[2] = {0,0};   //Array for min and max Puzz skill
    int ConnSkill[2] = {0,0};   //Array for min and max Conn skill
    vector<int> Skill(2);   //Vector for min and max skill
    if (Group.at(0))
    {
        AvgSkill[0]= 3*Group.at(0); //Rand low Avg
        AvgSkill[1]=5*Group.at(0);  //Rand max Avg
    }
    if (Group.at(1))
    {
        PuzzSkill[0]=6*Group.at(1); //Rand min Puzz
        PuzzSkill[1]=8*Group.at(1); //Rand max Puzz
    }
    if (Group.at(2))
    {
        ConnSkill[0]=10*Group.at(2);    //Rand low Conn
        ConnSkill[1]=15*Group.at(2);    //Rand max Conn
    }
    Skill.at(0)=AvgSkill[0]+PuzzSkill[0]+ConnSkill[0];  //Finds min skill
    Skill.at(1)=Skill[1]=AvgSkill[1]+PuzzSkill[1]+ConnSkill[1]; //Finds max skill
    return Skill;
}

int Simulation (int i, vector<int> Group, int room)
{
    wins = 0;   //Sets wins back to zero for new simulation
    AvgSkill[room][0] = 0;
    AvgSkill[room][1] = 0;
    AvgSkill[room][2] = 0;
    int Runs = 270/i;   //Finds number of runs
    if (Runs > 6)
    {
        Runs = 6;   //Breaks if runs is greater than 0
    }
    for (int j = 0; j < MAXDays; j++)
    {
        for (int k = 0; k < Runs; k++)
        {
            SetGroup(Group, i, j, room);    //Calls function to run room one time
        }
    }
    successPerc = 100*wins/(Runs*MAXDays); //Calculates percentage of wins
}

//void printArray(vector<int> Group, int arr_size);
void printArray(vector<int> Group)
{
    vector<int> Skill(2);   //Creates vector for skill
    Skill = GetSkill(Group); //Finds max and min skill
    for (int i = Skill.at(0)-5; i <= Skill.at(1); i++) //Checks all possibilities for skill
    {
        int room =0;
        for (int t = 0; t < 3; t++)
        {
            if (Group == Room[t])
            {
                room = t; //Tells which room is in use
            }
            else {

            }
        }

        SumGroup[2] = 0;    //Sets sum of profit to 0
        memset(ProfitMonth,0,sizeof(ProfitMonth)); //Resets the profit month back to zero
        Simulation(i, Group, room); //Calls the simulation for this room and group
        for (int w = 0; w < 3; w++)
        {
            if (SumGroup[2] > BestTotal[w] && Group == Room[w])
            {
                BestTotal[w] = SumGroup[2]; //Assigns best profit
                BestCombo[w] = Group;   //Assigns Combo of patrons
                BestDiff[w] = i;    //Assigns difficulty of room
                BestSuccess[w] = successPerc;   //Assigns the success percentage
                for (int k = 0; k < 3;k++)
                {
                    BestAvgSkill[w][k] = AvgSkill[w][k];
                    for(int z = 0; z < MAXDays;z++)
                    {
                        RecordProfitMonth[w][k][z]=ProfitMonth[w][k][z];    //Records profit daily for each patron type
                    }
                }
            }
        }
    }
}
void printCompositions(int n, int i)
{
    static vector<int> Group; //static vector
    Group.resize(i+1); //Expands vector to fit another element
    if (n  == 0)
    {
        Group.pop_back(); //Removes null element in back from resize
        if (Group.size() < 3)
        {
            Group.push_back(0); //Adds zero to back of vector
            printArray(Group);   //Progresses to step before sim
            Group.pop_back();   //Gets rid of back zero
            Group.emplace(Group.begin()+1,0);   //Puts zero in middle of vector
            printArray(Group);   //Progresses to step before sim
            Group.erase(Group.begin()+1);   //Erases middle zero in group
            Group.insert(Group.begin(),0); //Adds zero to end of group
            printArray(Group);   //Progress to step before sim
        }
        else if (Group.size() == 3)
        {
            printArray(Group); //When group size is three types call sim
        }
    }
    else if(n > 0)
    {
        int k;
        for (k = 1; k <= MAX_POINT; k++)
        {
            Group.at(i)=k; //Sets spot in vector to k value
            printCompositions(n-k, i+1); //Recursive function, repeats back and moves to next spot in vector
        }
    }
}




int main()
{
    srand(time(NULL));  //Seeds random num generator
    ofstream outfile;   //Creates output function
    outfile.open("EscapeRoomProfit.txt");   //Creates output file
    printCompositions(MAX_PEOPLE, 0);   //Calls function to find all combinations of 5 and lower that make 8

    for(int w=0;w<3;w++)    //Goes up by one for each room
    {
        outfile << BestTotal[w] << "\t";    //Total Profit for room
        outfile << BestDiff[w] << "\t";   //Difficulty
        outfile << BestSuccess[w] << "\t";    //Success Rate

        //outfile << "Room(Avg., Puzz, Conn): ";
        for (vector<int>::iterator i = BestCombo[w].begin(); i != BestCombo[w].end() ; i++) //Finds each number of patrons
        {
            outfile << *i << " ";   //
        }
        outfile << "\n";
        //string ProfitPhrase[3] = {"Profit Per Day (Avg.): ","Profit Per Day (Puzz): ","Profit Per Day (Conn): "};
        for(int t = 0;t<3;t++)
        {
            TotalPeeps[t] += BestCombo[w].at(t)*MAXDays*(270/BestDiff[w]);
            TotAvgSkill[t] += BestAvgSkill[w][t];
            //outfile << right <<ProfitPhrase[t];
            for (int i = 0; i < MAXDays;i++)
            {
                outfile << right <<RecordProfitMonth[w][t][i] << "\t"; //Outputs money earned each day for each patron type
                TotPatProf[t] += RecordProfitMonth[w][t][i];
            }
            outfile << "\n";
        }

        outfile << "";
    }
    for (int i = 0; i <3; i++)
    {
        outfile << (TotAvgSkill[i]/TotalPeeps[i]) << "\t";
        outfile << (TotPatProf[i]/TotalPeeps[i]) << "\t";
        outfile << (BestTotal[i]/MAXDays) << "\t\n";
    }

    outfile.close();
    return 0;
}