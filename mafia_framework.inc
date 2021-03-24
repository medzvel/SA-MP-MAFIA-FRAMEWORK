
#if !defined _streamer_included
	#error Include Streamer Plugin Before Using mafia_framework.inc
#endif

#if !defined CRASHDETECT_INC
	#error Include Crashdetect Plugin Before Using mafia_framework.inc
#endif	

#if !defined sscanf
	#error Include sscanf Plugin Before Using mafia_framework.inc
#endif	

/*
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
	//
	forward OnPlayerDealsWithMaterials(playerid, m_Materials, FROM, ACTION, ERROR_HANDLER);
	forward OnPlayerTryEnterMafiaVehicle(playerid, MafiaType:m_id, vehicleid, ERROR_HANDLER);
	forward OnPlayerEnterMafiaWarehouseCP(playerid, MafiaType:m_id);
*/

//MAFIA DEFINES
#define MAX_MAFIA MafiaType:10
#define MAX_MAFIA_NAME 64
#define INVALID_MAFIA_ID MafiaType:-1

//MAFIA TURF DEFINES
#define MAX_MAFIA_TURF 64
#define INVALID_MAFIA_TURF_ID -1

//MAFIA VEHICLE DEFINES
#define MAFIA_VEHICLE 560
#define MAFIA_MAX_VEHICLE_MATERIALS 100

//MAFIA WAREHOUSE DEFINES
#define MAFIA_WAREHOUSE_MAX_MATERIALS 1000

//CALLBACKS HANDLER
#define ERROR_CANT_ADD_THAT_MUCH 1
#define ERROR_CANT_TAKE_THAT_MUCH 2
#define ERROR_YOU_DONT_HAVE_THAT_MUCH 3
#define NO_ERROR_SUCCESSED 4
#define ACTION_PUTTING 5
#define ACTION_TAKING 6
#define MAFIA_CAR 7
#define MAFIA_WAREHOUSE 8
//VEHICLE CALLBACK HANDLER
#define ERROR_NOT_SAME_MAFIA 1

#if defined OnPlayerDealsWithMaterials
	forward OnPlayerDealsWithMaterials(playerid, m_Materials, FROM, ACTION, ERROR_HANDLER);
#endif	

#if defined OnPlayerTryEnterMafiaVehicle
	forward OnPlayerTryEnterMafiaVehicle(playerid, MafiaType:m_id, vehicleid, ERROR_HANDLER);
#endif	

#if defined OnPlayerEnterMafiaWarehouseCP
	forward OnPlayerEnterMafiaWarehouseCP(playerid, MafiaType:m_id);
#endif	

static 
		mafia_Name[MAX_MAFIA][MAX_MAFIA_NAME],
		// TURF VARIABLE
		mafia_Turf[MAX_MAFIA_TURF][MAX_MAFIA],
		//FOR SAVING MAFIA TURF COORDS
	Float:mafia_Turf_maxX[MAX_MAFIA_TURF][MAX_MAFIA],
	Float:mafia_Turf_maxY[MAX_MAFIA_TURF][MAX_MAFIA],
	Float:mafia_Turf_minX[MAX_MAFIA_TURF][MAX_MAFIA],
	Float:mafia_Turf_minY[MAX_MAFIA_TURF][MAX_MAFIA],

		mafia_Turf_Color[MAX_MAFIA_TURF][MAX_MAFIA],
		mafia_TurfCreated[MAX_MAFIA]
;
	



static MafiaType:mafia_TypesCreated = MafiaType:0;


/* PLAYER SIDE VARIABLES */
static 
		MafiaType:Player_Mafia[MAX_PLAYERS] = INVALID_MAFIA_ID,
		MafiaType:Player_MafiaLeader[MAX_PLAYERS] = INVALID_MAFIA_ID,
				  Player_Materials[MAX_PLAYERS] = 0
;	
//

/* MAFIA WAREHOUSE */

static 
		Mafia_Warehouse[MAX_MAFIA],
		Float:Mafia_Warehouse_posX[MAX_MAFIA],
		Float:Mafia_Warehouse_posY[MAX_MAFIA],
		Float:Mafia_Warehouse_posZ[MAX_MAFIA],
		Text3D:Mafia_Warehouse_Label[MAX_MAFIA],
		Mafia_Warehouse_Materials[MAX_MAFIA] = 0
