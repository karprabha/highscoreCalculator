#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include <iomanip>
#include <conio.h> // not mandatory its just for using _getch() to hold screen

using std::cin;
using std::cout;

void fileRead(std::vector<std::string> &names,std::vector<double> &scores)
{
	std::string name;
	double score;

	std::ifstream inFile("highscores.txt"); // You can custom location your file like - "Dirve:\\Folder\\Subfolder\\file.extension" we use double \\ as in string \\ => \ , example - "F:\\C++ Projects\\Files\\Highscores\\highscores.txt"

	if(!inFile) //If file not found
	{
		inFile.open("highscores.txt",std::ios::app); // It is not good to use output mode in ifstream. In C++11 ifstream.open() function clears the stream's state flags on success (setting them to goodbit).In case of failure, failbit is set.
	}

	if(inFile.is_open())
    {
		while(getline(inFile,name))
		{
			name.erase(0,8); //length of " Name : " is  8 characters (names are stored as - Name : XYZ)
			names.push_back(name);
			inFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //ignoring scores (data is stored as - name ,score alternatively)
		}
	
		inFile.clear(); //setting eof to goodbit
	    inFile.seekg(0, std::ios::beg); // putting cursor at begining 
	
	    while(!inFile.eof())
		{
			if(inFile>>score)
			{
				scores.push_back(score);
			}
			else
			{
				inFile.clear(); //removing error flag 
				inFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//clearing invalid characters from stream
			}
		}
	}
	else
	{
		cout<<" ERROR !! System is unable to read file "<<std::endl;
	}	

	inFile.close();
}

void highscoreBoard(std::vector<std::string> &names,std::vector<double> &scores)
{
	for(int i=0;i<scores.size()-1;i++)
	{
	    int minIndex=i;
	   	for(int j=i+1;j<scores.size();j++)
	   	{
	   		if(scores[j]>scores[minIndex])
	   			minIndex=j;
    	}
	   	double tempScore = scores[i];
	   	scores[i]=scores[minIndex];
    	scores[minIndex]=tempScore;

	   	std::string tempName = names[i];
    	names[i]=names[minIndex];
    	names[minIndex]=tempName;
	}
}

void fileWrite(std::vector<std::string> &names,std::vector<double> &scores)
{
	int highscoreIndex;
	scores.size()<=10?highscoreIndex = scores.size():highscoreIndex =10;

	std::ofstream oFile("highscores.txt");// You can custom location your file like - "Dirve:\\Folder\\Subfolder\\file.extension" we use double \\ as in string \\ => \ , example - "F:\\C++ Projects\\Files\\Highscores\\highscores.txt"

	if(oFile.is_open())
	{
		for(int i=0;i<highscoreIndex;i++)
		{
			oFile<<" Name : "<<names[i]<<std::endl;
	        oFile<<"\t"<<scores[i]<<" Points"<<std::endl;
		}
	}
	else
	{
		cout<<" ERROR !! System is unable to write file"<<std::endl;
	}

	oFile.close();
}

void displayHighscores(std::vector<std::string> &names,std::vector<double> &scores)
{
	int highscoreIndex;
	scores.size()<=10?highscoreIndex = scores.size():highscoreIndex =10;

	cout<<"\n Highscores : \n"<<std::endl;

	for(int i=0;i<highscoreIndex;i++)
	{
		cout<<std::setw(3)<<i+1<<")"<<std::setw(20)<<names[i]<<std::setw(2)<<" : "<<std::setw(15)<<scores[i]<<" Points"<<std::endl;
	}
}

int main() //When using in your game rename this to void highscore(double hscore)
{
	std::vector<std::string> names;
	std::vector<double> scores;
	std::string name;
	double score;
	bool validName;

	fileRead(names,scores);

	cout<<" Enter Your Name : ";

	do
	{
		getline(cin,name);
		validName = true; 
		for(std::string existingName : names)
	    {
	    	if(name==existingName)
	    	{
	    		cout<<"\n "<<name<<" is already an existing name.\n Enter different name : ";
	    		validName = false;
	    		break;
	    	}
		}
	}while(!validName);

	names.push_back(name);	

    cout<<"\n Enter Score : ";  // Remove this line when using this program to your game
    if(!(cin>>score))  //When using this program to your game replace (cin>>score) with (score=hscore)
    {
    	cout<<"\n ERROR !!! System Failed to get score\n Press any key to Continue......\0"<<std::endl;
    	_getch();
    	return -1;
    }

    scores.push_back(score);

    if(score>scores[0]||scores.size()==1)
    {
    	cout<<"\n New highscore !!\a  \n Name : "<<name<<"\n Score : "<<score<<" Points \n\0"<<std::endl;
    	highscoreBoard(names,scores);
    	fileWrite(names,scores);
    }
    else if(score==scores[0])
    {
    	cout<<"\n Highscore Tied :)\a\0"<<std::endl;
    	highscoreBoard(names,scores);
    	fileWrite(names,scores);
    }
    else if(score>scores[scores.size()-2]||(scores.size()<10)) // extra -1 because excluding itself from vector length
    {
    	cout<<"\n Congratulations you made it to the TOP 10 \a\0"<<std::endl;
    	highscoreBoard(names,scores);
    	fileWrite(names,scores);
    }

    displayHighscores(names,scores);
     
    cout<<"\n Press any Key to Continue ......\0"<<std::endl;
    _getch(); // not mandatory ..its just for holding screen
	return 0;
}