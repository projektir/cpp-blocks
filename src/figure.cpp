#include "figure.hpp"

vector<FigureVariant> create_figures() {
    vector<FigureVariant> figures;

    XY p00 = {0, 0};
    XY p01 = {0, 1};
    XY p10 = {1, 0};
    XY p11 = {1, 1};
    
    XY p02 = {0, 2};
    XY p03 = {0, 3};

    XY p20 = {2, 0};
    XY p30 = {3, 0};

    // [][]
    // [][]
    FigureVariant o;

    vector<XY> o_rotation = {p00, p01, p10, p11};

    o.type = Figure::O;   
    o.rotations.push_back(o_rotation);

    figures.push_back(o);

    // []
    // [] [][][][]
    // []
    // []
    FigureVariant i;

    vector<XY> i_rotation1 = {p00, p01, p02, p03};
    vector<XY> i_rotation2 = {p00, p10, p20, p30};

    o.type = Figure::I;
    o.rotations.push_back(i_rotation1);
    o.rotations.push_back(i_rotation2);

    return figures;
}
