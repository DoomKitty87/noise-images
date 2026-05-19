#include "noise.h"
#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // will add parameters later ig
  int width = 100;
  int height = 100;

  int values = width * height;
  unsigned char *data = (unsigned char *)malloc(
      values *
      sizeof(unsigned char)); // Allocate width * height long array for data

  if (data == NULL) {
    printf("malloc failed");
    return 1;
  }

  printf("%f\n", test_noise(0.0f, 0.0f));

  const char *file = "image.ppm"; // Output path
  write_ppm(file, width, height, data);

  free(data); // Free data memory
  return 0;
}
