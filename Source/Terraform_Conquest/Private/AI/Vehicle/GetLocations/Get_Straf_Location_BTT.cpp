// Alex Chatt Terraform_Conquest 2020


#include "AI/Vehicle/GetLocations/Get_Straf_Location_BTT.h"

UGet_Straf_Location_BTT::UGet_Straf_Location_BTT()
{
	bNotifyTick = true;
	NodeName = TEXT("Get Straf Location");
}

EBTNodeResult::Type UGet_Straf_Location_BTT::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	return EBTNodeResult::Type();
}
