#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bchart.h"

#define MAX_ITEMS_PER_LINE 48
#define MAX_LINES 21

int main(int argument_count, char *arguments[]) {
  FILE *input_file;
  int i = 0, j = 0;
  double item;
  int scan_res;
  double data_set[MAX_ITEMS_PER_LINE];
  BlockChart *chart;

  if (argument_count > 1) {
    input_file = fopen(arguments[1], "r");

    chart = bchart_init(MAX_ITEMS_PER_LINE, MAX_LINES);

    if (input_file != NULL) {

      while ((scan_res = fscanf(input_file, " %lf", &item)) != EOF) {
        if (scan_res == 0) {
          printf("Error reading file at line %d column %d!\n", j+1, i+1);
          return EXIT_FAILURE;
        }

        data_set[i] = item;
        i++;
        if (i % MAX_ITEMS_PER_LINE == 0) {
          bchart_draw_blocks(chart, data_set, i);
          bchart_next_line(chart);
          i = 0;
          j++;
        }
      }

      bchart_save(chart, "output2.pnm");
      bchart_dispose(chart);
      fclose(input_file);
    } else {
      printf("Could not open file %s\n", arguments[1]);
      return EXIT_FAILURE;
    }
  } else {
    printf("Please run with an input file:\n  a.exe test.txt\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
