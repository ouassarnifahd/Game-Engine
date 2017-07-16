#include "graphics/image.h"

#include "math/Matrix2x2.h"
#include "system/path.h"
#include "data/int_list.h"

Image* image_new(int width, int height, unsigned char* data) {
    Image* image = malloc(sizeof(image));
    image->data = malloc(width * height * 4);
    memcpy(image->data, data, width * height * 4);
    image->width = width;
    image->height = height;
    image->repeat_type = IMAGE_REPEAT_TILE;
    image->sample_type = IMAGE_SAMPLE_LINEAR;
    return image;
}

Image* image_empty(int width, int height) {
    Image* image = malloc(sizeof(image));
    image->data = malloc(width * height * 4);
    image->width = width;
    image->height = height;
    image->repeat_type = IMAGE_REPEAT_TILE;
    image->sample_type = IMAGE_SAMPLE_LINEAR;
    return image;
}

Image* image_blank(int width, int height) {
    Image* image = malloc(sizeof(image));
    image->data = calloc(width * height * 4, 1);
    image->width = width;
    image->height = height;
    image->repeat_type = IMAGE_REPEAT_TILE;
    image->sample_type = IMAGE_SAMPLE_LINEAR;
    return image;
}

Image* image_copy(Image* src) {
    Image* image = malloc(sizeof(image));
    image->data = malloc(src->width * src->height * 4);
    memcpy(image->data, src->data, src->width * src->height * 4);
    image->width = src->width;
    image->height = src->height;
    image->repeat_type = src->repeat_type;
    image->sample_type = src->sample_type;
    return image;
}

void image_delete(Image* image) {
    free(image->data);
    free(image);
}

static int image_wrap(int u, int m, int type) {
    if (u < 0 || u >= m) {
        switch (type) {
            case IMAGE_REPEAT_TILE:
                while (u < 0) {
                    u = m - 1 - u;
                }
                return u % m;
            case IMAGE_REPEAT_CLAMP:
                return u < 0 ? 0 : (u >= m ? m-1 : u);
            case IMAGE_REPEAT_MIRROR:
                u = max(u, -u) % (m * 2);
                return u >= m ? m - 1 - u : u;
            case IMAGE_REPEAT_ERROR:
                error("Image access out of bounds!");
                break;
            case IMAGE_REPEAT_BLACK:
                return -1;
        }
    }
    return u;
}

Vect4D image_get(Image* image, int u, int v) {
    u = image_wrap(u, image->width,  image->repeat_type);
    v = image_wrap(v, image->height, image->repeat_type);
    if (u == -1) return vect4D_zero();
    if (v == -1) return vect4D_zero();
    float r = (float)image->data[u * 4 + v * image->width * 4 + 0] / 255;
    float g = (float)image->data[u * 4 + v * image->width * 4 + 1] / 255;
    float b = (float)image->data[u * 4 + v * image->width * 4 + 2] / 255;
    float a = (float)image->data[u * 4 + v * image->width * 4 + 3] / 255;
    return vect4D_new(r, g, b, a);
}

void image_set(Image* image, int u, int v, Vect4D c) {
    u = image_wrap(u, image->width,  image->repeat_type);
    v = image_wrap(v, image->height, image->repeat_type);
    if (u == -1) return vect4D_zero();
    if (v == -1) return vect4D_zero();
    image->data[u * 4 + v * image->width * 4 + 0] = (c.x * 255);
    image->data[u * 4 + v * image->width * 4 + 1] = (c.y * 255);
    image->data[u * 4 + v * image->width * 4 + 2] = (c.z * 255);
    image->data[u * 4 + v * image->width * 4 + 3] = (c.t * 255);
}

void image_map(Image* image, Vect4D(*f)(Vect4D)) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            image_set(image, x, y, f(image_get(image, x, y)));
        }
    }
}

static Image* image_channel(Image* src, int channel) {
    Image* new = image_empty(src->width, src->height);
    for (int x = 0; x < src->width; x++) {
        for (int y = 0; y < src->height; y++) {
            Vect4D c = image_get(src, x, y);
            switch (channel) {
                case 0: image_set(new, x, y, vect4D_new(c.x,c.x,c.x,c.x)); break;
                case 1: image_set(new, x, y, vect4D_new(c.y,c.y,c.y,c.y)); break;
                case 2: image_set(new, x, y, vect4D_new(c.z,c.z,c.z,c.z)); break;
                case 3: image_set(new, x, y, vect4D_new(c.t,c.t,c.t,c.t)); break;
            }
        }
    }
    return new;
}