;		

/* MAFIA CARS */
static 
		Mafia_Car[MAX_MAFIA] = -1,
	Text3D:Mafia_CarLabel[MAX_MAFIA],
		Mafia_CarMaterials[MAX_MAFIA] = 0
;		

stock MafiaType:DefineMafiaType(maf_Name[])
{
	format(mafia_Name[mafia_TypesCreated], MAX_MAFIA_NAME, "%s", maf_Name);
	return mafia_TypesCreated++;
}


stock AddTurfForMafia(MafiaType:m_id, Float:m_t_minX, Float:m_t_minY, Float:m_t_maxX, Float:m_t_maxY, color)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: AddTurfForMafia | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}

	mafia_Turf_maxX[mafia_TurfCreated[m_id]][m_id] = m_t_maxX;
	mafia_Turf_maxY[mafia_TurfCreated[m_id]][m_id] = m_t_maxY;
	mafia_Turf_minX[mafia_TurfCreated[m_id]][m_id] = m_t_minX;
	mafia_Turf_minY[mafia_TurfCreated[m_id]][m_id] = m_t_minY;
	
	mafia_Turf_Color[mafia_TurfCreated[m_id]][m_id] = color;

	mafia_Turf[mafia_TurfCreated[m_id]][m_id] = GangZoneCreate(m_t_minX, m_t_minY, m_t_maxX, m_t_maxY);

	return mafia_TurfCreated[m_id]++;
}

/*stock GetMafiaTurfPositions(MafiaType:m_id, &Float:m_t_maxX, &Float:m_t_maxY, &Float:m_t_minX, &Float:min_t_minY)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: GetMafiaTurfPositions | Invalid Mafia ID!");
		return false;
	}
	m_t_maxX = mafia_Turf_maxX[mafia_TurfCreated[m_id]][m_id];
	m_t_maxY = mafia_Turf_maxY[mafia_TurfCreated[m_id]][m_id];
	m_t_minX = mafia_Turf_minX[mafia_TurfCreated[m_id]][m_id];
	m_t_minY = mafia_Turf_minY[mafia_TurfCreated[m_id]][m_id];
	return 1;
}*/

stock IsPlayerInMafiaTurf(playerid, MafiaType:m_id)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: IsPlayerInMafiaTurf | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}

	new
		Float:temp_pX,
		Float:temp_pY,
		Float:temp_pZ
	;

	GetPlayerPos(playerid, temp_pX, temp_pY, temp_pZ);
	for(new i; i<mafia_TurfCreated[m_id]; i++)
	{
		if (temp_pX >= mafia_Turf_minX[i][m_id] && temp_pX <= mafia_Turf_maxX[i][m_id] && temp_pY >= mafia_Turf_minY[i][m_id] && temp_pY <= mafia_Turf_maxY[i][m_id])
		{
			return true;
		}
	}
	return false;
}

stock GetMafiaIDFroPlayerPosInTurf(playerid, &MafiaType:m_id)
{
	new 
		Float:temp_pX,
		Float:temp_pY,
		Float:temp_pZ
	;

	GetPlayerPos(playerid, temp_pX, temp_pY, temp_pZ);
	for(new MafiaType:i; i<mafia_TypesCreated; i++)
	{
		for(new t_i; t_i<mafia_TurfCreated[i]; t_i++)
		{
			if(temp_pX >= mafia_Turf_minX[t_i][i] && temp_pX <= mafia_Turf_maxX[t_i][i] && temp_pY >= mafia_Turf_minY[t_i][i] && temp_pY <= mafia_Turf_maxY[t_i][i])
			{
				m_id = i;
				return 1;
			}
		}
	}
	return 0;
}

