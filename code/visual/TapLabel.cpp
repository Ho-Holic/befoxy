#include "TapLabel.hpp"

TapLabel::TapLabel(const QString& text, QWidget* parent)
:   QLabel(text, parent)
{
    //
}

void TapLabel::mousePressEvent(QMouseEvent*)
{
    QFont tapFont = this->font();
    tapFont.setPointSize(tapFont.pointSize() - 10);
    this->setFont(tapFont);
}

void TapLabel::mouseReleaseEvent(QMouseEvent*)
{
    QFont tapFont = this->font();
    tapFont.setPointSize(tapFont.pointSize() + 10);
    this->setFont(tapFont);

    emit clicked();
}
