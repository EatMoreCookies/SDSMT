#include<iostream>
#include<string>
#include<cstring>
using namespace std;


void abbr_subject(char fullname[], char abbrname[]);
void compute_hours(char abbrname[], int num_courses, double &major_credits, double &total_credits);
void display(char abbrname[], double major_credits, double total_credits);

int main()
{
	char major[100];
	char abbrname[100] = { 0 };
	int i = 0;
	int num_courses = 0;
	double major_credits = 0.0;
	double total_credits = 0.0;
	
	cout << "Enter your major: ";

	cin.getline(major, 50);

	abbr_subject(major, abbrname);

	cout << abbrname << endl;
	
	cout << "Enter the number of courses: ";
	cin >> num_courses;
	
	compute_hours(abbrname, num_courses,major_credits, total_credits);
	
	display(abbrname, major_credits, total_credits);
	
	
	return 0;
}


void abbr_subject(char fullname[], char abbrname[])
{
	int i = 0;
	char last_initial[2] = { 0 };
	
	abbrname[0] = fullname[i];

	for (i = 0; i < 100; ++i)
	{
		if (fullname[i] == ' ')
		{
			last_initial[0] = fullname[i+1];
			break;
		}
	}

	strcat(abbrname, last_initial);


}

void compute_hours(char abbrname[], int num_courses, double &major_credits, double &total_credits)
{
	char courses[100] = { 0 };
	double credits = 0.0;
	int i = 0;
	
	
	total_credits = 0.0;
	major_credits = 0.0;

	for (i = 0; i < num_courses; ++i)
	{
		cout << "Enter course #" << i + 1 << " :";
		cin.ignore();
		cin.getline(courses, 100);

		cout << "Enter credit hours #" << i + 1 << ": ";
		cin >> credits;

		
		total_credits = credits + total_credits;

		cout << courses << abbrname << endl;
		
		if (courses[i] == abbrname[i] && courses[i+1] == abbrname[i+1])
		{
			major_credits = major_credits + credits;
        }
		
	}
}

void display(char abbrname[], double major_credits, double total_credits)
{
	cout << abbrname << " major credits hours: " << major_credits << endl;
	cout << "Total credits hours: " << total_credits << endl;
}