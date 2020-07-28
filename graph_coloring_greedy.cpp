//
//  main.cpp
//  lag_sem4_lab6
//
//  Created by Александр Суртаев on 08/09/2019.
//  Copyright © 2019 Александр Суртаев. All rights reserved.
// Для детей была построена игровая площадка, состоящая из n платформ, соеди- ненных дорожками. Платформы было решено правильно покрасить в k цветов, исходя из их наличного количества. Под правильной раскраской понимается вершинная раскраска графа. Проверить, возможно ли это. Граф задан матрицей смежности.

//жадный алгоритм
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <locale.h>
#include <math.h>
#include <vector>
#include <array>
using namespace std;

int fromFile(vector<int> &matrix) { //создание графа из матрицы смежности
    ifstream file;
    file.open("Desktop/study/alg 4th semester/lab6/alg6_input_graph");
    copy(istream_iterator<int>(file), istream_iterator<int>(), back_inserter(matrix));
    file.close();
    
    if (matrix.size() == 0) {
        cout << "Файл пуст или отсутствует" << endl;
        return 1;
    }
    if (sqrt(matrix.size()) != (long long)sqrt(matrix.size())) {
        cout << "Матрица не квадратная" << endl;
        return 1;
    }
    
    return 0;
}

void printColors(int color[], int s) {
    for (int i = 0; i < s; i++)
        cout << i << ":" << color[i] << " ";
    cout << endl;
}

bool isSafe (int v, vector<int> graph, int color[], int c, int s) {
    for (int i = 0; i < s; i++)
        if (graph.at(v * s + i) && c == color[i])
            return false;
    return true;
}

bool graphColoringUtil(vector<int> graph, int m, int color[], int v, int s) {
    if (v == s) //когда вершина равна размеру
        return true;
    
    for (int c = 1; c <= m; c++)
        if (isSafe(v, graph, color, c, s)) {
            color[v] = c;
            if (graphColoringUtil (graph, m, color, v+1, s))
                return true;
            color[v] = 0;
        }
    
    return false;
}

void graphColoring(vector<int> graph, int m, int s) {
    int color[s]; //массив цветов размера кол-ва вершин
    for (int i = 0; i < s; i++)
        color[i] = 0;  //всему 0
    
    if (!graphColoringUtil(graph, m, color, 0, s))
        cout << "Решения не существует" << endl;
    else
        cout << "Решение существует" << endl;
    printColors(color, s);
}

int main() {
    vector<int> matrix;
    if (fromFile(matrix))
        return 1;
    int s = sqrt(matrix.size());
    int m = 0;
    cout << "Введите кол-во цветов" << endl;
    cin >> m;
    graphColoring (matrix, m, s);
    return 0;
}
