//
//  sincosineLut.cpp
//  emptyExample
//
//  Created by Roy Macdonald on 7/24/13.
//  Copyright (c) 2013 micasa. All rights reserved.
//

#include "sincosineLut.h"

vector<float> sinCosineLut::sinLut =vector<float> (sinCosineLut::initSin());
vector<float> sinCosineLut::cosLut =vector<float> (sinCosineLut::initCos());
int sinCosineLut::resolution = DEFAULT_RES;