#include <QApplication>
#include <QTableView>
#include <QPushButton>
#include "MyModel.h"
#include "InserterPool.h"

int main(int argc, char ** argv) {
  qRegisterMetaType<MyModelItem>();
  qRegisterMetaType<QVector<int>>();

  QApplication a(argc, argv);
  QTableView tableView;
  MyModel myModel;
  QPushButton addInserterButton("add inserter", &tableView);

  InserterPool inserterPool(myModel);
  QObject::connect(&addInserterButton, &QPushButton::clicked, &inserterPool, &InserterPool::addNewInserter);
  tableView.setModel(&myModel);
  tableView.show();
  return a.exec();
}
