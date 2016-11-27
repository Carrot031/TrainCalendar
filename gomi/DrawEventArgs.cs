using System;
using System.Drawing;
public class DrawEventArgs : EventArgs
{
	public DrawEventArgs(int w, int h)
	{
		this.Width = w;
		this.Height = h;
	}

	public int Width{get;private set;}
	public int Height{get;private set;}


	public Image DrawnImage{get;set;}
}
