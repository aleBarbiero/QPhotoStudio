#ifndef INDEX_H
#define INDEX_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

class Index:public QWidget{
    Q_OBJECT
    public:
        Index(QWidget* =nullptr);
    private:
        //layout
        QLabel* title;
        QLabel* img;
        QPixmap titleLimit;
        QPixmap imgLimit;
        QPushButton* insert;
        QPushButton* remove;
        QPushButton* alter;
};//index

#endif
