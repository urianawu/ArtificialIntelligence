//
//  ProblemHouse.h
//  CSP
//
//  Created by Uriana on 2/28/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __CSP__ProblemHouse__
#define __CSP__ProblemHouse__

#include <stdio.h>
#include "ProblemJobs.h"
class ProblemHouse : public ProblemJobs{
public:
    ProblemHouse();
    bool consistency(string var, string value, Map assignment);
private:
    bool inSameHouse(string property1, string property2, string var, string value, Map assignment);
};
#endif /* defined(__CSP__ProblemHouse__) */
