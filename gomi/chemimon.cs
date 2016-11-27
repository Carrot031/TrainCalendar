using System;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
public class MainClass
{
	public static void Main(string[] args)
	{
		var game = ChemimonGame.CreateInstance();
		game.Main();
		return;
		/*GameWindowBase gw = new GameWindowGtk(400,300);
		gw.Show();
		EventHandler handler;
		handler = (s,e)=>
		{
			gw.Close();
		};
		gw.WindowClosing += handler;
		gw.Title = "Chemical Monsters";
		gw.UpdatePNGImage(null);
		Task.Run(()=>{gw.Main();}).Wait();
		*/
	}

}
