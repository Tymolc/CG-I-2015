#version 150

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 5
//                     - Aufgabe 16
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 771103
// Matr.-Nr: 770496
//
// ======================================

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 viewprojection;
uniform float animationFrame;

in vec3 geom_normal[];

out vec4 vertex;
out vec3 normal;

/////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: Aufgabe 16
// Note: In GLSL matrices are defined in column-major order.
// Take into account the animationFrame parameter:
//      0.0f: No transformation at all
//      1.0f: Maximum rotation of 360° and maximum translation
/////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{   
    vec4 center = vec4(0,0,0,0);

    for (int i=0; i < 3; ++i) {
        vertex = gl_in[i].gl_Position;

        center += vertex;
    }

    center = vec4(center.x/3, center.y/3, center.z/3, vertex.w/3);

    for (int i=0; i < 3; ++i)
    {
        normal = normalize(geom_normal[i]);
        vertex = gl_in[i].gl_Position;

        //rotation
        float s = sin(radians(360.0) * animationFrame);
        float c = cos(radians(360.0) * animationFrame);

        mat4 transUp = mat4(1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            -center.x, -center.y, -center.z, 1);
        mat4 rotation = mat4(c, s, 0, 0,
                             -s, c, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1);
        mat4 transDown = mat4(1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            center.x, center.y, center.z, 1);

        //translation
        mat4 translation = mat4(1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                normal.x * animationFrame, normal.y * animationFrame, normal.z * animationFrame, 1);

        vertex = transDown * rotation * transUp * vertex;
        vertex = translation * vertex;

        gl_Position = viewprojection * vertex;
	
        EmitVertex();
    }

    EndPrimitive();
}
