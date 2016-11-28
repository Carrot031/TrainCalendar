#include "stdio.h"
#include "stdlib.h"
#include "GameScene.h"
#include "GameSceneMain.h"
#include "Random.h"
#include "pango/pango.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <dlfcn.h>

GameScene* GameSceneMain_New()
{
	GameScene* ret = malloc(sizeof(GameScene));
	ret->GameTick = GameSceneMain_GameTick;
	ret->Draw = GameSceneMain_Draw;
	ret->KeyDown = GameSceneMain_KeyDown;
	ret->KeyUp = GameSceneMain_KeyUp;
	ret->Dispose = GameSceneMain_Dispose;
	ret->Field = malloc(sizeof(GameSceneMain_Field));

	GameSceneMain_Field* field = ret->Field;

	/* initialize field */
	/*
	field->Akari = Akari_New();
	field->Akari->Position = (Point) {0,0};
	field->CleanOdangoTick = 0;
	field->OdangoArray = malloc(sizeof(Odango*) * MaxOdangos);
	{
		int i;
		for(i = 0; i < MaxOdangos; i++){
			field->OdangoArray[i] = NULL;
		}
	}
	field->EnemyArray = malloc(sizeof(Enemy*) * MaxEnemies);
	{
		int i;
		for(i = 0; i < MaxEnemies; i++){
			field->EnemyArray[i] = NULL;
		}
	}
	*/
	field->Score = 0;
	field->AttackFlag = false;
	field->KeyUpFlag = false;
	field->KeyDownFlag = false;
	field->KeyLeftFlag = false;
	field->KeyRightFlag = false;
	field->Language = Japanese;
	field->PluginIndex = 0;

	field->AliveFlag = true;

	field->NTickAttackCount = 0;
	field->NTickLanguageCount = 0;
	field->NTickPluginCount = 0;


	/* load images */
	/*
	field->akari_png = cairo_image_surface_create_from_png
	("akari.png");
	if(cairo_surface_status(field->akari_png) != CAIRO_STATUS_SUCCESS){
		perror("Couldn't load akari image");
		exit(EXIT_FAILURE);
	}

	field->odango_png = cairo_image_surface_create_from_png
	("odango.png");
	if(cairo_surface_status(field->odango_png) != CAIRO_STATUS_SUCCESS){
		perror("Couldn't load odango image");
		exit(EXIT_FAILURE);
	}

	field->crying_akari_png = cairo_image_surface_create_from_png
	("crying_akari.png");
	if(cairo_surface_status(field->crying_akari_png) != CAIRO_STATUS_SUCCESS){
		perror("Couldn't load crying akarin image");
		exit(EXIT_FAILURE);
	}
	*/
	/* load plugins */
	field->NPlugins = 0;
	field->PluginHandleArray = malloc(sizeof(void*) * MaxPlugins);
	field->PluginFunctionArray = malloc(sizeof(void*) * MaxPlugins);
	field->PluginIsActiveArray = malloc(sizeof(void*) * MaxPlugins);
	DIR* dir;
	struct dirent *dp;
	const char* path = "./plugins/";
	dir = opendir(path);

	for(dp = readdir(dir);dp!=NULL;dp=readdir(dir)){
		char* dot;
		dot = strrchr(dp->d_name,'.');
		//check whether .tcplugin
		if(dot && !strcmp(dot,".tcplugin")){
			char fullpath[256];
			snprintf(fullpath,sizeof(fullpath),"%s%s",path,dp->d_name);
			struct stat path_stat;
			stat(fullpath, &path_stat);
			if(S_ISREG(path_stat.st_mode)){
				printf("%s is regular.\n",fullpath);
				void* handle = dlopen(fullpath,RTLD_NOW);
				if(!handle){
					printf("failed to load plugin '%s'\n",
					dp->d_name);
					continue;
				}
				Draw sym = dlsym(handle,"Draw");
				if(!sym){
					printf("failed to load symbol of '%s'\n",dp->d_name);
					continue;
				}
				IsActive sym_isactive = dlsym(handle,"IsActive");
				if(!sym_isactive){
					printf("failed to load symbol of '%s'\n",dp->d_name);
					continue;
				}
				field->PluginHandleArray
				[field->NPlugins] = handle;
				field->PluginFunctionArray
				[field->NPlugins] = sym;
				field->PluginIsActiveArray
				[field->NPlugins] = sym_isactive;
				field->NPlugins++;
			}
		}
	}
	closedir(dir);

	printf("CREATED");
	fflush(stdout);
	return ret;
}

