
#include <iostream>
#include <cstdlib>
#include <startG.h>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWimmer { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWimmer Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
    enWimmer GameWimmer;
    string WinnerName = " ";
};

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

string WinnerName(enWimmer Winner)
{
    string arrWinnerName[3] = { "Player","Computer","No Wimmer" };

    return arrWinnerName[Winner - 1];
}

enWimmer WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWimmer::Draw;
    }

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWimmer::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWimmer::Computer;
        }
        break;

    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWimmer::Computer;
        }
        break;
    }

    //if you reach here then player 1 is the winner .
    return enWimmer::Player;

}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoice[3] = { "Ston" , "Paper" ,"Scissors" };

    return arrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWimmer Winner)
{
    switch (Winner)
    {
    case enWimmer::Player:
        system("color 2F");
        break;

    case enWimmer::Computer:
        system("color 4F");
        break;

    default:
        system("color 6F");
        break;
    }
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "]____________\n\n";
    cout << "Player 1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "__________________________________\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWimmer WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWimmer::Player;
    else if (ComputerWinTimes > Player1WinTimes)
        return enWimmer::Computer;
    else
        return enWimmer::Draw;
}

stGameResults FillGameResult(int GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.PlayerWinTimes = PlayerWinTimes;
    GameResults.Computer2WinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWimmer = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWimmer);

    return GameResults;
}

enGameChoice ReadPlayerChoice()
{
    short Choice = 1;

    do
    {
        cout << "\nYour Choice: [1]:Stone , [2]:Paper , [3]:Scissors ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

enGameChoice GetComputeChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputeChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        //Increase win/Draw counters
        if (RoundInfo.Winner == enWimmer::Player)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWimmer::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResult(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << Tabs(2) << "Game Rounds         : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times   : " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer won times  : " << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Draw times          : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner        : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";

    SetWinnerScreenColor(GameResults.GameWimmer);
}

short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {
        cout << "How Many Rounds 1 to 10 ?\n";
        cin >> GameRounds;

    } while (GameRounds < 1 || GameRounds >10);
    return GameRounds;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StatGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again ? Y/N ? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    //Seeds the random number generator in C++ , Called only once
    srand((unsigned)time(NULL));

    StatGame();

    return 0;

}
