#ifndef PLAYERMASTER_H
#define PLAYERMASTER_H

#include <QMainWindow>

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QList>
#include <QMediaContent>
#include <QListWidget>
#include <QLineEdit>
#include <QLCDNumber>
#include <QDesktopWidget>
#include <QIcon>
#include <QMouseEvent>
#include <QKeyEvent>

namespace Ui {
class PlayerMaster;
}

class PlayerMaster : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerMaster(QWidget *parent = 0);
    ~PlayerMaster();

private slots:
    void on_sliderProgress_sliderMoved(int position);
    void on_sliderVolume_sliderMoved(int position);
    void on_pushButtonPlayPause_clicked();
    void on_pushButtonAdd_clicked();
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);
    void on_pushButtonNext_clicked();
    void on_pushButtonPrev_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButtonClear_clicked();
    void on_pushButtonStop_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::PlayerMaster *ui;
    QMediaPlayer *player;
    QMediaPlaylist *list;
    QList<QMediaContent> content;
    double m;
    double s;
    int pos;
    int row;
    QDesktopWidget dw;
    QMainWindow w;
    int key;
    int vol;

protected:
    virtual void keyPressEvent(QKeyEvent* event);

};

#endif // PLAYERMASTER_H