stock LoadTurfsForMafia(MafiaType:m_id, filename[], mTurf_color)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: LoadTurfsForMafia | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}

	new
		File:file,
		line[256],
		linenumber = 1,
		count,

		funcname[32],
		funcargs[128],

		Float:temp_m_minX,
		Float:temp_m_minY,
		Float:temp_m_maxX,
		Float:temp_m_maxY,
		temp_mafia_name[MAX_MAFIA_NAME];

	if(!fexist(filename))
	{
		printf("[MAFIA FRAMEWORK ERROR] file: \"%s\" NOT FOUND", filename);
		return 0;
	}

	file = fopen(filename, io_read);

	if(!file)
	{
		printf("[MAFIA FRAMEWORK ERROR] \"%s\" NOT LOADED", filename);
		return 0;
	}

	while(fread(file, line))
	{
		if(line[0] < 65)
		{
			linenumber++;
			continue;
		}

		if(sscanf(line, "p<(>s[32]p<)>s[128]{s[96]}", funcname, funcargs))
		{
			linenumber++;
			continue;
		}

		if(!strcmp(funcname, "TurfPositions"))
		{
			if(sscanf(funcargs, "p<,>ffff", temp_m_minX, temp_m_minY, temp_m_maxX, temp_m_maxY))
			{
				printf("[MAFIA FRAMEWORK ERROR] [LOADING] Malformed parameters on line %d", linenumber);
				linenumber++;
				continue;
			}
			count++;
			linenumber++;
			AddTurfForMafia(m_id, temp_m_minX, temp_m_minY, temp_m_maxX, temp_m_maxY, mTurf_color);
		}
	}
	GetMafiaName(m_id, temp_mafia_name);
	printf("[MAFIA FRAMEWORK] Loaded [%d] Turfs - From File '%s'.  Turfs For Mafia: [%s] .", count, filename, temp_mafia_name);

	return 1;
}


stock GetMafiaName(MafiaType:m_id, output[], len = sizeof(output))
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: GetMafiaName | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	format(output, len, "%s", mafia_Name[m_id]);
	return 1;
}


stock SetPlayerMafia(playerid, MafiaType:m_id)
{
	if(!IsPlayerConnected(playerid)) return false;
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: SetPlayerMafia | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	Player_Mafia[playerid] = m_id;
	return true;
}

stock SetPlayerAsMafiaLeader(playerid, MafiaType:m_id)
{
	if(!IsPlayerConnected(playerid)) return false;
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: SetPlayerAsMafiaLeader | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	Player_MafiaLeader[playerid] = m_id;
	return true;
}

stock IsPlayerMafiaLeader(playerid)
{
	if(!IsPlayerConnected(playerid)) return false;
	if(Player_MafiaLeader[playerid] == INVALID_MAFIA_ID) return false;
	return true;
}

stock GetPlayerMafia(playerid, &MafiaType:m_id)
{
	if(!IsPlayerConnected(playerid)) return false;
	if(Player_Mafia[playerid] == INVALID_MAFIA_ID && Player_MafiaLeader[playerid] == INVALID_MAFIA_ID)
		return 0;
	if(IsPlayerMafiaLeader(playerid))
	{
		m_id = Player_MafiaLeader[playerid];
		return true;
	}
	m_id = Player_Mafia[playerid];
	return true;
}

stock bool:IsPlayerInAnyMafia(playerid)
{
	if(!IsPlayerConnected(playerid)) return false;
	if(Player_Mafia[playerid] == INVALID_MAFIA_ID && Player_MafiaLeader[playerid] == INVALID_MAFIA_ID)
		return false;
	return true;
}

stock bool:PlayerHavePermissionsInTurf(playerid)
{
	if(!IsPlayerConnected(playerid)) return false;
	new
		MafiaType:temp_mID,
		MafiaType:temp_pmID
	;
	if(GetMafiaIDFroPlayerPosInTurf(playerid, temp_mID))
	{
		if(GetPlayerMafia(playerid, temp_pmID))
		{
			if(temp_mID == temp_pmID) return true;
		}
	}
	return false;
}
/* PLAYER MATERIALS FUNCTIONS */

stock SetPlayerMaterials(playerid, m_Materials)
{
	if(!IsPlayerConnected(playerid)) return false;

	Player_Materials[playerid] = m_Materials;
	return true;
}

stock GivePlayerMaterials(playerid, m_Materials)
{
	if(!IsPlayerConnected(playerid)) return false;

	Player_Materials[playerid] += m_Materials;
	return true;
}

