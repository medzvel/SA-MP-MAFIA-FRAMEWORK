# SA-MP Mafia Framework 


This framework helps you to make your custom mafia system in your gamemode easily.

## Functions
```c
	native MafiaType:DefineMafiaType(maf_Name[]);
	native AddTurfForMafia(MafiaType:m_id, Float:m_t_minX, Float:m_t_minY, Float:m_t_maxX, Float:m_t_maxY, color);
	native IsPlayerInMafiaTurf(playerid, MafiaType:m_id);
	native GetMafiaIDFroPlayerPosInTurf(playerid, &MafiaType:m_id);
	native LoadTurfsForMafia(MafiaType:m_id, filename[], mTurf_color);
	native GetMafiaName(MafiaType:m_id, output[], len = sizeof(output));
	native SetPlayerMafia(playerid, MafiaType:m_id);
	native SetPlayerAsMafiaLeader(playerid, MafiaType:m_id);
	native IsPlayerMafiaLeader(playerid);
	native GetPlayerMafia(playerid, &MafiaType:m_id);
	native bool:IsPlayerInAnyMafia(playerid);
	native bool:PlayerHavePermissionsInTurf(playerid);
	//
	native SetPlayerMaterials(playerid, m_Materials);
	native GivePlayerMaterials(playerid, m_Materials);
	native RemovePlayerMaterials(playerid, m_Materials);
	native GetPlayerMaterials(playerid, &m_Materials);
	native PlayerTakeMaterialsFromCar(playerid, m_Materials);
	native PlayerPutMaterialsInCar(playerid, m_Materials);
	native IsPlayerNearMafiaCar(playerid, MafiaType:m_id);
	//
	native SendMafiaMessage(MafiaType:m_id, const mafia_Text[])
	//
	native AddMafiaCar(MafiaType:m_id, Float:mc_posX, Float:mc_posY, Float:mc_posZ, Float:mc_rotation, mc_color1, mc_color2);
	native SetMaterialsInMafiaCar(MafiaType:m_id, m_Materials);
	native GetMafiaCarID(MafiaType:m_id, &mc_ID);
	native AddMaterialsInMafiaCar(MafiaType:m_id, m_Materials);
	native RemoveMaterialsFromMafiaCar(MafiaType:m_id, m_Materials);
	native GetMafiaMaterialsInMafiaCar(MafiaType:m_id, &m_Materials);
	//
	native AddMafiaWarehouse(MafiaType:m_id, Float:m_w_posX, Float:m_w_posY, Float:m_w_posZ, m_w_virtualWorld = -1, m_w_interiorID = -1);
	native AddMaterialsInMafiaWarehouse(MafiaType:m_id, m_Materials);
	native RemoveMatsFromMafiaWarehouse(MafiaType:m_id, m_Materials);
	native SetMafiaWarehouseMaterials(MafiaType:m_id, m_Materials);
	native GetMafiaWarehouseMaterials(MafiaType:m_id, &m_Materials);
	native PlayerTakeMaterialsFromWarehous(playerid, m_Materials);
	native PlayerPutMaterialsInWarehouse(playerid, m_Materials);
	native bool:IsPlayerNearMafiaWarehouse(playerid, MafiaType:m_id);
```
## Callbacks
```c
	forward OnPlayerDealsWithMaterials(playerid, m_Materials, FROM, ACTION, ERROR_HANDLER);
	forward OnPlayerTryEnterMafiaVehicle(playerid, MafiaType:m_id, vehicleid, ERROR_HANDLER);
	forward OnPlayerEnterMafiaWarehouseCP(playerid, MafiaType:m_id);
```	


## License

MIT

## Credits
Medzvel - Whole include development.

Pufty - For his investition and Inspiration

