#include "DeutschlandreiseData.h"
#include "TopologyData.h"

DeutschlandreiseData::DeutschlandreiseData() 
    : topologyData(nullptr)
    , isDebug(false)
    , isDetailDebug(false)
    , isTest(false)
{
}

DeutschlandreiseData::~DeutschlandreiseData()
{
    delete topologyData;
}

DeutschlandreiseInputData DeutschlandreiseData::GetDeutschlandreiseInputData() const
{
    return deutschlandreiseInputData;
}
    
void DeutschlandreiseData::SetDeutschlandreiseInputData(const DeutschlandreiseInputData& _deutschlandreiseInputData)
{
    deutschlandreiseInputData = _deutschlandreiseInputData;
}

const TopologyData& DeutschlandreiseData::GetTopologyData() const
{
    return *topologyData;
}
    
void DeutschlandreiseData::SetTopologyData(TopologyData* _topologyData)
{
    delete topologyData;
    topologyData = _topologyData;
}

void DeutschlandreiseData::SetIsDebug(bool _isDebug)
{
    isDebug = _isDebug;  
}

bool DeutschlandreiseData::IsDebug() const
{
    return isDebug;
}

void DeutschlandreiseData::SetIsDetailDebug(bool _isDetailDebug)
{
    isDetailDebug = _isDetailDebug;  
}

bool DeutschlandreiseData::IsDetailDebug() const
{
    return isDetailDebug;
}

void DeutschlandreiseData::SetIsTest(bool _isTest)
{
    isTest = _isTest;
}
    
bool DeutschlandreiseData::IsTest() const
{
    return isTest;
}