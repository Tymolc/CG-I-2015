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
    for (int i=0; i < 3; ++i)
    {
        normal = normalize(geom_normal[i]);
        vertex = gl_in[i].gl_Position;
        gl_Position = viewprojection * vertex;

        //rotation
        float s = sin(360*animationFrame);
        float c = cos(360*animationFrame);
        float oc = 1.0 - c;
        /*rotation = mat4(oc*normal.x*normal.x+c,             oc*normal.x*normal.y-normal.z*s,    oc*normal.z*normal.x+normal.y*s, 0.0,
                    oc*normal.x*normal.y+normal.z*s,    oc*normal.y*normal.y+c,             oc*normal.y*normal.z-normal.x*s, 0.0,
                    oc*normal.x*normal.z-normal.y*s,    oc*normal.y*normal.z-normal.x*s,    oc*normal.z*normal.z+c, 0.0,
                    0.0, 0.0, 0.0, 1.0);*/
        mat3 rotation = mat3(c, -s, 0, s, c, 0, 0, 0, 1);
        normal = normal + (rotation * normal * animationFrame);

        float distance = 1;
        gl_Position.xyz = gl_Position.xyz + normal * animationFrame * distance;
	
        EmitVertex();
    }

    EndPrimitive();
}
