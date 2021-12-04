#include <stdio.h>

int main() {
  // 1)
  // righy step and down step are not the same
  // 2)
  // 9 1
  // 1
  // 3)
  // 3 2 9
  // 5
  // 1
  int map[8][8] = {{0, 1, 2, 3, 4, 5, 2},
                    {4, 2, 1, 4, 6, 2, 0, 3},
                    {1, 9, 9, 9, 9, 9, 9, 1},
                    {8, 7,-3, 2, 1, -2, 12, 3},
                    {9, 8, 7, 0, 1, 2, 7, 3},
                    {-3, 2, 2, 3, 1, -3, 1, 9},
                    {4, 5, 4, 0, 4, 5, 4, 5},
                    {9, 8, 7, 6, 5, 4, 3, 2}};
  int path[2 * 8 - 1];
  int size = sizeof(path) / sizeof(path[0]);
  int sum = map[0][0];
  int now_x = 0;
  int now_y = 0;

  for (int n1 = 0; n1 < size; n1++) {
    path[n1] = 0;
  }

  path[0] = map[0][0];

  for (int n1 = 0; n1 < size - 1; n1++) {
    if (now_x == 7) {
      sum += map[now_y + 1][now_x];
      path[now_x + now_y + 1] = map[now_y + 1][now_x];
      now_y++;
      continue;
    }

    if (now_y == 7) {
      sum += map[now_y][now_x + 1];
      path[now_x + now_y + 1] = map[now_y][now_x + 1];
      now_x++;
      continue;
    }

    if (map[now_y][now_x + 1] > map[now_y + 1][now_x]) {
      sum += map[now_y][now_x + 1];
      path[now_x + now_y + 1] = map[now_y][now_x + 1];
      now_x++;
    } else {
      sum += map[now_y + 1][now_x];
      path[now_x + now_y + 1] = map[now_y + 1][now_x];
      now_y++;
    }
  }

  printf("max is %d. \n", sum);

  printf("path: ");
  for (int n2 = 0; n2 < size; n2++) {
    printf("%d  ", path[n2]);
  }

  printf("\n");

  return 0;
}