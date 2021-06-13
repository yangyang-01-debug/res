#include "shooters.h"
int Shooters::m_cost = 100;
int cout =0;
int couttime = 10;
Shooters::Shooters(int id, QWidget *parent)
{
    this->m_id = id;
    this->m_plant = new BasicPlants(parent);
    this->m_plant->move(QPoint(0,-350));
    this->m_plant->setFixedSize(QSize(100,100));
    this->m_plant->setPlantStyle(shooter);
    setDefaultBlood();
    this->m_plant->startMovie();
    for(int i = 0; i < 10 ; i ++){
        BasicPbs *p = new BasicPbs(parent);
        p->setPbsType(FIRE_TYPE);
        p->setPbsType(NORMAL_TYPE);
        p->move(QPoint(0,500));
        this->m_pbs_list.push_back(p);
    }
}

Shooters::~Shooters()
{
    m_cost = 100;
     cout =0;
     couttime = 10;
    if(this->m_plant != nullptr){
        delete this->m_plant;
        this->m_plant = nullptr;
    }
    for(int i = 0; i < 10 ; i ++){
        BasicPbs *p = *(this->m_pbs_list.begin());
        this->m_pbs_list.pop_front();
        delete p;
        p = nullptr;
    }
}

void Shooters::shoot()
{
    this->m_is_shooting = true;
}

void Shooters::setPbsStart(int i)
{
    if(this->m_pbs_list.at(i)->m_Pbstype != NORMAL_TYPE){
        this->m_pbs_list.at(i)->setPbsType(NORMAL_TYPE);
    }
    this->m_pbs_list.at(i)->is_shooted = false;
    this->m_pbs_list.at(i)->stopMovie();
    this->m_pbs_list.at(i)->move(QPoint(0,-500));
    this->m_pbs_list.at(i)->m_len = 0;
}

void Shooters::stopshoot()
{
    this->m_is_shooting = false;
}

void Shooters::create(QPoint point)
{
    this->show();
    this->setDefaultBlood();
    this->m_is_died = false;
    this->m_is_shooting = false;
    this->move(point);
    this->m_point = point;
}

void Shooters::deleted()
{
    this->m_is_died = true;
    this->m_plant->move(QPoint(0,-500));
}

void Shooters::move(QPoint point)
{
    this->m_plant->move(point);
}

void Shooters::subBlood(int hert)
{
    this->m_blood -= hert;
}

void Shooters::setPbsType(PbsType type)
{
    for(int i =0;i<this->m_pbs_list.length();i++){
        this->m_pbs_list.at(i)->setPbsType(type);
    }
}

void Shooters::show()
{
    this->m_plant->show();
}

void Shooters::setCol_Id(int col, int id)
{
    this->m_col = col;
    this->m_id = id;
}

void Shooters::setDefaultBlood()
{
    //QString str = shootblood_;
    this->m_blood = this->defaultBlood;
}

void Shooters::setBlood(int blood)
{
    this->defaultBlood = blood;
}

void Shooters::on_timeout()
{
    if(this->m_is_died == true){
        for(int i =0; i<this->m_pbs_list.length();i++){
            if(this->m_pbs_list.at(i)->m_label->pos().x() > 2000){
                setPbsStart(i);
                break;
            }
            if(this->m_pbs_list.at(i)->is_shooted == true){
 //               if(cout % couttime ==0){
                    this->m_pbs_list.at(i)->move(QPoint(this->m_point.x() + this->m_pbs_list.at(i)->m_len,
                                                 this->m_point.y()));
//                }
//                cout++;
               // if(cout >= couttime*100){cout = 1;}
            }
        }
        return;
    }
    if(this->m_blood <= 0){
        deleted();
    }
    if(this->m_is_shooting == false){
        for(int i=0;i<this->m_pbs_list.length();i++){
            if(this->m_pbs_list.at(i)->is_shooted == true){
//                if(cout % couttime ==0){
//                    this->m_pbs_list.at(i)->move(QPoint(this->m_point.x() + this->m_pbs_list.at(i)->m_len,
//                                                 this->m_point.y()));
//                }
//                cout++;
//                if(cout >= couttime*100){cout = 1;}
                this->m_pbs_list.at(i)->move(QPoint(this->m_point.x() + this->m_pbs_list.at(i)->m_len,
                                             this->m_point.y()));
            }
        }
        return;
    }
    if(this->count % this->m_TimeCount == 0){
        this->count = 0;
    }
    if(this->count % this->m_TimeCount == 0){
        for(int i = 0; i < this->m_pbs_list.length() ; i ++){
            if(this->m_pbs_list.at(i)->is_shooted == false){
                this->m_pbs_list.at(i)->is_shooted = true;
                this->m_pbs_list.at(i)->startMovie();
                this->m_pbs_list.at(i)->show();
                break;
            }
        }
    }
    for(int i = 0; i < this->m_pbs_list.length() ; i ++){
        if(this->m_pbs_list.at(i)->is_shooted == true){
//            if(cout % couttime ==0){
//                this->m_pbs_list.at(i)->move(QPoint(this->m_point.x() + this->m_pbs_list.at(i)->m_len,
//                                             this->m_point.y()));
//            }
//            cout++;
//            if(cout >= couttime*100){cout = 0;}
            this->m_pbs_list.at(i)->move(QPoint(this->m_point.x() + this->m_pbs_list.at(i)->m_len,
                                                this->m_point.y()));

        }
        if(this->m_pbs_list.at(i)->m_label->pos().x() > 2000){
            setPbsStart(i);
        }
    }

    this->count ++;
}
