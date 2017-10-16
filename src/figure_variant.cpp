#include "figure_variant.hpp"

vector<FigureVariant> create_variants(vector<Texture*> textures) {
    if (textures.size() < 2) {
        throw exception("At least two textures must be loaded");
    }

    vector<FigureVariant> figures;

    XY p00 = {0, 0};
    XY p01 = {0, 1};
    XY p10 = {1, 0};
    XY p11 = {1, 1};
    
    XY p02 = {0, 2};
    XY p03 = {0, 3};

    XY p20 = {2, 0};
    XY p30 = {3, 0};

    {     
        // [][]
        // [][]
        FigureVariant o;
        o.type = FigureType::O;
        o.texture = (textures.at(0));

        vector<XY> o_rotation = {p00, p01, p10, p11};

        o.rotations.push_back(o_rotation);

        figures.push_back(o);
    }

    {
        // []
        // [] [][][][]
        // []
        // []
        FigureVariant i;
        i.type = FigureType::I;
        i.texture = (textures.at(1));

        vector<XY> i_rotation1 = {p00, p01, p02, p03};
        vector<XY> i_rotation2 = {p00, p10, p20, p30};

        i.rotations.push_back(i_rotation1);
        i.rotations.push_back(i_rotation2);

        figures.push_back(i);
    }

    return figures;
}
