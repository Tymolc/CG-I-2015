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


in float colorValue1;
in float colorValue2;
in float colorValue3;

out vec4 color;

uniform int interpolationMode;

void main()
{
    // TODO: Farbwert auslesen (vom Modus abhaengig)
    float colorValue = 0.0;

    /////////////////////////////////////////////////
    // TODO: Aufgabe 6c) - Farbe berechnen
    //////////////////////////////////////////////////

    // Als Graustufenwert interpretieren
    /*if(colorValue1 < 0.1) {
                colorValue1 = 0.2;
                colorValue2 *= 0.53;
                colorValue3 *= 0;
        }
        else if(height < 0.333)
                color = vec4((1-colorValue1) * 0.22, (1-colorValue2) * 0.17, (1-colorValue3) * 0.04, 1.0);
        else if(height < 0.667)
                color = vec4((1-colorValue1) * 0.5, (1-colorValue2) * 0.5, (1-colorValue3) * 0.5, 1.0);
        else if(height < 0.9)
                color = vec4((1-colorValue1) * 0.91, (1-colorValue2) * 0.91, (1-colorValue3) * 0.91, 1.0);*/
                color = vec4(colorValue1, colorValue2, colorValue3, 1.0);
}
