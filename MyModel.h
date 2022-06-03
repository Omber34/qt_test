//
// Created by Herman on 5/31/2022.
//

#pragma once
#include <QAbstractTableModel>
#include <QMetaType>
#include <mutex>
#include "MyMutex.h"

struct MyModelItem
{
  uint32_t threadID;
  uint32_t rowID;
};

class MyModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit MyModel(QObject* parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  void insertNewData(MyModelItem item);
  MyMutex createMyMutex();


private:
  std::vector<MyModelItem> m_data;
  std::vector<MyModelItem> m_futureData;
  std::vector<MyModelItem> m_proxyData;
  std::mutex globalMutex;
  std::mutex proxyMutex;

  friend class MyMutex;

  void updateData();
};

Q_DECLARE_METATYPE(MyModelItem);