stock RemovePlayerMaterials(playerid, m_Materials)
{
	if(!IsPlayerConnected(playerid)) return false;

	Player_Materials[playerid] -= m_Materials;
	return true;
}

stock GetPlayerMaterials(playerid, &m_Materials)
{
	if(!IsPlayerConnected(playerid)) return false;

	m_Materials = Player_Materials[playerid];
	return true;
}

stock PlayerTakeMaterialsFromCar(playerid, m_Materials)
{
	if(!IsPlayerConnected(playerid)) return false;

	new MafiaType:temp_mafiaID, temp_MafiaCarMaterials;

	if(GetPlayerMafia(playerid, temp_mafiaID))
	{
		GetMafiaMaterialsInMafiaCar(temp_mafiaID, temp_MafiaCarMaterials);
		if(temp_MafiaCarMaterials - m_Materials < 0) 
		{
			#if defined OnPlayerDealsWithMaterials
				CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_CAR, ACTION_TAKING, ERROR_CANT_TAKE_THAT_MUCH);
			#endif	
			return false;
		}	
		RemoveMaterialsFromMafiaCar(temp_mafiaID, m_Materials);
		GivePlayerMaterials(playerid, m_Materials);
		#if defined OnPlayerDealsWithMaterials
			CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_CAR, ACTION_TAKING, NO_ERROR_SUCCESSED);
		#endif	
		return true;
	}
	return false;
}

stock PlayerPutMaterialsInCar(playerid, m_Materials)
{
	if(!IsPlayerConnected(playerid)) return false;

	new MafiaType:temp_mafiaID, temp_MafiaCarMaterials, temp_PlayerMaterials;

	if(GetPlayerMafia(playerid, temp_mafiaID))
	{
		GetPlayerMaterials(playerid, temp_PlayerMaterials);
		if(temp_PlayerMaterials < m_Materials) 
		{
			#if defined OnPlayerDealsWithMaterials
				CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_CAR, ACTION_PUTTING, ERROR_YOU_DONT_HAVE_THAT_MUCH);
			#endif	
			return false;
		}
		GetMafiaMaterialsInMafiaCar(temp_mafiaID, temp_MafiaCarMaterials);
		if(temp_MafiaCarMaterials + m_Materials > MAFIA_MAX_VEHICLE_MATERIALS)
		{
			#if defined OnPlayerDealsWithMaterials
				CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_CAR, ACTION_PUTTING, ERROR_CANT_ADD_THAT_MUCH);
			#endif	
			return false;
		}
		#if defined OnPlayerDealsWithMaterials
			CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_CAR, ACTION_PUTTING, NO_ERROR_SUCCESSED);
		#endif	
		AddMaterialsInMafiaCar(temp_mafiaID, m_Materials);
		RemovePlayerMaterials(playerid, m_Materials);
		return true;
	}
	return false;
}

stock IsPlayerNearMafiaCar(playerid, MafiaType:m_id)
{
	if(!IsPlayerConnected(playerid)) return false;
	new
		Float:temp_vpX,
		Float:temp_vpY,
		Float:temp_vpZ
	;

	GetVehiclePos(Mafia_Car[m_id], temp_vpX, temp_vpY, temp_vpZ);

	if(IsPlayerInRangeOfPoint(playerid, 5.0, temp_vpX, temp_vpY, temp_vpZ))
	{
		return true;
	}
	return false;
}

/* PLAYER CHATS */
stock SendMafiaMessage(MafiaType:m_id, const mafia_Text[])
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: SendMafiaMessage | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	new temp_PlayerName[MAX_PLAYER_NAME], temp_Str[128+MAX_PLAYER_NAME];

	for(new i;i<MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(Player_Mafia[i] == m_id || Player_MafiaLeader[i] == m_id)
			{
				GetPlayerName(i, temp_PlayerName, MAX_PLAYER_NAME);
				format(temp_Str, sizeof(temp_Str), "%s sad: %s", temp_PlayerName, mafia_Text);
				SendClientMessage(i, -1, temp_Str);
			}
		}	
	}
	return true;	
}


/* MAFIA VEHICLE */

