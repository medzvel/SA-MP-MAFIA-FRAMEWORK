// This is a comment
// uncomment the line below if you want to write a filterscript
//#define FILTERSCRIPT

#include <a_samp>
#include <crashdetect>
#include <sscanf2>
#include <streamer>
#include <zcmd>
#include <mafia_framework>
#include <mdzvl_funcs>
#define COLOR_BLUE 0x33AAFFFF
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_RED 0xAA3333AA

main()
{
	print("\n----------------------------------");
	print(" Blank Gamemode by your name here");
	print("----------------------------------\n");
}

new MafiaType:LCN, MafiaType:Russian, MafiaType:Yakudza;

public OnGameModeInit()
{
	LCN = DefineMafiaType("La Cosa Nostra");
	Russian = DefineMafiaType("Russian Mafia");
	Yakudza = DefineMafiaType("Yakudza");
	// Don't use these lines if it's a filterscript
	SetGameModeText("Blank Script");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	new temp_GetMafiaName[MAX_MAFIA_NAME];
	GetMafiaName(LCN, temp_GetMafiaName);
	printf("MAFIA NAME IS %s", temp_GetMafiaName);
	//AddTurfForMafia(LCN, -3000, 608, 3000, 3000, COLOR_BLUE);
	LoadTurfsForMafia(LCN, "turfs/LCN.turfs", COLOR_YELLOW);
   	LoadTurfsForMafia(Yakudza, "turfs/Yakudza.turfs", COLOR_RED);
   	LoadTurfsForMafia(Russian, "turfs/Russian.turfs", COLOR_BLUE);

	return 1;
}

CMD:addmafiacar(playerid, params[])
{
	new
	        Float:temp_X,
			Float:temp_Y,
			Float:temp_Z
	;

	GetPlayerPos(playerid, temp_X, temp_Y, temp_Z);
			
    AddMafiaCar(LCN, temp_X, temp_Y, temp_Z, 90.0, COLOR_YELLOW, COLOR_RED);
	return 1;
}

CMD:addmaterials(playerid, params[])
{
    AddMaterialsInMafiaCar(LCN, 60);
    return 1;
}

CMD:addwarehouse(playerid, params[])
{
	new
		 Float:temp_pX,
		 Float:temp_pY,
		 Float:temp_pZ
	;
	GetPlayerPos(playerid, temp_pX, temp_pY, temp_pZ);
	AddMafiaWarehouse(LCN, temp_pX, temp_pY, temp_pZ);
	return 1;
}

CMD:addwarehouse1(playerid, params[])
{
	new
		 Float:temp_pX,
		 Float:temp_pY,
		 Float:temp_pZ
	;
	GetPlayerPos(playerid, temp_pX, temp_pY, temp_pZ);
	AddMafiaWarehouse(Yakudza, temp_pX, temp_pY, temp_pZ);
	return 1;
}

CMD:addwarehouse2(playerid, params[])
{
	new
		 Float:temp_pX,
		 Float:temp_pY,
		 Float:temp_pZ
	;
	GetPlayerPos(playerid, temp_pX, temp_pY, temp_pZ);
	AddMafiaWarehouse(Russian, temp_pX, temp_pY, temp_pZ);
	return 1;
}


CMD:removematsfromwh(playerid, params[])
{
 	RemoveMatsFromMafiaWarehouse(LCN, 35);
 	return 1;
}

CMD:removematerials(playerid, params[])
{
	RemoveMaterialsFromMafiaCar(LCN, 10);
	return 1;
}

CMD:veh(playerid, params[])
{
	new
	    Float:temp_X,
	    Float:temp_Y,
	    Float:temp_Z
	;
	GetPlayerPos(playerid, temp_X, temp_Y, temp_Z);
	CreateVehicle(411, temp_X, temp_Y, temp_Z, 90.0, -1, -1, 1);
	return 1;
}

CMD:takemats(playerid, params[])
{
	new
	        MafiaType:temp_PlayerMafia;
	        
	GetPlayerMafia(playerid, temp_PlayerMafia);

	if(IsPlayerNearMafiaCar(playerid, temp_PlayerMafia))
	{
	    if(PlayerTakeMaterialsFromCar(playerid, 30))
	    	SendClientMessage(playerid, -1, "You took 30 Material From Car");
	    return 1;
	}
	SendClientMessage(playerid, -1, "You are not near your mafia car");
	return 1;
}

