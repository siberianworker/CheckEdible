class CfgMods
{
	class SW_CheckEdible
	{
		type = "mod";
		dependencies[] = {"World","Mission"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"SW/simple_mods/SW_CheckEdible/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"SW/simple_mods/SW_CheckEdible/scripts/5_Mission"};
			};
		};
	};
};