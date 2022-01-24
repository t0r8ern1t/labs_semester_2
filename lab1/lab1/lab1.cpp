#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

void FillingMatrix(int n, vector<vector<int>> &matrix) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

int MultMember(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, int n, int a, int b) {
    int x = 0;
    for (int i = 0; i < n; ++i) {
        x += matrix1[a][i] * matrix2[i][b];
    }
    return x;
}

vector<vector<int>> Multiplying(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, int n) {
    vector<vector<int>> mult(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mult[i][j] = MultMember(matrix1, matrix2, n, i, j);
        }
    }
    return mult;
}

void PrintingMatrix(vector<vector<int>> &matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    ifstream in("input.txt");
    int n;
    in >> n;
    vector<vector<int>> matrix1(n, vector<int>(n));
    vector<vector<int>> matrix2(n, vector<int>(n));
    FillingMatrix(n, matrix1);
    FillingMatrix(n, matrix2);
    srand(time(0));
    vector<vector<int>> mult = Multiplying(matrix1, matrix2, n);
    clock_t time = clock();
    cout << "runtime " << time << endl;
    //PrintingMatrix(mult, n);

    return 0;
}
