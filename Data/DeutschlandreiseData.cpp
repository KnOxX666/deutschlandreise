#include "DeutschlandreiseData.h"

DeutschlandreiseInputData DeutschlandreiseData::GetDeutschlandreiseInputData() const
{
    return deutschlandreiseInputData;
}
    
void DeutschlandreiseData::SetDeutschlandreiseInputData(const DeutschlandreiseInputData& _deutschlandreiseInputData)
{
    deutschlandreiseInputData = _deutschlandreiseInputData;
}