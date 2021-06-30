#pragma once 

#include "tinysdl/graphics/shader.h"
#include "tinysdl/graphics/texture.h"
#include "tinysdl/graphics/color.h"
#include "tinysdl/numerics/matrix.h"
#include "tinysdl/numerics/rect.h"


#include <vector>

namespace TinySDL {
    
    struct Vertex {
        Vec2 pos;
        Vec2 uv;
        Color color;
        ByteVec3 cmix;
    };

    class SpriteBatch {
        public:
            SpriteBatch();
            ~SpriteBatch();
            
            void set_texture(Texture * tex);
            
            void push_transform(const Mat3x2 & new_transform);
            Mat3x2 pop_transform();

            // Draw texture/sprite
            void draw(const Rect & src, const Vec2 & pos);
            void draw(const Rect & src, const Rect & dst, float rot, bool centered);
            void draw(const Rect & src, const Vec2 & pos, const Vec2 & scale, float rot = 0.0f, bool centered = false);
           
            //Draw rectangle
            void draw_rect_fill(const Rect & rect, const Color & color);
            void draw_rect_line(const Rect & rect, const Color & color, float t);

            //Draw triangle
            void draw_triangle_fill(const Vec2 & p0, const Vec2 & p1, const Vec2 & p2, const Color & color);
            void draw_triangle_line(const Vec2 & p0, const Vec2 & p1, const Vec2 & p2, float t, const Color & color) ;

            //Draw circle
            void draw_circle_fill(const Vec2 & center, float radius, const Color & color, int steps = 15);
            void draw_circle_line(const Vec2 & center, float radius, float t, const Color & color, int steps = 15); 

            //Draw semi-circle
            void draw_semi_circle_fill(const Vec2 & center, float radius, float radians_start, float radians_end, const Color & color, int steps=15);
            void draw_semi_circle_line(const Vec2& center, float radius, float radians_start, float radians_end, float t, const Color& color, int steps = 15);

            //Draw line
            void draw_line(const Vec2 & start, const Vec2 & end, const Color & color, float t);


            void render();

        private:
            Mat3x2 transform;
            std::vector<Mat3x2> transform_stack;

            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            unsigned int vao_id;
            unsigned int vbo_id;
            unsigned int ebo_id;

            Texture * current_tex = nullptr;

            void push_vertex(const float & x, const float & y, const float & uv_x, const float & uv_y, const Color & color, const ByteVec3 & cmix);
            
            void push_quad(const float & x0, const float & y0, const float & x1, const float & y1, 
                           const float & x2, const float & y2, const float & x3, const float & y3, 
                           const float & uv_x0, const float & uv_y0, const float & uv_x1, const float & uv_y1, 
                           const float & uv_x2, const float & uv_y2, const float & uv_x3, const float & uv_y3, 
                           const Color & color, const ByteVec3 & cmix);
            
            void push_triangle(const float & x0, const float & y0, const float & x1, 
                               const float & y1, const float & x2, const float & y2, 
                               const float & uv_x0, const float & uv_y0, 
                               const float & uv_x1, const float & uv_y1, 
                               const float & uv_x2, const float & uv_y2, 
                               const Color & color, const ByteVec3 & cmix);
    };
}