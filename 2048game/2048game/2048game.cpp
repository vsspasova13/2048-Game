#include <iostream>
#include <fstream>
using namespace std;

/**
*
* Solution to course project #4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @Velislava Spasova 
* @9MI0600353 
* @GCC 
*
*
*/


unsigned const int MAX_NICKNAME_SIZE = 100;
unsigned const int MAX_MATRIX_SIZE = 10;
unsigned const int SIZE_OF_LEADERBOARD = 5;
unsigned const int SPACE_BETWEEN_NUMBERS = 5;

bool difference = false;

bool isValidSize(int size)
{
	return (size >= 4 && size <= 10);
}

bool isValidDirection(char dir)
{
	return (dir == 'w' || dir == 'a' || dir == 's' || dir == 'd');
}

bool isValidOption(int option)
{
	return (option == 1 || option == 2 || option == 3);
}

void myStrcpy(char* source, char* dest)
{
	if (!source || !dest)
		return;
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}

unsigned myStrlen(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str)
	{
		result++;
		str++;
	}
	return result;
}

void myStrcat(char* first, char* second)
{
	if (!first || !second)
		return;

	size_t firstLen = myStrlen(first);
	first += firstLen;
	myStrcpy(second, first);
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b; b = temp;
}

bool isMatrixFull(int matrix[][MAX_MATRIX_SIZE], unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}

void fillMatrixWithZeros(int matrix[][MAX_MATRIX_SIZE], unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

int lengthOfNumber(int n)
{
	if (n == 0)return 1;
	int length = 0;
	while (n > 0)
	{
		length++;
		n /= 10;
	}
	return length;
}

void printMatrix(int matrix[][MAX_MATRIX_SIZE], unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{

			cout << matrix[i][j];
			int length = lengthOfNumber(matrix[i][j]);

			for (int k = 0; k < SPACE_BETWEEN_NUMBERS - length; k++)
			{
				cout << " ";
			}
		}
		cout << endl;
		cout << endl;
	}
}

void print(int matrix[][MAX_MATRIX_SIZE], unsigned int size, unsigned int result)
{
	system("CLS");
	printMatrix(matrix, size);
	cout << "Result: " << result << endl;
}

unsigned int calculateResult(int matrix[][MAX_MATRIX_SIZE], unsigned int size, unsigned int& result)
{
	result = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			result += matrix[i][j];
		}
	}
	return result;
}

void generateRandomIndex(int matrix[][MAX_MATRIX_SIZE], unsigned int size, unsigned int& randX, unsigned int& randY)
{
	randX = (rand() % size);
	randY = (rand() % size);
	while (matrix[randX][randY] != 0 && difference == 1)
	{
		randX = (rand() % size);
		randY = (rand() % size);

	}

}

void putRandomNumber(int matrix[][MAX_MATRIX_SIZE], unsigned int size, unsigned int x, unsigned int& y)
{
	int m = 2 * (rand() % 2 + 1);
	matrix[x][y] = m;
}

void randomNumber(int matrix[][MAX_MATRIX_SIZE], unsigned int size, unsigned int& x, unsigned int& y)
{
	if (isMatrixFull(matrix, size) || difference == 0)
	{
		return;
	}
	else
	{
		generateRandomIndex(matrix, size, x, y);
		putRandomNumber(matrix, size, x, y);
	}
}

bool isGameOver(int matrix[][MAX_MATRIX_SIZE], unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int upEl = -1, downEl = -1, rightEl = -1, leftEl = -1;

			if (i - 1 >= 0)
			{
				upEl = matrix[i - 1][j];
			}
			if (i + 1 < size)
			{
				downEl = matrix[i + 1][j];
			}
			if (j + 1 < size)
			{
				rightEl = matrix[i][j + 1];
			}
			if (j - 1 >= 0)
			{
				leftEl = matrix[i][j - 1];
			}

			int currentEl = matrix[i][j];

			if (currentEl == downEl || currentEl == upEl || currentEl == rightEl || currentEl == leftEl)return false;

		}
	}
	return true;
}