stock AddMafiaCar(MafiaType:m_id, Float:mc_posX, Float:mc_posY, Float:mc_posZ, Float:mc_rotation, mc_color1, mc_color2)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: AddMafiaCar | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	new 
		temp_Str[32+MAX_MAFIA_NAME],
		temp_MafiaName[MAX_MAFIA_NAME]
	;
	GetMafiaName(m_id, temp_MafiaName);
	format(temp_Str, sizeof(temp_Str), "[%s]\nMaterials - %d/"#MAFIA_MAX_VEHICLE_MATERIALS"", temp_MafiaName, Mafia_CarMaterials[m_id]);
	Mafia_Car[m_id] = CreateVehicle(MAFIA_VEHICLE, mc_posX, mc_posY, mc_posZ, mc_rotation, mc_color1, mc_color2, 660);
	Mafia_CarLabel[m_id] = CreateDynamic3DTextLabel(temp_Str, 0xAA3333AA, mc_posX, mc_posY, mc_posZ, 5.0, .attachedvehicle = Mafia_Car[m_id]);
	return true;
}

stock SetMaterialsInMafiaCar(MafiaType:m_id, m_Materials)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: SetMaterialsInMafiaCar | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	if(m_Materials > MAFIA_MAX_VEHICLE_MATERIALS)
	{
		print("[MAFIA FRAMEWORK] ERROR: SetMaterialsInMafiaCar | Can't Add That Much Materials!");
		PrintAmxBacktrace();
		return false;
	}

	new 
		temp_Str[32+MAX_MAFIA_NAME],
		temp_MafiaName[MAX_MAFIA_NAME]
	;

	Mafia_CarMaterials[m_id] = m_Materials;

	GetMafiaName(m_id, temp_MafiaName);

	format(temp_Str, sizeof(temp_Str), "[%s]\nMaterials - %d/"#MAFIA_MAX_VEHICLE_MATERIALS"", temp_MafiaName, Mafia_CarMaterials[m_id]);
	UpdateDynamic3DTextLabelText(Mafia_CarLabel[m_id], 0xAA3333AA,  temp_Str);
	return true;
}

stock GetMafiaCarID(MafiaType:m_id, &mc_ID)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: GetMafiaCarID | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	if(Mafia_Car[m_id] == -1)
	{
		print("[MAFIA FRAMEWORK] ERROR: GetMafiaCarID | Mafia Car ID Equals To -1!");
		PrintAmxBacktrace();
		return false;
	}
	mc_id = Mafia_Car[m_id];
	return true;
}

stock AddMaterialsInMafiaCar(MafiaType:m_id, m_Materials)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: AddMaterialsInMafiaCar | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	if(Mafia_CarMaterials[m_id]+m_Materials > MAFIA_MAX_VEHICLE_MATERIALS)
	{
		print("[MAFIA FRAMEWORK] ERROR: AddMaterialsInMafiaCar | Can't Add More Materials!");
		PrintAmxBacktrace();
		return false;
	}

	new 
		temp_Str[32+MAX_MAFIA_NAME],
		temp_MafiaName[MAX_MAFIA_NAME]
	;

	Mafia_CarMaterials[m_id] += m_Materials;

	GetMafiaName(m_id, temp_MafiaName);

	format(temp_Str, sizeof(temp_Str), "[%s]\nMaterials - %d/"#MAFIA_MAX_VEHICLE_MATERIALS"", temp_MafiaName, Mafia_CarMaterials[m_id]);
	UpdateDynamic3DTextLabelText(Mafia_CarLabel[m_id], 0xAA3333AA,  temp_Str);
	
	return true;
}

