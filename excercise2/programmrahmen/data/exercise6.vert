#version 150

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2015 - Aufgabenblatt 2
//                     - Aufgabe 6
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 771103
// Matr.-Nr: 770496
//
// ======================================

uniform mat4 transform;
uniform sampler2D heightMap;

in vec2 position;

//////////////////////////////////////////////////
// TODO: Aufgabe 6d) - Interpolationsmodi anpassen
// Hinweis: Die Interpolationsmodi koennen vom laufenden Programm mittels der Tasten <1>, <2> und <3> gewechselt werden.
//////////////////////////////////////////////////

out float colorValue1;
out float colorValue2;
out float colorValue3;

float getHeight(vec2 uv)
{
    return texture(heightMap, uv).r;
}

void main()
{
    float height = getHeight(position);

    //////////////////////////////////////////////////
    // TODO: Aufgabe 6b) - Weltkoordinate berechnen
    //////////////////////////////////////////////////

    // Nutzen sie die Variable height fuer die Hoehe
    vec3 worldCoord = vec3(position.x, height, position.y);

    gl_Position = transform * vec4(worldCoord.x, 3.0 * worldCoord.y - 0.25, worldCoord.z, 1.0);

    //////////////////////////////////////////////////
    // TODO: Aufgabe 6c) - Farbwert zuweisen
    //////////////////////////////////////////////////

    // Statischer Farbwert
    float colorValue = height;

    // Farbwert zuweisen
    colorValue1 = colorValue;
    colorValue2 = colorValue;
    colorValue3 = colorValue;
}
