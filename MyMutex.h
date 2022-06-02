//
// Created by Herman on 6/1/2022.
//

#pragma once

class MyModel;

class MyMutex
{
private:
  MyMutex(MyModel& model);

public:
  virtual ~MyMutex();

private:
  MyModel& model;

  friend class MyModel;
};




