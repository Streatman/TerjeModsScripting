// <copyright file="PluginTerjeDatabase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeDatabase extends PluginBase
{
	private const string DATABASE_DIR = "$mission:terje_storage";
	private ref map<string, ref TerjePlayerProfile> m_profiles = null;
	private ref map<string, ref TerjePlayerProfile> m_autosaveCache = null;
	private ref TerjePlayerProfile m_localProfile = null;
	private float m_autosaveTimer = 0;
	
	bool GetPlayerProfile(string uid, out TerjePlayerProfile profile)
	{
		return m_profiles.Find(uid, profile);
	}
	
	ref TerjePlayerProfile GetLocalProfile()
	{
		return m_localProfile;
	}
	
	override void OnInit()
	{
		if (!GetGame().IsDedicatedServer())
		{
			GetTerjeRPC().RegisterHandler("core.profile", this, "OnReceiveClientProfile");
		}
		else if (GetGame().IsDedicatedServer())
		{
			MakeDirectory(DATABASE_DIR);
			MakeDirectory(DATABASE_DIR + "/profiles");
			m_profiles = new map<string, ref TerjePlayerProfile>;
			m_autosaveCache = new map<string, ref TerjePlayerProfile>;
		}
	};
	
	private void OnReceiveClientProfile(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param1<ref map<string, string>> clientData;
		if (!ctx.Read(clientData))
		{
			return;
		}
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player)
		{
			m_localProfile = player.CreateTerjeProfile();
			if (m_localProfile)
			{
				m_localProfile.ApplyFromServer(clientData.param1);
				player.OnTerjeProfileChanged();
			}
		}
	}
	
	override void OnUpdate(float delta_time)
	{
		super.OnUpdate(delta_time);
		
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void OnPlayerConnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	};
	
	void OnPlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	};
};

PluginTerjeDatabase GetTerjeDatabase() 
{
    return PluginTerjeDatabase.Cast(GetPlugin(PluginTerjeDatabase));
};
