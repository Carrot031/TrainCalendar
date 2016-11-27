using System;
public class WindowConfigurationChangedEventArgs : EventArgs
{
	public WindowConfigurationChangedEventArgs(int x,int y, int w, int h)
	{
		this.X = x;
		this.Y = y;
		this.Width = w;
		this.Height = h;
	}

	public int X{get;private set;}
	public int Y{get;private set;}
	public int Width{get;private set;}
	public int Height{get;private set;}
}
