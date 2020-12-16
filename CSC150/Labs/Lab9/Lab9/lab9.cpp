#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	double stopping_pts = 0.0;
	double array_x[20];
	double array_y[20];
	int i = 0; 
	double x_val = 0.0;
	double y_val = 0.0;
	double distance = 0.0;
	double distances[20];
	double max_val = 0.0;
	double max_xval = 0.0;
	double max_yval = 0.0;
	double min_val = 0.0;
	double total_distance = 0.0;
	int max_i = 0;
	int min_i = 0;
	
	
	cout << "How many stopping points are there: ";
	cin >> stopping_pts;
	
	cout << "Enter the stopping points in \"x, y\" form: ";
	for (i = 0; i < stopping_pts; ++i)
	{
		cout << endl;
		cin >> x_val >> y_val;

		array_x[i] = x_val;
		array_y[i] = y_val;

    }

	for (i = 0; i < stopping_pts - 1; ++i)
	{
		distance = sqrt(pow(array_x[i + 1] - array_x[i], 2) + pow(array_y[i + 1] - array_y[i], 2));
		distances[i] = distance;
	}
	
	for (i = 0; i < stopping_pts - 1; ++i)
	{
		total_distance = total_distance + distances[i];
	}
	
	cout << "The total distance " << total_distance << endl;
	
	max_val = distances[i];
	
	for (i = 1; i < stopping_pts - 1; ++i)
	{
		if (distances[i] > max_val)
		{
			max_val = distances[i];
			max_i = i;

		}

	}

	cout << "Max value is " << max_val <<  " @ " << array_x[max_i] << "," << array_y[max_i] << " and " << array_x[max_i + 1] << "," << array_y[max_i + 1] << endl;
	
	i = 0;
	
	min_val = distances[i];
	for (i = 1; i < stopping_pts - 1; ++i)
	{
		if (distances[i] < min_val)
		{
			min_val = distances[i];
			min_i = i;
		}

	}

	cout << "Min value is " << min_val << " @ " << array_x[min_i] << "," << array_y[min_i] << " and " << array_x[min_i + 1] << "," << array_y[min_i + 1] << endl;

	return 0;
}