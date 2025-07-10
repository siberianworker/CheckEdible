modded class PluginManager
{
    override void Init()
    {
        super.Init();
					    //"plugin_classname", client , server
		RegisterPlugin( "SW_PluginNutritionDumper", false, true );
    }
}