CMD:putmats(playerid, params[])
{
	new
	        MafiaType:temp_PlayerMafia;

	GetPlayerMafia(playerid, temp_PlayerMafia);

	if(IsPlayerNearMafiaCar(playerid, temp_PlayerMafia))
	{
	    if(PlayerPutMaterialsInCar(playerid, 30))
	    {
	    	SendClientMessage(playerid, -1, "You putted 30 material in car");
	    	return 1;
	    }
	    else
	    {
			SendClientMessage(playerid, -1, "You can't put 30 material in car");
		}

	}
	else
	{
		SendClientMessage(playerid, -1, "You are not near your mafia car");
	}
	return 1;
}

CMD:amiinmafia(playerid, params[])
{
	if(IsPlayerInAnyMafia(playerid))
	{
	    SendClientMessage(playerid, -1, "Yes You Are");
	}
	else
	{
	    SendClientMessage(playerid, -1, "No You Are Not");
	}
	return 1;
}

CMD:addwarehousemats(playerid, params[])
{
    AddMaterialsInMafiaWarehouse(LCN, 100);
    return 1;
}

public OnPlayerTryEnterMafiaVehicle(playerid, MafiaType:m_id, vehicleid, ERROR_HANDLER)
{
	new
	        temp_MafiaName[MAX_MAFIA_NAME],
			temp_Str[36+MAX_MAFIA_NAME]
	;
	
	GetMafiaName(m_id, temp_MafiaName);

	if(ERROR_HANDLER == ERROR_NOT_SAME_MAFIA)
	{
	    format(temp_Str, sizeof(temp_Str), "You don't have access for using {F91F2F}%s{FFFFFF}-s vehicle!", temp_MafiaName);
	    SendClientMessage(playerid, -1, temp_Str);
	}
	return 1;
}

public OnPlayerDealsWithMaterials(playerid, m_Materials, FROM, ACTION, ERROR_HANDLER)
{
	new temp_Str[64];
	if(ERROR_HANDLER == ERROR_CANT_ADD_THAT_MUCH && FROM == MAFIA_CAR)
	{
	    format(temp_Str, sizeof(temp_Str), "{F91F2F}You can't put %d material in car",m_Materials);
	    SendClientMessage(playerid, -1, temp_Str);
	}
	if(ERROR_HANDLER == ERROR_CANT_TAKE_THAT_MUCH && FROM == MAFIA_CAR)
	{
 		format(temp_Str, sizeof(temp_Str), "{F91F2F}You can't take %d material from car",m_Materials);
	    SendClientMessage(playerid, -1, temp_Str);
	}
	if(ERROR_HANDLER == ERROR_YOU_DONT_HAVE_THAT_MUCH && FROM == MAFIA_CAR)
	{
	    format(temp_Str, sizeof(temp_Str), "{F91F2F}You don't have %d material to put in car",m_Materials);
	    SendClientMessage(playerid, -1, temp_Str);
	}
	if(ERROR_HANDLER == NO_ERROR_SUCCESSED && ACTION == ACTION_PUTTING && FROM == MAFIA_CAR)
	{
	    format(temp_Str, sizeof(temp_Str), "{F91F2F}You succcessfully putted %d material in car",m_Materials);
	    SendClientMessage(playerid, -1, temp_Str);
	}
	if(ERROR_HANDLER == NO_ERROR_SUCCESSED && ACTION == ACTION_TAKING && FROM == MAFIA_CAR)
	{
	    format(temp_Str, sizeof(temp_Str), "{F91F2F}You successfully took %d material from car",m_Materials);
		SendClientMessage(playerid, -1, temp_Str);
	}
	if(ERROR_HANDLER == ERROR_CANT_ADD_THAT_MUCH && FROM == MAFIA_WAREHOUSE)
	{
	    format(temp_Str, sizeof(temp_Str), "{F91F2F}You can't put %d material in warehouse",m_Materials);
	    SendClientMessage(playerid, -1, temp_Str);
	}
	if(ERROR_HANDLER == ERROR_CANT_TAKE_THAT_MUCH && FROM == MAFIA_WAREHOUSE)
	{
 		format(temp_Str, sizeof(temp_Str), "{F91F2F}You can't take %d material from warehouse",m_Materials);
	    SendClientMessage(playerid, -1, temp_Str);
	}
	if(ERROR_HANDLER == ERROR_YOU_DONT_HAVE_THAT_MUCH && FROM == MAFIA_WAREHOUSE)
	{
	    format(temp_Str, sizeof(temp_Str), "{F91F2F}You don't have %d material to put in warehouse",m_Materials);
	    SendClientMessage(playerid, -1, temp_Str);
	}
	if(ERROR_HANDLER == NO_ERROR_SUCCESSED && ACTION == ACTION_PUTTING && FROM == MAFIA_WAREHOUSE)
	{
	    format(temp_Str, sizeof(temp_Str), "{F91F2F}You succcessfully putted %d material in warehouse",m_Materials);
	    SendClientMessage(playerid, -1, temp_Str);
	}
	if(ERROR_HANDLER == NO_ERROR_SUCCESSED && ACTION == ACTION_TAKING && FROM == MAFIA_WAREHOUSE)
	{
	    format(temp_Str, sizeof(temp_Str), "{F91F2F}You successfully took %d material from warehouse",m_Materials);
		SendClientMessage(playerid, -1, temp_Str);
	}
	return 1;
}

