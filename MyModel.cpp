//
// Created by Herman on 5/31/2022.
//

#include "MyModel.h"
#include <QCoreApplication>

MyModel::MyModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int MyModel::rowCount(const QModelIndex &parent) const
{
  return m_data.size();
}

int MyModel::columnCount(const QModelIndex &parent) const
{
  return 2;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (index.column() == 0)
      return QVariant::fromValue(m_data[index.row()].threadID);
    if (index.column() == 1)
      return QVariant::fromValue(m_data[index.row()].rowID);
  }
  return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  return QAbstractTableModel::headerData(section, orientation, role);
}

void MyModel::insertNewData(MyModelItem item)
{
  m_proxyData.push_back(item);
}

MyMutex MyModel::createMyMutex()
{
  return MyMutex(*this);
}

void MyModel::updateData()
{
  QMetaObject::invokeMethod(QCoreApplication::instance(),
                            [this]()
                            {
                              std::vector<MyModelItem> newData;
                              {
                                std::lock_guard<std::mutex> lock(globalMutex);
                                std::swap(m_futureData, newData);
                              }

                              beginInsertRows(QModelIndex(), m_data.size(), m_data.size() + newData.size());
                              std::copy(newData.begin(), newData.end(), std::back_inserter(m_data));
                              endInsertRows();
                            });
}