enum NutritionType
{
	FULLNESSINDEX,
	ENERGY,
	WATER,
	NUTRITIONALINDEX,
	TOXICITY
}

class SW_NutritionAnalyzer
{
	protected static float GetNutritionPropertyFromIndex(string classname, int index)
	{			
		string config_path = string.Format("CfgVehicles %1 Food FoodStages Raw nutrition_properties", classname);
		array<float> base_nutr_properties = new array<float>;
		GetGame().ConfigGetFloatArray( config_path, base_nutr_properties );
		
		return ( base_nutr_properties.Get( index ) );
	}

	static float GetNutrition(string classname, int nutr)
	{
		string class_path, path;
		int LiquidTypeInit;

		if(IsBottle(classname) && !HasNutrition(classname))
		{
			path = string.Format("CfgVehicles %1 varLiquidTypeInit", classname);
			LiquidTypeInit = GetGame().ConfigGetInt(path);
			classname = GetTypeLiquid(LiquidTypeInit);
			class_path = string.Format("cfgLiquidDefinitions %1 Nutrition", classname);
		}
		else if(HasStages(classname))
		{
			return GetNutritionPropertyFromIndex(classname, nutr);
		}
		else
		{
			class_path = string.Format("cfgVehicles %1 Nutrition", classname);
		}

		switch (nutr)
		{
			case NutritionType.ENERGY:
				return GetGame().ConfigGetFloat( class_path + " energy" );
			case NutritionType.WATER:
				return GetGame().ConfigGetFloat( class_path + " water" );
			case NutritionType.TOXICITY:
				return GetGame().ConfigGetFloat( class_path + " toxicity" );
			case NutritionType.FULLNESSINDEX:
				return GetGame().ConfigGetFloat( class_path + " fullnessIndex" );
			case NutritionType.NUTRITIONALINDEX:
				return GetGame().ConfigGetFloat( class_path + " nutritionalIndex" );
		}

		return 0;
	}

	static int GetQuantityMax(string classname)
	{
		string path = string.Format("cfgVehicles %1 varQuantityMax", classname);
		return GetGame().ConfigGetInt(path);
	}

	static string GetTypeLiquid(int TypeInit)
	{
		string path = "cfgLiquidDefinitions";
		string child_name = "";
		int count = g_Game.ConfigGetChildrenCount(path);

		for (int i = 0; i < count; ++i)
		{
			GetGame().ConfigGetChildName(path, i, child_name);

			if(GetGame().ConfigGetInt(path + child_name))
			{
				return child_name;
			}
		}

		return child_name;
	}

	static bool IsBottle(string classname)
	{
		if(GetGame().IsKindOf(classname, "Bottle_Base") || GetGame().IsKindOf(classname, "SodaCan_ColorBase"))
		{
			return true;
		}

		return false;
	}

	static bool HasNutrition(string classname)
	{
		if(GetGame().ConfigIsExisting(string.Format("CfgVehicles %1 Nutrition", classname)))
		{
			return true;
		}

		return false;
	}

	static bool HasStages(string classname)
	{
		if(GetGame().ConfigIsExisting(string.Format("CfgVehicles %1 Food", classname)))
		{
			return true;
		}

		return false;
	}
}