/*
 * Copyright 2017
 *
 * deploy.cpp
 *
 * 功能入口
 *
 * Date: March 26, 2017
 * Author: Wei Liu, Ling Bao, Shangyue Zhou
 *
 * $Id: deploy.h,v 0.1 2017/03/26 00:22:35 bl Exp $
 *
 */
#include "deploy.h"
#include "common.h"

//#define Mc
#define Zk

//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{
    char* result;
    double minCost;

    timer.Begin();//计时开始

    int t0=clock();

    // 图
    Graph G;
    G.init(topo);

    // 线性规划
    printf(splitLine);
    ChooseServer::lpChoose();//线性规划选择服务器

    // 遗传算法
    printf(splitLine);
//    if (ChooseServer::serverID.size() + ChooseServer::serverCandidate.size() + ChooseServer::serverPossible.size() > 300) {
//        OurGA ourGA = OurGA(filename);
//        if (ourGA.bSolve) {
//            ourGA.GaAlgorithmServer();
//        }
//    }
//    else {
//        OurGA1 ourGA = OurGA1(filename);
//        if (ourGA.bSolve) {
//            ourGA.GaAlgorithmServer();
//        }
//    }

//    OurGA1 ourGA = OurGA1(filename);
//    if (ourGA.bSolve) {
//        ourGA.GaAlgorithmServer();
//    }

    OurGA2 ourGA = OurGA2(filename);
    if (ourGA.bSolve) {
        ourGA.GaAlgorithmServer();
    }

    printf(splitLine);
    std::cout<<clock() - t0<<std::endl;

    timer.End();//计时结束
}





