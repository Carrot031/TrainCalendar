CC=gcc
CSC=mcs

chemimon.exe: chemimon.cs GameWindowBase.cs GameWindowGtk.cs WindowConfigurationChangedEventArgs.cs DrawEventArgs.cs ChemimonGame.cs GameSceneBase.cs GameSceneMenu.cs PngData.cs
	$(CSC) $^ -reference:System.Drawing.dll
gamewindow.so: gamewindow.c gamewindow.h
	$(CC) $< -shared -fPIC -o $@ `pkg-config --cflags --libs gtk+-3.0` -lcairo -Wall -g -lX11
.PHONY: clean
clean:
	rm *.so *.exe
