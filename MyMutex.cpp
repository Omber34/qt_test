//
// Created by Herman on 6/1/2022.
//

#include "MyMutex.h"
#include "MyModel.h"

MyMutex::MyMutex(MyModel& model) : model(model)
{
  model.proxyMutex.lock();
}

MyMutex::~MyMutex()
{
  {
    std::lock_guard<std::mutex> lock(model.globalMutex);
    std::copy(model.m_proxyData.begin(), model.m_proxyData.end(), std::back_inserter(model.m_futureData));
  }

  model.updateData();
  model.proxyMutex.unlock();
}