Image* image_red_channel(Image* src) {
    return image_channel(src, 0);
}

Image* image_green_channel(Image* src) {
    return image_channel(src, 1);
}

Image* image_blue_channel(Image* src) {
    return image_channel(src, 2);
}

Image* image_alpha_channel(Image* src) {
    return image_channel(src, 3);
}

void image_bgr_to_rgb(Image* image) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            Vect4D p = image_get(image, x, y);
            image_set(image, x, y, vect4D_new(p.z, p.y, p.x, p.t));
        }
    }
}

static void data_swap(void **x, void **y) {
	void *t = *x;
	*x = *y;
	*y = t;
}

void image_rotate_90_clockwise(Image* image) {
    Image* tmp = image_blank(image->height, image->width);
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            image_set(tmp, x, y, image_get(image, tmp->height - 1 - y, x));
        }
    }
    image->width  = tmp->width;
    image->height = tmp->height;
    data_swap((void**)&image->data, (void**)&tmp->data);
    image_delete(tmp);
}

void image_rotate_90_counterclockwise(Image* image) {
    Image* tmp = image_blank(image->height, image->width);
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            image_set(tmp, x, y, image_get(image, y, tmp->width - 1 - x));
        }
    }
    image->width  = tmp->width;
    image->height = tmp->height;
    data_swap((void**)&image->data, (void**)&tmp->data);
    image_delete(tmp);
}

void image_rotate_180(Image* image) {
    image_flip_vertical(image);
    image_flip_horizontal(image);
}

void image_rotate_inplace(Image* image, float amount) {
    Image* tmp = image_blank(image->height, image->width);
    int repeat = image->repeat_type;
    image->repeat_type = IMAGE_REPEAT_BLACK;
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            float u = ((float)x / image->width)  - 0.5;
            float v = ((float)y / image->height) - 0.5;
            Vect2D uv = mat2x2_mult_vect2D(mat2_rotation(amount), vect2D_new(u, v));
            uv = vect2D_add(uv, vect2D_new(0.5, 0.5));
            image_set(tmp, x, y, image_sample(image, uv));
        }
    }
    image->repeat_type = repeat;
    image_data_swap((void**)&image->data, (void**)&tmp->data);
    image_delete(tmp);
}

void image_flip_horizontal(Image* image) {
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width / 2; x++) {
            Vect4D l = image_get(image, x, y);
            Vect4D r = image_get(image, image->width - 1 - x, y);
            image_set(image, x, y, r);
            image_set(image, image->width - 1 - x, y, l);
        }
    }
}

void image_flip_vertical(Image* image) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height / 2; y++) {
            Vect4D t = image_get(image, x, y);
            Vect4D b = image_get(image, x, image->height - 1 - y);
            image_set(image, x, y, b);
            image_set(image, x, image->height - 1 - y, t);
        }
    }
}

void image_fill(Image* image, Vect4D color) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            image_set(image, x, y, color);
        }
    }
}

void image_fill_black(Image* image) {
    memset(image->data, 0, image->width * image->height * 4);
}

void image_fill_white(Image* image) {
    memset(image->data, 255, image->width * image->height * 4);
}

void image_apply_gamma(Image* image, float amount) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            image_set(image, x, y, vect4D_pow(image_get(image, x, y), amount));
        }
    }
}

void image_to_gamma(Image* image) {
    image_apply_gamma(image, 2.2);
}

void image_from_gamma(Image* image) {
    image_apply_gamma(image, 1.0/2.2);
}

void image_rgb_to_hsv(Image* image) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            Vect4D curr = image_get(image, x, y);
            Vect4D rslt = curr;
            float vmin = min(min(curr.x, curr.y), curr.z);
            float vmax = max(max(curr.x, curr.y), curr.z);
            float vdif = (vmax - vmin) + 0.0001;
            if (curr.x == vmax) {
                rslt.x = (curr.y - curr.z) / vdif;
                if (rslt.x < 0) rslt.x += 6;
            } else if (curr.y == vmax) {
                rslt.x = ((curr.z - curr.x) / vdif) + 2;
            } else {
                rslt.x = ((curr.x - curr.y) / vdif) + 4;
            }
            rslt.x = (rslt.x * 60) / 360.0;
            rslt.y = vdif / (vmax + 0.0001);
            rslt.z = vmax;
            image_set(image, x, y, rslt);
        }
    }
}

