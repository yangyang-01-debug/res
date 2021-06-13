#ifndef BASICPLANTS_H
#define BASICPLANTS_H

#include <QObject>
#include "basicmovie.h"

enum PlantStyle{
    shooter,
    nut,
    tallnut,
    sunflower
};

class BasicPlants : public BasicMovie
{
    Q_OBJECT
public:
    explicit BasicPlants(QWidget *parent = nullptr);
    virtual ~BasicPlants();
    void move(const QPoint &point);
    void setPlantStyle(PlantStyle style);
signals:
public:

};

#endif // BASICPLANTS_H
