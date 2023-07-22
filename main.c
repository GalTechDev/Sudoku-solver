#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int base[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0}};

int grid[9][9];

void clear() { system("clear"); }

void show_grid() {

  printf("╔═══════════╦═══════════╦═══════════╗\n");
  for (int l = 0; l < 9; l++) {
    printf("║");
    for (int c = 0; c < 9; c++) {
      printf(" %d ", grid[l][c]);
      if (c == 2 || c == 5) {
        printf("║");
      } else if (c == 8) {
        printf("║\n");
      } else {
        printf("│");
      }
    }
    if (l == 2 || l == 5) {
      printf("╠═══════════╬═══════════╬═══════════╣\n");
    } else if (l == 8) {
      // Do nothing
    } else {
      printf("║───┼───┼───║───┼───┼───║───┼───┼───║\n");
    }
  }
  printf("╚═══════════╩═══════════╩═══════════╝\n");
}

int cel_valide(int line, int col) {
  int val = grid[line][col];

  int lne[9];
  int lne_count = 0;
  for (int c = 0; c < 9; c++) {
    if (c != col) {
      lne[lne_count++] = grid[line][c];
    }
  }

  for (int i = 0; i < lne_count; i++) {
    if (val == lne[i]) {
      return 0;
    }
  }

  int column[9];
  int column_count = 0;
  for (int l = 0; l < 9; l++) {
    if (l != line) {
      column[column_count++] = grid[l][col];
    }
  }

  for (int i = 0; i < column_count; i++) {
    if (val == column[i]) {
      return 0;
    }
  }

  int chunk[9];
  int chunk_count = 0;
  int start_line = (line / 3) * 3;
  int start_col = (col / 3) * 3;
  for (int l = start_line; l < start_line + 3; l++) {
    for (int c = start_col; c < start_col + 3; c++) {
      if (l != line && c != col) {
        chunk[chunk_count++] = grid[l][c];
      }
    }
  }

  for (int i = 0; i < chunk_count; i++) {
    if (val == chunk[i]) {
      return 0;
    }
  }

  return 1;
}

int SudokuSolverIJ(int line, int col, int val) {
  for (int c = 0; c < 9; c++) {
    if (grid[line][c] == val) {
      return 0;
    }
  }

  for (int l = 0; l < 9; l++) {
    if (grid[l][col] == val) {
      return 0;
    }
  }

  int start_line = (line / 3) * 3;
  int start_col = (col / 3) * 3;

  for (int l = start_line; l < start_line + 3; l++) {
    for (int c = start_col; c < start_col + 3; c++) {
      if (grid[l][c] == val) {
        return 0;
      }
    }
  }

  return 1;
}

int SudokuSolver() {
  for (int l = 0; l < 9; l++) {
    for (int c = 0; c < 9; c++) {
      if (grid[l][c] == 0) {
        for (int val = 1; val <= 9; val++) {
          if (SudokuSolverIJ(l, c, val) == 1) {
            grid[l][c] = val;
            // show_grid();
            int res = SudokuSolver();
            if (res == 1) {
              return 1;
            } else {
              grid[l][c] = 0;
            }
          }
        }
        return 0;
      } else {
        if (c == 8 & l == 8) {
          return 1;
        }
      }
    }
  }
  return 0;
}

void traiterGrille() {
  SudokuSolver();
  show_grid();
}

void save_grid() {
  FILE *fichier = fopen("grille_sudoku_solution.txt", "a");
  if (fichier == NULL) {
    printf("Impossible d'ouvrir le fichier.");
    return;
  }

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      fprintf(fichier, "%d ", grid[i][j]);
    }
    fprintf(fichier, "\n");
  }

  fprintf(fichier, "\n");
  fclose(fichier);
  printf("La grille a été écrite dans le fichier avec succès.\n\n");
}

void load_grid() {
  FILE *fichier = fopen("grilles_sudoku.txt", "r");
  if (fichier == NULL) {
    printf("Impossible d'ouvrir le fichier.\n");
    return;
  }

  // Reset de la grille
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      grid[i][j] = base[i][j];
    }
  }

  int col = 0;
  int line = 0;
  int i = 0;
  int val;
  while (fscanf(fichier, "%d", &val) == 1) {
    grid[line][col] = val;
    col++;
    if (col == 9) {
      col = 0;
      line++;

      if (line == 9) {
        // Traitement de la grille complète
        show_grid();
        traiterGrille();
        save_grid();

        // Réinitialisation de la grille pour la prochaine
        for (int i = 0; i < 9; i++) {
          for (int j = 0; j < 9; j++) {
            grid[i][j] = base[i][j];
          }
        }

        line = 0;
      }
    }
  }

  fclose(fichier);
}

int main() {
  load_grid();

  return 0;
}
