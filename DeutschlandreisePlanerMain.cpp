#include "JourneyInput/JourneyInput.h"
#include "Data/DeutschlandreiseInputData.h"
#include "Data/DeutschlandreiseData.h"

int main()
{
    DeutschlandreiseData data;
    data.SetDeutschlandreiseInputData(JourneyInput().Input());

    return 0;
}
