#include "JourneyInput/JourneyInput.h"
#include "JourneyCalculator/PermutationCreator.h"
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
    //data.SetDeutschlandreiseInputData(JourneyInput().Input(data.GetTopologyData().nodes));
    DeutschlandreiseInputData testInputData;
    testInputData.originAndDestinationCity = "Bremen";
    testInputData.transitCities = {"Hamburg", "Dortmund", "Kiel", "Schwerin", "Bielefeld"};
    data.SetDeutschlandreiseInputData(testInputData);
    PermutationCreator().CalculatePermutations(data.GetDeutschlandreiseInputData().transitCities);

    return 0;
}
