using System;
using System.Drawing;
public abstract class GameWindowBase
{
	public abstract int Width{get;set;}
	public abstract int Height{get;set;}
	public abstract string Title{get;set;}


	public abstract void Show();
	public abstract void Main();
	public abstract void Close();
	public abstract void UpdatePNGImage(Image img);

	/* event declarations */
	public event EventHandler WindowClosing;
	public event EventHandler<WindowConfigurationChangedEventArgs> WindowConfigurationChanged;
	public event EventHandler GameTick;
	public event EventHandler<DrawEventArgs> Draw;
	
	/* event publisher methods */
	protected virtual void OnWindowClosing(EventArgs e)
	{
		var handler = WindowClosing;
		if(handler != null)
		{
			handler(this,e);
		}
	}

	protected virtual void OnWindowConfigurationChanged(WindowConfigurationChangedEventArgs e)
	{
		var handler = WindowConfigurationChanged;
		if(handler != null)
		{
			handler(this,e);
		}
	}

	protected virtual void OnGameTick(EventArgs e)
	{
		var handler = GameTick;
		if(handler != null)
		{
			handler(this,e);
		}
	}

	protected virtual void OnDraw(DrawEventArgs e)
	{
		var handler = Draw;
		if(handler != null)
		{
			handler(this,e);
		}
	}
}
