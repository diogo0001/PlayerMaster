#include "playermaster.h"
#include "ui_playermaster.h"

PlayerMaster::PlayerMaster(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayerMaster)
{
     ui->setupUi(this);
     ui->centralWidget->setLayout(ui->verticalLayout_2);

     setWindowTitle("PlayerMaster");
     setWindowIcon(QIcon("PlayerIcon.png"));

     player = new QMediaPlayer(this);
     list = new QMediaPlaylist(player);
     player->setPlaylist(list);

     ui->lcdNumber->display("00:00");

     connect(player, &QMediaPlayer::positionChanged, this, &PlayerMaster::on_positionChanged);
     connect(player, &QMediaPlayer::durationChanged, this, &PlayerMaster::on_durationChanged);
 }
 //-------------------------------------------------------------------------------------
 PlayerMaster::~PlayerMaster()
 {
     delete ui;
 }
 //-------------------------------------------------------------------------------------
 //Atualiza a posição da música ao mexer na barra
 void PlayerMaster::on_sliderProgress_sliderMoved(int position)
 {
     player->setPosition(position);
     int h;
     int min;
     int seg;

     seg = position/1000;   // Atualiza o tempo no display ao mexer na barra
     m = 0;

     if(seg>60){
         h = seg/3600;
         min = (seg%3600)/60;
         s = (seg%3600)%60;
         m = h*60 + min;
     }
 }
 //-------------------------------------------------------------------------------------
 void PlayerMaster::on_sliderVolume_sliderMoved(int position)
 {
     player->setVolume(position);
     vol = position;
 }
 //-------------------------------------------------------------------------------------
 // Adiciona a pasta de musicas à lista
 void PlayerMaster::on_pushButtonAdd_clicked()
 {
     QString directory = QFileDialog::getExistingDirectory(this,tr("Escolha a pasta"));

     if(directory.isEmpty())
         return;

     QDir dir(directory);
     QStringList files = dir.entryList(QStringList() << "*.mp3",QDir::Files);

     for(const QString& f:files)
     {
         content.push_back(QUrl::fromLocalFile(dir.path()+"/" + f));
         QFileInfo fi(f);
         ui->listWidget->addItem(fi.fileName());
     }

     list->addMedia(content);
     ui->listWidget->setCurrentRow(list->currentIndex() != -1? list->currentIndex():0);  // Seleciona a linha

 }
 //-------------------------------------------------------------------------------------
 // Atualiza aposição do slider conforme a música progride e mostra o tempo
 void PlayerMaster::on_positionChanged(qint64 position)
 {
     QString time;
     ui->sliderProgress->setValue(position);
     double aux = position/1000;

     if(row != list->currentIndex()){
         row = list->currentIndex();
         s = 0;
         m = 0;
         ui->lcdNumber->display("00:00");
         ui->listWidget->setCurrentRow(list->currentIndex() != -1? list->currentIndex():0);
     }

     if(aux<1)
         s = 0;

     if(s==60){
         s = 0;
         m++;
     }

     if(s<10)
         time = '0'+ QString::number(double(m))+":0"+QString::number(double(s));
     else
         time = '0'+ QString::number(double(m))+':'+QString::number(double(s));

     ui->lcdNumber->display(time);

     s++;

//     qDebug()<<position/1000;
 }
 //-------------------------------------------------------------------------------------
 void PlayerMaster::on_durationChanged(qint64 position)
 {
     ui->sliderProgress->setMaximum(position);
     pos = position;
 }
 //-------------------------------------------------------------------------------------
 void PlayerMaster::on_pushButtonNext_clicked()
 {
    if(list->isEmpty()==false){
        s = 0;
        m = 0;
        list->next();
        ui->listWidget->setCurrentRow(list->currentIndex() != -1? list->currentIndex():0);
        ui->lcdNumber->display("00:00");
        row = list->currentIndex();
     }
    qDebug() << player->errorString();
 }
 //-------------------------------------------------------------------------------------
 void PlayerMaster::on_pushButtonPrev_clicked()
 {
     if(list->isEmpty()==false){
         s = 0;
         m = 0;
         list->previous();
         ui->listWidget->setCurrentRow(list->currentIndex() != -1? list->currentIndex():0);
         ui->lcdNumber->display("00:00");
         row = list->currentIndex();
     }
     qDebug() << player->errorString();
 }
 //-------------------------------------------------------------------------------------
 // Defide o botão para tocar ou parar
 void PlayerMaster::on_pushButtonPlayPause_clicked()
 {

     if(list->isEmpty()==false){     // Teste para não dar crash

         if(ui->pushButtonPlayPause->text() == tr("Play"))
         {
            // s = 0;
           //  m = 0;
             player->play();
             ui->pushButtonPlayPause->setText(tr("Pause"));
            // ui->lcdNumber->display("00:00");
             row = list->currentIndex();
         }
         else
         {  // s = 0;
            // m = 0;
             player->pause();
             ui->pushButtonPlayPause->setText(tr("Play"));
            // ui->lcdNumber->display("00:00");
         }
     }

//     qDebug() << player->errorString();
 }
 //-------------------------------------------------------------------------------------
 // Se clicar 2 vezes sobre a música ela executa
 void PlayerMaster::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
 {
     int to = item->listWidget()->currentIndex().row();

     if(list->isEmpty()==false){

         list->setCurrentIndex(to);
         if(ui->pushButtonPlayPause->text() == tr("Play"))
         {
             s = 0;
             m = 0;
             player->play();
             ui->pushButtonPlayPause->setText(tr("Pause"));
             ui->lcdNumber->display("00:00");
         }

     }
     row = list->currentIndex();
 //    int from = list->currentIndex();
 //    qDebug()<<"sel:"<<to<<" new:"<<from;
 }
//-------------------------------------------------------------------------------------
void PlayerMaster::on_pushButtonClear_clicked()
{
     if(list->isEmpty()==false){
        list->clear();
        ui->listWidget->clear();
     }
}
//-------------------------------------------------------------------------------------
void PlayerMaster::on_pushButtonStop_clicked()
{
    if(list->isEmpty()==false){     // Teste para não dar crash

        if(ui->pushButtonPlayPause->text() != tr("Play")|| ui->pushButtonPlayPause->text() != tr("Pause"))
        {
            s = 0;
            m = 0;
            player->stop();
            ui->pushButtonPlayPause->setText(tr("Play"));
            ui->lcdNumber->display("00:00");
        }
    }
}
//-------------------------------------------------------------------------------------
void PlayerMaster::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(key == Qt::Key_Delete){
    }
}
//-------------------------------------------------------------------------------------
void PlayerMaster::keyPressEvent(QKeyEvent* event)
{
    key = event->key();

    if(key == 16777221){
         on_pushButtonPlayPause_clicked();
    }
    if(key == 16777234){
         on_pushButtonPrev_clicked();
    }
    if(key == 16777236){
         on_pushButtonNext_clicked();
    }
//    if(key == 16777235){
//          vol +=3;
//          if(vol >100)  vol = 100;
//          player->setVolume(vol);
////          on_sliderVolume_sliderMoved(vol);
//    }
//    if(key == 16777237){
//         vol -=3;
//         if(vol <0) vol = 0;
//         player->setVolume(vol);
////         on_sliderVolume_sliderMoved(vol);
//    }

//    16777222  insert
//    16777223  delete


//    qDebug()<<"key: "<<key;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------

