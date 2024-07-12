#pragma once
#include <memory>
#include "DeutschlandreiseInputData.h"

class DeutschlandreiseData
{
public:
    DeutschlandreiseInputData GetDeutschlandreiseInputData() const;
    void SetDeutschlandreiseInputData(const DeutschlandreiseInputData& deutschlandreiseInputData);
    
private:
    DeutschlandreiseInputData deutschlandreiseInputData;
};