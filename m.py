#!/usr/bin/python3
import sys
from math import *

def deriveRelation(pp1, pp2):
    pp1 = int(pp1)
    pp2 = int(pp2)
    if pp1 == pp2 and pp1 == 0:
        return 5
    elif pp1 == 0 and pp2 > 0:
        return 4
    elif pp1 > 0 and pp2 == 0:
        return 3
    elif pp1 == pp2:
        return 2
    elif pp1 > pp2:
        return 1
    elif pp1 < pp2:
        return 0
    return -1

if __name__ == "__main__":
    f=open("./pi.txt","r")
    g=open("./negative_changes.txt","w")
    h=open("./negative_values.txt","w")
    _previous_value_ = 0
    _state_value_ = 0
    pp1 = str(f.read(1))
    pp2 = str(f.read(1))
    last_pp = pp1 + pp2
    _previous_relation_ = deriveRelation(pp1, pp2)
    g.write(str(0))
    h.write(str(0))
    t = 0
    while True:
        pp1 = str(f.read(1))
        if not pp1 or pp1 == "" or len(pp1) == 0:
            break
        pp2 = str(f.read(1))
        if not pp2 or pp2 == "" or len(pp2) == 0:
            break
        pp = int(pp1 + pp2)
        _relation_ = deriveRelation(pp1, pp2)
        if _relation_ != _previous_relation_:
            g.write(str(1))
            if int(pp) < int(last_pp):
                if t == 1:
                    if _previous_value_ == 0:
                        _state_value_ = 9
                    else:
                        _state_value_ = abs(_previous_value_ - 1) % 10
                else:
                    _state_value_ = abs(_previous_value_ + 1) % 10
            elif int(pp) > int(last_pp):
                if t == 1:
                    _state_value_ = abs(_previous_value_ + 1) % 10
                else:
                    if _previous_value_ == 0:
                        _state_value_ = 9
                    else:
                        _state_value_ = abs(_previous_value_ - 1) % 10
            _previous_value_ = _state_value_
            _previous_relation_ = _relation_
            h.write(str(_state_value_))
        else:
            g.write(str(0))
            h.write(str(_previous_value_))
        last_pp = pp
    g.close()
    h.close()
    f.close()
