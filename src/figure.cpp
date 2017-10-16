#include "figure.hpp"

Figure::Figure(FigureVariant variant, Texture& texture) : texture(texture) {
    this->variant = variant;
    this->rotation = 0;

    auto rotations = this->variant.rotations[rotation];

    for (auto iter = rotations.begin(); iter != rotations.end(); iter++) {
        auto rotation_offsets = *iter;

        SDL_Rect rect;
        rect.x = (rotation_offsets.x * SQUARE_SIZE);
        rect.y = (rotation_offsets.y * SQUARE_SIZE);
        rect.w = SQUARE_SIZE;
        rect.h = SQUARE_SIZE;

        this->squares.push_back(rect);
    }
}

int Figure::render(Context& context) {
    for (auto iter = squares.begin(); iter != squares.end(); iter++) {
        texture.render(context, *iter);
    }

    return 0;
}

bool operator<(XY a, XY b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}

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

    o.type = FigureType::O;   
    o.rotations.push_back(o_rotation);

    figures.push_back(o);

    // []
    // [] [][][][]
    // []
    // []
    FigureVariant i;

    vector<XY> i_rotation1 = {p00, p01, p02, p03};
    vector<XY> i_rotation2 = {p00, p10, p20, p30};

    o.type = FigureType::I;
    o.rotations.push_back(i_rotation1);
    o.rotations.push_back(i_rotation2);

    return figures;
}
