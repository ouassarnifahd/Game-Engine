#ifndef _IMAGE_
#define _IMAGE_

// #include <.h>
#include "common.h"
#include "math/4Dvectors.h"

typedef struct {
  int width;
  int height;
  unsigned char* data;
  int repeat_type;
  int sample_type;
} Image;

enum {
  IMAGE_REPEAT_TILE   = 0,
  IMAGE_REPEAT_CLAMP  = 1,
  IMAGE_REPEAT_MIRROR = 2,
  IMAGE_REPEAT_ERROR  = 3,
  IMAGE_REPEAT_BLACK  = 4
};

enum {
  IMAGE_SAMPLE_LINEAR  = 0,
  IMAGE_SAMPLE_NEAREST = 1
};

Image* image_new(int width, int height, unsigned char* data);
Image* image_empty(int width, int height);
Image* image_blank(int width, int height);
Image* image_copy(Image* src);
void image_delete(Image* image);

Vect4D image_get(Image* image, int u, int v);
void image_set(Image* image, int u, int v, Vect4D c);
void image_map(Image* image, Vect4D(*f)(Vect4D));

Image* image_red_channel(Image* src);
Image* image_green_channel(Image* src);
Image* image_blue_channel(Image* src);
Image* image_alpha_channel(Image* src);

void image_bgr_to_rgb(Image* image);
void image_rotate_90_clockwise(Image* image);
void image_rotate_90_counterclockwise(Image* image);
void image_rotate_180(Image* image);
void image_rotate_inplace(Image* image, float amount);
void image_flip_horizontal(Image* image);
void image_flip_vertical(Image* image);

void image_fill(Image* image, Vect4D color);
void image_fill_black(Image* image);
void image_fill_white(Image* image);

void image_apply_gamma(Image* image, float amount);
void image_to_gamma(Image* image);
void image_from_gamma(Image* image);

void image_rgb_to_hsv(Image* image);
void image_hsv_to_rgb(Image* image);
void image_hsv_scalar(Image* image);

Vect4D image_min(Image* image);
Vect4D image_max(Image* image);
Vect4D image_mean(Image* image);
Vect4D image_var(Image* image);
Vect4D image_std(Image* image);
void image_auto_contrast(Image* image);
void image_set_to_mask(Image* image);
void image_set_brightness(Image* image, float brightness);

Vect4D image_alpha_mean(Image* image);

Image* image_get_subimage(Image* src, int left, int top, int width, int height);

void image_set_subimage(Image* image, int left, int top, Image* src);
void image_paste_subimage(Image* image, int left, int top, Image* src);

Vect4D image_sample(Image* image, Vect2D uv);
void image_paint(Image* image, Vect2D uv, Vect4D color);

void image_scale(Image* image, Vect2D scale);

void image_mask_not(Image* image);
void image_mask_binary(Image* image0, Image* image1, bool(*f)(bool,bool));
void image_mask_or(Image* image0, Image* image1);
void image_mask_and(Image* image0, Image* image1);
void image_mask_xor(Image* image0, Image* image1);
void image_mask_nor(Image* image0, Image* image1);
void image_mask_nand(Image* image0, Image* image1);
void image_mask_xnor(Image* image0, Image* image1);

Image* image_mask_alpha(Image* image);
Image* image_mask_nearest(Image* image);
Image* image_mask_nearest(Image* image);
Image* image_mask_flood_fill(Image* src, int u, int v, float tolerance);
Image* image_mask_difference(Image* src, Vect4D color, float tolerance);

long image_mask_count(Image* image);
void image_mask_median(Image* image, int* u, int* v);
void image_mask_random(Image* image, int* u, int* v);

Image* image_read_from_file(char* filename);
Image* image_tga_load_file(char* filename);
Image* image_bmp_load_file(char* filename);

void image_write_to_file(Image* image, char* filename);
void image_tga_save_file(Image* image, char* filename);
void image_bmp_save_file(Image* image, char* filename);

#endif /* end of include guard: _IMAGE_ */
