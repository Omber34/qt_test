//
// Created by Herman on 5/31/2022.
//

#include "InserterPool.h"
#include <chrono>

Inserter::Inserter(MyModel &model)
{
  mainThread = std::thread([this, &model]()
                           {
                             threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
                             while (!m_stop)
                             {
                               {
                                 auto mutex = model.createMyMutex();

                                 model.insertNewData(MyModelItem{ threadID, rowCount++ });
                               }

                               std::this_thread::sleep_for(std::chrono::milliseconds(5));
                             }
                           });

  mainThread.detach();
}

void Inserter::stop()
{
  m_stop = true;
}

void InserterPool::addNewInserter()
{
  inserters.push_back(std::make_shared<Inserter>(model));
}

InserterPool::~InserterPool()
{
  for (const auto &inserter: inserters)
    inserter->stop();
}
