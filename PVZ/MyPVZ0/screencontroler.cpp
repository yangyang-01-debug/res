#include "screencontroler.h"
#include <QDebug>
#include "firstscreen.h"
#include <QMessageBox>
ScreenControler::ScreenControler(QWidget *parent)
{
    this->timer = new QTimer();
   // this->timer2 = new QTimer();
    connect(this->timer,&QTimer::timeout,this,&ScreenControler::on_timeOut);
    for(int i = 0; i < 5; i ++){
        for(int j =0;j<9;j++){
           shooter[i][j] = nullptr;
           sunflower[i][j] = nullptr;
           wallnut[i][j] = nullptr;
        }
    }
    for(int i=0;i<zombie_num;i++){
        zombie[i] = new Zombies(i,parent);
        connect(this->timer,&QTimer::timeout,zombie[i],&Zombies::on_timeout);
    }
}

ScreenControler::~ScreenControler()
{
    for(int i = 0; i < 5; i ++){
        for(int j =0;j<9;j++){
            if(shooter[i][j] != nullptr){
                delete shooter[i][j];
                shooter[i][j] = nullptr;
            }
            if(sunflower[i][j] != nullptr){
                delete sunflower[i][j];
                sunflower[i][j] = nullptr;
            }
            if(wallnut[i][j] != nullptr){
                delete wallnut[i][j];
                wallnut[i][j] = nullptr;
            }
        }
    }
    for(int i=0;i<zombie_num;i++){
        if(zombie[i] != nullptr){
            delete zombie[i];
            zombie[i] = nullptr;
        }
    }
    if(timer != nullptr){
        delete timer;
        timer = nullptr;
    }
//    if(timer2 != nullptr){
//        delete timer2;
//        timer2 = nullptr;
//    }
}

QPoint ScreenControler::getPoint(int col, int id)
{
    if(col >= 5 || col < 0 || id >= 9 || id < -1){
        return QPoint(0,0);
    }
    if(id ==-1){
        return QPoint(1800,point_row_V[col] - 60);
    }
    return QPoint(point_col_H[id],point_row_V[col]);
}

void ScreenControler::addPlant(int col, int id, QString name, QWidget *parent)
{
    if(name == "shooter"){
        if(shooter[col][id] == nullptr){
            shooter[col][id] = new Shooters(plantId,parent);
            plantId ++;
            connect(this->timer,&QTimer::timeout,shooter[col][id],&Shooters::on_timeout);
        }
        shooter[col][id]->create(getPoint(col,id));
        shooter[col][id]->setCol_Id(col,id);
    }else if (name == "sunflower") {
       // qDebug()<<"create";
        if(sunflower[col][id] == nullptr){
            sunflower[col][id] = new SunFlower(plantId,parent);
            plantId++;
            connect(sunflower[col][id],&SunFlower::getSunNum,this,&ScreenControler::on_getSunNum);
            //connect(this->timer,&QTimer::timeout,sunflower[col][id],&SunFlower::on_timeout);
        }
        sunflower[col][id]->create(getPoint(col,id));
        sunflower[col][id]->setCol_Id(col,id);
//        sunflower[col][id]->m_plant->startMovie();
        sunflower[col][id]->show();
    }else if(name == "wallnut"){
        if(wallnut[col][id] == nullptr){
            wallnut[col][id] = new WallNut(parent);
            connect(this->timer,&QTimer::timeout,wallnut[col][id],&WallNut::on_timeout);
        }
        wallnut[col][id]->setCol_Id(col,id);
        wallnut[col][id]->create(getPoint(col,id));
        //wallnut[col][]
    }

}

void ScreenControler::deletePlant(int col, int id)
{
    if(shooter[col][id] == nullptr){
       // return;
    }else {
        shooter[col][id]->deleted();
    }

    if(sunflower[col][id] == nullptr){
        //return;
    }else {
        sunflower[col][id]->deleted();
    }

    if(wallnut[col][id] == nullptr){
        //return;
    }else {
        wallnut[col][id]->deleted();
    }
}

void ScreenControler::addZombie(int col)
{
    for(int i =0; i < zombie_num;i++){
        if(zombie[i]->m_is_died == true){
            zombie[i]->setCol(col);
            zombie[i]->create(getPoint(col,-1));
            //QMessageBox::warning(0,"0",QString("%1").arg(i));
            break;
        }
    }
}

