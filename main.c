#include "color.h"
#include "noise.h"
#include "ppm.h"
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

  // Create color mapping function
  int num_stops = 8;
  int *stops =
      (int *)malloc(num_stops * sizeof(int)); // Array to hold stop locations
  color *colors =
      (color *)malloc(num_stops * sizeof(color)); // To hold stop colors

  srand(25); // Seed

  int total_size = 0;
  for (int i = 0; i < num_stops; i++) {
    // Populate stops
    int size = rand() % 1000; // Width of stop
    if (i < num_stops - 1)
      total_size += size;

    float r = (float)rand() / (float)(RAND_MAX);
    float g = (float)rand() / (float)(RAND_MAX);
    float b = (float)rand() / (float)(RAND_MAX);

    // printf("%f%f%f\n", r, g, b);
    stops[i] = total_size - size;

    colors[i].r = r;
    colors[i].g = g;
    colors[i].b = b;
  }

  printf("%f\n", test_noise(0.0f, 0.0f));

  // Populate the data array with noise values
  // printf("About to loop\n");
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int idx = (y * width + x) * 3;
      float px = x / 50.0f;
      float py = y / 50.0f;

      float noise_val = gradient_noise(px, py);

      color col = color_ramp(noise_val, stops, colors, total_size, num_stops);
      // printf("%f\n", col.r);

      data[idx] = (unsigned char)(col.r * 255.0f);
      data[idx + 1] = (unsigned char)(col.g * 255.0f);
      data[idx + 2] = (unsigned char)(col.b * 255.0f);
    }
  }

  printf("Finished populating data\n");

  const char *file = "image.ppm"; // Output path
  write_ppm(file, width, height, data);

  free(data);  // Free data memory
  free(stops); // Free stops
               // ^ C autoformatter lines up the comments lol. Cool
  return 0;
}
