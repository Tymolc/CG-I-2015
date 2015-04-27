#include "example.h"

Example::Example(const QString &filename, QWidget *parent)
: ImageView(parent)
{
    QImage image(filename);

    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            // (x, y)
            if (x % 10 == 0 || y % 10 == 0)
            {
                QColor color = QColor(image.pixel(x, y));

                color.setRedF(1.0 - color.redF());
                color.setGreenF(1.0 - color.greenF());
                color.setBlueF(1.0 - color.blueF());

                image.setPixel(x, y, color.rgb());
            }
        }
    }

    setImage(image);
}
