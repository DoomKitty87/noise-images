#include "vec2.h"
#include <math.h>

unsigned int hash2d(int x, int y) {
  unsigned int h = x * 374761397u + y * 668265263u;
  h = (h ^ (h >> 13)) * 1274126177u;
  return h ^ (h >> 16);
}

vec2 grad(vec2 p) {
  int x = p.x;
  int y = p.y;
  int h1 = hash2d(x, y);
  int h2 = hash2d((x + 29182u) % y, y * 132u % x * 3);

  return vec2_normalize(vec2_create(h1, h2));
}

float lerp(float a, float b, float t) { return (a + t * (b - a)); }

float random(vec2 p) {
  return hash2d(floorf(p.x), floorf(p.y)) % 1000 / 1000.0f;
}

float test_noise(float x, float y) { return 0.0f; }

float white_noise(int x, int y) { return random(vec2_create(x, y)); }

float value_noise(float x, float y) {
  vec2 p = vec2_create(floorf(x), floorf(y));
  vec2 p0 = p;
  vec2 p1 = vec2_add(p, vec2_create(1, 0));
  vec2 p2 = vec2_add(p, vec2_create(0, 1));
  vec2 p3 = vec2_add(p, vec2_create(1, 1));

  float r0 = random(p0);
  float r1 = random(p1);
  float r2 = random(p2);
  float r3 = random(p3);

  vec2 f = vec2_fract(vec2_create(x, y));

  vec2 u = vec2_vmul(
      f, vec2_vmul(f, vec2_sub(vec2_create(3.0, 3.0), vec2_mul(f, 2.0))));

  float res = lerp(r0, r1, u.x);
  res += (r2 - r0) * u.y * (1.0 - u.x);
  res += (r3 - r1) * u.x * u.y;

  return res;
}

float gradient_noise(float x, float y) {
  vec2 p = vec2_create(floorf(x), floorf(y));
  vec2 p0 = p;
  vec2 p1 = vec2_add(p, vec2_create(1, 0));
  vec2 p2 = vec2_add(p, vec2_create(0, 1));
  vec2 p3 = vec2_add(p, vec2_create(1, 1));

  vec2 g0 = grad(p0);
  vec2 g1 = grad(p1);
  vec2 g2 = grad(p2);
  vec2 g3 = grad(p3);

  vec2 pf = vec2_create(x, y);

  vec2 d0 = vec2_sub(pf, p0);
  vec2 d1 = vec2_sub(pf, p1);
  vec2 d2 = vec2_sub(pf, p2);
  vec2 d3 = vec2_sub(pf, p3);

  float r0 = vec2_dot(g0, d0);
  float r1 = vec2_dot(g1, d1);
  float r2 = vec2_dot(g2, d2);
  float r3 = vec2_dot(g3, d3);

  vec2 f = vec2_fract(vec2_create(x, y));

  vec2 u = vec2_vmul(
      f, vec2_vmul(f, vec2_sub(vec2_create(3.0, 3.0), vec2_mul(f, 2.0))));

  float res = lerp(r0, r1, u.x);
  res += (r2 - r0) * u.y * (1.0 - u.x);
  res += (r3 - r1) * u.x * u.y;

  return (res + 1.0f) / 3.0f;
}
