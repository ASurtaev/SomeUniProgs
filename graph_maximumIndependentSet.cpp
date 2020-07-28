//
//  main.cpp
//  alg_sem4_lab5
//
//  Created by Александр Суртаев on 08/09/2019.
//  Copyright © 2019 Александр Суртаев. All rights reserved.
// Имеется n проектов, которые должны быть выполнены. Для выполнения про- екта xi требуется некоторое подмножетсво Ri наличных ресурсов из множества {1, ..., p}. Пусть каждый проект, задаваемый совокупностью средств, необходимых для его реализации, может быть выполнен за один и тот же промежуток времени. Построим граф G, каждая вер- шина которого соответствует некоторому проекту, а ребро (xi, xj) наличию общих средств обеспечения у проектов xi и xj. Какое максимальное множество проектов, которое можно выполнить одновременно за один и тот же промежуток времени?

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <locale.h>
#include <math.h>
#include <vector>
#include <array>
#include <queue>
#include <list>
#include <set>
#define inf 2147483647
using namespace std;

ifstream fin("Desktop/study/alg 4th semester/lab5/alg5_input_graph");

int** maximumIndependentSet(int **mas, int n){
    queue<int> currIndElem; //очередь из независимых эл-тов, по которым осущ поиск
    int **nodes = new int* [n]; //две строки в массиве
    for (int count = 0; count < n; count++)
        nodes[count] = new int [n];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            nodes[i][j] = 0;
    
    int **result = new int* [n]; //две строки в массиве
    for (int count = 0; count < n; count++)
        result[count] = new int [n];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            result[i][j] = -1;
    for(int m = 0; m < n; m++){
        nodes[m][m] = 2;
        int isEndFlag = 0;
        result[m][m] = m;
        currIndElem.push(m);
        while(!currIndElem.empty() && !isEndFlag){
            int current = currIndElem.front();
            currIndElem.pop();
            for(int i = 0; i < n; i++)
                if(mas[current][i] != 0 && (nodes[m][i] == 0 || nodes[m][i] == 1)){
                    nodes[m][i] = 3;
                }
            for(int i = 0; i < n; i++){
                if(nodes[m][i] == 3){
                    for(int j = 0; j < n; j++){
                        if(mas[i][j] != 0 && nodes[m][j] == 0){
                            nodes[m][j] = 2;
                            currIndElem.push(j);
                            result[m][j] = j;
                            for(int k = 0; k < n; k++)
                                if(mas[j][k] != 0 && nodes[m][k] == 0)
                                    nodes[m][k] = 1;
                        }
                    }
                }
            }
            isEndFlag = 1;
            for(int i = 0; i < n; i++)
                if(nodes[m][i] == 0){
                    isEndFlag = 0;
                    break;
                }
            
            if(currIndElem.empty() && !isEndFlag)
                for(int i = 0; i < n; i++)
                    if(nodes[m][i] == 0){
                        currIndElem.push(i);
                        result[m][i] = i;
                    }
        }
        while(!currIndElem.empty())
            currIndElem.pop();
    }
    return result;
}

int main(){
    
    int errorFlag = 0;
    
    ifstream fin("Desktop/study/alg 4th semester/lab5/alg5_input_graph");
    if (!fin.is_open()) cout << "Файл ввода не открылся!\n";
    else if (fin.peek() == EOF) cout << "Файл ввода пуст!\n";
    else {
        int nums[100][100];
        int rowsCounter = 0;
        int colsCounter = 0;
        int previousCols = 0;
        while(fin.peek() != '\0' && fin.peek() != EOF){
            if(fin.peek() == '\n'){
                rowsCounter++;
                if(previousCols == 0)
                    previousCols = colsCounter;
                else
                    if(previousCols != colsCounter){
                        errorFlag = 1; break;
                    }
                colsCounter = 0;
            }
            fin >> nums[rowsCounter][colsCounter++];
        }
        rowsCounter++;
        if(rowsCounter != colsCounter || errorFlag != 0) cout << "Ошибка ввода!\n";
        else{
            int **mas = new int* [rowsCounter]; //две строки в массиве
            for (int count = 0; count < rowsCounter; count++)
                mas[count] = new int [rowsCounter];
            
            for(int i = 0; i < rowsCounter; i++)
                for(int j = 0; j < rowsCounter; j++)
                    mas[i][j] = nums[i][j];
            cout << "Матрица смежности:\n";
            for(int i = 0; i < rowsCounter; i++){
                for(int j = 0; j < rowsCounter; j++){
                    cout.width(2);
                    cout << mas[i][j] << " ";
                }
                cout << "\n";
            }
            
            int **result = maximumIndependentSet(mas, rowsCounter);
            
            cout << "Максимальное независимое множество:\n";
            int *maxIS = new int [rowsCounter];
            for(int i = 0; i < rowsCounter; i++)
                maxIS[i] = 0;
            for(int i = 0; i < rowsCounter; i++)
                for(int j = 0; j < rowsCounter; j++)
                    if(result[i][j] != -1)
                        maxIS[i]++;
            
            int maxID = 0;
            for(int i = 0; i < rowsCounter; i++)
                if(maxIS[maxID] < maxIS[i])
                    maxID = i;
            
            for(int i = 0; i < rowsCounter; i++)
                if(result[maxID][i] != -1)
                    cout << result[maxID][i] << " ";
        }
    }
    return 0;
}


