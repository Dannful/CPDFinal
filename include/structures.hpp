#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

struct ReviewedPlayer {
    unsigned int identifier;
    double rating;
};

const auto users_fun = [](ReviewedPlayer *a, ReviewedPlayer *b) {
    return a->rating == b->rating || a->rating > b->rating;
};

struct PlayerData {
    unsigned int identifier;
    string name;
    string positions;
    set<string> *tags;
    double rating;
    unsigned int count;
};

#endif