//
// Created by Rylie Anderson on 12/21/23.
//

#ifndef PHALLOC_CONSTANTS_H
#define PHALLOC_CONSTANTS_H

//Environmental Parameters
//Constraints: width is required to be a multiple of two
#define wayness 4
#define width 256
#define line 64

//Algorithmic Parameters
#define flow_fraction 0.1
#define depth_multiplier 2

//Derived Parameters
#define depth (wayness * depth_multiplier)
#define maxflow (width * depth * flow_fraction)
#define bcount (width * depth)

#endif //PHALLOC_CONSTANTS_H
