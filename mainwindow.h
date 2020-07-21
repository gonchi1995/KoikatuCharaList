#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>

#define SRC_PATH    "D:\\Games\\illusion\\Koikatu_\\UserData\\chara\\female"    // 送信元ディレクトリ
#define DST_PATH    "D:\\Games\\illusion\\Koikatu\\UserData\\chara\\female"     // 送信先ディレクトリ

#define DELIMITER   "\\"    // デリミタ

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 更新ボタンクリック
    void on_pushButtonUpdate_clicked();

    void on_listViewImgList_pressed(const QModelIndex &index);

private:
    // path内ののファイル名の文字列リストを生成
    QStringList FindFilesList(const QString &path);
    // listをListViewに登録
    bool SetList(QListView &view, const QStringList &list);

    void ShowImage(const QModelIndex &index);

    void SetImage(const QString &imgPath);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
