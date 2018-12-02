//
//  main.cpp
//  Dijkstra
//
//  Created by Ibrahim El Mountasser on 02/12/2018.
//  Copyright © 2018 Ibrahim El Mountasser. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iterator>

const int SIZE = 201;

struct Node{
    int data;
    int weight;
    struct Node* next;
    
};
struct LinkedList {
    struct Node* head = NULL;
};
class Graph {
private:
    LinkedList list[SIZE];
    int dist[SIZE];
    int src[SIZE];
    
public:
    Graph(std::string fileName) {

        std::ifstream infile(fileName);
        if(!infile.is_open()) return;
        std::string line;
        
        int i = 0;
        while ( i < SIZE && getline(infile, line) )
        {
            std::istringstream str(line);
            int u;
            int w;
            
            str >> u;
            if ( u > SIZE )
            {
                // Problem.
                std::cout<<"u is too large!"<<std::endl;
                exit(-1);
            }
            
            int v;
            char c;
            while ( str >> v >> c >> w)
            {
                if( u < v)
                {
                    createEdge(u, v, w);
                }
            }

    }
    
    
    }
    Node* createNode(int data, int weight){
        Node* newNode = new Node;
        newNode->data = data;
        newNode->weight = weight;
        newNode->next = NULL;
        return newNode;
    }
    void createEdge(int src, int dist, int weight) {
        Node* newNode = createNode(dist, weight);
        newNode->next = list[src].head;
        list[src].head = newNode;
        newNode = createNode(src, weight);
        newNode->next = list[dist].head;
        list[dist].head = newNode;
        
    }
    void printGraph() {
        for (int i=0; i<SIZE; i++) {
            std::cout<<"# "<<i;
        
            Node* temp = list[i].head;

            while (temp != NULL) {
                std::cout<<" -> "<<temp->data<<","<<temp->weight;
                temp = temp->next;
               
            }
            std::cout<<std::endl;
        }
    }
    void dijkstra() {
        std::map<int, int> shortestPath;
        bool done[SIZE];
        for (int i=0; i<SIZE; i++) {
            dist[i] = 1000000;
            shortestPath[i] = 1000000;
            done[i] = false;
        }
     
        shortestPath[1] = 0;
        int cost = shortestPath[1];
        done[1] = 1;
        Node* temp = list[1].head;
        shortestPath.erase(0);
        shortestPath.erase(1);
        dist[1] = 0;
        
        int current = 1;
        while (!shortestPath.empty()) {
            while (temp != NULL) {
                if ( done[temp->data] == false) {
                    if (shortestPath[temp->data] > cost + temp->weight) {
                        shortestPath[temp->data] = cost + temp->weight;
                        src[temp->data] = current;
                    }
                }
                
                temp = temp->next;
            }
            int min = shortestPath.begin()->second;
            int minIndex = shortestPath.begin()->first;
            for (std::map<int, int>::iterator itr = shortestPath.begin(); itr != shortestPath.end(); ++itr) {
                if (itr->second < min) {
                    minIndex = itr->first;
                    min = itr->second;
                }
            }
            current = minIndex;
            temp = list[minIndex].head;
            cost = shortestPath[minIndex];
            dist[minIndex] = shortestPath[minIndex];
            done[minIndex] = 1;
            shortestPath.erase(minIndex);
        }
  

        
    }
    void path(int v) {
        int i=v;
        while (src[i] != 1) {
            
            std::cout<<src[i]<<"<-";
            i = src[i];
        }
        std::cout<<"i #";
        std::cout<<std::endl;
        std::cout<<"Distance : "<<dist[v]<<std::endl;

        
    }
    void printDist() {
        for (int i=0; i<SIZE; i++) {
            std::cout<<i<<" : "<<dist[i]<<std::endl;
        }
    }
    
};

int main() {
    Graph gr("data.txt");
    gr.dijkstra();
    //All distances from V:1
    gr.printDist();
    //Path from V:1 to W:18
    gr.path(18);

  

    

    return 0;
}
