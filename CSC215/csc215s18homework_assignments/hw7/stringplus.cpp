#include"stringplus.h"
void trimString(string &s, char method)
{
	int i;
	bool foundNoSpace = false; 
	
	method = toupper(method);


	if (method == 'F' || method == 'B')
	{
		for (i = 0; i < s.length(); ++i)
		{
			if (isspace(s[i]) == 0)
			{
				foundNoSpace = true;
				
				s.erase(0, i);

				i = s.length();
			}
		}
	
		if (foundNoSpace == false)
		{
			s.erase();
		}
	}

    if (method == 'E' || method == 'B')
	{
		for (i = s.length() - 1; i >= 0; --i)
		{
			if (isspace(s[i]) == 0)
			{
				foundNoSpace = true; 
				
				s.erase(i + 1, s.length());

				return;
			}
        }
        
		if (foundNoSpace == false)
		{
			s.erase();
		}
	}

}

void extractStringNames(string fullname, string &first, string
	&middle, string &last)
{
	int i;

	trimString(fullname, 'B');

	std::string::size_type idx;

	idx = fullname.find(",");

	if (idx != string::npos)
	{
		for (i = 0; i < fullname.length(); ++i)
		{
			if (isspace(fullname[i]) != 0)
			{
				last = fullname.substr(0, i - 1);

				fullname.erase(0, i);

				trimString(fullname, 'F');

				i = 0;

				idx = fullname.find(" ");

				if (idx != string::npos)
				{
					first = fullname.substr(0, idx);

					fullname.erase(0, idx);

					trimString(fullname, 'F');

					middle = fullname;
				}

				else
				{
					first = fullname;
				}

			}
		}
	}

	else
	{
		idx = fullname.find(" ");

		first = fullname.substr(0, idx);

		fullname.erase(0, idx);

		trimString(fullname, 'F');

		idx = fullname.find(" ");

		if (idx != string::npos)
		{
			middle = fullname.substr(0, idx);

			fullname.erase(0, idx);

			trimString(fullname, 'F');

			last = fullname;
		}

		else
		{
			last = fullname;
		}

	}




}