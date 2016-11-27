using System;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public class PngData
{
	public byte[] Data;
	public ulong Size;
}
