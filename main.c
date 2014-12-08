#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

#define BLOCK_WIDTH 20
#define BLOCK_HEIGHT 20
#define MAX_ITEMS_PER_LINE 48
#define MAX_LINES 21

void draw_block(ppm *image, int start_x, int start_y, double value) {
  int i, j;
  unsigned int r = 255 - (255 * value);
  unsigned int g = 255 - (149 * value);
  unsigned int b = 255U;

  pixel px = make_pixel(r, g, b);
  for(i = 1; i < BLOCK_WIDTH; i++){
    for (j = 1; j < BLOCK_HEIGHT; j++) {
      set_pixel(image, i+start_x, j+start_y, px);
    }
  }
}

int main(int argument_count, char *arguments[]) {
  FILE *input_file;
  int i = 0, j = 0;
  double data;

  if (argument_count > 1) {
    input_file = fopen(arguments[1], "r");

    if (input_file != NULL) {
      ppm *img = make_image(BLOCK_WIDTH * MAX_ITEMS_PER_LINE + 2, MAX_LINES * BLOCK_HEIGHT, make_pixel(255U, 255U, 255U));

      while (fscanf(input_file, " %lf", &data) != EOF) {
        draw_block(img, BLOCK_WIDTH*i+1,  BLOCK_HEIGHT*j, data);
        i++;
        if (i % MAX_ITEMS_PER_LINE == 0) {
          i = 0;
          j++;
        }
      }
      write_image(img, "output.pnm");
      release_image(img);
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
