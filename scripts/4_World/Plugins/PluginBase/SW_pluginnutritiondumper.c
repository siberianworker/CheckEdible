class SW_PluginNutritionDumper extends PluginBase
{
	static ref TStringArray m_AllLines = new TStringArray;	
	static const string FILENAME = "nutritional_values.csv";
	
	static void CheckInit()
	{
		int scope, children_count;
		string config_path, child_name, path;

		m_AllLines.Clear();
		string line = "Classname,quantityMax,energy,water,toxicity,fullnessIndex,nutritionalIndex,isBottle";
		m_AllLines.Insert(line);
		
		config_path = "CfgVehicles";
		children_count = GetGame().ConfigGetChildrenCount(config_path);
		
		for(int i = 0; i < children_count; i++)
		{
			GetGame().ConfigGetChildName(config_path, i, child_name);
			path = config_path + " " + child_name;
			scope = GetGame().ConfigGetInt( config_path + " " + child_name + " scope" );
			
			if ( scope == 2 )
			{
				if(SW_NutritionAnalyzer.HasNutrition(child_name) || SW_NutritionAnalyzer.HasStages(child_name) || SW_NutritionAnalyzer.IsBottle(child_name))
				{
					line = "";
					line = BuildLine(child_name);
					m_AllLines.Insert(line);
				}
			}
		}
	
		SaveToFile(FILENAME);
	}
	
	
	protected static void SaveToFile(string filename)
	{
		string Folder = "$profile:\\SW\\";
		string Path = Folder + filename;

		if (!FileExist(Path))
		{
			MakeDirectory( Folder );
		}

		FileHandle file = OpenFile(Path, FileMode.WRITE);

		if( file!=0 )
		{
			for(int i = 0; i < m_AllLines.Count(); i++)
			{
				FPrintln(file,m_AllLines.Get(i));
			}			
		}

		CloseFile(file);
	}
	
	static string BuildLine(string item_name)
	{
		string line = item_name+",";
		line = line + SW_NutritionAnalyzer.GetQuantityMax(item_name)+",";
		line = line + SW_NutritionAnalyzer.GetNutrition(item_name, NutritionType.ENERGY)+",";
		line = line + SW_NutritionAnalyzer.GetNutrition(item_name, NutritionType.WATER)+",";
		line = line + SW_NutritionAnalyzer.GetNutrition(item_name, NutritionType.TOXICITY)+",";
		line = line + SW_NutritionAnalyzer.GetNutrition(item_name, NutritionType.FULLNESSINDEX)+",";
		line = line + SW_NutritionAnalyzer.GetNutrition(item_name, NutritionType.NUTRITIONALINDEX)+",";
		line = line + SW_NutritionAnalyzer.IsBottle(item_name);

		return line;
	}
}