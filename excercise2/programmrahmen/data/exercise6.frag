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
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

//////////////////////////////////////////////////
// TODO: Aufgabe 6d) - Interpolationsmodi anpassen
//
// Hinweis: Die Interpolationsmodi koennen vom laufenden Programm mittels der Tasten <1>, <2> und <3> gewechselt werden.
//////////////////////////////////////////////////


flat in float colorValue1;
in float colorValue2;
noperspective in float colorValue3;

out vec4 color;

uniform int interpolationMode;

void main()
{
    // TODO: Farbwert auslesen (vom Modus abhaengig)
        float colorValue;
        if(interpolationMode == 0)
                colorValue = colorValue1;
        if(interpolationMode == 1)
                colorValue = colorValue2;
        if(interpolationMode == 2)
                colorValue = colorValue3;

    /////////////////////////////////////////////////
    // TODO: Aufgabe 6c) - Farbe berechnen
    //////////////////////////////////////////////////

    // Als Graustufenwert interpretieren
    /*if(colorValue < 0.1)
                color = vec4(((1-colorValue) * 0.2), (1-colorValue) * 0.54, (1-colorValue) * 0, 1.0);
        else */if(colorValue < 0.333)
                color = vec4(((1-colorValue/0.333) * 0.2 + colorValue/0.333 * 0.22), ((1-colorValue/0.333) * 0.54 + colorValue/0.333 * 0.17), colorValue/0.333 * 0.04, 1.0);
        else if(colorValue < 0.667)
                color = vec4(((1-colorValue/0.667) * 0.22 + colorValue/0.667 * 0.5), ((1-colorValue/0.667) * 0.17 + colorValue/0.667 * 0.5), ((1-colorValue/0.667) * 0.04 + colorValue/0.667 * 0.5), 1.0);
        else if(colorValue < 0.9)
                color = vec4(((1-colorValue/0.9) * 0.5 + colorValue/0.9 * 0.91), ((1-colorValue/0.9) * 0.5 + colorValue/0.9 * 0.91), ((1-colorValue/0.9) * 0.5 + colorValue/0.9 * 0.91), 1.0);
        else
                color = vec4((1-colorValue) * 0.91 + colorValue, (1-colorValue) * 0.91 + colorValue, (1-colorValue) * 0.91 + colorValue, 1.0);
}
