#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStringListModel>

#include "MyStandardItem.h"

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
    QStringList imageFilesList2;

    imageFilesList = FindFilesList(SRC_PATH);
    imageFilesList2 = FindFilesList(DST_PATH);
    SetList(*(ui->listViewImgList), imageFilesList);
    SetList(*(ui->listViewImgList_2), imageFilesList2);


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
bool MainWindow::SetList(QListView &view, const QStringList &list)
{
    // 設定モデルの取得
    QStandardItemModel *oldModel = qobject_cast<QStandardItemModel *>(view.model());
    // リストビューのクリア
    if (oldModel) {
        oldModel->removeRows(0, oldModel->rowCount());
    }

    QStandardItemModel *newModel = new QStandardItemModel();
    if (!newModel) {
        Q_ASSERT(false);
        return false;
    }

    foreach (QString url, list) {
        MyStandardItem *item = new MyStandardItem;
        QStringList urlsplit = url.split(DELIMITER);
        QString fileName = urlsplit.last();
        item->setUrl(url);
        item->setText(fileName);
        newModel->appendRow(item);
    }

    // モデルを設定
    view.setModel(newModel);
    view.setEditTriggers(QAbstractItemView::NoEditTriggers);    // ダブルクリックによる編集を禁止

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

    MyStandardItem *item = reinterpret_cast<MyStandardItem *>(model->itemFromIndex(index));
    QString imagePath = item->getUrl();
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