void readingFromFile(int points[6], char nicknames[6][MAX_NICKNAME_SIZE], size_t size)
{
	int rank;
	char fileName[10][13] = { "../4x4.txt", "../5x5.txt", "../6x6.txt", "../7x7.txt",
							 "../8x8.txt", "../9x9.txt", "../10x10.txt" };

	ifstream file(fileName[size - 4]);

	if (!file.is_open())
	{
		cout << "Error opening the file." << endl;
		return;
	}

	for (int i = 0; i < SIZE_OF_LEADERBOARD; ++i)
	{
		if (!(file >> rank >> nicknames[i] >> points[i] >> ws))
		{
			cout << "Error while reading from file." << endl;
			break;
		}
	}
	file.close();
}

void writeInFile(int points[], char nicknames[][MAX_NICKNAME_SIZE], int size)
{
	char fileName[10][13] = { "../4x4.txt", "../5x5.txt", "../6x6.txt", "../7x7.txt",
							 "../8x8.txt", "../9x9.txt", "../10x10.txt" };

	ofstream file(fileName[size - 4]);
	if (!file.is_open())
	{
		cout << "Error opening the file." << endl;
		return;
	}

	for (int i = 0; i < SIZE_OF_LEADERBOARD; i++)
	{
		file << i + 1 << " " << nicknames[i] << " " << points[i] << endl;
	}
	file.close();
}

void swapStr(char* str1, char* str2)
{
	char copy[MAX_NICKNAME_SIZE];
	myStrcpy(str1, copy);
	myStrcpy(str2, str1);
	myStrcpy(copy, str2);
}

void changeLeadboard(int result, char* nickname, size_t size)
{
	int points[SIZE_OF_LEADERBOARD+1];
	char nicknames[SIZE_OF_LEADERBOARD+1][MAX_NICKNAME_SIZE];

	readingFromFile(points, nicknames, size);

	if (points[SIZE_OF_LEADERBOARD-1] >= result)
	{
		return;
	}
	points[SIZE_OF_LEADERBOARD] = result;
	myStrcpy(nickname, nicknames[SIZE_OF_LEADERBOARD]);

	for (int i = 0; i < SIZE_OF_LEADERBOARD+1; i++)
	{

		for (int j = 0; j < SIZE_OF_LEADERBOARD - i; j++)
		{

			if (points[j] < points[j + 1])
			{
				swap(points[j], points[j + 1]);
				swapStr(nicknames[j], nicknames[j + 1]);
			}
		}
	}

	writeInFile(points, nicknames, size);

}

void printLeadboard()
{
	cout << "Choose size: ";
	int leadboardSize;
	cin >> leadboardSize;
	cout << endl;

	char fileName[10][13] = { "../4x4.txt", "../5x5.txt", "../6x6.txt", "../7x7.txt",
						 "../8x8.txt", "../9x9.txt", "../10x10.txt" };

	ifstream file(fileName[leadboardSize - 4]);

	if (!file.is_open())
	{
		cout << "Error opening the file." << endl;
		return;
	}
	char line[MAX_NICKNAME_SIZE];
	cout << "LEADBOARD FOR SIZE " << leadboardSize << "x" << leadboardSize << endl;
	cout << endl;
	cout << "RANK: NICKNAME: POINTS:" << endl;
	cout << "----------------------" << endl;
	while (!file.eof())
	{
		file.getline(line, MAX_NICKNAME_SIZE);
		cout << line << endl;

	}
	cout << endl;
	file.clear();
	file.close();
}

bool logic(int matrix[][MAX_MATRIX_SIZE], unsigned int size, unsigned int& result, char* nickname, bool& flag)
{
	unsigned int randX, randY;
	if (flag)
	{
		difference = true;
		randomNumber(matrix, size, randX, randY);
		flag = false;
	}

	if (!isMatrixFull(matrix, size))
	{

		randomNumber(matrix, size, randX, randY);
		calculateResult(matrix, size, result);
		print(matrix, size, result);
	}
	else if (isGameOver(matrix, size))
	{
		changeLeadboard(result, nickname, size);
		return false;
	}
	return true;
}