stock RemoveMaterialsFromMafiaCar(MafiaType:m_id, m_Materials)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: RemoveMaterialsFromMafiaCar | Invalid Mafia ID!");
		return false;
	}
	if(Mafia_CarMaterials[m_id]-m_Materials < 0)
	{
		print("[MAFIA FRAMEWORK] ERROR: RemoveMaterialsFromMafiaCar | Can't Take That Much Materials From Car!");
		return false;
	}

	new 
		temp_Str[32+MAX_MAFIA_NAME],
		temp_MafiaName[MAX_MAFIA_NAME]
	;

	Mafia_CarMaterials[m_id] -= m_Materials;

	GetMafiaName(m_id, temp_MafiaName);

	format(temp_Str, sizeof(temp_Str), "[%s]\nMaterials - %d/"#MAFIA_MAX_VEHICLE_MATERIALS"", temp_MafiaName, Mafia_CarMaterials[m_id]);
	UpdateDynamic3DTextLabelText(Mafia_CarLabel[m_id], 0xAA3333AA,  temp_Str);

	return true;
}

stock GetMafiaMaterialsInMafiaCar(MafiaType:m_id, &m_Materials)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: GetMafiaMaterialsInMafiaCar | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	
	m_Materials = Mafia_CarMaterials[m_id];
	return true;
}


/* MAFIA WAREHOUSE */
stock AddMafiaWarehouse(MafiaType:m_id, Float:m_w_posX, Float:m_w_posY, Float:m_w_posZ, m_w_virtualWorld = -1, m_w_interiorID = -1)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: AddMafiaWarehouse | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	new 
		temp_Str[41+MAX_MAFIA_NAME],
		temp_MafiaName[MAX_MAFIA_NAME]
	;
	GetMafiaName(m_id, temp_MafiaName);

	Mafia_Warehouse_posX[m_id] = m_w_posX;
	Mafia_Warehouse_posY[m_id] = m_w_posY;
	Mafia_Warehouse_posZ[m_id] = m_w_posZ;

	Mafia_Warehouse[m_id] = CreateDynamicCP(m_w_posX, m_w_posY, m_w_posZ, 2.0, m_w_virtualWorld, m_w_interiorID, .streamdistance = 5.0);

	format(temp_Str, sizeof(temp_Str), "[%s] Warehouse\nMaterials - %d/"#MAFIA_WAREHOUSE_MAX_MATERIALS"", temp_MafiaName, Mafia_Warehouse_Materials[m_id]);
	Mafia_Warehouse_Label[m_id] = CreateDynamic3DTextLabel(temp_Str, 0xFFFF00AA, m_w_posX, m_w_posY, m_w_posZ, 5.0, .worldid = m_w_virtualWorld, .interiorid = m_w_interiorID);
	return true;
}


stock AddMaterialsInMafiaWarehouse(MafiaType:m_id, m_Materials)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: AddMaterialsInMafiaWarehouse | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	if(Mafia_Warehouse_Materials[m_id] + m_Materials > MAFIA_WAREHOUSE_MAX_MATERIALS)
	{
		print("[MAFIA FRAMEWORK] ERROR: AddMaterialsInMafiaWarehouse | Can't add that much materials!");
		PrintAmxBacktrace();
		return false;
	}
	
	new 
		temp_Str[41+MAX_MAFIA_NAME],
		temp_MafiaName[MAX_MAFIA_NAME]
	;
	GetMafiaName(m_id, temp_MafiaName);

	Mafia_Warehouse_Materials[m_id] += m_Materials;

	format(temp_Str, sizeof(temp_Str), "[%s] Warehouse\nMaterials - %d/"#MAFIA_WAREHOUSE_MAX_MATERIALS"", temp_MafiaName, Mafia_Warehouse_Materials[m_id]);
	UpdateDynamic3DTextLabelText(Mafia_Warehouse_Label[m_id], 0xFFFF00AA, temp_Str);
	
	return true;
}


stock RemoveMatsFromMafiaWarehouse(MafiaType:m_id, m_Materials)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: RemoveMaterialsFromMafiaWarehouse | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	if(Mafia_Warehouse_Materials[m_id] - m_Materials < 0)
	{
		print("[MAFIA FRAMEWORK] ERROR: RemoveMaterialsFromMafiaWarehouse | Can't remove that much materials!");
		PrintAmxBacktrace();
		return false;
	}
	
	new 
		temp_Str[41+MAX_MAFIA_NAME],
		temp_MafiaName[MAX_MAFIA_NAME]
	;
	GetMafiaName(m_id, temp_MafiaName);

	Mafia_Warehouse_Materials[m_id] -= m_Materials;

	format(temp_Str, sizeof(temp_Str), "[%s] Warehouse\nMaterials - %d/"#MAFIA_WAREHOUSE_MAX_MATERIALS"", temp_MafiaName, Mafia_Warehouse_Materials[m_id]);
	UpdateDynamic3DTextLabelText(Mafia_Warehouse_Label[m_id], 0xFFFF00AA, temp_Str);
	
	return true;
}


