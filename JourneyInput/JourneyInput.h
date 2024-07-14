#pragma once
#include <vector>
class DeutschlandreiseInputData;
class NodeData;

class JourneyInput
{
public:
    DeutschlandreiseInputData Input (const std::vector<NodeData*> nodeData) const;
};