void ScreenControler::startTime()
{
    if(timer->isActive()){

    }else {
        this->timer->start(100);
    }
//    if(timer2->isActive()){

//    }else {
//        this->timer2->start(100);
//    }

}

void ScreenControler::stopTime()
{
    if(this->timer->isActive()){
        timer->stop();
    }
//    if(this->timer2->isActive()){
//        timer2->stop();
//    }
}

int ScreenControler::shooterCost()
{
    return Shooters::m_cost;
}

int ScreenControler::sunFlowerCost()
{
    return SunFlower::m_cost;
}

int ScreenControler::plantBlood(int i, int j)
{
    if(shooter[i][j] != nullptr && shooter[i][j]->m_is_died == false){
        return shooter[i][j]->m_blood;
    }
    if(sunflower[i][j] != nullptr && sunflower[i][j]->m_is_died ==false){
        return sunflower[i][j]->m_blood;
    }
    return -10;

}

int ScreenControler::plantCost()
{//sunflower[i][j] = nullptr;
    return 50;
}

void ScreenControler::setZombiesBlood(int blood)
{
    for(int i=0;i<zombie_num;i++){
        zombie[i]->setBlood(blood);
    }
}

void ScreenControler::on_timeOut()
{
    int is_end = 0;
    int flag[5] = {0,0,0,0,0};
    for(int k =0;k < zombie_num;k++){
        switch (zombie[k]->m_col) {
        case 0:{
            flag[0] ++;
            break;
        }
        case 1:{
            flag[1] ++;
            break;
        }
        case 2:{
            flag[2] ++;
            break;
        }
        case 3:{
            flag[3] ++;
            break;
        }
        case 4:{
            flag[4] ++;
            break;
        }
        default:
            break;
        }
    }

    for(int i=0; i< zombie_num;i++){
        for(int j =0; j < 5; j ++){
            for(int k =0; k < 9; k ++){
                if(sunflower[j][k] == nullptr)continue;
                if(sunflower[j][k]->m_is_died == true)continue;
                if(/*zombie[i]->m_zombie->m_rect.intersects(sunflower[j][k]->m_plant->m_rect) ||*/
//                        (zombie[i]->m_zombie->m_rect.x() >sunflower[j][k]->m_plant->m_rect.x() &&
//                         sunflower[j][k]->m_plant->m_label->pos().x()>100 &&
//                         zombie[i]->m_zombie->m_rect.x() < sunflower[j][k]->m_plant->m_rect.x() +
//                         sunflower[j][k]->m_plant->m_rect.width())
                       sunflower[j][k]->m_plant->m_rect.intersects(zombie[i]->m_zombie->m_rect) && sunflower[j][k]->m_col == zombie[i]->m_col){
                        zombie[i]->setZombiesInfo(ATTACKING);
                        //qDebug()<<"sunflower attack";
                    if(zombie[i]->m_attackCount % zombie[i]->m_attackTimeCount == 0){
                        sunflower[j][k]->subBlood(zombie[i]->m_hert);
                        if(sunflower[j][k]->m_blood <=0){
                            zombie[i]->setZombiesInfo(RUNNING);
                            //qDebug()<<"sunflower running";
                        }
                    }
                }else {
                    //zombie[i]->setZombiesInfo(RUNNING);
                }
            }
        }
    }

    for(int i=0;i< zombie_num;i++){
        for(int j =0; j < 5; j ++){
            for(int k =0; k < 9; k ++){
                if(wallnut[j][k] == nullptr)continue;
                if(wallnut[j][k]->m_is_died == true)continue;/*//(zombie[i]->m_zombie->m_rect.x() >wallnut[j][k]->m_plant->m_rect.x() &&
                wallnut[j][k]->m_plant->m_label->pos().x()>100 &&
                zombie[i]->m_zombie->m_rect.x() < wallnut[j][k]->m_plant->m_rect.x() +
                wallnut[j][k]->m_plant->m_rect.width())*/
                if(zombie[i]->m_zombie->m_rect.intersects(wallnut[j][k]->m_plant->m_rect) &&
                         zombie[i]->m_col == wallnut[j][k]->m_col
                        ){
                        zombie[i]->setZombiesInfo(ATTACKING);
                        //qDebug()<<"wallnut attack";
                    if(zombie[i]->m_attackCount % zombie[i]->m_attackTimeCount == 0){
                        wallnut[j][k]->subBlood(zombie[i]->m_hert);
                        if(wallnut[j][k]->m_blood <=0){
                            zombie[i]->setZombiesInfo(RUNNING);
                            //qDebug()<<"wallnut running";
                        }
                    }
                }else {
                    ///zombie[i]->setZombiesInfo(RUNNING);
                }
            }
        }
    }


    for(int i =0; i < zombie_num;i ++){
        if(zombie[i]->m_is_died == true){
            is_end++;
        }
        if(zombie[i]->m_zombie->m_label->pos().x() <= 130){
            emit ending();
            return;
        }


        for(int j =0; j < 5; j ++){
            for(int k =0; k < 9; k ++){
                if(shooter[j][k] == nullptr){
                    continue;
                }
                if(flag[shooter[j][k]->m_col] > 0){
                    int is_shoot =0;
                    for(int m=0;m<zombie_num;m++){
                        //qDebug()<<m<<zombie[m]->m_col<<shooter[j][k]->m_col;
                        if((shooter[j][k]->m_plant->m_label->pos().x() <
                            zombie[m]->m_zombie->m_label->pos().x()) &&
                                zombie[m]->m_col == shooter[j][k]->m_col){
                            //shooter[j][k]->shoot();
                            is_shoot ++;
                        }
                    }
                    if(is_shoot > 0){
                        //qDebug()<<"shoot";
                        shooter[j][k]->shoot();
                    }else {
                       // qDebug()<<"stopshoot";
                        shooter[j][k]->stopshoot();
                    }
                }else {
                    //qDebug()<<"stopshoot";
                    shooter[j][k]->stopshoot();
                }


                if(zombie[i]->m_is_died == true){
                    continue;
                }



                if(zombie[i]->m_zombie->m_rect.intersects(shooter[j][k]->m_plant->m_rect)){
                    zombie[i]->setZombiesInfo(ATTACKING);
                    //qDebug()<<"shooter attack";
                    if(zombie[i]->m_attackCount % zombie[i]->m_attackTimeCount == 0){
                        shooter[j][k]->subBlood(zombie[i]->m_hert);
                        if(shooter[j][k]->m_blood <= 0){
                            zombie[i]->setZombiesInfo(RUNNING);
                            //qDebug()<<"shooter running";
                        }
                    }
                }

                if(shooter[j][k]->m_is_died == true){
                    continue;
                }
                if(shooter[j][k]->m_col < 0){
                    continue;
                }
//                for(int m=0;m<5;m++){
//                    qDebug()<<flag[m];
//                }


                for(int m=0;m<shooter[j][k]->m_pbs_list.length();m++){
                    if(shooter[j][k]->m_pbs_list.at(m)->is_shooted == false){
                        continue;
                    }
                    if(zombie[i]->m_zombie->m_rect.intersects(shooter[j][k]->m_pbs_list.at(m)->m_rect)){
                        zombie[i]->m_blood -= shooter[j][k]->m_pbs_list.at(m)->m_hert;
                        shooter[j][k]->setPbsStart(m);
                        emit attackZombie();
                    }
                }
            }
        }
    }

    for(int i=0;i< zombie_num;i++){
        int is_all = 0;
        for(int o =0; o<5;o ++){
            for(int p =0; p<9;p ++){
                if(shooter[o][p] != nullptr && shooter[o][p]->m_is_died == false){
                    if(shooter[o][p]->m_plant->m_rect.intersects(zombie[i]->m_zombie->m_rect)){
                        is_all ++;
                    }
                }
                if(wallnut[o][p] != nullptr && wallnut[o][p]->m_is_died == false){
                    if(wallnut[o][p]->m_plant->m_rect.intersects(zombie[i]->m_zombie->m_rect)){
                        is_all ++;
                    }
                }
                if(sunflower[o][p] != nullptr && sunflower[o][p]->m_is_died == false){
                    if(sunflower[o][p]->m_plant->m_rect.intersects(zombie[i]->m_zombie->m_rect)){
                        is_all ++;
                    }
                }
            }
        }
        if(is_all == 0)zombie[i]->setZombiesInfo(RUNNING);

    }


    if(is_end == zombie_num){
 //       qDebug()<<"win";
        emit winning();
    }
}

void ScreenControler::on_getSunNum()
{
    emit SunMunApl();
}

