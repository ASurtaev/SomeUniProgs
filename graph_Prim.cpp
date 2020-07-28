//
//  main.cpp
//  alg_sem4_lab3
//
//  Created by Александр Суртаев on 30/04/2019.
//  Copyright © 2019 Александр Суртаев. All rights reserved.
// 9. Необходимо соединить некоторым образом между собой определенные факты, но соединение одного факта с разными имеет различную стоимость и необходимо суммарную стоимость минимизировать. Входные данные заданы в «input.txt». В первой строке содер- жится количество фактов. Далее следует матрица смежности, в которой 0 означает отсутст- вие возможности соединения фактов, а число отличное от нуля означает стоимость соедине- ния. В выходном файле «output.txt» должны содержаться соединения, которые указываются номерами фактов. Нумерация фактов начинается с 0. Для решения задачи использовать алгоритм Прима.

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
    void ostAdd(int n) {
        element *tmp = new element(n);
        Collection->push_back(tmp);
    }
    void connectArc(int first, int second, int value) { //создание дуги first->second
        link *tmp = new link(second, value);
        for (auto const& i : *Collection)
            if (i->number == first)
                i->edges->push_back(tmp);
    }
    void Output() {
        for (auto const& i : *Collection) {
            cout << endl << "vertex: " << i->number;
            cout << " edges: ";
            for (auto const& k :*i->edges) {
                cout << k->number << " ";
            }
        }
    }
    int fromAdjacencyMatrix() { //создание графа из матрицы смежности
        vector<int> matrix;
        ifstream file;
        file.open("Desktop/study/alg 4th semester/lab3/alg3_input_graph");
        matrix = read_ints(file);
        
        if (matrix.size() == 0) {
            cout << "Файл пуст или отсутствует" << endl;
            return 1;
        }
        if (sqrt(matrix.size()) != (long long)sqrt(matrix.size())) {
            cout << "Матрица не квадратная" << endl;
            return 1;
        }
        
        int size = sqrt(matrix.size());
        for (int i = 0; i < size; i++)
            Add();
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (matrix.at(i*size + j))
                    connectArc(i, j, matrix.at(i*size + j));
        return 0;
    }
    void Prim(Graph *ost_graph) {
        vector<int>* unused = new vector<int>();
        for (int i = 1; i < Collection->size(); i++)
            unused->push_back(i);
        ost_graph->ostAdd(0);
        
        while (unused->size()){ //все неиспользованные элементы
            int min = inf;
            //поиск минимальной связи
            for (auto const& ogit : *ost_graph->Collection) // эл-ты остоавного графа
                for (auto const& git : *Collection) //эл-ты  осн графа
                    if (git->number == ogit->number) // поиск эл-та остовного графа в осн графе
                        for (auto const& eit : *git->edges) { //связи эл-та в осн графе
                            //установка флага, есть ли этот э-нт среди неиспользованных
                            bool unused_flag = false;
                            for (int i = 0; i < unused->size(); i++)
                                if (unused->at(i) == eit->number)
                                    unused_flag = true;
                            if ((min > eit->key) && (eit->key > 0) && (unused_flag))
                                min = eit->key;
                        }
            
            for (auto const& ogit : *ost_graph->Collection) // эл-ты остоавного графа
                for (auto const& git : *Collection) //эл-ты  осн графа
                    if (git->number == ogit->number) // поиск эл-та остовного графа в осн графе
                        for (auto const& eit : *git->edges) { // связи эл-та в осн графе
                            //установка флага, есть ли этот э-нт среди неиспользованных
                            bool unused_flag = false;
                            for (int i = 0; i < unused->size(); i++)
                                if (unused->at(i) == eit->number)
                                    unused_flag = true;
                            //если это минимальная связь и эл-нт не использован
                            if ((min == eit->key) && (unused_flag)) {
                                //добавление э-та в остовной граф и нужные связи
                                ost_graph->ostAdd(eit->number);
                                ost_graph->connectArc(git->number, eit->number, eit->key);
                                ost_graph->connectArc(eit->number, git->number, eit->key);
                                //удаление исполькованного э-та из списка неиспользованных
                                for (auto it = unused->begin(); it != unused->end();)
                                    if (*it == eit->number)
                                        it = unused->erase(it);
                                    else
                                        ++it;
                                //переход к концу цикла
                                goto label1;
                            }
                        }
        label1:;
        }
        ost_graph->Output();
    }
private:
    vector<int> read_ints(istream& is) {
        vector<int> result;
        copy(istream_iterator<int>(is), istream_iterator<int>(), back_inserter(result));
        return result;
    }};

int main(int argc, const char * argv[]) {
    cout << endl;
    Graph* my_graph = new Graph();
    Graph* ost_graph = new Graph();
    my_graph->fromAdjacencyMatrix();
    my_graph->Prim(ost_graph);
    cout << endl;
    
    return 0;
}
