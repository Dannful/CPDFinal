#include "./graphics.hpp"
#include "hash_table.hpp"

void print_player(const PlayerData& player, char *separator) {
  printf("%06d\t%40s\t%10s\t%1.5lf\t%5d%s", player.identifier, player.name.c_str(), player.positions.c_str(), player.rating,
         player.count, separator);
}

void print_user_player(const PlayerData& player, float rating) {
  char separator[] = "\t";
  print_player(player, separator);
  printf("%1.1f\n", rating);
}