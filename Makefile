CC=gcc
CSC=mcs

TrainCalendar:OdangoShooting.c GameSceneMenu.c GameSceneMain.c SList.c Akari.c Enemy.c Gamboh.c Chinatsu.c Odango.c Config.c Random.c Colision.c
	$(CC) $^ -fPIC -o $@ `pkg-config --cflags --libs gtk+-3.0` -lcairo -Wall -g -lX11 -O4 -lfontconfig -lm -ldl
SListTest:SListTest.c SList.c
	$(CC) $^ -o $@ -g -Wall -O0

SListSpeed:SListSpeed.c SList.c
	$(CC) $^ -o $@ -g -Wall -O0
ColisionTest:ColisionTest.c Colision.c
	$(CC) $^ -o $@ -g -Wall


chemimon.exe: chemimon.cs GameWindowBase.cs GameWindowGtk.cs WindowConfigurationChangedEventArgs.cs DrawEventArgs.cs ChemimonGame.cs GameSceneBase.cs GameSceneMenu.cs PngData.cs
	$(CSC) $^ -reference:System.Drawing.dll
gamewindow.so: gamewindow.c gamewindow.h
	$(CC) $< -shared -fPIC -o $@ `pkg-config --cflags --libs gtk+-3.0` -lcairo -Wall -g
.PHONY: clean
clean:
	rm TrainCalendar