stock SetMafiaWarehouseMaterials(MafiaType:m_id, m_Materials)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: SetMafiaWarehouseMaterials | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	if(m_Materials > MAFIA_WAREHOUSE_MAX_MATERIALS)
	{
		print("[MAFIA FRAMEWORK] ERROR: SetMafiaWarehouseMaterials | Can't set that much materials!");
		PrintAmxBacktrace();
		return false;
	}
	
	new 
		temp_Str[41+MAX_MAFIA_NAME],
		temp_MafiaName[MAX_MAFIA_NAME]
	;
	GetMafiaName(m_id, temp_MafiaName);

	Mafia_Warehouse_Materials[m_id] = m_Materials;

	format(temp_Str, sizeof(temp_Str), "[%s] Warehouse\nMaterials - %d/"#MAFIA_WAREHOUSE_MAX_MATERIALS"", temp_MafiaName, Mafia_Warehouse_Materials[m_id]);
	UpdateDynamic3DTextLabelText(Mafia_Warehouse_Label[m_id], 0xFFFF00AA, temp_Str);
	
	return true;
}


stock GetMafiaWarehouseMaterials(MafiaType:m_id, &m_Materials)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: GetMafiaWarehouseMaterials | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}
	
	m_Materials = Mafia_Warehouse_Materials[m_id];
	return true;
}


stock PlayerTakeMaterialsFromWarehous(playerid, m_Materials)
{
	if(!IsPlayerConnected(playerid)) return false;

	new MafiaType:temp_mafiaID, temp_mafiaWHMaterials;

	if(GetPlayerMafia(playerid, temp_mafiaID))
	{
		GetMafiaWarehouseMaterials(temp_mafiaID, temp_mafiaWHMaterials);
		if(temp_mafiaWHMaterials - m_Materials < 0) 
		{
			#if defined OnPlayerDealsWithMaterials
				CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_WAREHOUSE, ACTION_TAKING, ERROR_CANT_TAKE_THAT_MUCH);
			#endif	
			return false;
		}	
		RemoveMatsFromMafiaWarehouse(temp_mafiaID, m_Materials);
		GivePlayerMaterials(playerid, m_Materials);
		#if defined OnPlayerDealsWithMaterials
			CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_WAREHOUSE, ACTION_TAKING, NO_ERROR_SUCCESSED);
		#endif	
		return true;
	}
	return false;
}

stock PlayerPutMaterialsInWarehouse(playerid, m_Materials)
{
	if(!IsPlayerConnected(playerid)) return false;

	new MafiaType:temp_mafiaID, temp_mafiaWHMaterials, temp_PlayerMaterials;

	if(GetPlayerMafia(playerid, temp_mafiaID))
	{
		GetPlayerMaterials(playerid, temp_PlayerMaterials);
		if(temp_PlayerMaterials < m_Materials) 
		{
			#if defined OnPlayerDealsWithMaterials
				CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_WAREHOUSE, ACTION_PUTTING, ERROR_YOU_DONT_HAVE_THAT_MUCH);
			#endif	
			return false;
		}
		GetMafiaMaterialsInMafiaCar(temp_mafiaID, temp_mafiaWHMaterials);
		if(temp_mafiaWHMaterials + m_Materials > MAFIA_WAREHOUSE_MAX_MATERIALS)
		{
			#if defined OnPlayerDealsWithMaterials
				CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_WAREHOUSE, ACTION_PUTTING, ERROR_CANT_ADD_THAT_MUCH);
			#endif	
			return false;
		}
		#if defined OnPlayerDealsWithMaterials
			CallLocalFunction("OnPlayerDealsWithMaterials", "ddddd", playerid, m_Materials, MAFIA_WAREHOUSE, ACTION_PUTTING, NO_ERROR_SUCCESSED);
		#endif	
		AddMaterialsInMafiaWarehouse(temp_mafiaID, m_Materials);
		RemovePlayerMaterials(playerid, m_Materials);
		return true;
	}
	return false;
}