GameScene* GameSceneMain_GameTick(void* this)
{
	GameScene* ptr = this;
	GameSceneMain_Field* field = ptr->Field;
	//const int speed = 2;

	/*
	if(field->Akari->HP <= 0){
	}
	*/

	/* count ntick */
	if(field->NTickAttackCount < NTickAttackInterval){
		field->NTickAttackCount++;
	}

	if(field->NTickLanguageCount < NTickLanguageInterval){
		field->NTickLanguageCount++;
	}else{
		field->NTickLanguageCount = 0;
		field->Language++;
		if(field->Language > English){
			field->Language = Japanese;
		}
	}
	if(field->NPlugins){
		if(field->NTickPluginCount < NTickPluginInterval){
			field->NTickPluginCount++;
		}else{
			//field->NTickPluginCount = 0;
			field->PluginIndex++;
			if(field->PluginIndex >= field->NPlugins){
				field->PluginIndex = 0;
			}
			if(field->PluginIsActiveArray[field->PluginIndex]()){
				field->NTickPluginCount = 0;
			}
		}
	}

	/*
	if(field->CleanOdangoTick < OdangoCleanInterval){
		field->CleanOdangoTick++;
	}

	if(field->CleanOdangoTick == OdangoCleanInterval){
		GameSceneMain_CleanOdangoArray(this);
		field->CleanOdangoTick = 0;
	}
	*/

	/* move akari */
	/*
	if(field->KeyUpFlag){
		field->Akari->Position.Y -= speed;
	}
	if(field->KeyDownFlag){
		field->Akari->Position.Y += speed;
	}
	if(field->KeyLeftFlag){
		field->Akari->Position.X -= speed;
	}
	if(field->KeyRightFlag){
		field->Akari->Position.X += speed;
	}
	*/

	/* move odango */
	/*
	{
		int i;
		for(i = 0; i < MaxOdangos; i++){
			Odango* to_move = field->OdangoArray[i];
			if(!to_move) continue;
			to_move->Position.X += 1;
			to_move->Position.Y += 0;
		}
	}
	*/

	/* generate odango */
	/*
	if(field->AttackFlag && 
	field->NTickAttackCount >= NTickAttackInterval){
		Odango* to_add = Odango_New();
		to_add->Position.X = field->Akari->Position.X +
		cairo_image_surface_get_width(field->akari_png) * 0.4;
		to_add->Position.Y = field->Akari->Position.Y;
		field->NTickAttackCount = 0;

		int i;
		for(i = 0; i < MaxOdangos; i++){
			Odango** o = &field->OdangoArray[i];
			if(!*o){
				*o = to_add;
				break;
			}
		}
	}
	*/

	/* move enemies */
	/*
	{
		int i;
		for(i = 0; i < MaxEnemies; i++){
			Enemy* e = field->EnemyArray[i];
			if(!e) continue;
			e->Position.X += e->Velocity.X;
			e->Position.Y += e->Velocity.Y;
		}
	}
	*/

	/* generate chinatsu */
	/*
	if(GetRandom(0,256)==0){
		int i;
		for(i = 0; i < MaxEnemies; i++){
			Enemy* e = field->EnemyArray[i];
			if(!e){
				e = Chinatsu_New();
				e->Position.X = LogicalWidth;
				e->Position.Y = GetRandom(0,LogicalHeight);
				field->EnemyArray[i] = e;
				break;
			}
		}
	}
	*/

	/* Colision Check */
	/*
	Point p1[4];
	p1[0].X = field->Akari->Position.X;
	p1[0].Y = field->Akari->Position.Y;
	p1[1].X = field->Akari->Position.X +
		cairo_image_surface_get_width(
				field->akari_png)*0.4;
	p1[1].Y = field->Akari->Position.Y;
	p1[2].X = p1[1].X;
	p1[2].Y = field->Akari->Position.Y +
		cairo_image_surface_get_height(
				field->akari_png)*0.4;
	p1[3].X = p1[0].X;
	p1[3].Y = p1[2].Y;
	*/
	
	{ /* akari and enemies */
		/*
		Point p2[4];

		int i;
		for(i = 0; i < MaxEnemies; i++){
			Enemy* e = field->EnemyArray[i];
			if(!e) continue;
			p2[0].X = e->Position.X;
			p2[0].Y = e->Position.Y;
			p2[1].X = e->Position.X +
			cairo_image_surface_get_width(e->PNGImage) *
			e->Scale;
			p2[1].Y = p2[0].Y;
			p2[2].X = p2[1].X;
			p2[2].Y = p2[0].Y +
			cairo_image_surface_get_height(e->PNGImage) *
			e->Scale;
			p2[3].X = p2[0].X;
			p2[3].Y = p2[2].Y;
			if(Colide(&p1[0],sizeof(p1)/sizeof(Point),&p2[0],sizeof(p2)/sizeof(Point))){
				printf("[%d]COLIDE\n",i);
				field->Akari->HP -= e->TouchDamage;
				e->HP -= field->Akari->TouchDamage;
			}
		}
		*/
	}

	{ /* odango and enemies */
	/*
		Point podango[4];
		Point penemy[4];
		int io,ie;
		for(io = 0; io < MaxOdangos; io++){
			for(ie = 0; ie < MaxEnemies; ie++){			
				Odango** o =&(field->OdangoArray[io]);
				Enemy** e = &(field->EnemyArray[ie]);
				if(!(*o)) continue;
				if(!(*e)) continue;
				podango[0].X = (*o)->Position.X;
				podango[0].Y = (*o)->Position.Y;
				podango[1].X = podango[0].X +
				cairo_image_surface_get_width(field->odango_png) * 0.6;
				podango[1].Y = podango[0].Y;
				podango[2].X = podango[1].X;
				podango[2].Y = podango[0].Y +
				cairo_image_surface_get_height(field->odango_png) * 0.6;
				podango[3].X = podango[0].X;
				podango[3].Y = podango[2].Y;

				penemy[0].X = (*e)->Position.X;
				penemy[0].Y = (*e)->Position.Y;
				penemy[1].X = penemy[0].X +
				cairo_image_surface_get_width((*e)->PNGImage) * (*e)->Scale;
				penemy[1].Y = penemy[0].Y;
				penemy[2].X = penemy[1].X;
				penemy[2].Y = penemy[0].Y +
				cairo_image_surface_get_height((*e)->PNGImage) * (*e)->Scale;
				penemy[3].X = penemy[0].X;
				penemy[3].Y = penemy[2].Y;

				if(Colide(&podango[0],sizeof(podango)/sizeof(Point),&penemy[0],sizeof(penemy)/sizeof(Point))){
					(*e)->HP -= 1;
					*o = NULL;
				}
			}
		}
		*/
	}

	/* remove enemies whose HP <= 0 */
	/*
	{
		int i;
		for(i = 0; i < MaxEnemies; i++){
			Enemy** e = &(field->EnemyArray[i]);
			if(!*e) continue;
			if((*e)->HP <= 0){
				field->Score += (*e)->DestroyScore;
				*e = NULL;
			}
		}
	}
	*/

	//GameSceneMain_CleanOdangoArray(this);
	return NULL;
}

