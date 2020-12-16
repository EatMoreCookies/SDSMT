#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<string>
using namespace std;

void calc_string_length(ifstream &input, double string_length[]);

void pluck_string(ifstream &input, int strings[][7000], double string_length[]);


int main(int argc, char* argv[])
{
	ifstream input;
	ofstream output;

	int i = 0;
	char file_name[100];
	double string_length[7000] = { 0 };
	int strings[128][7000] = { 0 };

	srand(7843);

	if (i == 100) //FIXME 
	{
		if ((argc < 2) || (argc > 3))
		{
			cout << "Incorrect number of arguments entered. " << endl;

			return -1;
		}

		strcpy(file_name, argv[1]);
	}

	cout << "Enter filename: "; //FIXME
	cin.getline(file_name, 100);

	//opens input file
	input.open(file_name);

	//makes sure file is open
	if (!input.is_open())
	{
		cout << "Error: Unable to open file. " << endl;

		return -1;
	}

	//opens output file
	output.open("temp_data");

	//makes sure input file opens
	if (!output.is_open())
	{
		cout << "Error: Unable to open file. " << endl;

		return -1;
	}



	calc_string_length(input, string_length);




	input.close();
	output.close();

	return 0;
}

void calc_string_length(ifstream &input, double string_length[])
{
	int midi;

	for (midi = 0; midi < 128; ++midi)
	{

		string_length[midi] = 44100 / (pow(2, (midi - 69 / 12)) * 440);
		cout << string_length[midi];

	}


}

void pluck_string(ifstream &input, int strings[][7000], double string_length[])
{
	int i, time, midi, volume;

	input >> time >> midi >> volume;

	for (i = 0; i < string_length[midi]; ++i)
	{
		strings[i][midi] = rand() % (time / 2) - (-1 * (time / 2));
		cout << strings[i][midi];
	}
}