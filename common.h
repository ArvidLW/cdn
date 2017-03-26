/*
 * Copyright 2017
 *
 * common.h
 *
 * 包含所有模块，宏定义，头文件
 *
 * 注意：包含顺序，否则可能出错
 *
 * Date: March 26, 2017
 * Author: Wei Liu, Ling Bao, Shangyue Zhou
 *
 * $Id: common.h,v 0.1 2017/03/26 00:22:35 lw Exp $
 *
 */

#ifndef CDN_COMMON_H
#define CDN_COMMON_H


#define MAXNODE 1000                //最大节点数
#define MAXCONSUMER 500             //最大消费节点数
#define MAXVALUE 1000.0             //设定的最大值
#define MIN_VALUE 0.01              //用来界定选择服务器
#define MIN_VALUE_ZERO 0.005        //用来界定所有备选服务器
#define MAX_VALUE_SUPER_OUT 2000.0  //用来设定超源节点与服务器位置关系，作为服务器最大输出系数
#define SERVER_VAL_PARA 1.0         //服务器价格参数，用来变换服务器价格

#define INF 9999                    //极大值
//#define MAX_EDGE_NUM_G (2000*20+1500)
#define MAX_NODE_NUM 1010           //最大节点数

//#define WEDEBUG                     //用于打印基本信息与计算过程

//c库
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <cstdio>
#include <cmath>
#include <cassert>

//c++
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <list>
#include <stack>
#include <queue>
#include <unordered_map>

//we
#include "Graph.h"          //1、建图
#include "lwlp.h"           //2、建线性规划
#include "chooseServer.h"   //3、开始选择服务器
#include "mc_zk.h"          //4、mcmf和zkw共有头文件
#include "mcmf.h"           //4.1、最小费用流mcmf
#include "zkw.h"            //4.2、zkw
//#include "ga.h"             //5、遗传
#include "NeSearch.h"       //邻域搜索+禁忌




#endif //CDN_COMMON_H