void GameSceneMain_Draw(void* this, cairo_t* cr,int width,int height)
{
	GameScene* ptr = this;
	GameSceneMain_Field* field = ptr->Field;


	/* clear */
	cairo_set_source_rgba(cr,1.0,1.0,1.0,1.0);
	cairo_rectangle(cr,0,0,width,height);
	cairo_fill(cr);



	/* paint akari */
	cairo_save(cr);
	/*int akari_width = cairo_image_surface_get_width(field->akari_png)
	* 0.4 * ((double)width)/400;*/
	/*
	cairo_translate(cr,field->Akari->Position.X * width / 400,field->Akari->Position.Y * width / 400);
	cairo_scale(cr,0.4 * ((double)width)/400,0.4 * ((double)width)/400);
	cairo_set_source_surface(cr,field->akari_png,0,0);
	cairo_paint(cr);
	cairo_restore(cr);
	cairo_identity_matrix(cr);
	*/

	/* paint odango */
	{
		/*
		int i;
		for(i = 0; i < MaxOdangos; i++){
			Odango* o = field->OdangoArray[i];
			if(!o) continue;
			cairo_identity_matrix(cr);
			cairo_translate(cr,o->Position.X * width / LogicalWidth,
			o->Position.Y * width / LogicalWidth);
			cairo_scale(cr,0.6*((double)width)/LogicalWidth,0.6*((double)width)/LogicalWidth);
			cairo_set_source_surface(cr,field->odango_png,0,0);
			cairo_paint(cr);
		}
		*/
	}

	/* paint enemies */
	/*
	{
		int i;
		for(i = 0; i < MaxEnemies; i++){
			Enemy* e = field->EnemyArray[i];
			if(!e) continue;
			cairo_identity_matrix(cr);
			cairo_translate(cr,e->Position.X * width / LogicalWidth,e->Position.Y * width / LogicalWidth);
			cairo_scale(cr,e->Scale*((double)width)/LogicalWidth,e->Scale*((double)width)/LogicalWidth);
			cairo_set_source_surface(cr,e->PNGImage,0,0);
			cairo_paint(cr);
		}
	}
	*/
	/*
	PangoLayout *layout;
	PangoFontDescription *desc;
	
	layout = pango_cairo_create_layout(cr);
	*/

	/* show title */
	/*
	pango_layout_set_text(layout, "お団子シューティング", -1);
	char fds[64];
	snprintf(fds,sizeof(fds),"IPAexGothic %dpx",40*width/400);
	desc = pango_font_description_from_string(fds);
	pango_layout_set_font_description(layout, desc);
	pango_layout_set_width(layout,pango_units_from_double(width));
	pango_layout_set_alignment(layout,PANGO_ALIGN_CENTER);
	pango_font_description_free(desc);
	cairo_set_source_rgb(cr, 1.0, 0.41, 0.70);
	pango_cairo_update_layout(cr, layout);
	pango_cairo_show_layout(cr, layout);
	*/
	/* draw glay rectangle */
	cairo_identity_matrix(cr);
	cairo_set_source_rgb(cr,0.5,0.5,0.5);
	cairo_rectangle(cr,0,0,width,100*width/400);
	cairo_fill(cr);
	
	/* draw white box for day */
	double wbox_width = 0.50;
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_rectangle(cr,width/2 - wbox_width * width /2,20*width/400,
	wbox_width * width, 75*width/400);
	cairo_fill(cr);

	cairo_set_source_rgb(cr,0,0,0);
	/* draw leftside text*/
	{
		cairo_translate(cr,0,75*width/400);
		PangoLayout *layout;
		PangoFontDescription *desc;
		layout = pango_cairo_create_layout(cr);
		if(field->Language == Japanese){
			pango_layout_set_text(layout,"ただいま",-1);
		}else if(field->Language == English){
			pango_layout_set_text(layout,"Today is",-1);
		}
		

		char fds[64];
		snprintf(fds,sizeof(fds),"IPAexGothic %dpx",20*width/400);

		desc = pango_font_description_from_string(fds);
		pango_layout_set_font_description(layout,desc);
		pango_layout_set_width(layout,
		pango_units_from_double(width/2 - wbox_width * width /2));
		pango_layout_set_alignment(layout,PANGO_ALIGN_RIGHT);
		pango_font_description_free(desc);

		pango_cairo_update_layout(cr,layout);
		pango_cairo_show_layout(cr,layout);

		g_object_unref(layout);
	}
	/* draw です */
	{
		
		cairo_identity_matrix(cr);
		cairo_translate(cr,
		width/2 + wbox_width * width /2,75*width/400);
		PangoLayout *layout;
		PangoFontDescription *desc;
		layout = pango_cairo_create_layout(cr);
		if(field->Language == Japanese){
			pango_layout_set_text(layout, "です", -1);
		}else{
		}

		char fds[64];
		snprintf(fds,sizeof(fds),"IPAexGothic %dpx",20*width/400);
		desc = pango_font_description_from_string(fds);
		pango_layout_set_font_description(layout,desc);
		pango_font_description_free(desc);

		pango_cairo_update_layout(cr,layout);
		pango_cairo_show_layout(cr,layout);

		g_object_unref(layout);
	}

	/* draw white box for time */
	cairo_identity_matrix(cr);
	double timebox_width = 0.12;
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_rectangle(cr,width - 10*width/400 - width*timebox_width,75*width/400,width*timebox_width,20*width/400);
	cairo_fill(cr);

	/* draw white box for date */
	cairo_identity_matrix(cr);
	double datebox_width = 0.22;
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_rectangle(cr,width - 10*width/400 -width*datebox_width,35*width/400,width*datebox_width,20*width/400);
	cairo_fill(cr);
	
	/* draw time label*/
	{
		cairo_set_source_rgb(cr,0.0,0.0,0.0);
		cairo_identity_matrix(cr);
		cairo_translate(cr,
		width - 10*width/400 - timebox_width * width,58*width/400);
		PangoLayout *layout;
		PangoFontDescription *desc;
		layout = pango_cairo_create_layout(cr);
		if(field->Language == Japanese){
			pango_layout_set_text(layout, "現在時刻", -1);
		}else if(field->Language == English){
			pango_layout_set_text(layout,"Time",-1);
		}

		char fds[64];
		snprintf(fds,sizeof(fds),"IPAexGothic %dpx",12*width/400);
		desc = pango_font_description_from_string(fds);
		pango_layout_set_font_description(layout,desc);
		pango_font_description_free(desc);

		pango_cairo_update_layout(cr,layout);
		pango_cairo_show_layout(cr,layout);

		g_object_unref(layout);
	}
	/* draw date label*/
	{
		cairo_set_source_rgb(cr,0.0,0.0,0.0);
		cairo_identity_matrix(cr);
		cairo_translate(cr,
		width - 60*width/400,20*width/400);
		PangoLayout *layout;
		PangoFontDescription *desc;
		layout = pango_cairo_create_layout(cr);
		if(field->Language == Japanese){
			pango_layout_set_text(layout, "日付", -1);
		}else if(field->Language == English){
			pango_layout_set_text(layout, "Date", -1);
		}

		char fds[64];
		snprintf(fds,sizeof(fds),"IPAexGothic %dpx",12*width/400);
		desc = pango_font_description_from_string(fds);
		pango_layout_set_font_description(layout,desc);
		pango_font_description_free(desc);

		pango_cairo_update_layout(cr,layout);
		pango_cairo_show_layout(cr,layout);

		g_object_unref(layout);
	}

	/* draw time */
	char datestr[64];
	char timestr[64];
	time_t timer;
	struct tm *timeptr;

	timer = time(NULL);
	timeptr = localtime(&timer);
	strftime(timestr, sizeof(timestr), "%H:%M",timeptr);
	strftime(datestr, sizeof(datestr), "%Y/%m/%d",timeptr);
	{
		cairo_set_source_rgb(cr,0.0,0.0,0.0);
		cairo_identity_matrix(cr);
		cairo_translate(cr,width - 10*width/400 - width*timebox_width,75*width/400);
		PangoLayout *layout;
		PangoFontDescription *desc;
		layout = pango_cairo_create_layout(cr);
		pango_layout_set_text(layout, timestr, -1);

		char fds[64];
		snprintf(fds,sizeof(fds),"IPAexGothic %dpx",16*width/400);
		desc = pango_font_description_from_string(fds);
		pango_layout_set_font_description(layout,desc);
		pango_layout_set_width(layout,pango_units_from_double(0.95*timebox_width*width));
		pango_layout_set_alignment(layout,PANGO_ALIGN_RIGHT);
		pango_font_description_free(desc);

		pango_cairo_update_layout(cr,layout);
		pango_cairo_show_layout(cr,layout);

		g_object_unref(layout);
	}
	
	/* draw date */
	{
		cairo_set_source_rgb(cr,0.0,0.0,0.0);
		cairo_identity_matrix(cr);
		cairo_translate(cr,width - 10*width/400 - width*datebox_width,40*width/400);
		PangoLayout *layout;
		PangoFontDescription *desc;
		layout = pango_cairo_create_layout(cr);
		pango_layout_set_text(layout, datestr, -1);

		char fds[64];
		snprintf(fds,sizeof(fds),"IPAexGothic %dpx",14*width/400);
		desc = pango_font_description_from_string(fds);
		pango_layout_set_font_description(layout,desc);
		pango_layout_set_width(layout,pango_units_from_double(0.95*datebox_width*width));
		pango_layout_set_alignment(layout,PANGO_ALIGN_RIGHT);
		pango_font_description_free(desc);

		pango_cairo_update_layout(cr,layout);
		pango_cairo_show_layout(cr,layout);

		g_object_unref(layout);
	}

	/* show status */
	cairo_identity_matrix(cr);
	cairo_translate(cr,0,30*width/400);
	PangoLayout *layout;
	PangoFontDescription *desc;
	layout = pango_cairo_create_layout(cr);
	char text_buf[512];
	snprintf(text_buf,sizeof(text_buf),"%s","月曜日");
	int day = timeptr->tm_wday;
	if(field->Language == Japanese){
		switch(day){
			case 0:
			pango_layout_set_text(layout,"日曜日",-1);
			break;
			case 1:
			pango_layout_set_text(layout,"月曜日",-1);
			break;
			case 2:
			pango_layout_set_text(layout,"火曜日",-1);
			break;
			case 3:
			pango_layout_set_text(layout,"水曜日",-1);
			break;
			case 4:
			pango_layout_set_text(layout,"木曜日",-1);
			break;
			case 5:
			pango_layout_set_text(layout,"金曜日",-1);
			break;
			case 6:
			pango_layout_set_text(layout,"土曜日",-1);
			break;
		}
	}else if(field->Language == English){
		switch(day){
			case 0:
			pango_layout_set_text(layout,"Sunday",-1);
			break;
			case 1:
			pango_layout_set_text(layout,"Monday",-1);
			break;
			case 2:
			pango_layout_set_text(layout,"Thuesday",-1);
			break;
			case 3:
			pango_layout_set_text(layout,"Wednesday",-1);
			break;
			case 4:
			pango_layout_set_text(layout,"Thursday",-1);
			break;
			case 5:
			pango_layout_set_text(layout,"Friday",-1);
			break;
			case 6:
			pango_layout_set_text(layout,"Saturday",-1);
			break;
		}
	}
	char fds[64];
	const char* weekdaystr = pango_layout_get_text(layout);
	int len_wds = (int)strlen(weekdaystr);
	snprintf(fds,sizeof(fds),"IPAexGothic %dpx",(int)((double)len_wds/9*50*width/400));
	desc = pango_font_description_from_string(fds);
	pango_font_description_set_weight(desc,PANGO_WEIGHT_BOLD);
	pango_layout_set_font_description(layout, desc);
	pango_layout_set_width(layout,pango_units_from_double(width));
	pango_layout_set_alignment(layout,PANGO_ALIGN_CENTER);
	pango_font_description_free(desc);
	cairo_set_source_rgb(cr, 0.086, 0.3425, 0.086);
	pango_cairo_update_layout(cr, layout);
	pango_cairo_show_layout(cr, layout);
	

	g_object_unref(layout);

	cairo_identity_matrix(cr);
	cairo_translate(cr,0,0.25*width);
	if(field->NPlugins){
		field->PluginFunctionArray[field->PluginIndex](cr,width,height,LogicalWidth,LogicalHeight);
	}

}