void image_hsv_to_rgb(Image* image) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            Vect4D curr = image_get(image, x, y);
            if (curr.y <= 0) {
                image_set(image, x, y, vect4D_new(curr.z, curr.z, curr.z, curr.t));
                continue;
            }
            float hh = (curr.x * 360) / 60;
            long j = (long)hh;
            float ff = hh - j;
            float p = curr.z * (1 -  curr.y);
            float q = curr.z * (1 - (curr.y * ff));
            float t = curr.z * (1 - (curr.y * (1 - ff)));
            switch(j) {
                case 0:  curr = vect4D_new(curr.z, t, p, curr.t); break;
                case 1:  curr = vect4D_new(q, curr.z, p, curr.t); break;
                case 2:  curr = vect4D_new(p, curr.z, t, curr.t); break;
                case 3:  curr = vect4D_new(p, q, curr.z, curr.t); break;
                case 4:  curr = vect4D_new(t, p, curr.z, curr.t); break;
                case 5:  curr = vect4D_new(curr.z, p, q, curr.t); break;
                default: curr = vect4D_zero(); break;
            }
            image_set(image, x, y, curr);
        }
    }
}

void image_hsv_scalar(Image* image) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            Vect4D curr = image_get(image, x, y);
            float amount = (curr.x + curr.y * 2 + curr.z * 5) / 8;
            image_set(image, x, y, vect4D_new(amount, amount, amount, amount));
        }
    }
}

Vect4D image_min(Image* image) {
    Vect4D vmin = vect4D_one();
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            vmin = vect4D_min(vmin, image_get(image, x, y));
        }
    }
    return vmin;
}

Vect4D image_max(Image* image) {
    Vect4D vmax = vect4D_one();
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            vmax = vect4D_max(vmax, image_get(image, x, y));
        }
    }
    return vmax;
}

Vect4D image_mean(Image* image) {
    Vect4D total = vect4D_zero();
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            total = vect4D_add(total, vect4D_div(image_get(image, x, y), image->width * image->height));
        }
    }
    return total;
}

Vect4D image_var(Image* image) {
    Vect4D total = vect4D_zero(), mean = image_mean(image);
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            Vect4D diff = vect4D_sub(image_get(image, x, y), mean);
            total = vect4D_add(total, vect4D_div(vect4D_mult_vect4D(diff, diff), image->width * image->height));
        }
    }
    return total;
}

Vect4D image_std(Image* image) {
    return vect4D_sqrt(image_var(image));
}

void image_auto_contrast(Image* image) {
    Vect4D mean = image_mean(image), std = image_std(image);
    float smean = vect4D_dot(mean, vect4D_new(0.33, 0.33, 0.33, 0));
    float sstd  = vect4D_dot(std, vect4D_new(0.33, 0.33, 0.33, 0));
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            Vect4D curr = image_get(image, x, y);
            curr = vect4D_sub(curr, vect4D_new(smean, smean, smean, 0));
            curr = vect4D_div(curr, sstd * 4);
            curr = vect4D_saturate(vect4D_add(curr, vect4D_new(0.5, 0.5, 0.5, 0)));
            image_set(image, x, y, curr);
        }
    }
}

void image_set_to_mask(Image* image) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            float v = vect4D_dot(image_get(image, x, y), vect4D_new(0.333, 0.333, 0.333, 0));
            if (v > 0.5) {
                image_set(image, x, y, vect4D_one());
            } else {
                image_set(image, x, y, vect4D_zero());
            }
        }
    }
}

void image_set_brightness(Image* image, float brightness) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            image_set(image, x, y, vect4D_saturate(vect4D_add(image_get(image, x, y), vect4D_new(b, b, b, b))));
        }
    }
}

Vect4D image_alpha_mean(Image* image) {
    Vect4D total = vect4D_zero();
    float scale = 0.0;
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            Vect4D c = image_get(image, x, y);
            c.x = c.x * c.t;
            c.y = c.y * c.t;
            c.z = c.z * c.t;
            total = vect4D_add(total, c);
            scale = scale + c.t;
        }
    }
    return vect4D_div(total, scale);
}

Image* image_get_subimage(Image* src, int left, int top, int width, int height) {
    Image* image = image_blank(width, height);
    image->repeat_type = src->repeat_type;
    image->sample_type = src->sample_type;
    for (int x = 0; x < image->width;  x++)
        for (int y = 0; y < image->height; y++) {
            image_set(image, x, y, image_get(src, left + x, top + y));
        }
    }
    return image;
}

void image_set_subimage(Image* image, int left, int top, Image* src) {
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            image_set(image, x, y, image_get(src, x-left, y-top));
        }
    }
}

