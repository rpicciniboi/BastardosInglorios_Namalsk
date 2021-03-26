#include "$CurrentDir:\\mpmissions\\construcoes\\BancoDayz.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\trade\\tradeOZERKO.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\trade\\TradeOrlovet.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\trade\\BlackPedreiraGIGI.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\trade\\NAMALSK_TRADER.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\trade\\black_namalsk.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\trade\\NamalskCacador.c"
//#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NAMALSK_AIRFIELD.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskStationZebra.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskVillage.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskHarbour.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskPrison.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskMilitaryCamp.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskTFOutpost.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskOutpost.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskSubmarine.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskMilitaryPrison.c"
#include "$CurrentDir:\\mpmissions\\construcoes\\mapa\\NamalskBattalionHQ.c"

void DroparObjeto(string objectName, vector position, vector orientation) {
    Object obj;
    obj = Object.Cast(GetGame().CreateObject(objectName, "0 0 0"));
    obj.SetPosition(position);
    obj.SetOrientation(orientation);
    //Force collision update
    vector roll = obj.GetOrientation();
    roll [ 2 ] = roll [ 2 ] - 1;
    obj.SetOrientation( roll );
    roll [ 2 ] = roll [ 2 ] + 1;
    obj.SetOrientation( roll );
 
    // Force update collisions
    if (obj.CanAffectPathgraph())
    {
        obj.SetAffectPathgraph(true, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
    }
};

void construcoes() {
	//TradeS
	//tradeOZERKO();	
	//TradeOrlovet();
	NAMALSK_TRADER();
	
	//Caçador
	NamalskCacador();
	
	//Black
	//BlackPedreiraGIGI();
	black_namalsk();
	
	//Arena de eventos
	
	//ATM espalhados pelo mapa
	//BancoDayz(); 
	
	//Bases
	
	//heli
	//Heliporto();

	//Mapas
	NamalskBattalionHQ();
	NamalskMilitaryPrison();
	NamalskSubmarine();
	NamalskOutpost();
	//NamalskTFOutpost();
	NamalskMilitaryCamp();
	NamalskPrison();
	NamalskHarbour();
	NamalskVillage();
	NamalskStationZebra();
	//NAMALSK_AIRFIELD();
};