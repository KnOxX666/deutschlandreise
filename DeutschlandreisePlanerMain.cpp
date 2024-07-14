#include "JourneyInput/JourneyInput.h"
#include "JourneyCalculator/JourneyCalculator.h"
#include "Data/DeutschlandreiseInputData.h"
#include "Data/DeutschlandreiseData.h"
#include "Data/JSonLoader.h"
#include "Data/TopologyData.h"
#include <iostream>
#include <cstring>
int main(int argc, char *argv[])
{
    DeutschlandreiseData data;
    for(size_t i = 0; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) data.SetIsDebug(true);
    }
    
    TopologyData* topologyData = JSonLoader().Load();
    data.SetTopologyData(topologyData);
    //data.SetDeutschlandreiseInputData(JourneyInput().Input(data.GetTopologyData().nodes));
    DeutschlandreiseInputData testInputData;
    testInputData.originAndDestinationCity = "Bremen";
    testInputData.transitCities = {"Hamburg", "Dortmund", "Kiel", "Schwerin", "Bielefeld"};
    data.SetDeutschlandreiseInputData(testInputData);
    JourneyCalculator(data).Calculate();

    return 0;
}