void image_paste_subimage(Image* image, int left, int top, Image* src) {
    for (int x = left; x < left + src->width; x++)
        for (int y = top;  y < top  + src->height; y++) {
            Vect4D t = image_get(src, x - left, y - top);
            Vect4D b = image_get(i, x, y);
            Vect3D c = vect3D_lerp(vect3D_new(b.x, b.y, b.z), vect3D_new(t.x, t.y, t.z), t.t);
            image_set(i, x, y, vect4D_new(c.x, c.y, c.z, t.w));
        }
    }
}

Vect4D image_sample(Image* image, Vect2D uv) {
    float u = image->width * uv.x, v = image->height * uv.y;
    int s1_u = u, s1_v = v;
    int s2_u = (int)(1 + u), s2_v = v;
    int s3_u = u; s3_v = (int)(1 + v);
    int s4_u = (int)(1 + u); s4_v = (int)(1 + v);
    float amount_x = u - (int)u;
    float amount_y = v - (int)v;
    vect4D s1 = image_get(image, s1_u, s1_v), s2 = image_get(image, s2_u, s2_v), s3 = image_get(image, s3_u, s3_v), s4 = image_get(image, s4_u, s4_v);
    switch (image->sample_type) {
        case IMAGE_SAMPLE_LINEAR:  return vect4D_bilinear_interp(s1, s2, s3, s4, amount_x, amount_y);
        case IMAGE_SAMPLE_NEAREST: return vect4D_binearest_interp(s1, s2, s3, s4, amount_x, amount_y);
        default: return vect4D_zero();
    }
}

void image_paint(Image* image, Vect2D uv, Vect4D color) {
    float u = image->width * uv.x, v = image->height * uv.y;
    int s1_u = u, s1_v = v;
    int s2_u = (int)(1 + u), s2_v = v;
    int s3_u = u; s3_v = (int)(1 + v);
    int s4_u = (int)(1 + u); s4_v = (int)(1 + v);
    float amount_x = u - (int)u;
    float amount_y = v - (int)v;
    vect4D s1 = image_get(image, s1_u, s1_v), s2 = image_get(image, s2_u, s2_v), s3 = image_get(image, s3_u, s3_v), s4 = image_get(image, s4_u, s4_v);
    switch (image->sample_type) {
        case IMAGE_SAMPLE_LINEAR:
            s1 = vect4D_lerp(s1, color, (1-amount_x + 1-amount_y)/2);
            s2 = vect4D_lerp(s2, color, (amount_x + 1-amount_y)/2);
            s3 = vect4D_lerp(s3, color, (amount_x + amount_y)/2);
            s3 = vect4D_lerp(s4, color, (1-amount_x + amount_y)/2);
            image_set(image, s1_u, s1_v, s1);
            image_set(image, s2_u, s2_v, s2);
            image_set(image, s3_u, s3_v, s3);
            image_set(image, s4_u, s4_v, s4);
            break;
        case IMAGE_SAMPLE_NEAREST;
            s1 = vect4D_nearest_interp(s1, color, (1-amount_x + 1-amount_y)/2);
            s2 = vect4D_nearest_interp(s2, color, (amount_x + 1-amount_y)/2);
            s3 = vect4D_nearest_interp(s3, color, (amount_x + amount_y)/2);
            s3 = vect4D_nearest_interp(s4, color, (1-amount_x + amount_y)/2);
            image_set(image, s1_u, s1_v, s1);
            image_set(image, s2_u, s2_v, s2);
            image_set(image, s3_u, s3_v, s3);
            image_set(image, s4_u, s4_v, s4);
            break;
    }
}

void image_scale(Image* image, Vect2D scale);

void image_mask_not(Image* image);

void image_mask_binary(Image* image0, Image* image1, bool(*f)(bool,bool));

static bool image_op_or(bool x, bool y) {
    return x || y;
}

void image_mask_or(Image* image0, Image* image1);

static bool image_op_and(bool x, bool y) {
    return x && y;
}

void image_mask_and(Image* image0, Image* image1);

static bool image_op_xor(bool x, bool y) {
    return x != y;
}

void image_mask_xor(Image* image0, Image* image1);

static bool image_op_nor(bool x, bool y) {
    return !(x || y);
}

void image_mask_nor(Image* image0, Image* image1);

static bool image_op_nand(bool x, bool y) {
    return !(x && y);
}

void image_mask_nand(Image* image0, Image* image1);

static bool image_op_xnor(bool x, bool y) {
    return !(x != y);
}

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
