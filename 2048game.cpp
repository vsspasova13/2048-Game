#include <iostream>
using namespace std;

unsigned const int MAX_NICKNAME_SIZE = 100;
unsigned const int MAX_MATRIX_SIZE = 10;

bool difference = false;

bool gameOver = false;

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

int lengthOfMaxNumber(int n)
{
	if (n == 0)return 1;
	int length = 0;
	while (n > 0)
	{
		length++;
		n/=10;
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
			int l = lengthOfMaxNumber(matrix[i][j]);

			for (int k = 0; k < 5-l; k++)
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

	}//izbirame proizvolno mqsto ot matricata kudeto da postavim proizv element(2,4)

}

void generateAndPutRandomNumber(int matrix[][MAX_MATRIX_SIZE], unsigned int size, unsigned int x, unsigned int& y)
{//dve funkcii
	if (isMatrixFull(matrix, size) || difference == 0) { return; }
	else
	{
		generateRandomIndex(matrix, size, x, y);
		int m = 2 * (rand() % 2 + 1);
		matrix[x][y] = m;
	}

}

bool isGameOver(int matrix[][MAX_MATRIX_SIZE], unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int upEl = 0, downEl = 0, rightEl = 0, leftEl = 0;
			if (i - 1 >= 0) 
			{
				upEl = matrix[i - 1][j];
			}
			if(i+1<size)
			{ 
			downEl = matrix[i + 1][j];
			}
			if(j + 1 < size)
			{
			rightEl = matrix[i][j + 1];
			}
			if (j-1>=0)
			{
			leftEl = matrix[i][j - 1];
			}

			int currentEl = matrix[i][j];

			if (currentEl == downEl || currentEl == upEl || currentEl == rightEl || currentEl == leftEl)return false;

		}
	}
	return true;
}

void game(int matrix[][MAX_MATRIX_SIZE], unsigned int size, unsigned int result)//logic
{
	unsigned int randX, randY;
	if (!isMatrixFull(matrix, size))
	{
		generateRandomIndex(matrix, size, randX, randY);
		generateAndPutRandomNumber(matrix, size, randX, randY);
		calculateResult(matrix, size, result);
		print(matrix, size, result);
	}
	else if (isGameOver(matrix, size)) { print(matrix, size, result); gameOver = true; }
}

void startGame(int matrix[][MAX_MATRIX_SIZE], unsigned int size, unsigned int result)
{
	difference = true;
	unsigned int randX, randY;
	generateRandomIndex(matrix, size, randX, randY);
	generateAndPutRandomNumber(matrix, size, randX, randY);
	game(matrix, size, result);

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
	//i = ind;
	while (i >= 0)
	{
		if (matrix[i][coll] != 0)
		{
			matrix[ind][coll] = matrix[i][coll]; difference = true;
			matrix[i][coll] = 0; ind--; i--;
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

	i = ind;
	while (i < size)
	{
		if (matrix[i][coll] != 0)
		{
			matrix[ind][coll] = matrix[i][coll]; difference = true;
			matrix[i][coll] = 0; ind++; i++;
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

	i = ind;
	while (i < size)
	{
		if (matrix[row][i] != 0)
		{
			matrix[row][ind] = matrix[row][i]; difference = true;
			matrix[row][i] = 0; ind++; i++;
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
	//da go opravq
	//i = ind;
	while (i >= 0)
	{
		if (matrix[row][i] != 0)
		{
			matrix[row][ind] = matrix[row][i]; difference = true;
			matrix[row][i] = 0; ind--; i--;
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

void moves(int matrix[][MAX_MATRIX_SIZE], unsigned int size, char dir, bool arr[][MAX_MATRIX_SIZE])
{
	difference = false;
	if (dir == 'w')
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

	if (dir == 's')
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

	if (dir == 'a')
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

	if (dir == 'd')
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

}

int main()
{
	srand(time(0));
	cout << "1. Start game" << endl << "2. Leadboard" << endl << "3. Quit" << endl;
	unsigned int option;
	cin >> option;
	char c;
	cin.get(c);
	if (option == 1)
	{
		char nickname[MAX_NICKNAME_SIZE];
		cin.getline(nickname, MAX_NICKNAME_SIZE);
		cout << nickname << endl;

		//validaciq
		unsigned int matrixSize;
		cin >> matrixSize;//validaciq

		int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
		fillMatrixWithZeros(matrix, matrixSize);

		int result = 0;

		startGame(matrix, matrixSize, result);

		bool arr[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
		fillWithValue(arr, matrixSize, false);

		while (!gameOver)
		{

			char dir; cin >> dir;
			moves(matrix, matrixSize, dir, arr);
			game(matrix, matrixSize, result);

		}
		cout << "Game over";
	}


}

//kato nqma kak da se murdat da ne generira chislo  +
//da opravq vs funkcii
//validdaciq
//winning/losing cond                               +
//nqkak si da proverqvam dali ima mqsto prazno v matricata shtoto taka stava bezkraen while v generate funkciqta +
// i suotvetno taka da razbiram dali igrata e prikluchila   +
// *s promenliva??    +
//da opravq forovete v moves

// kraqt na igrata ne e kto e zapulnena matricata a kato nqma poveche hodove

