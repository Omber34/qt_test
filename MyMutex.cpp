//
// Created by Herman on 6/1/2022.
//

#include "MyMutex.h"
#include "MyModel.h"

MyMutex::MyMutex(MyModel& model) : model(model)
{
  model.globalMutex.lock();
}

MyMutex::~MyMutex()
{
  model.updateData();
  model.globalMutex.unlock();
}