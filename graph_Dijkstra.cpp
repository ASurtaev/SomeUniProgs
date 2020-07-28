//
//  main.cpp
//  alg_sem4_lab2
//
//  Created by Александр Суртаев on 10/04/2019.
//  Copyright © 2019 Александр Суртаев. All rights reserved.
// 18. Найти вершины, максимально и минимально удаленные от заданной вершины. Граф задан списковой структурой. Все ребра имеют неотрицательный вес.

#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <vector>
#include <list>
#include <fstream>
#define inf 2147483647
using namespace std;

class link {
public:
    int number;
    int key;
    link (int new_number, int new_key) {
        number = new_number;
        key = new_key;
    }
};

class element {
public:
    int number;
    list<link*>* edges;
    element (int new_number) {
        number = new_number;
        edges = new list<link*>();
    }
};

class Graph {
public:
    list<element*>* Collection;
    Graph() {
        Collection = new list<element*>();
    }
    void Add() {
        element *tmp = new element(0);
        if (!Collection->empty())
            tmp->number = Collection->back()->number + 1;
        Collection->push_back(tmp);
    }
    void connectArc(int first, int second, int value) { //создание дуги first->second
        link *tmp = new link(second, value);
        for (auto const& i : *Collection)
            if (i->number == first) { //нахожу эл-нт first
                std::list<link*>::iterator n;
                n = i->edges->begin(); //итератор на начало списка связей
                for (auto const& k :*i->edges) { //проход по связям
                    if (k->key > value) { //если вес новой связи меньше, то вставить перед ней
                        i->edges->insert(n, tmp);
                        return;
                    }
                    ++n; //итератор ++
                }
                i->edges->push_back(tmp); //вставить в конец, если связь самая тяжелая
            }
    }
    int fromAdjacencyMatrix() { //создание графа из матрицы смежности
        vector<int> matrix; //храню матрицу в одномерном массиве
        ifstream file;
        file.open("Desktop/study/alg 4th semester/lab2/alg2_input_graph");
        matrix = read_ints(file);
        
        if (matrix.size() == 0) {
            cout << "Файл пуст или отсутствует" << endl;
            return 1;
        }
        if (sqrt(matrix.size()) != (long long)sqrt(matrix.size())) {
            cout << "Матрица не квадратная" << endl;
            return 1;
        }
        
        int size = sqrt(matrix.size()); //размерность матрицы
        for (int i = 0; i < size; i++)
            Add();
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (matrix.at(i*size + j)) {
                    if (matrix.at(i*size + j) > inf - 1) {
                        cout << "Слишком большой вес связи";
                        return 1;
                    }
                    else
                        connectArc(i, j, matrix.at(i*size + j));
                }
        
        return 0;
    }
    void findClosest(int vertex) {
        int min = inf;
        cout << "Веришины минимально удаленные от " << vertex << ": " << endl;
        for (auto const& i : *Collection)
            if (i->number == vertex) {
                min = i->edges->front()->key;
                for (auto const& k : *(i->edges))
                    if (k->key == min)
                        cout << k->number << " ";
                break;
            }
        cout << endl;
    }
    void findFar(int vertex) {
        bool visited[Collection->size()]; //инициализация
        int marks[Collection->size()];
        for (int i = 0; i < Collection->size(); i++) {
            visited[i] = false;
            marks[i] = inf;
        }
        marks[vertex] = 0;
        
        Dijkstra(vertex, visited, marks);
        
        cout << "Веришины максимально удаленные от " << vertex << ": " << endl;
        int max = 0;
        for (int i = 0; i < Collection->size(); i++)
            if (max < marks[i])
                max = marks[i];
        for (int i = 0; i < Collection->size(); i++)
            if (marks[i] == max)
                cout << i << " ";
        cout << endl;
        for (int i = 0; i < Collection->size(); i++)
            cout << i << ": " << marks[i] << " ";
        cout << endl;
    }
private:
    vector<int> read_ints(istream& is) {
        vector<int> result;
        copy(istream_iterator<int>(is), istream_iterator<int>(), back_inserter(result));
        return result;
    }
    int Dijkstra(int vertex, bool visited[], int marks[]) {
        
        bool finished = true;
        for (int i = 0; i < Collection->size(); i++) //найти, есть ли непосещенный эл-нт
            if (!visited[i]) {
                finished = false;
                break;
            }
        
        if (!finished) {
            for (auto const& el : *Collection)
                if (el->number == vertex)
                    for (auto const& lnk : *el->edges)
                        if ( ((lnk->key + marks[el->number]) < marks[lnk->number]) && (!visited[lnk->number]) ) //если метка вершины + путь до следущей меньше текущей метки, то заменить на сумму
                            marks[lnk->number] = lnk->key + marks[el->number];
            visited[vertex] = true;
            
            int next = 0;
            for (auto const& el : *Collection)
                if (el->number == vertex)
                    for (auto const& lnk : *el->edges)
                        if (!visited[lnk->number]) {
                            next = lnk->number;
                            break;
                        }
            
            Dijkstra(next, visited, marks);
        }
        return 0;
    }
};

int main(int argc, const char * argv[]) {
    Graph* my_graph = new Graph();
    int e = 0;
    if (my_graph->fromAdjacencyMatrix())
        return 1;
    cout << "От какого эл-та искать?" << endl;
    cin >> e;
    my_graph->findClosest(e);
    my_graph->findFar(e);
    
    return 0;
}
