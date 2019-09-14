#include "mystring.h"

void trim(char cstr[], char method)
{
	char *ptr = nullptr;
	int i, j;
	int length;
	bool foundNonSpace = false;

	method = toupper(method);

	length = strlen(cstr);

	if (method == 'F')
	{
		for (i = 0; i < length + 1; ++i)
		{
			if (isspace(cstr[i]) == 0)
			{

				ptr = &cstr[i];

				strcpy(cstr, ptr);

				return;
			}

		}
	}

	if (method == 'E')
	{
		for (i = length - 1; i >= 0; --i)
		{
			if (isspace(cstr[i]) == 0)
			{
				foundNonSpace = true;
				cstr[i + 1] = '\0';

				return;
			}

			if (i == 0 && foundNonSpace == false)
			{
				cstr[0] = '\0';

				return;
			}

		}
	}

	if (method == 'B')
	{
		for (i = length - 1; i >= 0; --i)
		{
			if (isspace(cstr[i]) == 0)
			{
				foundNonSpace = true;
				cstr[i + 1] = '\0';

				for (j = 0; j < length + 1; ++j)
				{
					if (isspace(cstr[j]) == 0)
					{

						ptr = &cstr[j];

						strcpy(cstr, ptr);

						return;
					}

				}

			}

			if (i == 0 && foundNonSpace == false)
			{
				cstr[0] = '\0';

				return;
			}
		}



	}
}


void extractNames(char str[], char first[], char middle[], char last[])
{
	char *strPtr = nullptr;
	char *tokPtr;
	int i = 0;

	trim(str, 'B');

	strPtr = strchr(str, ',');

	if (strPtr == nullptr)
	{
		tokPtr = strtok(str, " ");

		strcpy(first, tokPtr);

		tokPtr = strtok(NULL, " ");
		
		if (tokPtr != NULL)
		{
			strcpy(last, tokPtr);
		}

		tokPtr = strtok(NULL, " ");

		if (tokPtr != NULL)
		{
			strcpy(middle, last);

			strcpy(last, tokPtr);
		}

	}


	else
	{
		tokPtr = strtok(str, ",");

		strcpy(last, tokPtr);

		tokPtr = strtok(NULL, " ");

		if (tokPtr != NULL)
		{
			strcpy(first, tokPtr);
		}
		
		tokPtr = strtok(NULL, " ");

		if (tokPtr != NULL)
		{
			strcpy(middle, tokPtr);
		}
	}

}