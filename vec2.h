#ifndef VEC2_H
#define VEC2_H
#include <math.h>

typedef struct {
  float x;
  float y;
} vec2;

static inline vec2 vec2_create(float x, float y) {
  vec2 v = {x, y};
  return v;
}

static inline vec2 vec2_add(vec2 a, vec2 b) {
  return vec2_create(a.x + b.x, a.y + b.y);
}

static inline vec2 vec2_sub(vec2 a, vec2 b) {
  return vec2_create(a.x - b.x, a.y - b.y);
}

static inline vec2 vec2_mul(vec2 v, float scalar) {
  return vec2_create(v.x * scalar, v.y * scalar);
}

static inline float vec2_dot(vec2 a, vec2 b) {
  return (a.x * b.x) + (a.y * b.y);
}

static inline float vec2_length(vec2 v) {
  return sqrtf((v.x * v.x) + (v.y * v.y));
}

static inline vec2 vec2_normalize(vec2 v) {
  float len = vec2_length(v);
  if (len == 0.0f)
    return vec2_create(0.0f, 0.0f);
  return vec2_mul(v, 1.0f / len);
}

static inline vec2 vec2_fract(vec2 v) {
  return vec2_create(v.x - (int)v.x, v.y - (int)v.y);
}

static inline vec2 vec2_vmul(vec2 a, vec2 b) {
  return vec2_create(a.x * b.x, a.y * b.y);
}
#endif
