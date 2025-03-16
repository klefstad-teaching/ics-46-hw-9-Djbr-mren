#include "dijkstras.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    Graph G;

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Cannot open file " << filename << endl;
        return 1;
    }

    infile >> G;
    infile.close();

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    cout << "Shortest paths from vertex 0:\n";
    for (int i = 0; i < distances.size(); ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        cout << "To " << i << ": ";
        print_path(path, distances[i]);
    }

    return 0;
}
