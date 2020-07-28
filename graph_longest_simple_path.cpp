//
//  main.cpp
//  alg_sem4_lab1
//
//  Created by Александр Суртаев on 01/04/2019.
//  Copyright © 2019 Александр Суртаев. All rights reserved.
// 4. Найти самый длинный простой путь в графе.

#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <vector>
#include <array>
#include <queue>
#include <list>
using namespace std;

class Vertex { //вершины
public:
    int data;
    vector<Vertex*>* Outcoming;
    vector<Vertex*>* Incoming;
    Vertex(int new_data) {
        Outcoming = new vector<Vertex*>();
        Incoming = new vector<Vertex*>();
        data = new_data;
    }
};

class Graph { //сам граф с методами
public:
    vector<Vertex*>* Collection; //массив вершин
    Graph() {
        Collection = new vector<Vertex*>();
    }
    void Add(int value) {// добаввление
        Vertex* some_vertex = new Vertex(value);
        Collection->push_back(some_vertex);
        
    }
    void connectArc(Vertex* first, Vertex* second) { //создание дуги first->second
        first->Outcoming->push_back(second);
        second->Incoming->push_back(first);
    }
    void deleteArc(Vertex* first, Vertex* second) { //удаление дуги first->second
        for (int i = 0; i < first->Outcoming->size(); i++)
            if(first->Outcoming->at(i) == second)
                first->Outcoming->erase(first->Outcoming->begin() + i);
        for (int i = 0; i < second->Incoming->size(); i++)
            if(second->Incoming->at(i) == first)
                second->Incoming->erase(second->Incoming->begin() + i);
    }
    void Delete(Vertex* some_vertex) { //удаление веришины и её дуг
        for (int i = 0; i < some_vertex->Incoming->size(); i++)
            deleteArc(some_vertex->Incoming->at(i), some_vertex);
        for (int i = 0; i < some_vertex->Outcoming->size(); i++)
            deleteArc(some_vertex, some_vertex->Outcoming->at(i));
        for (int i = 0; i < Collection->size(); i++)
            if (Collection->at(i) == some_vertex)
                Collection->erase(Collection->begin() + i);
    }
    int fromAdjacencyMatrix() { //сздание графа из матрицы смежности
        vector<bool>* matrix = new vector<bool>();
//matrix->push_back(0);matrix->push_back(0);matrix->push_back(1);matrix->push_back(1);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);
//matrix->push_back(0);matrix->push_back(0);matrix->push_back(1);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);
//matrix->push_back(1);matrix->push_back(1);matrix->push_back(0);matrix->push_back(0);matrix->push_back(1);matrix->push_back(0);matrix->push_back(0);
//matrix->push_back(1);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);matrix->push_back(1);matrix->push_back(0);matrix->push_back(0);
//matrix->push_back(0);matrix->push_back(0);matrix->push_back(1);matrix->push_back(1);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);
//matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);matrix->push_back(1);
//matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);matrix->push_back(0);matrix->push_back(1);matrix->push_back(0);
        if (getAdjacencyMatrixFromFile(matrix)) //получение матрицы из файла + проверка на ошибки
            return 1;
        int size = sqrt(matrix->size());
        for (int i = 0; i < size; i++)
            Add(i);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (matrix->at(i*size + j))
                    connectArc(Collection->at(i), Collection->at(j));
        return 0;
    }
//    void DFS(int start) { //поиск в глубину
//        vector<bool>* used = new vector<bool>();
//        for (int i = 0; i < Collection->size(); i++) //помечаем белым всё
//            used->push_back(false);
//        for (int i = start; i < Collection->size(); i++) //берём вершины, начиная с заданной
//            if (!used->at(i))
//                DFSrec(Collection->at(i), used, i);
//        for (int i = 0; i < start; i++)
//            if (!used->at(i))
//                DFSrec(Collection->at(i), used, i);
//        cout << endl;
//    }
//    void BFS(int start) { //поиск в ширину
//        queue<Vertex*>* next = new queue<Vertex*>();
//        vector<Vertex*>* visited = new vector<Vertex*>();
//        next->push(Collection->at(start)); //начальный элемент
//        visited->push_back(Collection->at(start));
//        while (next->size()) {
//            Vertex* v = next->front(); //берем элемент из очереди
//            cout << v->data << " ";
//            next->pop();
//            for (int i = 0; i < v->Outcoming->size(); i++) { //добавляем в очередь связанные, с v эл-ты
//                bool visited_marker = false;
//                for (int j = 0; j < visited->size(); j++) //не добавляем посещённые
//                    if (visited->at(j) == v->Outcoming->at(i))
//                        visited_marker = true;
//                if (!visited_marker) {
//                    next->push(v->Outcoming->at(i));
//                    visited->push_back(v->Outcoming->at(i));
//                }
//            }
//        }
//        cout << endl;
//    }
    void longestPath() {
        vector<int>* new_path = new vector<int>();
        int paths[Collection->size() * Collection->size()][Collection->size()];
        for (int i = 0; i < Collection->size() * Collection->size(); i++)
            for (int k = 0; k < Collection->size(); k++)
                paths[i][k] = -1;
        int paths_counter = 0;
        unsigned long max = 0;
        for (int i = 0; i < Collection->size(); i++)
            for (int j = 0; j < Collection->size(); j++)
                if (!findLongestPathTwo(new_path, i, j)) {
                    if (new_path) {
                        for (int k = 0; k < new_path->size(); k++)
                            paths[paths_counter][k] = new_path->at(k);
                        paths_counter++;
                        if (max < new_path->size())
                            max = new_path->size();
                    }
                }
        for (int i = 0; i < paths_counter; i++)
            for (int k = 0; k < Collection->size(); k++)
                if ((k == max - 1) && (paths[i][k] != -1)) {
                    for (int j = 0; j < max; j++)
                        cout << paths[i][j] << " ";
                    cout << endl;
                }
        
    }
private:
    int findLongestPathTwo(vector<int>* new_path, int start, int destination) {
        if ( start != destination) {
            vector<bool>* used = new vector<bool>();
            for (int i = 0; i < Collection->size(); i++) //помечаем белым всё
                used->push_back(false);
            int* path = new int[Collection->size()];
            int path_index = 0;
            vector<int>* curr_longest_path = new vector<int>();
            findLongestPathRec(Collection->at(start), destination, used, start, path, path_index, curr_longest_path);
            if (curr_longest_path->size()) { //путь существует
                new_path->clear();
                for (int i = 0; i < curr_longest_path->size(); i++)
                    new_path->push_back(curr_longest_path->at(i));
                return 0;
            }
            return 1;
        }
        else
            return 1;
    }
    void findLongestPathRec(Vertex* element, int destination, vector<bool>* used, int n, int path[], int &path_index, vector<int>* curr_longest_path) { //рекурсивваная n-номер передающегося элемента в коллекции
        used->at(n) = true;
        path[path_index] = n;
        path_index++;
        if (n == destination) {
            if (path_index > curr_longest_path->size()) {
                curr_longest_path->clear();
                for (int i = 0; i < path_index; i++)
                    curr_longest_path->push_back(path[i]);
            }
        } else {
            for (int i = 0; i < element->Outcoming->size(); i++)
                for(int k = 0; k < Collection->size(); k++)
                    if(Collection->at(k) == element->Outcoming->at(i))
                        if (!used->at(k)) {
                            findLongestPathRec(element->Outcoming->at(i), destination, used, k, path, path_index, curr_longest_path);
                        }
        }
        path_index--; // Убираем текущую вершину из path[] и помечаем как непосещённую
        used->at(n) = false;
    }
//    void DFSrec(Vertex* element, vector<bool>* used, int n) { //рекурсивваня часть поиска в глубину
//        used->at(n) = true;
//        cout << element->data << " ";
//        for (int i = 0; i < element->Outcoming->size(); i++)
//            for (int k = 0; k < Collection->size(); k++)
//                if(Collection->at(k) == element->Outcoming->at(i))
//                    if (!used->at(k))
//                        DFSrec(element->Outcoming->at(i), used, k);
//    }
    int getAdjacencyMatrixFromFile(vector<bool>* matrix) { //получение матрицы смежности из файла
        FILE *file;
        file = fopen("debug.dat", "r");
        //file = fopen("Desktop/study/alg 4th semester/lab1/alg1_input_graph", "r");
        
        if (!file) {
            cout << "Файл input_graph.dat отсутствует. Завершение программы.";
            fclose(file);
            return 1;
        }
        char bufer;
        bufer = getc(file);
        while (bufer != EOF) {
            switch (bufer) {
                case '0':
                    matrix->push_back(false);
                    break;
                case '1':
                    matrix->push_back(true);
                    break;
                case '\n':
                    break;
                default:
                    cout << "В файле input_graph.dat обнаружены недопустимые символы, он должен состоять только из 0, 1 и знаковв переноса строки. Завершение программы." << endl;
                    fclose(file);
                    return 1;
                    break;
            }
            bufer = getc(file);
        }
        if (sqrt(matrix->size()) != (long long)sqrt(matrix->size()) ) { //проверка, что матрица квадратная
            cout << "В файле input_graph.dat матрица не квадратная" << endl;
            fclose(file);
            return 1;
        }
        fclose(file);
        return 0;
    }
};

int main(int argc, const char * argv[]) {
    Graph* my_graph = new Graph();
    if (my_graph->fromAdjacencyMatrix())
        return 1;
    cout << endl << "Longest path:" << endl;
    my_graph->longestPath();
    return 0;
}
