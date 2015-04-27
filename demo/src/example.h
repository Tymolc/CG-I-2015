#pragma once

#include "imageview.h"

class Example : public ImageView
{
public:
    Example(const QString & filename, QWidget * parent = NULL);
};
