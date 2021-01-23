#include <emscripten.h>
#include <vector>
using namespace std;

vector<vector<int>> make_2d_array(int cols, int rows) {
  vector<vector<int>> arr(cols, vector<int> (rows));
  return arr;
}

int count_neighbours(vector<vector<int>> grid, int x, int y) {
  int rows = grid.size();
  int cols = grid[0].size();

  int sum = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      int col = (x + i + cols) % cols;
      int row = (y + j + rows) % rows;
      sum += grid[col][row];
    }
  }
  sum -= grid[x][y];
  return sum;
}

EMSCRIPTEN_KEEPALIVE
vector<vector<int>> next_grid(vector<vector<int>> grid) {
  int rows = grid.size();
  int cols = grid[0].size();
  vector<vector<int>> next = make_2d_array(cols, rows);
  // Compute next based on grid
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      int state = grid[i][j];
      // Count live neighbors!
      int sum = 0;
      int neighbors = count_neighbours(grid, i, j);

      if (state == 0 && neighbors == 3) {
        next[i][j] = 1;
      } else if (state == 1 && (neighbors < 2 || neighbors > 3)) {
        next[i][j] = 0;
      } else {
        next[i][j] = state;
      }

    }
  }
  return next;
}

EMSCRIPTEN_KEEPALIVE
extern "C" int daysInWeek() {
  return 7;
}
