// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
  Car *newCar = new Car;
  newCar->light = light;
  if (first == nullptr) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car *tail = first->prev;
    tail->next = newCar;
    newCar->prev = tail;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (first == nullptr) return 0;

  countOp = 0;
  first->light = true;

  Car *passenger = first;
  int steps = 0;

  for (;;) {
    passenger = passenger->next;
    countOp++;
    steps++;

    if (passenger->light) {
      passenger->light = false;
      Car *checker = passenger;
      for (int i = 0; i < steps; ++i) {
        checker = checker->prev;
        countOp++;
      }

      if (!checker->light) {
        return steps;
      }

      passenger = checker;
      for (int i = 0; i < steps; ++i) {
        passenger = passenger->next;
        countOp++;
      }
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
