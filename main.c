#include "color.h"
#include "noise.h"
#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc == 2 && strcmp(argv[1], "--help") == 0) {
    // Print help
    printf("Running with no arguments defaults to 1000x1000px, gradient "
           "noise, with time as seed and 5 color stops.\n"
           "Defaults to just one octave.\n"
           "Options are as follows:\n"
           "-w INT: sets width of image\n"
           "-h INT: sets height of image\n"
           "-f INT: sets noise function to be used\n"
           "-s INT: sets seed to use\n"
           "-c INT: sets number of color ramp stops to use\n"
           "-a FLOAT: sets scale of noise (higher is larger features)\n"
           "-t FLOAT: sets stretch factor (x / y)\n"
           "-o INT: sets octaves (default 1)\n"
           "-l FLOAT: sets lacunarity (default 2.0)\n"
           "-m FLOAT: sets amplitude (default 0.5)\n"
           "Functions available:\n"
           "0: Value noise\n"
           "1: Gradient noise\n");

    return 0;
  }

  int width = 1000;
  int height = 1000;
  int noise_func = 1;
  int seed = time(NULL);
  int num_stops = 5;
  float scale = 50.0f;
  float stretch = 1.0f;
  int octaves = 1;
  float lacunarity = 2.0f;
  float amplitude = 0.5f;

  int opt;
  while ((opt = getopt(argc, argv, "w:h:f:s:c:a:t:o:l:m:")) != -1) {
    switch (opt) {
    case 'w':
      width = atoi(optarg);
      break;
    case 'h':
      height = atoi(optarg);
      break;
    case 'f':
      // Set the noise function to be used
      noise_func = atoi(optarg);
      break;
    case 's':
      seed = atoi(optarg);
      break;
    case 'c':
      num_stops = atoi(optarg);
      break;
    case 'a':
      scale = atof(optarg);
      break;
    case 't':
      stretch = atof(optarg);
      break;
    case 'm':
      amplitude = atof(optarg);
      break;
    case 'o':
      octaves = atoi(optarg);
      break;
    case 'l':
      lacunarity = atof(optarg);
      break;
    }
  }

  int values = width * height * 3;
  unsigned char *data = (unsigned char *)malloc(
      values *
      sizeof(unsigned char)); // Allocate width * height * 3 long array for data

  if (data == NULL) {
    printf("Malloc failed\n");
    return 1;
  }

  // Create color mapping function
  int *stops =
      (int *)malloc(num_stops * sizeof(int)); // Array to hold stop locations
  color *colors =
      (color *)malloc(num_stops * sizeof(color)); // To hold stop colors

  srand(seed); // Seed

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

  // printf("%f\n", test_noise(0.0f, 0.0f));

  float (*noise_functions[2])(float, float) = {value_noise, gradient_noise};

  // Populate the data array with noise values
  // printf("About to loop\n");
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int idx = (y * width + x) * 3;
      float px = x / scale * stretch + seed % 1000;
      float py = y / scale + seed % 1000;

      // Do fbm
      float res = 0.0f;
      float total_amp = 0.0f;
      float amp = 1.0f;
      float scl = 1.0f;

      for (int o = 0; o < octaves; o++) {
        float val = noise_functions[noise_func](px * scl, py * scl) * amp;
        total_amp += amp;
        res += val;

        amp *= amplitude;
        scl *= lacunarity;
      }

      float noise_val = res / total_amp;

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

  free(data);   // Free data memory
  free(stops);  // Free stops
  free(colors); // ^ C autoformatter lines up the comments lol. Cool
  return 0;
}
