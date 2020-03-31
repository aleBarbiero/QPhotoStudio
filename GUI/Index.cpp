#include "Index.h"
#include "../mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>
#include <QVBoxLayout>

Index::Index(QWidget* q):
    QWidget(q),
    title(new QLabel(this)),
    img(new QLabel(this)),
    titleLimit(QPixmap(":/images/title.png")),
    imgLimit(QPixmap(":/images/image.png")),
    insert(new QPushButton("Inserisci",this)),
    remove(new QPushButton("Listino",this)),
    alter(new QPushButton("Modifica/Rimuovi",this)){
        QGridLayout* indexL=new QGridLayout(this);
        QVBoxLayout* buttonL=new QVBoxLayout();
        //immagine
        img->setFixedSize(350,350);
        imgLimit=imgLimit.scaled(img->size(),Qt::KeepAspectRatio);
        img->setPixmap(imgLimit);
        img->setAlignment(Qt::AlignRight);
        //titolo
        title->setFixedSize(400,200);
        titleLimit=titleLimit.scaled(title->size(),Qt::KeepAspectRatio);
        title->setPixmap(titleLimit);
        title->setAlignment(Qt::AlignLeft);
        //bottone
        buttonL->addWidget(insert);
        buttonL->addWidget(remove);
        buttonL->addWidget(alter);
        buttonL->setAlignment(insert,Qt::AlignLeft);
        buttonL->setAlignment(remove,Qt::AlignLeft);
        buttonL->setAlignment(alter,Qt::AlignLeft);
        //impostare_pagina
        indexL->addWidget(title);
        indexL->addWidget(img,0,4,5,5);
        indexL->addLayout(buttonL,3,0,1,3);
        //connect
        connect(insert,SIGNAL(clicked(bool)),q,SLOT(insertSet()));
        connect(remove,SIGNAL(clicked(bool)),q,SLOT(removeSet()));
        connect(alter,SIGNAL(clicked(bool)),q,SLOT(battleSet()));
}//index
