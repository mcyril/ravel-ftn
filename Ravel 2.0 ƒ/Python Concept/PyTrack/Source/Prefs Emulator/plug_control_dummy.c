//	�	plug_control_dummy.c#include "PyPlug.h"#include "plug_control_dummy.h"//#if PYTRACK_STANDALONE#include "stringutl.h"//#endif#include "PascalStr.h"PlugsControl *create_plug_control(){	short	i, j;	short	akas = 2;	short	links = 2;	short	groups = 2;	short	echoes = 2;	short	routes = 2;	PlugsControl *pc = (PlugsControl *)NewPtrClear(sizeof(PlugsControl));	//	Home system		pc->Preferences.homesystem = (homeHndl)NewHandleClear(sizeof(homeType) + akas * sizeof(daddr));	HLock((Handle)pc->Preferences.homesystem);		pStrCopy("\pMacsBug Exception", (**pc->Preferences.homesystem).system);	pStrCopy("\pCyril Moorzin", (**pc->Preferences.homesystem).sysop);	pStrCopy("\pSt. Petersburg", (**pc->Preferences.homesystem).location);	pStrCopy("\p7-812-5855897", (**pc->Preferences.homesystem).phone);	pStrCopy("\p33600", (**pc->Preferences.homesystem).baud);	pStrCopy("\pMO", (**pc->Preferences.homesystem).emsi_flags);		parseaddr (&(**pc->Preferences.homesystem).mainAddr.ad, "2:5030/700");		(**pc->Preferences.homesystem).AKAcount = akas;	parseaddr (&(**pc->Preferences.homesystem).AKAAddr[0].ad, "2:5030/25.36");	parseaddr (&(**pc->Preferences.homesystem).AKAAddr[1].ad, "2:5030/198.1");//	Netmail ares settings	pc->Preferences.mailHndl = (mailPrefHndl)NewHandleClear(sizeof(mailPrefType));	HLock((Handle)pc->Preferences.mailHndl);	pStrCopy("\pNETMAIL", (**pc->Preferences.mailHndl).mailName);	(**pc->Preferences.mailHndl).areaflags = 0;	(**pc->Preferences.mailHndl).purger = 900;	(**pc->Preferences.mailHndl).useAKA = 0;		//	ie. main address//	Links settings	pc->Preferences.NodesNumber = links;	pc->Preferences.nodesHndls = (nodePrefHndl *)NewPtrClear(sizeof(nodePrefHndl) * links);	for (i = 0; i < links; i++)	{		pc->Preferences.nodesHndls[i] = (nodePrefHndl)NewHandleClear(sizeof(nodePrefType) + groups * sizeof(short));		HLock((Handle)pc->Preferences.nodesHndls[i]);				if (i == 0)		{			pStrCopy("\pGP BBS", (**pc->Preferences.nodesHndls[i]).nodeName);			parseaddr (&(**pc->Preferences.nodesHndls[i]).Addr, "2:5030/448");		}		else		{			pStrCopy("\pRavel dev. Group", (**pc->Preferences.nodesHndls[i]).nodeName);			parseaddr (&(**pc->Preferences.nodesHndls[i]).Addr, "2:5030/700.1");		}		(**pc->Preferences.nodesHndls[i]).GroupsNumber = groups;		for (j = 0; j < groups; j++)			(**pc->Preferences.nodesHndls[i]).group[j] = j;	}//	Echoes settings	pc->Preferences.AreasNumber = echoes;	pc->Preferences.areasHndls = (areaPrefHndl *)NewPtrClear(sizeof(areaPrefHndl) * echoes);	for (i = 0; i < echoes; i++)	{		pc->Preferences.areasHndls[i] = (areaPrefHndl)NewHandleClear(sizeof(areaPrefType) + links * sizeof(ExpItem));		HLock((Handle)pc->Preferences.areasHndls[i]);				if (i == 0)		{			pStrCopy("\pMACS.BUG.INFO", (**pc->Preferences.areasHndls[i]).areaName);			(**pc->Preferences.areasHndls[i]).group = 0;			(**pc->Preferences.areasHndls[i]).useAKA = 0;		}		else		{			pStrCopy("\pRU.MAC", (**pc->Preferences.areasHndls[i]).areaName);			(**pc->Preferences.areasHndls[i]).group = 1;			(**pc->Preferences.areasHndls[i]).useAKA = 1;		}		(**pc->Preferences.areasHndls[i]).purger = 300;		(**pc->Preferences.areasHndls[i]).areaflags = 0;		(**pc->Preferences.areasHndls[i]).numExports = links;		for (j = 0; j < links; j++)		{			(**pc->Preferences.areasHndls[i]).Export[j].Export = j;			(**pc->Preferences.areasHndls[i]).Export[j].Diodes = 0;		}	}	//	Groups settings	pc->Preferences.GroupsNumber = groups;	pc->Preferences.groupsHndls = (groupPrefHndl *)NewPtrClear(sizeof(groupPrefHndl) * groups);	for (i = 0; i < groups; i++)	{		pc->Preferences.groupsHndls[i] = (groupPrefHndl)NewHandleClear(sizeof(groupPrefType) + links * sizeof(ExpItem));		HLock((Handle)pc->Preferences.groupsHndls[i]);				if (i == 0)		{			pStrCopy("\pLOCAL", (**pc->Preferences.groupsHndls[i]).groupName);			(**pc->Preferences.groupsHndls[i]).useAKA = 0;		}		else		{			pStrCopy("\pMYUPLINK", (**pc->Preferences.groupsHndls[i]).groupName);			(**pc->Preferences.groupsHndls[i]).useAKA = 1;		}		(**pc->Preferences.groupsHndls[i]).purger = 300;		(**pc->Preferences.groupsHndls[i]).areaflags = 0;		(**pc->Preferences.groupsHndls[i]).numExports = links;		for (j = 0; j < links; j++)		{			(**pc->Preferences.groupsHndls[i]).Export[j].Export = j;			(**pc->Preferences.groupsHndls[i]).Export[j].Diodes = 0;		}	}//	Routing		pc->Preferences.Routing = (routeHndl)NewHandleClear(sizeof(short) + routes * sizeof(routeType));	HLock((Handle)pc->Preferences.Routing);		(**pc->Preferences.Routing).routes = routes;		for (i = 0; i < routes; i++)	{		parsemask(&(**pc->Preferences.Routing).route[i].mask, (i == 0) ? "2:5030/700.1" : "*:*/*.*");		(**pc->Preferences.Routing).route[i].node = (i == 0) ? 1 : 0;	}//	paths		pc->Preferences.BundlesPath = "\p:";	pc->Preferences.OutboundPath = "\p:";	pc->Preferences.InboundPath = "\p:";	pc->Preferences.BasePath = "\p:";	pc->Preferences.TempPath = "\p:";	pc->Preferences.NodeLists = "\p:";	pc->Preferences.LogPath = "\p:Log";		return pc;}