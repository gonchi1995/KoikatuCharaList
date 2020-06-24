#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 更新ボタン押下
void MainWindow::on_pushButtonUpdate_clicked()
{
    bool ret = false;
    QStringList imageFilesList;

    imageFilesList = FindFilesList(SRC_PATH);
    ret = SetList(imageFilesList);

    qDebug() << ret;
//    foreach(QString debugStr, imageFilesList) {
//        qDebug() << debugStr;
//    }
}

// リストビューアイテム選択
void MainWindow::on_listViewImgList_pressed(const QModelIndex &index)
{
    // 画像をビューに表示
    ShowImage(index);
}

// 指定パスのファイルリスト
QStringList MainWindow::FindFilesList(const QString& path)
{
    QStringList fileList;
    QDir dir(path);

    fileList.clear();

    foreach(QString fileName, dir.entryList(QDir::Files)) {
        fileList.append(QString(path) + QDir::separator() + fileName);
    }

    return fileList;
}

// リストをリストビューに設定
bool MainWindow::SetList(const QStringList &list)
{
    // 設定モデルの取得
    QStandardItemModel *oldModel = qobject_cast<QStandardItemModel *>(ui->listViewImgList->model());
    // リストビューのクリア
    if (oldModel) {
        oldModel->removeRows(0, oldModel->rowCount());
    }

    QStandardItemModel *newModel = new QStandardItemModel();
    if (!newModel) {
        Q_ASSERT(false);
        return false;
    }

    foreach (QString str, list) {
        QStandardItem *item = new QStandardItem();
        item->setText(str);
        newModel->appendRow(item);
    }

    // モデルを設定
    ui->listViewImgList->setModel(newModel);
    ui->listViewImgList->setEditTriggers(QAbstractItemView::NoEditTriggers);    // ダブルクリックによる編集を禁止

    return true;
}

// リストビューで選択したアイテムの画像を表示
void MainWindow::ShowImage(const QModelIndex &index)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->listViewImgList->model());
    if (!model) {
        Q_ASSERT(false);
        return;
    }

    QString imagePath = model->data(index).toString();
    SetImage(imagePath);
}

// 指定したパスの画像をGraphicsViewに表示
void MainWindow::SetImage(const QString &imgPath)
{
    QImage img(imgPath);
    QPixmap pixmap = QPixmap::fromImage(img);

    // 前のSceneをクリア
    QGraphicsScene *oldScene = ui->graphicsView->scene();
    delete oldScene;

    // SceneをGraphicsViewに設定
    QGraphicsScene *newScene = new QGraphicsScene();
    newScene->addPixmap(pixmap.scaledToHeight(195));
    ui->graphicsView->setScene(newScene);
}
