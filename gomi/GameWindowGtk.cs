using System;
using System.Runtime.InteropServices;
using System.Drawing;
public class GameWindowGtk : GameWindowBase
{

	public override int Width{get;set;}
	public override int Height{get;set;}
	public override string Title
	{
		get
		{
			return gamewindow_get_title();
		}
		set
		{
			gamewindow_set_title(value);
		}
	}
	public GameWindowGtk(int w,int h)
	{
		gamewindow_init();
		gamewindow_set_event_windowclosing_callback
		(()=>{OnWindowClosing(new EventArgs());});
		/*gamewindow_set_event_gametick_callback
		(()=>{OnGameTick(new EventArgs());});*/
		gamewindow_set_event_draw_callback
		(DrawCallback);
		gamewindow_set_event_windowconfigurationchanged_callback
		((newx,newy,neww,newh)=>{OnWindowConfigurationChanged
		(new WindowConfigurationChangedEventArgs(newx,newy,neww,newh));});
		
	}

	private PngData DrawCallback()
	{
			var e = new DrawEventArgs(Width,Height);
			OnDraw(e);

			if(e == null)
			{
				Console.WriteLine("??????????????");
			}
			var imgconv = new ImageConverter();
			byte[] b = (byte[])imgconv.ConvertTo(e.DrawnImage,typeof(byte[]));
			
			var ret = new PngData();
			GC.KeepAlive(ret.Data);
			GC.KeepAlive(ret);
			ret.Data = b;
			ret.Size = (ulong)b.LongLength;
			return ret;
	}

	public override void UpdatePNGImage(Image img)
	{
		/*
		img = Image.FromFile("/home/carrot031/ドキュメント/yuruyuri_sta.png");
		var g = Graphics.FromImage(img);
		g.DrawLine(Pens.Green,0,0,400,500);
		g.Dispose();
		*/
		var imgconv = new ImageConverter();
		byte[] b = (byte[])imgconv.ConvertTo(img,typeof(byte[]));
		gamewindow_thread_safe_update_image(b,(ulong)b.Length);

	}

	public override void Show()
	{
		gamewindow_show();
	}

	public override void Main()
	{
		gamewindow_main();
	}

	public override void Close()
	{
		gamewindow_close();
	}

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_init();

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_show();

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_thread_safe_update_image(
	byte[] data, ulong length);

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_update_image(byte[] data,ulong length);

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_main();

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_close();

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_set_event_windowclosing_callback
	(Action a);

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_set_event_gametick_callback
	(Action a);

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_set_event_draw_callback
	(Func<PngData> pngdata);

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_set_event_windowconfigurationchanged_callback
	(Action<int,int,int,int> a);

	[DllImport("./gamewindow.so")]
	private static extern string gamewindow_get_title();

	[DllImport("./gamewindow.so")]
	private static extern void gamewindow_set_title(string title);

}
