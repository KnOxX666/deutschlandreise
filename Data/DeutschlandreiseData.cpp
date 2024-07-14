#include "DeutschlandreiseData.h"
#include "TopologyData.h"

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