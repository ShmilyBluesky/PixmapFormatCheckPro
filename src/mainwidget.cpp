#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_btn_selectImgSrc_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                                    tr("Open Directory"),
                                                    ".",
                                                    QFileDialog::ShowDirsOnly);
    if (dir.length() > 0)
    {
        ui->edit_imgSrc->setText(dir);
    }
}

void MainWidget::on_btn_process_clicked()
{
    QStringList listImages = getImageFileName(ui->edit_imgSrc->text());

    foreach (const QString& value, listImages)
    {
        QImage image(value);
        if (!image.isNull())
        {
            image.save(value);
        }
    }
}

QStringList MainWidget::getImageFileName(const QString &path)
{
    QStringList retList;

    QDir dir(path);

    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    foreach (const QFileInfo& value, fileInfoList)
    {
        // 文件夹
        if (value.isDir())
        {
            retList.append(getImageFileName(value.absoluteFilePath()));
        }
        // 文件
        else if (value.isFile())
        {
            QString fileName = value.absoluteFilePath();
            QStringList listSuffix = getImageSuffixes();

            foreach (const QString& value, listSuffix)
            {
                if (fileName.endsWith(value))
                {
                    retList.push_back(fileName);
                    break;
                }
            }
        }
    }

    return retList;
}

QStringList MainWidget::getImageSuffixes() const
{
    QStringList list = ui->edit_suffix->text().split(QString(","));

    QStringList listResult;
    foreach (const QString& value, list)
    {
        if (value.length() > 0)
            listResult.push_back(value);
    }

    return listResult;
}
