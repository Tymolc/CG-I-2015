#version 150

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 5
//                     - Aufgabe 18
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

in vec4 vertex;
in vec3 normal;

out vec4 out_color;

uniform vec3 lightsource;
uniform mat3 normalMatrix;
uniform vec4 color;

void main()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 18, part 5
    // Adjust the color depending on the depth of the vertex.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    float distcolor = 1 - (gl_FragCoord.z-0.90)*10;
    out_color = vec4(distcolor, distcolor, distcolor, 1);
}
