#include "figure_variant.hpp"

vector<FigureVariant> create_variants(vector<Texture*> textures) {
    if (textures.size() < 6) {
        throw exception("At least six textures must be loaded");
    }

    vector<FigureVariant> figures;

    XY p00 = {0, 0};
    XY p01 = {0, 1};
    XY p10 = {1, 0};
    XY p11 = {1, 1};

    XY p12 = {1, 2};
    XY p21 = {2, 1};
    
    XY p02 = {0, 2};
    XY p03 = {0, 3};

    XY p20 = {2, 0};
    XY p30 = {3, 0};

    {     
        // [][]
        // [][]
        FigureVariant o;
        o.type = FigureType::O;
        o.texture = textures.at(0);

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
        i.texture = textures.at(1);

        vector<XY> i_rotation1 = {p00, p01, p02, p03};
        vector<XY> i_rotation2 = {p00, p10, p20, p30};

        i.rotations.push_back(i_rotation1);
        i.rotations.push_back(i_rotation2);

        figures.push_back(i);
    }

    {
        // []   [][][]    []     
        // [][]   []    [][]   []
        // []             [] [][][]
        FigureVariant t;
        t.type = FigureType::T;
        t.texture = textures.at(2);

        vector<XY> t_rotation1 = {p00, p01, p11, p02};
        vector<XY> t_rotation2 = {p00, p10, p11, p20};
        vector<XY> t_rotation3 = {p01, p10, p11, p12};
        vector<XY> t_rotation4 = {p01, p10, p11, p21};

        t.rotations.push_back(t_rotation1);
        t.rotations.push_back(t_rotation2);
        t.rotations.push_back(t_rotation3);
        t.rotations.push_back(t_rotation4);

        figures.push_back(t);
    }

    {
        //    [][] []
        //  [][]   [][]
        //           []
        FigureVariant s;
        s.type = FigureType::S;
        s.texture = textures.at(3);

        vector<XY> s_rotation1 = {p01, p10, p11, p20};
        vector<XY> s_rotation2 = {p00, p01, p11, p12};

        s.rotations.push_back(s_rotation1);
        s.rotations.push_back(s_rotation2);

        figures.push_back(s);
    }

    {
        // []   [][][] [][]     
        // []   []       []     []
        // [][]          [] [][][] 
        FigureVariant l;
        l.type = FigureType::L;
        l.texture = textures.at(4);

        vector<XY> l_rotation1 = {p00, p01, p02, p12};
        vector<XY> l_rotation2 = {p00, p01, p10, p20};
        vector<XY> l_rotation3 = {p00, p10, p11, p12};
        vector<XY> l_rotation4 = {p01, p11, p20, p21};

        l.rotations.push_back(l_rotation1);
        l.rotations.push_back(l_rotation2);
        l.rotations.push_back(l_rotation3);
        l.rotations.push_back(l_rotation4);

        figures.push_back(l);
    }

    {
        //   [] []     [][] 
        //   [] [][][] []   [][][]
        // [][]        []       []
        FigureVariant j;
        j.type = FigureType::J;
        j.texture = textures.at(5);

        vector<XY> j_rotation1 = {p02, p10, p11, p12};
        vector<XY> j_rotation2 = {p00, p01, p11, p21};
        vector<XY> j_rotation3 = {p00, p10, p01, p02};
        vector<XY> j_rotation4 = {p00, p10, p20, p21};

        j.rotations.push_back(j_rotation1);
        j.rotations.push_back(j_rotation2);
        j.rotations.push_back(j_rotation3);
        j.rotations.push_back(j_rotation4);

        figures.push_back(j);
    }

    return figures;
}
