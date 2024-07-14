#include "JourneyInput/JourneyInput.h"
#include "Data/DeutschlandreiseInputData.h"
#include "Data/DeutschlandreiseData.h"
#include "Data/JSonLoader.h"
#include "Data/TopologyData.h"
#include <iostream>
int main()
{
    TopologyData* topologyData = JSonLoader().Load();
    
    DeutschlandreiseData data;
    data.SetTopologyData(topologyData);
    data.SetDeutschlandreiseInputData(JourneyInput().Input(data.GetTopologyData().nodes));

    return 0;
}