void fillWithValue(bool arr[][MAX_MATRIX_SIZE], unsigned int size, bool value)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			arr[i][j] = value;
		}
	}
}

void moveDownColumns(int matrix[][MAX_MATRIX_SIZE], unsigned int size, int coll)
{
	int i = size - 1, ind = size - 1;
	while (matrix[i][coll] != 0)
	{
		ind--;
		i--;
	}
	//ind-the index of the first null
	while (i >= 0)
	{
		if (matrix[i][coll] != 0)
		{
			matrix[ind][coll] = matrix[i][coll];
			difference = true;
			matrix[i][coll] = 0;
			ind--;
			i--;
		}
		else { i--; continue; }
	}
}

void calculateDown(int matrix[][MAX_MATRIX_SIZE], unsigned int size, bool arr[][MAX_MATRIX_SIZE])
{
	for (int i = size - 1; i > 0; i--)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0 && matrix[i - 1][j] == matrix[i][j] && arr[i][j] == false)
			{
				matrix[i][j] += matrix[i - 1][j]; matrix[i - 1][j] = 0; arr[i - 1][j] = true;
			}
		}
	}
}

void moveUpColumns(int matrix[][MAX_MATRIX_SIZE], unsigned int size, int coll)
{
	int i = 0, ind = 0;
	while (matrix[i][coll] != 0)
	{
		ind++;
		i++;
	}
	while (i < size)
	{
		if (matrix[i][coll] != 0)
		{
			matrix[ind][coll] = matrix[i][coll];
			difference = true;
			matrix[i][coll] = 0;
			ind++; i++;
		}
		else { i++; continue; }
	}
}

void calculateUp(int matrix[][MAX_MATRIX_SIZE], unsigned int size, bool arr[][MAX_MATRIX_SIZE])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0 && matrix[i + 1][j] == matrix[i][j] && arr[i][j] == false)
			{
				matrix[i][j] += matrix[i + 1][j]; matrix[i + 1][j] = 0; arr[i + 1][j] = true;
			}
		}

	}
}

void moveLeftColumns(int matrix[][MAX_MATRIX_SIZE], unsigned int size, int row)
{
	int i = 0, ind = 0;
	while (matrix[row][i] != 0)
	{
		ind++;
		i++;
	}
	while (i < size)
	{
		if (matrix[row][i] != 0)
		{
			matrix[row][ind] = matrix[row][i];
			difference = true;
			matrix[row][i] = 0;
			ind++; i++;
		}
		else { i++; continue; }
	}
}

void calculateLeft(int matrix[][MAX_MATRIX_SIZE], unsigned int size, bool arr[][MAX_MATRIX_SIZE])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0 && matrix[i][j + 1] == matrix[i][j] && arr[i][j] == false)
			{
				matrix[i][j] += matrix[i][j + 1]; matrix[i][j + 1] = 0; arr[i][j + 1] = true;
			}
		}

	}
}

void moveRightColumns(int matrix[][MAX_MATRIX_SIZE], unsigned int size, int row)
{
	int i = size - 1, ind = size - 1;
	while (i >= 0 && matrix[row][i] != 0)
	{
		ind--;
		i--;
	}
	while (i >= 0)
	{
		if (matrix[row][i] != 0)
		{
			matrix[row][ind] = matrix[row][i];
			difference = true;
			matrix[row][i] = 0;
			ind--; i--;
		}
		else { i--; }
	}
}

void calculateRight(int matrix[][MAX_MATRIX_SIZE], unsigned int size, bool arr[][MAX_MATRIX_SIZE])
{
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0 && matrix[i][j + 1] == matrix[i][j] && arr[i][j] == false)
			{
				matrix[i][j] += matrix[i][j + 1]; matrix[i][j + 1] = 0; arr[i][j + 1] = true;
			}
		}

	}
}

