#ifndef COLOR_H
#define COLOR_H
typedef struct {
  float r;
  float g;
  float b;
} color;

static inline color lerp_color(color a, color b, float t) {
  color c = {0.0f, 0.0f, 0.0f};

  c.r = (a.r + t * (b.r - a.r));
  c.g = (a.g + t * (b.g - a.g));
  c.b = (a.b + t * (b.b - a.b));

  return c;
}

static inline color color_ramp(float v, int *stops, color *colors, int stop_sum,
                               int stop_count) {
  color c = {0.0f, 0.0f, 0.0f};
  int vi = (int)(v * stop_sum);

  for (int i = stop_count - 2; i >= 0; i--) {
    if (vi >= stops[i]) {
      // This stop is the starting point
      color ca = colors[i];
      color cb = colors[i + 1];

      float x = (float)(vi - stops[i]) / (float)(stops[i + 1] - stops[i]);

      c = lerp_color(ca, cb, x);
      break;
    }
  }
  return c;
}
#endif
