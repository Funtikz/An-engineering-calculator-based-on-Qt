#include "stylehelper.h"


QString StyleHelper::getMainWidetStyle()
{
    return "QWidget{"
    "background-image: url(:/resourses/1674372862_catherineasquithgallery-com-p-fon-tekstura-serii-foto-1.jpg);"
           "}";
}

QString StyleHelper::getStartButtonsStyle()
{
    return "QPushButton{"
           "background: none;"
           "color: #fffbfb;"
           "background-color:#fe9e0b"
           "}";
}

QString StyleHelper::getNumberButton()
{
    return
    "QPushButton{"
           "background: none;"
           "color: #fffbfb;"
           "background-color:#333"


           "}";

}

QString StyleHelper::getUprav()
{
    return "QPushButton{"
           "background: none;"
           "color: #0a0309;"
           "background-color:#999"
           "}";
}
