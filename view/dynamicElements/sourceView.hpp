#ifndef SOURCEVIEW_H
#define SOURCEVIEW_H

#include <QWidget>
#include <QPushButton>

#include "model/elements/source.hpp"

class SourceView : public QPushButton
{
    Q_OBJECT

    Source * source;

public:

    SourceView(Source *source, QWidget * parent = 0);
    ~SourceView();

public slots:

    void switchSource();
};

#endif // SOURCEVIEW_H