#include "$CurrentDir:\\mpmissions\\construcoes\\construcoes.c"

void main()
{
	/*
	  [Namalsk] CE init (offline)
	*/
	CreateHive();
	GetHive().InitOffline();
	
	//******************************************************************************************************
    //Construções personalizadas
	//******************************************************************************************************
	construcoes();
	
	//******************************************************************************************************
	//Gerador de loot de áreas personalizadas - Tirar "//" na primeira execução
	//******************************************************************************************************
	//GetCEApi().ExportProxyData( "7500 0 7500", 100000 );  //Center of map, radius of how far to go out and find buildings.
	

	/*
	  [Namalsk] Weather init
	   Warning: DO NOT ALTER following values as they are interconnected with other Namalsk-specific systems!
	   To ensure correct functionality, it is necessary to include weaher init AFTER the hive init.
	*/
	Weather weather = GetGame().GetWeather();
	weather.MissionWeather( true );
	weather.GetOvercast().SetLimits( 0.10, 0.30 );
	weather.GetRain().SetLimits( 0.0, 0.0 );
	weather.GetFog().SetLimits( 0.0, 0.0 );
	weather.GetOvercast().SetForecastChangeLimits( 0.1, 0.3 );
	weather.GetOvercast().SetForecastTimeLimits( 1600, 2100 );
	weather.GetOvercast().Set( Math.RandomFloatInclusive( 0.1, 0.2 ), 0, 0 );	// ignored if storage is present
	weather.GetRain().Set( 0, 0, 0 );											// ignored if storage is present
	weather.GetFog().Set( 0, 0, 0 );											// ignored if storage is present
	weather.SetWindMaximumSpeed( 30 );
	weather.SetWindFunctionParams( 0.1, 1.0, 42 );
	weather.SetStorm( 0, 1, 1 );
	weather.SetRainThresholds( 0.0, 1.0, 0 );

	/*
	  [Namalsk] Mission time init
	   after CE init to determine if storage mission type is outside of the required time-frame
	   currently recommended time-frame is:
		11/1 -> 11/30
		keep in mind that gameplay features are tied to the mission date (stored in the storage) and that it SHOULD remain this period!
	   while using:
		day accelerated 6 times (serverTimeAcceleration=6), resulting in an average 78 min of day-time (RL)
		night accelerated 24 times (serverNightTimeAcceleration=4), resulting in an average of 26 min of night-time (RL)
	*/
	int year, month, day, hour, minute;
	GetGame().GetWorld().GetDate( year, month, day, hour, minute );

    if ( ( month < 11 ) || ( month >= 12 ) )
    {
    	year = 2011;
        month = 11;
        day = 1;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}
};

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise event system is switched on automatically and runs from default values
		// comment this whole block if NOT using Namalsk Survival
		if ( m_EventManagerServer )
		{
			// enable/disable event system, min time between events, max time between events, max number of events at the same time
			m_EventManagerServer.OnInitServer( true, 550, 1000, 2 );
			// registering events and their probability
			m_EventManagerServer.RegisterEvent( Aurora, 0.85 );
			m_EventManagerServer.RegisterEvent( Blizzard, 0.05 );
			m_EventManagerServer.RegisterEvent( ExtremeCold, 0.05 );
			m_EventManagerServer.RegisterEvent( Snowfall, 0.2 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.35 );
			m_EventManagerServer.RegisterEvent( HeavyFog, 0.05 );
		}
	}

	void SetRandomHealth(EntityAI itemEnt)
	{
		if (itemEnt)
		{
			float rndHlt = Math.RandomFloat( 0.50, 0.85 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
	{
		player.RemoveAllItems();
		
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;
		
		// top
		//itemClothing = player.FindAttachmentBySlotName( "Body" );
		itemClothing = player.GetInventory().CreateInInventory("dzn_bubblegoose_bastardos_red");
		if ( itemClothing )
		{
			//SetRandomHealth( itemClothing );

			itemEnt = itemClothing.GetInventory().CreateInInventory( "Rag" );
			if ( Class.CastTo( itemBs, itemEnt ) )
				itemBs.SetQuantity( 4 );
			player.SetQuickBarEntityShortcut( itemEnt, 1 );

			itemEnt = itemClothing.GetInventory().CreateInInventory( "RoadFlare" );			
			itemEnt = itemClothing.GetInventory().CreateInInventory( "RoadFlare" );			
			player.SetQuickBarEntityShortcut( itemEnt, 2 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( "Msp_VorpalKnife" );			
			player.SetQuickBarEntityShortcut( itemEnt, 0 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( "Heatpack" );
			itemEnt = itemClothing.GetInventory().CreateInInventory( "Heatpack" );
			player.SetQuickBarEntityShortcut( itemEnt, 3 );
		}

		// pants
		//itemClothing = player.FindAttachmentBySlotName( "Legs" );
		itemClothing = player.GetInventory().CreateInInventory("FP4_TacticalPants_Dolg");
		if ( itemClothing )
		{
			//lanterna
			ItemBase light = itemClothing.GetInventory().CreateInInventory("Flashlight");
			light.GetInventory().CreateAttachment("Battery9V");
			player.SetQuickBarEntityShortcut( light, 4 );

			int throwDice = Math.RandomInt( 0, 2 );
			if ( throwDice == 0 )
				itemEnt = itemClothing.GetInventory().CreateInInventory( "dzn_tool_watch" );
			else
				itemEnt = itemClothing.GetInventory().CreateInInventory( "dzn_tool_watch2" );
			player.SetQuickBarEntityShortcut( itemEnt, 5 );
		}

		// shoes
		//itemClothing = player.FindAttachmentBySlotName( "Feet" );
		itemClothing = player.GetInventory().CreateInInventory("MilitaryBoots_Redpunk");
		itemClothing = player.GetInventory().CreateInInventory("OMNOGloves_Brown");
		itemClothing = player.GetInventory().CreateInInventory("ZmijovkaCap_Red");
		itemClothing = player.GetInventory().CreateInInventory("Snipe_Mask_blood");
		//if ( itemClothing )
		//{
		//	SetRandomHealth( itemClothing );
		//}

		//Loot padrão para todos
		//itemEnt = player.GetInventory().CreateInInventory("PersonalRadio");		
		
		
		//arma padrão
		//itemEnt = player.GetHumanInventory().CreateInHands("Glock19");
        //itemBs = itemEnt.GetInventory().CreateAttachment("Mag_Glock_15Rnd");
		//player.SetQuickBarEntityShortcut( itemEnt, 0, true );
		
		itemEnt = player.GetInventory().CreateInInventory("FP4_Kolbasa");
		itemEnt = player.GetInventory().CreateInInventory("WaterBottle");
		
		// bump fresh spawn water and energy values (to compensate for the frozen food and harder-to-get wells)
		player.GetStatWater().Set( 900 );
		player.GetStatEnergy().Set( 1100 );
	
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(NotificationSystem.SimpleNoticiation, 1000, false ,  "Bem Vindo ao server Bastardos Inglórios!\nEntre em nosso Discord para obter ajuda e nos dar seu feedback! (pause/break)\n\nBoa sorte e se divirta!!", "Welcome", "Notifications/gui/data/notifications.edds", ARGB(240, 90, 140, 195), 30, player.GetIdentity());
	}
	
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
};
