// <copyright file="Environment.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Environment
{
	override protected float GetEnvironmentTemperature()
	{
		float result = super.GetEnvironmentTemperature();
		if (m_Player && m_Player.IsAlive() && m_Player.GetTerjeSkills())
		{
			float relativeTemp;
			float skillModifierValue;
			if (m_Player.GetTerjeSkills().GetSkillModifierValue("surv", "survtempmod", skillModifierValue))
			{
				float settingsMod = 1.0;
				GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_SURV_TEMPERATURE_MODIFIER, settingsMod);
				relativeTemp = result - GameConstants.ENVIRO_PLAYER_COMFORT_TEMP;	
				relativeTemp = relativeTemp * Math.Clamp(1.0 + (skillModifierValue * settingsMod), 0, 1);
				result = relativeTemp + GameConstants.ENVIRO_PLAYER_COMFORT_TEMP;
			}
			
			float perkColdresValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("surv", "coldres", perkColdresValue))
			{
				relativeTemp = result - GameConstants.ENVIRO_PLAYER_COMFORT_TEMP;	
				if (relativeTemp < 0)
				{
					relativeTemp = relativeTemp * Math.Clamp(1.0 - perkColdresValue, 0, 1);
				}
				result = relativeTemp + GameConstants.ENVIRO_PLAYER_COMFORT_TEMP;
			}
		}
		
		return result;
	}
};
