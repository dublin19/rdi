#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include "imagepreview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLabel *displayLbl;

    ImagePreview *imgPreview;
};

#endif // MAINWINDOW_H
