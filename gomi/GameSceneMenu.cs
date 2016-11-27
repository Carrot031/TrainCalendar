using System;
using System.Drawing;
using System.IO;
public class GameSceneMenu : GameSceneBase
{
	public override Image Draw(int width, int height)
	{
		var img = new Bitmap(400,300);
		var g = Graphics.FromImage(img);

		return img;
		g.FillRegion(Brushes.LightGreen,g.Clip);
		g.DrawRectangle(Pens.Black,2,2,400,400);
		g.FillRectangle(Brushes.Red,0,0,400,400);
		g.Flush();
		g.Dispose();
		var ms = new MemoryStream();
		img.Save(ms,System.Drawing.Imaging.ImageFormat.Png);
		ms.Flush();
		img.Dispose();
		var pngimg = Image.FromStream(ms);
		ms.Dispose();
		return pngimg;
	}
}
