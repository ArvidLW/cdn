/*
 * Copyright 2017
 *
 * ga.h
 *
 * 遗传算法优化初始解
 *
 * 算法思路：
 * 每组服务器为一个个体
 * 第一阶段：增大个体差异
 * 第二阶段：选择优秀基因传承，好个体关联分析
 * 第三阶段：个体变异进化
 *
 * 初始服务器：ServerID,ServerCandidate,ServerPossible
 *
 * 少一个有服务器情景，少两个服务器情景，结果最好的前n个，抽取共同基因片段，做传承基因
 * 如果，少了任何一个服务器价格高于LP价，则尝试增加服务器个数，ln(allServer)
 *
 * Date: March 26, 2017
 * Author: Wei Liu, Ling Bao, Shangyue Zhou
 *
 * $Id: ga.h,v 0.1 2017/03/26 00:30:30 bl Exp $
 *
 */

#ifndef CDN_WEGA_H
#define CDN_WEGA_H


class WeGa {
private:
    char * thefilename;
    std::vector<int> allServer;
    std::bitset<MAXCONSUMER> BESTServer;//个体基因，标记所选择的服务器
    std::bitset<MAXCONSUMER> LPBestServer;//保存最好的基因，即选择服务器的最好结果
    std::bitset<MAXCONSUMER> BestGene;//最好的基因片段，即选出来的最好的需要传承的基因
    std::vector<std::bitset<MAXCONSUMER>> gaPopulation;//种群，从种群中选择好的基因
    int lpSIDcount;//线性规划结果ServerID个数
    int lpSCanCount;//线性规划结果ServerCandidate个数
    int lpSPosCount;//线性规划结果ServerPossible个数
    int initPopulationSize;
    int populationSize;//种群大小
    int maxIterate;
    int serverCountRange;//计算服务器要在ServerID上变动的个数，为ln(allserver)
    double minCost;
public:
    std::vector<int> GServerID;//存放ga选择的服务器节点,经解码过后
private:
    void stageOneGeneP();//生成种群第一阶段，减少服务器数
    void stageTwoGeneP();//生成种群第二阶段，增加服务器数

    void chooseBestGene();//精英群体
    void generatePopulation();//生成种群
    void decode();//基因解码，即对应真实服务器ID
    void initial();//初始化种群服务器
    void calcFitness();//计算适应度
    void mate();//个体交配，基因片段交换
    void swap();//交换父子群体
    void mutate();//突变操作
public:
    WeGa(char * filename):minCost{INF},
                          lpSIDcount{ChooseServer::serverID.size()},
                          lpSCanCount{ChooseServer::serverCandidate.size()},
                          lpSPosCount{ChooseServer::serverPossible.size()} {
        allServer.insert(allServer.end(),ChooseServer::serverID.begin(),ChooseServer::serverID.end());
        allServer.insert(allServer.end(),ChooseServer::serverCandidate.begin(),ChooseServer::serverCandidate.end());
        allServer.insert(allServer.end(),ChooseServer::serverPossible.begin(),ChooseServer::serverPossible.end());
        serverCountRange=(int)log(allServer.size());
        thefilename=filename;
    }
    void chooseServer();//ga选择服务器

};
void WeGa::initial() {
    for (int i = 0; i <ChooseServer::serverID.size() ; ++i) {
        LPBestServer.set(i);
    }
}
void WeGa::calcFitness() {
    ZKW m;
    for (int i = 0; i <gaPopulation.size()  ; ++i) {
        ChooseServer::serverID.clear();
        for (int j = 0; j < lpSIDcount+lpSCanCount; ++j) {
            if(gaPopulation[i][j]){
                ChooseServer::serverID.push_back(allServer[j]);
            }
        }

        m.run(Graph::nodeCount,Graph::arcCount);
        if(minCost>m.minicost){
            minCost=m.minicost;
            BESTServer=gaPopulation[i];
        }
    }
    for (int j = 0; j < lpSIDcount+lpSCanCount; ++j) {
        if(BESTServer[j]){
            ChooseServer::serverID.push_back(allServer[j]);
        }
    }
    std::cout<<"mincost: "<<minCost<<std::endl;
    write_result(m.s,thefilename);
}
void WeGa::chooseServer() {
    initial();
    stageOneGeneP();
    calcFitness();
}
void WeGa::stageOneGeneP() {
    //close a server from ServerID
    for(int i=0;i<ChooseServer::serverID.size();++i){
        std::bitset<MAXCONSUMER> b{LPBestServer};
        b.reset(i);
        gaPopulation.push_back(b);
        //std::cout<<b<<std::endl;
    }
    printf(splitLine);
    //open a server from ServerCandidate
    for (int j = lpSIDcount; j < lpSIDcount+lpSCanCount; ++j) {
        std::bitset<MAXCONSUMER> b{LPBestServer};
        b.set(j);
        std::cout <<b<<std::endl;
        gaPopulation.push_back(b);
    }
    printf(splitLine);
    std::cout<<"gaPopu Size : "<<gaPopulation.size()<<std::endl;

}
//void WeGa::stageTwoGeneP() {
//    for(int i=0;i<ChooseServer::serverID.size();++i){
//        std::bitset<MAXCONSUMER> b;
//        b.bitset();
//        b.reset(i);
//        for (int j= i+1; j < ChooseServer::serverID.size(); ++j) {
//            b.reset(j);
//        }
//        gaPopulation.push_back(b);
//    }
//}





#endif //CDN_WEGA_H
