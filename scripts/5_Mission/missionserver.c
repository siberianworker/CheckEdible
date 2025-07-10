modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		
		SW_PluginNutritionDumper.CheckInit();
	};
};