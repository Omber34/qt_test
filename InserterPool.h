//
// Created by Herman on 5/31/2022.
//

#pragma once
#include "MyModel.h"
#include <QObject>
#include <thread>

class Inserter : public QObject
{
  Q_OBJECT
public:
  Inserter(MyModel& model);

signals:
  void insertNewData(MyModelItem item);

public:
  void stop();

private:
  std::thread mainThread;
  uint32_t threadID;
  uint32_t rowCount = 0;
  bool m_stop = false;
};
using InserterPtr = std::shared_ptr<Inserter>;

class InserterPool : public QObject
{
  Q_OBJECT
public:
  InserterPool(MyModel& model, QObject* parent = nullptr) : QObject(parent), model(model) {}

public slots:
  void addNewInserter();

public:
  ~InserterPool();

private:
  MyModel& model;
  std::vector<InserterPtr> inserters;
};