void moveUp(int matrix[][MAX_MATRIX_SIZE], unsigned int size, bool arr[][MAX_MATRIX_SIZE])
{
	fillWithValue(arr, size, false);
	for (int i = 0; i < size; i++)
	{
		moveUpColumns(matrix, size, i);
	}
	calculateUp(matrix, size, arr);
	for (int i = 0; i < size; i++)
	{
		moveUpColumns(matrix, size, i);
	}
}

void moveDown(int matrix[][MAX_MATRIX_SIZE], unsigned int size, bool arr[][MAX_MATRIX_SIZE])
{
	fillWithValue(arr, size, false);
	for (int i = 0; i < size; i++)
	{
		moveDownColumns(matrix, size, i);
	}
	calculateDown(matrix, size, arr);
	for (int i = 0; i < size; i++)
	{
		moveDownColumns(matrix, size, i);
	}
}

void moveLeft(int matrix[][MAX_MATRIX_SIZE], unsigned int size, bool arr[][MAX_MATRIX_SIZE])
{
	fillWithValue(arr, size, false);
	for (int i = 0; i < size; i++)
	{
		moveLeftColumns(matrix, size, i);
	}
	calculateLeft(matrix, size, arr);
	for (int i = 0; i < size; i++)
	{
		moveLeftColumns(matrix, size, i);
	}
}

void moveRight(int matrix[][MAX_MATRIX_SIZE], unsigned int size, bool arr[][MAX_MATRIX_SIZE])
{
	fillWithValue(arr, size, false);
	for (int i = 0; i < size; i++)
	{
		moveRightColumns(matrix, size, i);
	}
	calculateRight(matrix, size, arr);
	for (int i = 0; i < size; i++)
	{
		moveRightColumns(matrix, size, i);
	}
}

void moves(int matrix[][MAX_MATRIX_SIZE], unsigned int size, char dir, bool arr[][MAX_MATRIX_SIZE])
{
	difference = false;
	if (dir == 'w')
	{
		moveUp(matrix, size, arr);
	}

	if (dir == 's')
	{
		moveDown(matrix, size, arr);
	}

	if (dir == 'a')
	{
		moveLeft(matrix, size, arr);
	}

	if (dir == 'd')
	{
		moveRight(matrix, size, arr);
	}
}

void game()
{
	char nickname[MAX_NICKNAME_SIZE];
	cout << "Enter your nickname: ";
	cin.getline(nickname, MAX_NICKNAME_SIZE);

	unsigned int matrixSize;
	do
	{
		cout << "Enter size: ";
		cin >> matrixSize;

	} while (!isValidSize(matrixSize));

	int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
	fillMatrixWithZeros(matrix, matrixSize);

	unsigned int result = 0;

	bool isFirstMove = true;

	bool arr[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
	fillWithValue(arr, matrixSize, false);
	do
	{
		char dir;
		do
		{
			cout << "Enter direction: ";
			cin >> dir;

		} while (!isValidDirection(dir));

		if (!logic(matrix, matrixSize, result, nickname, isFirstMove))break;
		moves(matrix, matrixSize, dir, arr);

	} while (logic(matrix, matrixSize, result, nickname, isFirstMove));

	cout << "Game over" << endl;

}

void printMenu()
{
	cout << "1. Start game" << endl << "2. Leadboard" << endl << "3. Quit" << endl;
}

int chooseOption()
{
	unsigned int option;
	do
	{
		cout << "Option: ";
		cin >> option;
		cin.ignore();
	} while (!isValidOption(option));

	return option;
}

int main()
{

	srand(time(0));
	printMenu();

	unsigned int option = chooseOption();

	while (true)
	{
		if (option == 1)
		{
			game();
		}
		if (option == 2)
		{
			printLeadboard();
		}
		if (option == 3) return 0;
		printMenu();
		option = chooseOption();

	}

}


