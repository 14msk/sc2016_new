#include <string>
#include <vector>
#include "test_1.hpp"

mesh::mesh(const int m, const int n)
    : _VertexCoords(nullptr), _Topology(nullptr) {
        _VertexCoords = new double [m];
        _Topology = new int [n];
}

mesh:: ~mesh() {
}

void ReadFromBinary(std::string const& InFileName) {


}

void mesh::WriteToBinary(std::string const& OutFileName) const {
}
