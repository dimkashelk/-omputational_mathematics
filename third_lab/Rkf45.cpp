#include "Rkf45.h"

dimkashelk::Rkf45::Rkf45(int count): F1(nullptr),
                                     F2(nullptr),
                                     F3(nullptr),
                                     F4(nullptr),
                                     F5(nullptr),
                                     SAVRE(nullptr),
                                     SAVAE(nullptr),
                                     KOP(nullptr),
                                     INIT(nullptr),
                                     JFLAG(nullptr),
                                     KFLAG(nullptr) {
}
