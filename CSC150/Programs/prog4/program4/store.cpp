#include<iostream>

using namespace std;


int main(int arg)
{
	int argc = 3;
	char* argv[100];
	int i = 0;
	char file_name[100];
	double string_length[128] = { 0 };
	double strings[6000][128] = { 0 };
	double test;


	//makes sure number of arguments is correct
	if (i == 100){ //FIXME. if statement Debug
		if ((argc < 2) || (argc > 3))
		{
			cout << "Error: incorrect number of arguments. " << endl;

			return -1;
		}
	}

	cout << "Enter file name: ";
	cin.getline(file_name, 100);

	//copies file name entered to the array file_name
	if (i == 100){  //FIXME: if statement. Debug
		++i;
	}

	//opening music file

	return 0;
}