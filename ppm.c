#include <stdio.h>

void write_ppm(const char *file, int width, int height, unsigned char *data) {
  FILE *fptr = fopen(file, "wb");
  if (!fptr)
    return;

  // Header line indicating specs (255 is max value)
  fprintf(fptr, "P6\n %d %d 255\n", width, height);

  // Write data body
  fwrite(data, sizeof(unsigned char), width * height * 3, fptr);
}