stock bool:IsPlayerNearMafiaWarehouse(playerid, MafiaType:m_id)
{
	if(m_id == INVALID_MAFIA_ID)
	{
		print("[MAFIA FRAMEWORK] ERROR: IsPlayerNearMafiaWarehouse | Invalid Mafia ID!");
		PrintAmxBacktrace();
		return false;
	}	
	new
		Float:temp_pX,
		Float:temp_pY,
		Float:temp_pZ
	;
	GetPlayerPos(playerid, temp_pX, temp_pY, temp_pZ);

	if(IsPlayerInRangeOfPoint(playerid, 2.0, Mafia_Warehouse_posX[m_id], Mafia_Warehouse_posY[m_id], Mafia_Warehouse_posZ[m_id]))
	{
		return true;
	}	
	return false;
}


/* HOOKED CALLBACKS */
public OnPlayerSpawn(playerid)
{
	for(new MafiaType:m_i = MafiaType:0; m_i<mafia_TypesCreated; m_i++)
	{
		for(new i; i<mafia_TurfCreated[m_i]; i++)
		{
			GangZoneShowForPlayer(playerid, mafia_Turf[i][m_i], mafia_Turf_Color[i][m_i]);
		}
	}
	return 1;
}

#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn Maf_Frame_OnPlayerSpawn
#if defined Maf_Frame_OnPlayerSpawn
    forward Maf_Frame_OnPlayerSpawn(playerid);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		new 
			newcar = GetPlayerVehicleID(playerid),
			MafiaType:temp_PlayerMafia = INVALID_MAFIA_ID
		;	 
		if(IsPlayerInAnyMafia(playerid))
			GetPlayerMafia(playerid, temp_PlayerMafia);
		for(new MafiaType:i; i<mafia_TypesCreated; i++)
		{
			if(newcar == Mafia_Car[i])
			{
				if(temp_PlayerMafia != i)
				{
					RemovePlayerFromVehicle(playerid);
					#if defined OnPlayerTryEnterMafiaVehicle
						CallLocalFunction("OnPlayerTryEnterMafiaVehicle", "dddd", playerid, _:i, newcar, ERROR_NOT_SAME_MAFIA);
					#endif	
					return 1;
				}
				#if defined OnPlayerTryEnterMafiaVehicle
					CallLocalFunction("OnPlayerTryEnterMafiaVehicle", "dddd", playerid, _:i, newcar, NO_ERROR_SUCCESSED);
				#endif	
			}	
		}	
	}	
	return 1;
}

#if defined _ALS_OnPlayerStateChange
    #undef OnPlayerStateChange
#else
    #define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange Maf_Frame_OnPlayerStateChange
#if defined Maf_Frame_OnPlayerStateChange
    forward Maf_Frame_OnPlayerStateChange(playerid, newstate, oldstate);
#endif


public OnPlayerDisconnect(playerid, reason)
{
	Player_Materials[playerid] = 0;
	Player_Mafia[playerid] = INVALID_MAFIA_ID;
	Player_MafiaLeader[playerid] = INVALID_MAFIA_ID;
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect Maf_Frame_OnPlayerDisconnect
#if defined Maf_Frame_OnPlayerDisconnect
    forward Maf_Frame_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
	for(new MafiaType:i; i<mafia_TypesCreated;i++)
	{
		if(checkpointid == Mafia_Warehouse[i])
		{
			#if defined OnPlayerEnterMafiaWarehouseCP
				CallLocalFunction("OnPlayerEnterMafiaWarehouseCP", "dd", playerid, _:i);
			#endif	
			return 1;
		}
	}
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicCP
    #undef OnPlayerEnterDynamicCP
#else
    #define _ALS_OnPlayerEnterDynamicCP
#endif
#define OnPlayerEnterDynamicCP Maf_Frm_OnPlayerEnterDynamicCP
#if defined Maf_Frm_OnPlayerEnterDynamicCP
    forward Maf_Frm_OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid);
#endif