public OnPlayerEnterMafiaWarehouseCP(playerid, MafiaType:m_id)
{
	new
	    temp_MafiaName[MAX_MAFIA_NAME],
	    temp_Str[41+MAX_MAFIA_NAME]
	;

	GetMafiaName(m_id, temp_MafiaName);
	format(temp_Str, sizeof(temp_Str), "You entered in {F91F2F}%s{FFFFFF}-s Warehouse Checkpoint", temp_MafiaName);
	SendClientMessage(playerid, -1, temp_Str);
	return 1;
}

CMD:aminearwh(playerid, params[])
{
    if(IsPlayerNearMafiaWarehouse(playerid, LCN))
    {
        SendClientMessage(playerid, -1, "Yes you are !");
		return 1;
	}
	SendClientMessage(playerid, -1, "No you are not");
	return 1;
}

CMD:mymats(playerid, params[])
{
	new
	        temp_Str[32],
	        temp_PlayerMaterials
	;

	GetPlayerMaterials(playerid, temp_PlayerMaterials);

	format(temp_Str, sizeof(temp_Str), "You have %d Materials",temp_PlayerMaterials);
	SendClientMessage(playerid, -1, temp_Str);
	return 1;
}

CMD:mchat(playerid, params[])
{
	new
	    MafiaType:temp_MafiaID
	;
	if(GetPlayerMafia(playerid, temp_MafiaID))
	{
    	SendMafiaMessage(temp_MafiaID, "Test Message To The Mafia Members");
    	return 1;
	}
	SendClientMessage(playerid, -1, "You are not member of any mafia");
    return 1;
}

CMD:getmelcn(playerid, params[])
{
	SendClientMessage(playerid, -1, "You are member of LCN From now");
	SetPlayerMafia(playerid, LCN);
	return 1;
}

CMD:cani(playerid, params[])
{
	if(PlayerHavePermissionsInTurf(playerid))
	{
	    SendClientMessage(playerid, -1, "You have permissions here");
		return 1;
	}
	SendClientMessage(playerid, -1, "You don't have permissions here");
	return 1;
}

CMD:iminturf(playerid, params[])
{
    if(IsPlayerInMafiaTurf(playerid, LCN))
    {
        SendClientMessage(playerid, -1, "You are in turf of LCN Mafia");
		return 1;
	}
	SendClientMessage(playerid, -1, "NO YOU ARE NOT");
	return 1;
}

CMD:ownerturf(playerid, params[])
{
	new
		MafiaType:temp_mafiaID,
		temp_MafiaName[MAX_MAFIA_NAME],
		temp_Str[64]
	;
	
	if(GetMafiaIDFroPlayerPosInTurf(playerid, temp_mafiaID))
	{
		GetMafiaName(temp_mafiaID, temp_MafiaName);
	}
	else
	{
	    SendClientMessage(playerid, -1, "You are not in any zone");
	    return 1;
	}
	format(temp_Str, sizeof(temp_Str), "You are in zone of %s", temp_MafiaName);
	SendClientMessage(playerid, -1, temp_Str);
	return 1;
}
	


public OnGameModeExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerConnect(playerid)
{
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnPlayerSpawn(playerid)
{
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/mycommand", cmdtext, true, 10) == 0)
	{
		// Do something here
		return 1;
	}
	return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	return 1;
}



public OnRconLoginAttempt(ip[], password[], success)
{
	if(success)
		SendClientMessage(GetPlayerIDFromIP(ip), -1, "You are logged in as admin");
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}
