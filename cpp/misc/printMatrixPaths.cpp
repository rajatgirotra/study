#include <iostream>
#include <cstdlib>
using namespace std;

bool** matrix =  0;
int printPaths(int r, int c, int rows, int cols)
{
    if((r == (rows-1)) && (c == (cols - 1)))
        return 1;
    else if ( (r >= rows) || (c >= cols) || !matrix[r][c])
        return 0;
    else
        return printPaths(r+1, c, rows, cols) + printPaths(r, c+1, rows, cols);
}

int main()
{
    int rows, cols;
    cout << "Rows: ";
    cin>>rows;
    cout << "Cols: ";
    cin>>cols;

    matrix = (bool**)malloc(rows * sizeof(bool*));
    for(int i = 0; i < rows; ++i)
    {
        matrix[i] = (bool*)malloc(cols * sizeof(bool));
    }
    for(int i = 0;  i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            cout << "matrix[" << i << "," << j << "] (0 or 1 only): ";
            cin >> matrix[i][j];
        }
    }

    cout << printPaths(0, 0, rows, cols) << endl;
}
