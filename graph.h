#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

//edits to this are likely not needed
template <class T>
struct Vertex {
  T label; // unique int for a vertex
  vector<T> adj_list;
  int indegree; // Part 2: number of nodes pointing in
  int top_num; // Part 2: topological sorting number
  Vertex(T l) : label(l) {top_num = 0;} //Part 1
  // You may include default constructor optionally.
  Vertex() { label = T(); indegree = 0; top_num = 0; }
};

// template <class T>
// ostream& operator<<(ostream &o, Vertex<T> v){};

// std::priority_queue may take takes three template parameters: <Type, ContainerType, Functor>
// syntax for custom compare functor
// Refer the instructions PDF last section for more information

// template<class T>
// class VertexCompare
// {
// public:
//   bool operator()(Vertex<T> v1, Vertex<T> v2){
//     //todo - implement here
//     return false;
//   }
// };

template <class T>
class Graph {
private:
  //c++ stl hash table
  unordered_map<T, Vertex<T>> node_set;

  //Use other data fields if needed
  vector<T> sorted;
  

public:
  Graph() {};  //No modification needed to default constructor. Can be used optionally if needed.
  ~Graph() {}; //No modification needed to destructor. Can be used optionally if needed.

  // build a graph - refer the instructions PDF for more information.
  void buildGraph(istream &input) {
    // loop until end of input stream
    while (!input.eof()) {
      // initialize
      string adjLine = "";
      T l;
      T adjValue;

      // get the rest of the values in the line
      getline(input, adjLine);

      if(adjLine == "") {
        break;
      }

      // put the line into a string stream
      istringstream iss(adjLine);

      // get the first value
      iss >> l;

      // initialize vecotor with label
      Vertex<T> v = Vertex<T>(l);
      
      // push back each of the values to the adj_list vector in vect
      while (iss >> adjValue) {
        (v.adj_list).push_back(adjValue);
      }

      // emplace the vertex
      node_set.emplace(l, v);

    }
  }

  // display the graph into o - refer the instructions PDF for more information.
  void displayGraph(ostream& o) {
    for (auto it = node_set.begin(); it != node_set.end(); ++it) {
      o << it->second.label << ": ";
        for (int i = 0; i < (it->second.adj_list).size(); ++i) {
          o << (it->second.adj_list)[i] << " ";
        }
      o << endl;
    }
  }

  //return the vertex at label, else throw any exception  - refer the instructions PDF for more information.
  Vertex<T> at(T label) {
    if (node_set.find(label) == node_set.end()) {
      throw out_of_range("Label is not in node_set.");
    }

    return node_set[label];
  }

  //return the graph size (number of verticies)
  int size() {
    return node_set.size();
  }

  // topological sort
  // return true if successful, false on failure (cycle)
  bool topological_sort() {
    int counter = 0;
    queue<T> q;

    // (for each Vertex v)
    for (auto it = node_set.begin(); it != node_set.end(); ++it) {
      if(it->second.indegree == 0) {
        q.emplace(it->first);
      }
    }

    while (!q.empty()) {
      // dequeue
      T label = q.front();
      q.pop();

      // get the vertex
      Vertex<T>& vert = node_set[label];

      // update top num
      vert.top_num = ++counter; // assign next num

      // add vertex to the vector
      sorted.push_back(label);

      // for each Vertex w adjacent to v
      for (int i = 0; i < (vert.adj_list).size(); ++i) {
        T l = (vert.adj_list)[i];
        Vertex<T>& w = node_set[l];
        // update indegree value
        --w.indegree;
        if (w.indegree == 0) {
          q.emplace(w.label);
        }
      }
    }

    if (counter != node_set.size()) {
      return false;
    }

    return true;
  }; // Part 2

  // find indegree
  void compute_indegree() {
    // for each vertex V
    for (auto it = node_set.begin(); it != node_set.end(); ++it) {
      (it->second).indegree = 0;
    }

    // for each vertex V
    for (auto it = node_set.begin(); it != node_set.end(); ++it) {
      // for each vertex w adjacent to v
      for (int i = 0; i < (it->second.adj_list).size(); ++i) {
        T l = (it->second.adj_list)[i];
        node_set[l].indegree++;
      }
    }
  }; // Part 2


  // print topological sort into o
  //  if addNewline is true insert newline into stream
  void print_top_sort(ostream& o, bool addNewline=true)
  { 
    //TODO - implement things here
    for (int i = 0; i < sorted.size(); i++) {
      o << sorted[i] << " ";
    }
    
    if(addNewline){o << '\n';};
  }; // Part 2
};

#endif
