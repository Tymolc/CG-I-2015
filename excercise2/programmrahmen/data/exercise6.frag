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

flat in float colorValue1;
in float colorValue2;
noperspective in float colorValue3;

out vec4 color;

uniform int interpolationMode;

void main()
{
    //Farbwert auslesen (vom Modus abhaengig)
        float colorValue;
        if(interpolationMode == 0)
                colorValue = colorValue1;
        if(interpolationMode == 1)
                colorValue = colorValue2;
        if(interpolationMode == 2)
                colorValue = colorValue3;

    //Farbwert berechnen

        if(colorValue < 0.1){
            color = vec4(0.204, 0.529, 0, 1.0);
        }
        else if(colorValue < 0.333){
            //Farbkomponente = (colorValue-minWert) * ((Farbkomponente_neu - Farbkomponente_alt)/(maxWert-minWert)) + Farbkomponente_alt
            color = vec4((colorValue-0.1) * 0.067 + 0.204, (colorValue-0.1) * (-1.53) + 0.529, (colorValue-0.1) * 0.167, 1.0);
        }
        else if(colorValue < 0.667){
            color = vec4((colorValue-0.333) * 0.84 + 0.219, (colorValue-0.333) * 0.99 + 0.173, (colorValue-0.333) * 1.39 + 0.039, 1.0);
        }
        else if(colorValue < 0.9){
            color = vec4((colorValue-0.667) * 1.76 + 0.502, (colorValue-0.667) * 1.76 + 0.502, (colorValue-0.667) * 1.76 + 0.502, 1.0);
        }
        else{
            color = vec4((colorValue-0.9) * 0.86 + 0.914, (colorValue-0.9) * 0.86 + 0.914, (colorValue-0.9) * 0.86 + 0.914, 1.0);
        }
}
