#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QFileInfoList>
#include <QTextStream>
#include <QDir>
#include <QDebug>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_btn_selectImgSrc_clicked();

    void on_btn_process_clicked();

private:
    // 获取所有图片
    QStringList getImageFileName(const QString& path);
    QStringList getImageSuffixes() const;

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
