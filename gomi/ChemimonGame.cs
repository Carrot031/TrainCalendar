using System;
using System.Diagnostics;
public class ChemimonGame
{
	/* Singleton pattern */
	private static bool instance_created = false;
	private ChemimonGame()
	{
		instance_created = true;
		scene = new GameSceneMenu();
		window = new GameWindowGtk(400,300);
		window.Title = "Chemical Monsters";
		window.Show();
		window.WindowClosing +=
		(s, e) =>{window.Close();};
		window.Draw += 
		(s, e) =>{e.DrawnImage = scene.Draw(window.Width,window.Height);};
	}

	public static ChemimonGame CreateInstance()
	{
		if(instance_created)
		{
			throw new Exception("Only single instance is allowed.");
		}

		return new ChemimonGame();
	}

	/* readonly variables */
	private static readonly int processing_interval = 8; // 1 / 120 sec
	private static readonly int drawing_interval = 17; // 1 / 60 sec

	/* global variables */
	private GameWindowBase window;
	private GameSceneBase scene;
	/* Main loop */
	public void Main()
	{
		window.Main();
	}


}
