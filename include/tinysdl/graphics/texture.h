#pragma once

#include "tinysdl/numerics/rect.h"

namespace TinySDL {

    struct Image {
        Image() = default;
        Image(const char * path);
        ~Image();
        void free_image_data();

        unsigned char * data = nullptr;
        int w = 0, h = 0, n_comp = 0;        
    };

    struct Texture {

        Texture() = default;
        Texture(int w, int h, int n_comp, unsigned char * data);
        
        unsigned int id;
        unsigned int tex_slot = 0;
        
        int w = 0, h = 0;
        Rect full_rect;

        void bind() const;
        static Texture from_file(const char * path);
        static Texture from_sprite(Image * spr);
        static Texture empty(int w, int h);
    };

    struct TexRegion {
        
        TexRegion() = default;
        TexRegion(Texture * texture, const Rect & src) {
            tex = texture;
            set_src(src);
        }

        Texture * tex = nullptr;
        Vec2 uv[4];
        
        float w = 0;
        float h = 0;

        void set_src(const Rect & src) {
            // src_rect = src;
            w = src.w;
            h = src.h;

            if (tex) {
                uv[0] = {src.x / (float) tex->w, src.y / (float) tex->h};
                uv[1] = {(src.x + src.w) / (float) tex->w, src.y / (float) tex->h};
                uv[2] = {(src.x + src.w) / (float) tex->w, (src.y + src.h) / (float) tex->h};
                uv[3] = {src.x / (float) tex->w, (src.y + src.h) / (float) tex->h};
            }
            else {
                for (int i = 0; i < 4; i++) 
                    uv[i] = Vec2::zeros;
            }
        }

    // private:
    //     Rect src_rect;
    };
}