void GameSceneMain_KeyDown(void* this,GameKeys key)
{
	GameScene* ptr = this;
	GameSceneMain_Field* field = ptr->Field;
	if(key == GameKey_A)
	{
		field->AttackFlag = true;
	}
	if(key == GameKey_Up){
		field->KeyUpFlag = true;
	}
	if(key == GameKey_Down){
		field->KeyDownFlag = true;
	}
	if(key == GameKey_Left){
		field->KeyLeftFlag = true;
	}
	if(key == GameKey_Right){
		field->KeyRightFlag = true;
	}
}

void GameSceneMain_KeyUp(void* this,GameKeys key)
{
	GameScene* ptr = this;
	GameSceneMain_Field* field = ptr->Field;
	if(key == GameKey_A)
	{
		field->AttackFlag = false;
	}
	if(key == GameKey_Up)
	{
		field->KeyUpFlag = false;
	}
	if(key == GameKey_Down)
	{
		field->KeyDownFlag = false;
	}
	if(key == GameKey_Left)
	{
		field->KeyLeftFlag = false;
	}
	if(key == GameKey_Right)
	{
		field->KeyRightFlag = false;
	}
}

/*
void GameSceneMain_CleanOdangoArray(void* this)
{
	GameSceneMain_Field* field = ((GameScene*)this)->Field;
	int i;
	for(i = 0; i < MaxOdangos; i++)
	{
		Odango** o = &(field->OdangoArray[i]);
		if(!(*o)) continue;
		if(
		(*o)->Position.X > LogicalWidth ||
		(*o)->Position.Y > LogicalHeight
		){
			Odango_Dispose(*o);
			*o = NULL;
		}
	}
}

*/
void GameSceneMain_Dispose(void* this)
{
	printf("DISPOSED");
	fflush(stdout);
	GameScene* ptr = this;
	//GameSceneMain_Field* field = ptr->Field;
	//free(field->EnemyArray);
	free(ptr->Field);
	free(ptr);
}
