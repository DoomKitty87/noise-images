#include "noise.h"
#include "ppm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // will add parameters later ig
  int width = 1000;
  int height = 1000;

  int values = width * height;
  unsigned char *data = (unsigned char *)malloc(
      values *
      sizeof(unsigned char)); // Allocate width * height long array for data

  if (data == NULL) {
    printf("Malloc failed\n");
    return 1;
  }

  printf("%f\n", test_noise(0.0f, 0.0f));

  // Populate the data array with noise values
  // printf("About to loop\n");
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int idx = (y * width + x) * 3;
      // printf("Getting noise value\n");
      float px = x / 10.0f;
      float py = y / 10.0f;
      unsigned char r = (unsigned char)(floorf(gradient_noise(px, py) * 255.0));
      // printf("Got noise value\n");
      data[idx] = r;
      data[idx + 1] = r;
      data[idx + 2] = r;
    }
  }

  printf("Finished populating data\n");

  const char *file = "image.ppm"; // Output path
  write_ppm(file, width, height, data);

  free(data); // Free data memory
  return 0;
}
